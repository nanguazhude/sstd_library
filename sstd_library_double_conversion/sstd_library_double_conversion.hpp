#pragma once

#include <string>
#include <string_view>
#include "../sstd_library.hpp"

namespace sstd {

    namespace detail {

        SSTD_SYMBOL_DECL double toDouble(std::string_view);
        SSTD_SYMBOL_DECL float toFloat(std::string_view);
        SSTD_SYMBOL_DECL long double toLongDouble(std::string_view);
        
        SSTD_SYMBOL_DECL std::basic_string<char,std::char_traits<char>,sstd::allocator<char>> fromStringFloat(float);
        SSTD_SYMBOL_DECL std::basic_string<char,std::char_traits<char>,sstd::allocator<char>> fromStringDouble(double);
        SSTD_SYMBOL_DECL std::basic_string<char,std::char_traits<char>,sstd::allocator<char>> fromStringLongDouble(long double);

    }/*namespace detail*/

    inline void toNumber(std::string_view arg,double & ans) {
        ans = detail::toDouble(arg);
    }

    inline void toNumber(std::string arg,float & ans) {
        ans = detail::toFloat(arg);
    }

    inline void toNumber(std::string arg,long double &ans) {
        ans = detail::toLongDouble(arg);
    }

    inline auto toString(double arg) {
        return detail::fromStringDouble(arg);
    }

    inline auto toString(float arg) {
        return detail::fromStringFloat(arg);
    }

    inline auto toString(long double arg) {
        return detail::fromStringLongDouble(arg);
    }

}/*namespace sstd*/














