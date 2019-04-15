
#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std::string_view_literals;

constexpr const static char endl = '\n';
constexpr const static std::size_t theSize = 512uLL;
constexpr const static std::size_t theNewLineSize = 64;

inline std::string getHelper(std::size_t arg) {

    ++arg;
    if (arg < 2) {
        return {};
    }

    std::stringstream var;

    var << u8R"( template< auto A0 )"sv << endl;

    for (std::size_t i = 1, j = 0; i < arg; ++j, ++i) {

        var << u8R"(,auto A)"sv << i;
        if (j < theNewLineSize) {
            var << ' ';
        } else {
            var << endl;
            j = 0;
        }
    }

    var << u8R"( ,auto ... Args >
class string_constexpr_builder_helper< )"sv
        << arg << u8R"(, A0)" << endl;

    for (std::size_t i = 1, j = 0; i < arg; ++j, ++i) {
        var << u8R"( , A)"sv << i;
        if (j < theNewLineSize) {
            var << ' ';
        } else {
            var << endl;
            j = 0;
        }
    }

    var << u8R"( ,Args ... > {
public:)"sv;
    var << u8R"(
using type = constexpr_string_literal< A0  )"sv;

    for (std::size_t i = 1, j = 0; i < arg; ++j, ++i) {
        var << u8R"( , A)"sv << i;
        if (j < theNewLineSize) {
            var << ' ';
        } else {
            var << endl;
            j = 0;
        }
    }

    var << u8R"(>;
};
)"sv;
    return var.str();

}

class ofstream : public std::ofstream {
    using super = std::ofstream;
public:
    template<typename T>
    inline ofstream( T && fn ) : super( std::forward<T>(fn) ,std::ios::binary ) {
        this->sync_with_stdio(false);
        this->write("\xef\xbb\xbf",3);
    }
};

int main(int, char **) {

    ofstream varAns{ "string_constexpr.hpp"  };

    varAns << "#pragma once"sv << endl;

    varAns << u8R"(

#include <string_view>
#include "constexpr_string.hpp"

namespace sstd{

template<auto ... Args>
class constexpr_string_literal {
    const constexpr static char thisData[]{ Args ... , char(0) };
public:
    inline static constexpr std::string_view toStringView() noexcept {
        return{ thisData , sizeof...(Args) };
    }
    inline static constexpr constexpr_string toConstexprStringView() noexcept{
        return {thisData};
    }
    inline constexpr static const char * data() noexcept {
        return thisData;
    }
    inline constexpr static std::size_t size() noexcept {
        return sizeof...(Args);
    }
};

)"sv << endl;


    varAns << u8R"(
namespace _detail_sstd_string {

template<std::size_t N,auto ...>
class string_constexpr_builder_helper {
public:
    static_assert(N>0);
    static_assert(N<=)"sv;

    varAns << theSize;

    varAns << u8R"();
};

template< auto ... Args>
class string_constexpr_builder_helper<0,  Args... > {
public:
    using type = constexpr_string_literal< >;
};

template< auto A0 , auto ... Args>
class string_constexpr_builder_helper<1 ,A0,Args ... > {
public:
    using type = constexpr_string_literal< A0 >;
};)"sv << endl;

    {
        std::string varFileName;
        for (std::size_t i = 1; i < theSize; ++i) {
            {
                {
                    std::stringstream varStream;
                    varStream << "string_constexpr."sv
                        << std::setw(8)
                        << std::setfill('0')
                        << i << ".hxx"sv;
                    varStream >> varFileName;
                }
                ofstream varAnsPart{ varFileName };
                varAnsPart << getHelper(i);
            }
            varAns << u8R"(#include ")"sv
                << varFileName
                << u8R"(")"sv<<endl;
        }
    }

    varAns << u8R"(
}/*namespace _detail_sstd_string*/
)"sv << endl;

    varAns << u8R"(
}/*namespace sstd*/

 )"sv << endl;

    varAns << u8R"(

#ifndef _sstd_key_at
#define _sstd_key_at(_POS_SSTD_,...) ((_POS_SSTD_)<(sizeof(__VA_ARGS__))?(__VA_ARGS__[_POS_SSTD_]):char(0))
#endif

#ifndef sstd_cstr
#define sstd_cstr(...) ::sstd::_detail_sstd_string::string_constexpr_builder_helper< (sizeof(__VA_ARGS__)-1)  \
)"sv;

    for (std::size_t i = 0, j = 0; i < theSize; ++j, ++i) {

        varAns << u8R"1(,_sstd_key_at( )1"sv;
        varAns << i;
        varAns << u8R"1( ,__VA_ARGS__)  )1"sv;

        if (j < theNewLineSize) {
            continue;
        } else {
            varAns << u8R"( \)"sv << endl;
            j = 0;
        }

    }

    varAns << u8R"(>::type
#endif)"sv;
    varAns << endl;

}
