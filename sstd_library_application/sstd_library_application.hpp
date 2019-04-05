#pragma once

#include <vector>
#include <string>
#include <functional>
#include "../sstd_library.hpp"

namespace sstd {

    namespace detail {
        /*如果没有注册则加入注册表，否则直接执行*/
        SSTD_SYMBOL_DECL void callOnceAfterStart(std::function<void(void)>);
        /*如果在析构之前加入注册表，析构时执行，否则忽略*/
        SSTD_SYMBOL_DECL void callOnceBeforeQuit(std::function<void(void)>);
    }/* namespace detail */

    class SSTD_SYMBOL_DECL Application {
        const bool isRef;
    public:
        /*构造Application*/
        Application(int, char **);
        /*当前Application的引用*/
        Application();
        virtual ~Application();
    public:
        inline operator bool() const noexcept;
    public:
        static bool isConstruct();
        static bool isDestruct();
    public:
        inline static void callOnDestruct(std::once_flag&, std::function<void(void)>);
        inline static void callOnConstruct(std::once_flag&, std::function<void(void)>);
    public:
        using string = std::basic_string< char, std::char_traits<char>, sstd::allocator<char> >;
        static const std::vector< string, sstd::allocator<string> > * getArgs();
    private:
        sstd_delete_copy_create(Application);
    public:
        sstd_class(Application);
    };

    inline void Application::callOnDestruct(std::once_flag& argF, std::function<void(void)> arg) {
        std::call_once(argF, &detail::callOnceBeforeQuit, std::move(arg));
    }

    inline void Application::callOnConstruct(std::once_flag& argF, std::function<void(void)> arg) {
        std::call_once(argF, &detail::callOnceAfterStart, std::move(arg));
    }

    inline Application::operator bool() const noexcept {
        return isConstruct();
    }

}/*namespace sstd*/

#ifndef sstd_call_once_after_start
#define sstd_call_once_after_start( _NAME_SSTD_ , ... ) static class u1##_NAME_SSTD_##class_sstd {   \
public : \
       inline u1##_NAME_SSTD_##class_sstd(){ ::sstd::detail::callOnceAfterStart( __VA_ARGS__ );   } \
} d1##_NAME_SSTD_##class_sstd/**/;
#endif

#ifndef sstd_call_once_before_quit
#define sstd_call_once_before_quit( _NAME_SSTD_ , ... ) static class u2##_NAME_SSTD_##class_sstd {   \
public : \
       inline u2##_NAME_SSTD_##class_sstd(){ ::sstd::detail::callOnceBeforeQuit( __VA_ARGS__ );   } \
} d2##_NAME_SSTD_##class_sstd/**/;
#endif
