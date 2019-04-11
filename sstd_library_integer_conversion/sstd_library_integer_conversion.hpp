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

    }/*namespace detail*/

}/*namespace sstd*/













