#include "sstd_library_integer_conversion.hpp"

#if __has_include(<charconv>)
#include <charconv>
#define HAS_INCLUDE_SSTD_CHARCONV_ (1u)
#else
#include <sstream>
#define HAS_INCLUDE_SSTD_CHARCONV_ (0u)
#endif

namespace sstd {

    namespace detail {

        using string_type_ = std::basic_string<char, std::char_traits<char>, sstd::allocator<char>>;

#if HAS_INCLUDE_SSTD_CHARCONV_

        template<typename T>
        inline static T \uacf1ToNumber(const std::string_view & arg) {
            T varAns;
            std::from_chars(arg.data(), arg.data() + arg.size(), varAns);
            return varAns;
        }

        template<typename T>
        inline static string_type_ \uacf1ToString(const T & arg) {
            string_type_ varAns{ 64,char(0) };
            auto[p, e] = std::to_chars(varAns.data(), varAns.data() + varAns.size(), arg);
            if (e != std::errc{}) {
                return{};
            }
            varAns.resize(static_cast<std::size_t>(p - varAns.data()));
            return std::move(varAns);
        }

#else
        template<typename T>
        inline static T \uacf1ToNumber(const std::string_view & arg) {
            std::stringstream varConv;
            T varAns;
            varConv << arg;
            varConv >> varAns;
            return varAns;
        }
#endif

        SSTD_SYMBOL_DECL int toInt(std::string_view arg) {
            return \uacf1ToNumber<int>(arg);
        }

        SSTD_SYMBOL_DECL unsigned int toUnsignedInt(std::string_view arg) {
            return \uacf1ToNumber<unsigned int>(arg);
        }

        SSTD_SYMBOL_DECL long toLong(std::string_view arg) {
            return \uacf1ToNumber<long>(arg);
        }

        SSTD_SYMBOL_DECL unsigned long toUnsignedLong(std::string_view arg) {
            return \uacf1ToNumber<unsigned long>(arg);
        }

        SSTD_SYMBOL_DECL short toShort(std::string_view arg) {
            return \uacf1ToNumber<short>(arg);
        }

        SSTD_SYMBOL_DECL unsigned short toUnsignedShort(std::string_view arg) {
            return \uacf1ToNumber<unsigned short>(arg);
        }

        SSTD_SYMBOL_DECL long long toLongLong(std::string_view arg) {
            return \uacf1ToNumber<long long>(arg);
        }

        SSTD_SYMBOL_DECL unsigned long long toUnsignedLongLong(std::string_view arg) {
            return \uacf1ToNumber<unsigned long long>(arg);
        }

        SSTD_SYMBOL_DECL char32_t toChar32_t(std::string_view arg) {
            return \uacf1ToNumber<std::uint32_t>(arg);
        }

        SSTD_SYMBOL_DECL char16_t toChar16_t(std::string_view arg) {
            return \uacf1ToNumber<std::uint16_t>(arg);
        }

        SSTD_SYMBOL_DECL wchar_t toWChar_t(std::string_view arg) {
            if constexpr (sizeof(wchar_t) == 1) {
                return (unsigned char)(toUnsignedChar(arg));
            } else if constexpr (sizeof(wchar_t) == 2) {
                return (wchar_t)(toChar16_t(arg));
            } else {
                return (wchar_t)(toChar32_t(arg));
            }
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringWChar_t(wchar_t arg) {
            if constexpr (sizeof(wchar_t) == 1) {
                return fromStringChar((char)(arg));
            } else if constexpr (sizeof(wchar_t) == 2) {
                return fromStringChar16_t((char16_t)(arg));
            } else {
                return fromStringChar32_t((char32_t)(arg));
            }
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringInt(int arg) {
            return \uacf1ToString(arg);
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedInt(unsigned int arg) {
            return \uacf1ToString(arg);
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringShort(short arg) {
            return \uacf1ToString(arg);
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedShort(unsigned short arg) {
            return \uacf1ToString(arg);
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringLong(long arg) {
            return \uacf1ToString(arg);
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedLong(unsigned long arg) {
            return \uacf1ToString(arg);
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringLongLong(long long arg) {
            return \uacf1ToString(arg);
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringUnsignedLongLong(unsigned long long arg) {
            return \uacf1ToString(arg);
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringChar32_t(char32_t arg) {
            return \uacf1ToString(*reinterpret_cast<std::uint32_t*>(&arg));
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringChar16_t(char16_t arg) {
            return \uacf1ToString(*reinterpret_cast<std::uint16_t*>(&arg));
        }

    }/*namespace detail*/

}/*namespace sstd*/


















