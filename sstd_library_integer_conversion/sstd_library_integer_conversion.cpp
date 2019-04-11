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
        inline static T toNumber(const std::string_view & arg) {
            T varAns;
            std::from_chars(arg.data(), arg.data() + arg.size(), varAns);
            return varAns;
        }
#else
        template<typename T>
        inline static T toNumber(const std::string_view & arg) {
            std::stringstream varConv;
            T varAns;
            varConv << arg;
            varConv >> varAns;
            return varAns;
        }
#endif

        SSTD_SYMBOL_DECL int toInt(std::string_view arg) {
            return toNumber<int>(arg);
        }

        SSTD_SYMBOL_DECL unsigned int toUnsignedInt(std::string_view arg) {
            return toNumber<unsigned int>(arg);
        }

        SSTD_SYMBOL_DECL long toLong(std::string_view arg) {
            return toNumber<long>(arg);
        }

        SSTD_SYMBOL_DECL unsigned long toUnsignedLong(std::string_view arg) {
            return toNumber<unsigned long>(arg);
        }

        SSTD_SYMBOL_DECL short toShort(std::string_view arg) {
            return toNumber<short>(arg);
        }

        SSTD_SYMBOL_DECL unsigned short toUnsignedShort(std::string_view arg) {
            return toNumber<unsigned short>(arg);
        }

        SSTD_SYMBOL_DECL long long toLongLong(std::string_view arg) {
            return toNumber<long long>(arg);
        }

        SSTD_SYMBOL_DECL unsigned long long toUnsignedLongLong(std::string_view arg) {
            return toNumber<unsigned long long>(arg);
        }

    }/*namespace detail*/

}/*namespace sstd*/


















