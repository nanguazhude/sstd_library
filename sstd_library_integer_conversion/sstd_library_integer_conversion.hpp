#pragma once

#include <string>
#include <string_view>
#include "../sstd_library.hpp"


namespace sstd {

    namespace detail {

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

        SSTD_SYMBOL_DECL bool toBool(std::string_view);

        SSTD_SYMBOL_DECL char toChar(std::string_view arg);
        SSTD_SYMBOL_DECL unsigned char toUnsignedChar(std::string_view arg);
        SSTD_SYMBOL_DECL signed char toSignedChar(std::string_view arg);

    }/*namespace detail*/

    namespace detail {

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringChar(char arg);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringSignedChar(signed char arg);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedChar(unsigned char arg);

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringInt(int);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedInt(unsigned int);

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringShort(short);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedShort(unsigned short);

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringLong(long);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedLong(unsigned long);

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringLongLong(long long);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedLongLong(unsigned long long);

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringChar32_t(char32_t);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringChar16_t(char16_t);
        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringWChar_t(wchar_t);

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringBool(bool);

    }/*namespace detail*/

    inline void toNumber(std::string_view arg, bool & ans) {
        ans = detail::toBool(arg);
    }

    inline void toNumber(std::string_view arg, int & ans) {
        ans = detail::toInt(arg);
    }

    inline void toNumber(std::string_view arg, unsigned int & ans) {
        ans = detail::toUnsignedInt(arg);
    }

    inline void toNumber(std::string_view arg, short & ans) {
        ans = detail::toShort(arg);
    }

    inline void toNumber(std::string_view arg, unsigned short & ans) {
        ans = detail::toUnsignedShort(arg);
    }

    inline void toNumber(std::string_view arg, long & ans) {
        ans = detail::toLong(arg);
    }

    inline void toNumber(std::string_view arg, unsigned long & ans) {
        ans = detail::toUnsignedLong(arg);
    }

    inline void toNumber(std::string_view arg, long long & ans) {
        ans = detail::toLongLong(arg);
    }

    inline void toNumber(std::string_view arg, unsigned long long & ans) {
        ans = detail::toUnsignedLongLong(arg);
    }

    inline void toNumber(std::string_view arg, unsigned char & ans) {
        ans = detail::toUnsignedChar(arg);
    }

    inline void toNumber(std::string_view arg, char & ans) {
        ans = detail::toChar(arg);
    }

    inline void toNumber(std::string_view arg, signed char & ans) {
        ans = detail::toSignedChar(arg);
    }

    inline void toNumber(std::string_view arg, wchar_t & ans) {
        ans = detail::toWChar_t(arg);
    }

    inline void toNumber(std::string_view arg, char32_t & ans) {
        ans = detail::toChar32_t(arg);
    }

    inline void toNumber(std::string_view arg, char16_t & ans) {
        ans = detail::toChar16_t(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(char arg) {
        return detail::fromStringChar(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(unsigned char arg) {
        return detail::fromStringUnsignedChar(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(signed char arg) {
        return detail::fromStringSignedChar(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(wchar_t arg) {
        return detail::fromStringWChar_t(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(char32_t arg) {
        return detail::fromStringChar32_t(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(char16_t arg) {
        return detail::fromStringChar16_t(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(int arg) {
        return detail::fromStringInt(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(unsigned int arg) {
        return detail::fromStringUnsignedInt(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(short arg) {
        return detail::fromStringShort(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(unsigned short arg) {
        return detail::fromStringUnsignedShort(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(long arg) {
        return detail::fromStringLong(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(long long arg) {
        return detail::fromStringLongLong(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(unsigned long arg) {
        return detail::fromStringUnsignedLong(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(unsigned long long arg) {
        return detail::fromStringUnsignedLongLong(arg);
    }

    inline std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> toString(bool arg) {
        return detail::fromStringBool(arg);
    }

}/*namespace sstd*/
