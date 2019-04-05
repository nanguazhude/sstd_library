
#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <sstream>

using namespace std::string_view_literals;

constexpr const static char endl = '\n';
constexpr const static std::size_t theSize = 256uLL;
constexpr const static std::size_t theNewLineSize = 64;

inline std::string getHelper(std::size_t arg) {

    ++arg;
    if (arg < 2) {
        return {};
    }

    std::stringstream var;

    var << u8R"( template< auto A0 )"sv << endl;
    
    for (std::size_t i=1,j=0;i<arg;++j,++i) {

        var << u8R"(,auto A)"sv << i   ;
        if(j<theNewLineSize){
           var  <<' ';
        }else{
            var    << endl;
            j = 0;
        }
    }

    var << u8R"( ,auto ... Args >  class string_constexpr_builder_helper< )"sv 
        << arg<<u8R"(, A0)" <<endl;

    for (std::size_t i = 1,j=0; i < arg; ++j,++i) {
        var << u8R"( , A)"sv<<i ;
        if(j<theNewLineSize){
           var  <<' ';
        }else{
            var    << endl;
            j = 0;
        }
    }

    var << u8R"( ,Args ... > {public:)"sv;
    var << u8R"( using type = constexpr_string_literal< A0  )"sv;

    for (std::size_t i = 1,j=0; i < arg; ++j,++i) {
        var << u8R"( , A)"sv << i  ;
        if(j<theNewLineSize){
           var  <<' ';
        }else{
            var    << endl;
            j = 0;
        }
    }

    var << u8R"(>;
};
)"sv;
    return var.str();

}


int main(int ,char ** ){

    std::ofstream varAns{"ans.txt",std::ios::binary};
    varAns.sync_with_stdio(false);

    varAns << "#pragma once"sv << endl;

    varAns << u8R"( 

#include <string_view>

namespace sstd{ 

template<auto ... Args>
class constexpr_string_literal{
    const constexpr static char thisData[ ]{ Args ... , char(0) };
public:
    inline static constexpr std::string_view toStringView() noexcept {
        return{ thisData , sizeof...(Args) };
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

    varAns<<u8R"();
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
};)"sv <<endl;

    for (std::size_t i = 0; i < theSize; ++i) {
        varAns << getHelper(i);
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

    for (std::size_t i = 0; i < theSize;++i) {

        varAns << u8R"1(,_sstd_key_at( )1"sv;
        varAns << i;
        varAns << u8R"1( ,__VA_ARGS__)  \)1"sv << endl;

    }

    varAns << u8R"(>::type 
#endif)"sv;
    varAns << endl;

}



