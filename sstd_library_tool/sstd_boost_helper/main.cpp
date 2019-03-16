
#include <string>
#include <memory>
#include <string_view>
#include <type_traits>

using namespace std::string_literals;
using namespace std::string_view_literals;

#include <utility>
#include <algorithm>

#include <fstream>
#include <iostream>

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include <list>
#include <vector>

#include <regex>

#if __has_include(<execution>)
#include <execution>
#endif

#include <cctype>

#include <map>
#include <functional>

namespace thisMainFile {

    class ifstream : public std::ifstream {
        using super = std::ifstream;
    public:
        inline ifstream(const fs::path & arg);
    };

    class ofstream : public std::ofstream {
        using super = std::ofstream;
    public:
        inline ofstream(const fs::path & arg);
    };

    class CopyItem {
    public:
        fs::path from;
        fs::path to;
        inline CopyItem() = default;
        inline CopyItem(const CopyItem &) = default;
        inline CopyItem(CopyItem &&) = default;
        inline CopyItem &operator=(CopyItem &&) = default;
        inline CopyItem &operator=(const CopyItem &) = default;
        template<typename A, typename B>
        inline CopyItem(A&&, B&&);
    };

    class CopyInfo {
    public:
        std::list< CopyItem > dirs;
        std::list< CopyItem > files;
    };

    inline CopyInfo createCopyInfo(fs::path from, fs::path to);
    inline void createDirs(const CopyInfo &);
    inline void copyFiles(const CopyInfo &);
    inline void rawCopyAFile(const CopyItem &);

}/*namespace thisMainFile*/


int main(int argc, char ** argv) {

    if (argc != 3) {
        return -1;
    }

    fs::path varFrom = argv[1];
    fs::path varTo = argv[2];

    {
        auto varCopyInfo = thisMainFile::createCopyInfo(varFrom, varTo);
        thisMainFile::createDirs(varCopyInfo);
        thisMainFile::copyFiles(varCopyInfo);
    }

    {
        thisMainFile::ofstream varOfs{ varTo / "sstd"sv / "boost"sv / "config"sv / "user.hpp"sv };
        varOfs << "\xEF\xBB\xBF"sv;
        varOfs << u8R"aaa(
#pragma once

#ifndef BOOST_ALL_DYN_LINK
#define BOOST_ALL_DYN_LINK               (1u)
#endif 

#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB                 (1u)
#endif

#if defined(SSTD_BUILD_BOOST_SOURCE)

#if defined(_WIN32)

#ifndef BOOST_USE_WINDOWS_H
#define BOOST_USE_WINDOWS_H              (1u)
#endif  

#endif  

#endif

//BOOST_ATOMIC_SOURCE
//BOOST_CHRONO_SOURCE
//BOOST_DATE_TIME_SOURCE
//BOOST_SYSTEM_SOURCE
//BOOST_THREAD_BUILD_DLL
//BOOST_CONTEXT_SOURCE

)aaa"sv;
    }


    return 0;

}

namespace thisMainFile {

    inline std::string_view getEndl() {
        return "\n"sv;
    }


    template <typename T>
    inline auto getPathName(const fs::path & arg){
        if constexpr( std::is_constructible_v< T, const std::wstring > ){
            return arg.wstring();
        }else{
            return arg.string();
        }
    }

    inline ifstream::ifstream(const fs::path & arg) :
        super(getPathName<super>(arg), std::ios::binary) {
        this->sync_with_stdio(false);
    }

    inline ofstream::ofstream(const fs::path & arg) :
        super(getPathName<super>(arg), std::ios::binary) {
        this->sync_with_stdio(false);
    }

    inline CopyInfo createCopyInfo(fs::path argFrom, fs::path argTo) {

        std::list< CopyItem > varDirs;
        varDirs.emplace_back(std::move(argFrom), argTo / u8R"(sstd)"s);

        CopyInfo varAns;

        while (!varDirs.empty()) {

            auto & varItem = varAns.dirs;
            varItem.splice(varItem.end(),
                varDirs,
                varDirs.begin());

            auto & var = varItem.back();

            fs::directory_iterator varPos{ var.from };
            fs::directory_iterator varEnd;

            for (; varPos != varEnd; ++varPos) {

                const auto & varPath = varPos->path();
                const auto varFileName = varPath.filename();

                if (fs::is_directory(varPos->status())) {
                    varDirs.emplace_front(varPath,
                        var.to / varFileName);
                    continue;
                } else {
                    varAns.files.emplace_back(varPath,
                        var.to / varFileName);
                    continue;
                }

            }

        }

        return std::move(varAns);

    }

    inline void createDirs(const CopyInfo & arg) {
        for (const auto & varI : arg.dirs) {
            try {
                fs::create_directories(varI.to);
            } catch (...) {
                continue;
            }
        }
    }

