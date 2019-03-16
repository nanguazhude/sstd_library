#include "sstd_library_exception.hpp"
#include "../sstd_library_memory/sstd_library_memory.hpp"

#include <atomic>
#include <sstream>
#include <iostream>
#include <string_view>

using namespace std::string_view_literals;

namespace _theSSTDLibraryExceptionFile {

    inline void defaultExceptioinFunctioin(std::exception_ptr arg,
        std::string_view argFunc,
        std::string_view argFile,
        int argLine) noexcept {

        std::basic_stringstream<char, std::char_traits<char>, sstd_allocator<char> > varString;
        varString << u8R"(:func:)"sv << argFunc
            << u8R"(:file:)"sv << argFile
            << u8R"(:line:)"sv << argLine
            << u8R"(:what:)"sv;

        try {
            std::rethrow_exception(arg);
        } catch (const std::exception & stdException) {
            varString << stdException.what() << std::endl;
        } catch (...) {
            varString << "unKnow Exception"sv << std::endl;
        }

        std::cout << varString.rdbuf();

    }

    using DataType = std::atomic< sstd::OnExceptionType >;
    inline DataType & getExceptionFunction() {
        static DataType varAns{ &defaultExceptioinFunctioin };
        return varAns;
    }

}/*namespace _theSSTDLibraryExceptionFile*/

namespace sstd {

    SSTD_SYMBOL_DECL OnExceptionType getExceptionFunction() noexcept {
        return _theSSTDLibraryExceptionFile::getExceptionFunction().load();
    }

    SSTD_SYMBOL_DECL OnExceptionType setExceptionFunction(OnExceptionType arg) noexcept {
        return _theSSTDLibraryExceptionFile::getExceptionFunction().exchange(arg);
    }

    SSTD_SYMBOL_DECL void onException(std::string_view argFun, std::string_view argFile, int argLine) noexcept {
        auto varFunction = getExceptionFunction();
        if (varFunction) {
            varFunction(std::current_exception(), argFun, argFile, argLine);
        } else {
            _theSSTDLibraryExceptionFile::defaultExceptioinFunctioin(std::current_exception(), argFun, argFile, argLine);
        }
    }

}/*namespace sstd*/



