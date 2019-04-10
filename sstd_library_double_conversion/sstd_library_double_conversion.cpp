#include "sstd_library_double_conversion.hpp"
#include <limits>

namespace sstd {

    namespace detail {

        SSTD_SYMBOL_DECL double toDouble(std::string_view arg) {
            if (arg.empty()) {
                return std::numeric_limits<double>::quiet_NaN();
            }
            return {};
        }

        SSTD_SYMBOL_DECL float toFloat(std::string_view arg) {
            if (arg.empty()) {
                return std::numeric_limits<float>::quiet_NaN();
            }
            return {};
        }

        SSTD_SYMBOL_DECL long double toLongDouble(std::string_view arg) {
            if (arg.empty()) {
                return std::numeric_limits<long double>::quiet_NaN();
            }
            return {};
        }

        SSTD_SYMBOL_DECL std::string_view fromStringFloat(float) {
            return {};
        }

        SSTD_SYMBOL_DECL std::string_view fromStringDouble(double) {
            return {};
        }

        SSTD_SYMBOL_DECL std::string_view fromStringLongDouble(long double) {
            return {};
        }

    }/*namespace detail*/

}/*namespace sstd*/