    inline void copyAFile(const CopyItem & varI) {

        if (!varI.from.has_extension()) {
            rawCopyAFile(varI);
            return;
        }

        {
            const auto varExtension
                = varI.from.extension().wstring();
            const static
                std::wregex varCheckIsNotBinary{
                    LR"121([.](?:(?:hpp)|(?:h)|(?:cxx)|(?:cpp)|(?:c)|(?:hxx)|(?:txt)))121"s ,
                    std::regex::ECMAScript | std::regex::icase
            };
            if (!std::regex_match(varExtension, varCheckIsNotBinary)) {
                rawCopyAFile(varI);
                return;
            }
        }

        ofstream varOut{ varI.to };
        ifstream varIn{ varI.from };

        /*增加UTF8-bom*/
        varOut << "\xEF\xBB\xBF"sv;

        /*用于保存过去已经读取的line*/
        std::list< std::string > varFileLines;

        while (varIn.good()) {

            std::string varLine;
            std::string varNewLine;
            std::getline(varIn, varLine);

            while (!varLine.empty()) {/*删除行尾空行*/
                auto varChar = varLine.back();
                if ((varChar > 0) && (varChar < char(127)) && std::isspace(varChar)) {
                    varLine.pop_back();
                } else {
                    break;
                }
            }

            /*结束时保存当前行*/
            class LineLock {
                std::string line;
                std::list< std::string > * const lines;
            public:
                inline LineLock(std::string & arg, std::list<std::string> * v) :
                    line(arg), lines(v) {
                }
                inline ~LineLock() {
                    lines->push_back(std::move(line));
                }
            }varLineLock{ varLine , &varFileLines };

            if (varLine.empty()) {
                varOut << getEndl();
                continue;
            }

            if ((!varFileLines.empty()) && varFileLines.back().empty()) {/*尝试替换孤行#define*/
                using convert_string_map_t =
                    std::map< std::string, std::function<std::string(std::string_view)> >;

                const static convert_string_map_t varConvertStringMap = []()->convert_string_map_t {
                    convert_string_map_t varAns;

                    varAns.emplace("#define BOOST_ATOMIC_SOURCE"s, [](std::string_view)->std::string {
                        return u8R"(#ifndef BOOST_ATOMIC_SOURCE/*added ...*/
#define BOOST_ATOMIC_SOURCE/*added ...*/
#endif  /*added ...*/)"s;  });

                    varAns.emplace("#define BOOST_CHRONO_SOURCE"s, [](std::string_view)->std::string {
                        return u8R"(#ifndef BOOST_CHRONO_SOURCE/*added ...*/
#define BOOST_CHRONO_SOURCE/*added ...*/
#endif  /*added ...*/)"s;  });

                    varAns.emplace("#define BOOST_DATE_TIME_SOURCE"s, [](std::string_view)->std::string {
                        return u8R"(#ifndef BOOST_DATE_TIME_SOURCE/*added ...*/
#define BOOST_DATE_TIME_SOURCE/*added ...*/
#endif  /*added ...*/)"s;  });

                    varAns.emplace("#define BOOST_SYSTEM_SOURCE"s, [](std::string_view)->std::string {
                        return u8R"(#ifndef BOOST_SYSTEM_SOURCE/*added ...*/
#define BOOST_SYSTEM_SOURCE/*added ...*/
#endif  /*added ...*/)"s;  });

                    varAns.emplace("#define BOOST_THREAD_BUILD_DLL"s, [](std::string_view)->std::string {
                        return u8R"(#ifndef BOOST_THREAD_BUILD_DLL/*added ...*/
#define BOOST_THREAD_BUILD_DLL/*added ...*/
#endif  /*added ...*/)"s;  });

                    varAns.emplace("#define BOOST_CONTEXT_SOURCE"s, [](std::string_view)->std::string {
                        return u8R"(#ifndef BOOST_CONTEXT_SOURCE/*added ...*/
#define BOOST_CONTEXT_SOURCE/*added ...*/
#endif  /*added ...*/)"s;  });

                    return std::move(varAns);
                }();

                auto varPos = varConvertStringMap.find(varLine);
                if (varPos != varConvertStringMap.end()) {
                    varOut << varPos->second(varLine) << getEndl();
                    continue;
                }
            }

            /*包含 boost 但是不包含 boost\\ */
            if ((varLine.find("boost"sv) != std::string::npos) &&
                (varLine.find(u8R"(boost\\)"sv) == std::string::npos)) {

                const static std::regex  varReplaceRegex{
                    u8R"rrr((["<(])boost([/\\]))rrr"s ,
                    std::regex::ECMAScript };
                const static auto varTarget = u8R"vvv($1sstd$2boost$2)vvv"s;

                varNewLine = std::regex_replace(varLine,
                    varReplaceRegex, varTarget,
                    std::regex_constants::format_first_only);

#ifdef _DEBUG
                if ((std::string::npos != varNewLine.find(u8R"(boost\)"sv)) && (varLine != varNewLine)) {
                    std::cout << varNewLine << std::endl;
                }
#endif

            } else {
                varNewLine = std::move(varLine);
            }

            varOut
                << varNewLine
                << getEndl();

        }

    }

    inline void copyFiles(const CopyInfo & arg) {

#if __has_include(<execution>)
        std::for_each(std::execution::par,
            arg.files.begin(),
            arg.files.end(),
            &copyAFile);
#else
        std::for_each(arg.files.begin(), arg.files.end(), &copyAFile);
#endif
    }

    inline void rawCopyAFile(const CopyItem & arg) {
        ofstream varOut{ arg.to };
        ifstream varIn{ arg.from };
        varOut << varIn.rdbuf();
    }

    template<typename A, typename B>
    inline CopyItem::CopyItem(A&& a, B&& b) :
        from(std::forward<A>(a)),
        to(std::forward<B>(b)) {
    }

}/*namespace thisMainFile*/




