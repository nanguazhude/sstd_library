#pragma once

#include <vector>
#include <string>
#include <functional>
#include "../sstd_library.hpp"

namespace sstd {

    /*如果没有注册则加入注册表，否则执行*/
    SSTD_SYMBOL_DECL void callOnceAfterStart(std::function<void(void)>);
    /*如果在析构之前加入注册表，析构时执行，否则忽略*/
    SSTD_SYMBOL_DECL void callOnceBeforeQuit(std::function<void(void)>);

    class SSTD_SYMBOL_DECL Application {
        const bool isRef;
    public:
        /*构造Application*/
        Application(int, char **);
        /*当前Application的引用*/
        Application();
        ~Application();
    public:
        inline operator bool() const noexcept;
    public:
        static bool isConstruct();
        static bool isDestruct();
    public:
        using string = std::basic_string< char, std::char_traits<char>, sstd::allocator<char> >;
        static const std::vector< string, sstd::allocator<string> > * getArgs();
    private:
        sstd_delete_copy_create( Application );
    public:
        sstd_class( Application );
    };

    inline Application::operator bool() const noexcept {
        return isConstruct();
    }

}/*namespace sstd*/
















