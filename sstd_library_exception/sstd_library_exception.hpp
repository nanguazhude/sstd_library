#pragma once

#include "../global_sstd_library.hpp"
#include <exception>
#include <string_view>

namespace _theSSTDLibraryExceptionFile {
}/*namespace _theSSTDLibraryExceptionFile*/

namespace sstd {

    typedef void(*OnExceptionType)(std::exception_ptr, std::string_view/*func*/, std::string_view/*file*/, int/*line*/) noexcept;
    SSTD_SYMBOL_DECL OnExceptionType getExceptionFunction() noexcept;
    SSTD_SYMBOL_DECL OnExceptionType setExceptionFunction(OnExceptionType) noexcept;
    SSTD_SYMBOL_DECL void onException(std::string_view/*func*/, std::string_view/*file*/, int/*line*/) noexcept;

}/*namespace sstd*/

#ifndef sstd_on_exception
#define sstd_on_exception(...) ::sstd::onException( __func__,__FILE__,__LINE__ ); static_assert(true)
#endif

#ifndef sstd_try
#define sstd_try try
#endif

#ifndef sstd_catch
#define sstd_catch catch
#endif

#ifndef sstd_throw
#define sstd_throw(...) throw __VA_ARGS__;
#endif

