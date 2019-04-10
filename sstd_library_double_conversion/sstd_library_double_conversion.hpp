#pragma once

#include <string>
#include <string_view>
#include "../sstd_library.hpp"

namespace sstd {

    namespace detail {

        SSTD_SYMBOL_DECL double toDouble(std::string_view);
        SSTD_SYMBOL_DECL float toFloat(std::string_view);
        SSTD_SYMBOL_DECL long double toLongDouble(std::string_view);

        SSTD_SYMBOL_DECL std::string_view fromStringFloat(float);
        SSTD_SYMBOL_DECL std::string_view fromStringDouble(double);
        SSTD_SYMBOL_DECL std::string_view fromStringLongDouble(long double);

    }/*namespace detail*/

}/*namespace sstd*/














