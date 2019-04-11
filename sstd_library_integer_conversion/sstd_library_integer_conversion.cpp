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

#if HAS_INCLUDE_SSTD_CHARCONV_
        template<typename T>
        inline static T \uacf1ToNumber(const std::string_view & arg) {
            T varAns;
            std::from_chars(arg.data(), arg.data() + arg.size(), varAns);
            return varAns;
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

    }/*namespace detail*/

}/*namespace sstd*/


















