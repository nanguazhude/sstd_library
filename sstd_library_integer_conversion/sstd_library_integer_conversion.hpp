#pragma once

#include <string>
#include <string_view>
#include "../sstd_library.hpp"


namespace sstd{

    namespace detail{

        SSTD_SYMBOL_DECL int toInt(std::string_view);
        SSTD_SYMBOL_DECL unsigned int toUnsignedInt(std::string_view);

        SSTD_SYMBOL_DECL long toLong(std::string_view);
        SSTD_SYMBOL_DECL unsigned long toUnsignedLong(std::string_view);

        SSTD_SYMBOL_DECL short toShort(std::string_view);
        SSTD_SYMBOL_DECL unsigned short toUnsignedShort(std::string_view);

        SSTD_SYMBOL_DECL long long toLongLong(std::string_view);
        SSTD_SYMBOL_DECL unsigned long long toUnsignedLongLong(std::string_view);

        SSTD_SYMBOL_DECL char32_t toChar32_t(std::string_view);
        SSTD_SYMBOL_DECL char16_t toChar16_t(std::string_view);
        SSTD_SYMBOL_DECL wchar_t toWChar_t(std::string_view);

        inline char toChar(std::string_view arg) {
            if (arg.empty()) {
                return char(0);
            }
            return arg[0];
        }

        inline unsigned char toUnsignedChar(std::string_view arg) {
            if (arg.empty()) {
                return unsigned char(0);
            }
            return (unsigned char)(arg[0]);
        }

        inline signed char toSignedChar(std::string_view arg) {
            if (arg.empty()) {
                return signed char(0);
            }
            return (signed char)(arg[0]);
        }

    }/*namespace detail*/

    namespace detail {

        inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringChar(char arg) {
            return{1,arg};
        }

        inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringSignedChar(signed char arg) {
            return{ 1,(char)(arg) };
        }

        inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedChar(unsigned char arg) {
            return{ 1,(char)(arg) };
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringInt(int);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedInt(unsigned int);

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringShort(short);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedShort(unsigned short);

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringLong(long);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedLong(unsigned long );

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringLongLong(long long);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedLongLong(unsigned long long);

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringChar32_t(char32_t);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringChar16_t(char16_t);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringWChar_t(wchar_t);

    }/*namespace detail*/

    inline void toNumber(std::string_view arg,int & ans) {
        ans = detail::toInt(arg);
    }

}/*namespace sstd*/













