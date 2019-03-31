#include "sstd_library_local_utf8.hpp"

#if defined( _WIN32 ) 

#include <Windows.h>

namespace sstd {

    SSTD_SYMBOL_DECL detail::utf8String localToUtf8(std::wstring_view arg) {
        if (arg.empty()) {
            return{};
        }

        auto varCharSize =
            ::WideCharToMultiByte(CP_UTF8, 0,
                arg.data(), static_cast<int>(arg.size()),
                nullptr, 0, 
                nullptr, nullptr);

        detail::utf8String varAns;

        varAns.resize(varCharSize);
        ::WideCharToMultiByte(CP_UTF8, 0,
            arg.data(), static_cast<int>(arg.size()),
            varAns.data(), varCharSize,
            nullptr, nullptr);

        return std::move(varAns);
    }

    SSTD_SYMBOL_DECL detail::localWstring utf8ToLocal(std::string_view arg) {
        if (arg.empty()) {
            return {};
        }

        int varCharSize = ::MultiByteToWideChar(CP_UTF8, 0, 
            arg.data(), static_cast<int>( arg.size() ), 
            nullptr, 0);

        detail::localWstring varAns;
        varAns.resize(varCharSize);

        ::MultiByteToWideChar(CP_UTF8, 0, 
            arg.data(), static_cast<int>(arg.size()), 
            varAns.data(), varCharSize);

        return std::move(varAns);

    }

}/*namespace sstd*/


#else/*not windows*/

#if __has_include(<codecvt>)

#include <locale>
#include <codecvt>

namespace sstd {

    SSTD_SYMBOL_DECL detail::utf8String localToUtf8(std::wstring_view arg) {
        if (arg.empty()) {
            return{};
        }
        std::wstring_convert<std::codecvt_utf8<wchar_t>,
            wchar_t,
            sstd::allocator<wchar_t>,
            sstd::allocator<char>> varConvert;
        return varConvert.to_bytes(arg.data(), arg.data() + arg.size());
    }

    SSTD_SYMBOL_DECL detail::localWstring utf8ToLocal(std::string_view arg) {
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

#error "must have codecvt"

#endif

#endif
