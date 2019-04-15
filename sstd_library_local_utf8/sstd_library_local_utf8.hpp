#pragma once

#include "../sstd_library.hpp"

namespace sstd{

    namespace detail {
        using utf8String=
            std::basic_string< char ,std::char_traits<char>,sstd::allocator<char> >;
        using localWstring=
            std::basic_string< wchar_t ,std::char_traits<wchar_t>,sstd::allocator<wchar_t> >;
    }

    SSTD_SYMBOL_DECL detail::utf8String localToUtf8(std::wstring_view );
    SSTD_SYMBOL_DECL detail::localWstring utf8ToLocal(std::string_view );

}/*namespace sstd*/
