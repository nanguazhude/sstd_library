
#if __has_include(<filesystem>)
#include <filesystem>
namespace filesystem = std::filesystem;
#else
#include <experimental/filesystem>
namespace filesystem = std::experimental::filesystem;
#endif

#include <string>
#include <string_view>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <cassert>
#include <iomanip>

using namespace std::string_literals;
using namespace std::string_view_literals;

template<typename T>
inline std::string toFileName(T && arg) {
    std::stringstream varAns;
    varAns << "botan_all."sv;
    varAns << std::setw(8) << std::setfill('0') << arg;
    varAns << ".cpp"sv;
    std::string varAnsStr;
    varAns >> varAnsStr;
    return std::move(varAnsStr);
}

int main(int argc, char ** argv) {

    if (argc < 2) {
        return -1;
    }


    std::vector< std::vector<std::string> > varFiles;
    auto varFilePath = filesystem::path{ argv[1] }.remove_filename();

    {

        std::ifstream varRead{ argv[1] ,std::ios::binary };
        if (false == varRead.is_open()) {
            return -2;
        }

        std::string varLine;

        constexpr auto varLicense = "Botan is released under the Simplified BSD License"sv;

        bool varFindLicense{ false };
        const static std::regex varRegex{
            u8R"(\s*\*/\s*)" };

        assert(std::regex_match("*/\r", varRegex));

        std::vector<std::string> varCurrentFile;

        while (std::getline(varRead, varLine)) {

            while (!varLine.empty()) {
                if (varLine.back() != '\r') {
                    break;
                }
                varLine.pop_back();
            }

            if (varLine.find(varLicense) != std::string::npos) {
                varFindLicense = true;
            }

            const auto isLicenseEndl =
                varFindLicense && std::regex_match(varLine, varRegex);
            varCurrentFile.push_back(std::move(varLine));

            if (isLicenseEndl) {
                varFiles.push_back(std::move(varCurrentFile));
                varFindLicense = false;
            }

        }

        if (!varCurrentFile.empty()) {
            varFiles.push_back(std::move(varCurrentFile));
        }

    }

    if (varFiles.size() < 1) {
        return -1;
    }


    auto varHeader = 1 + varFiles.cbegin();

    std::vector< std::string > varFileNames;

    int varCurrentIndex = 1;
    for (auto varPos = varHeader + 1;
        varPos != varFiles.end();
        ++varPos, ++varCurrentIndex) {

        const auto & varFileName =
            varFileNames.emplace_back(toFileName(varCurrentIndex));

        std::ofstream varStream{
            varFilePath / varFileName,
            std::ios::binary };

        for (const auto & varLine : *varHeader) {
            varStream << varLine << '\n';
        }

        varStream << u8R"(
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>
#include <utility>
)"sv;

        for (const auto & varLine : *varPos) {
            varStream << varLine << '\n';
        }

    }

    std::ofstream varOut{
        varFilePath/ "botan_all.pri"s,
        std::ios::binary
    };

    varOut << "SOURCES += "sv;
    for ( const auto & varI:varFileNames ) {
        varOut << u8R"( \
    $$PWD/)"sv<< varI ;
    }
    varOut << '\n';


    return 0;

}


