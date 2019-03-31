
#include "sstd_library_local_utf8.hpp"

#if __has_include(<codecvt>)

#include <locale>
#include <codecvt>

namespace sstd {

    SSTD_SYMBOL_DECL detail::utf8String localToUtf8(std::wstring_view arg){
        if (arg.empty()) {
            return{};
        }
        std::wstring_convert<std::codecvt_utf8<wchar_t>,
            wchar_t,
            sstd::allocator<wchar_t>,
            sstd::allocator<char>> varConvert;
        return varConvert.to_bytes(arg.data(),arg.data()+arg.size());
    }

    SSTD_SYMBOL_DECL detail::localWstring utf8ToLocal(std::string_view arg){
        if (arg.empty()) {
            return {};
        }
        std::wstring_convert<std::codecvt_utf8<wchar_t>,
            wchar_t,
            sstd::allocator<wchar_t>,
            sstd::allocator<char>> varConvert;
        return varConvert.from_bytes(arg.data(), arg.data() + arg.size());
    }

}/*namespace sstd*/

#else

#error "must have codecvt!!!"

#endif

