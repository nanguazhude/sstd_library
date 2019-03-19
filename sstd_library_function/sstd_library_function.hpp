#pragma once

#include "../sstd_library.hpp"

namespace sstd {

    /*T should have ->start() noexcept ; */
    template <typename T>
    class StartFunction {
        T thisFunction;
    public:

        template<typename U,
            typename = std::enable_if_t< std::is_constructible_v< T, U&& > > >
            inline StartFunction(U && arg) :
            thisFunction{ std::forward<U>(arg) } {
        }

        inline void operator()() const noexcept {
            this->start();
        }

        inline void start() const noexcept {
            (const_cast<StartFunction *>(this)->thisFunction)->start();
        }

    public:
        sstd_default_copy_create(StartFunction);
    private:
        sstd_class(StartFunction);
    };

    template <typename U, typename T, typename E, typename N>
    class BindDataWithFunction {
        U other;
        T fun;
        E exceptionFun;
        N normalFun;
    public:
        template<typename A0, typename A1, typename A2, typename A3>
        inline BindDataWithFunction(A0&&argOther, A1 && argFun, A2 && argEFun, A3 && argNFun) :
            other(std::forward<A0>(argOther)),
            fun(std::forward<A1>(argFun)),
            exceptionFun(std::forward<A2>(argEFun)),
            normalFun(std::forward<A3>(argNFun)) {
        }
        inline void operator()() const noexcept {
            sstd_try{
                (const_cast<BindDataWithFunction *>(this)->fun)();
            }sstd_catch(...) {
                exceptionFun();
                return;
            }
            normalFun();
        }
    public:
        sstd_default_copy_create(BindDataWithFunction);
    private:
        sstd_class(BindDataWithFunction);
    };

    template <typename U, typename ... Args>
    inline StartFunction< std::shared_ptr<U> > makeStartFunction(Args && ... args) {
        return StartFunction< std::shared_ptr<U> >{
            sstd_make_shared<U>(std::forward<Args>(args)...)
        };
    }

}/*namespace sstd*/

template <typename U, typename ... Args>
inline sstd::StartFunction< std::shared_ptr<U> > sstd_make_start_function(Args && ... args) {
    return sstd::makeStartFunction<U>(std::forward<Args>(args)...);
}

namespace sstd {
    class SSTD_SYMBOL_DECL YieldFunctionBasic {
        sstd_delete_copy_create(YieldFunctionBasic);
    public:
        YieldFunctionBasic();
        virtual ~YieldFunctionBasic();
    protected:
        virtual void doRun() = 0;
        virtual void doException() noexcept;
    private:
        sstd_class(YieldFunctionBasic);
    };
}/*namespace sstd*/

namespace sstd {

    class YieldResumeFunctionPrivate;
    class _YieldResumeFunctionPrivate;
    class SSTD_SYMBOL_DECL YieldResumeFunction :
        public YieldFunctionBasic,
        public std::enable_shared_from_this<YieldResumeFunction> {
        friend class _YieldResumeFunctionPrivate;
        YieldResumeFunctionPrivate * const thisPrivate;
        sstd_delete_copy_create(YieldResumeFunction);
        using shared_super = std::enable_shared_from_this<YieldResumeFunction>;

        template<bool>
        class InAnotherFunctionStatck {
            YieldResumeFunction * super;
        public:
            sstd_default_copy_create(InAnotherFunctionStatck);
        public:
            inline InAnotherFunctionStatck(YieldResumeFunction * arg) : super(arg) {
            }
            inline void operator()() const noexcept;
        };

    public:
        YieldResumeFunction(std::size_t = 1024uLL * 1024uLL * 64uLL);
        virtual ~YieldResumeFunction();
    public:
        void start() noexcept;
        template<typename T>
        using BindDataFunction = BindDataWithFunction< std::shared_ptr<const void>,
            std::remove_cv_t< std::remove_reference_t<T> >,
            InAnotherFunctionStatck<true>,
            InAnotherFunctionStatck<false>>;
    protected:
        template<typename T>
        inline BindDataFunction<T> bindFunctionWithThis(T &&) const noexcept;
    public:
        bool hasException() const noexcept;
        bool isFinished() const noexcept;
    private:
        void yield() noexcept;
        void resume() noexcept;
        void directRun() noexcept;
        void resumeWithException() noexcept;
        void directYield() noexcept;
        void directResume() noexcept;
    private:
        using shared_super::shared_from_this;
        using shared_super::weak_from_this;
        /*如果拷贝到当前栈区会形成循环引用*/
        std::shared_ptr<YieldResumeFunction> copyThisToAnotherStack() noexcept;
    private:
        sstd_class(YieldResumeFunction);
    };

    template<typename T>
    inline YieldResumeFunction::BindDataFunction<T> YieldResumeFunction::bindFunctionWithThis(T && arg) const noexcept {
        return { const_cast<YieldResumeFunction*>(this)->copyThisToAnotherStack() ,
                 std::forward<T>(arg) ,
                 InAnotherFunctionStatck<true>{const_cast<YieldResumeFunction*>(this)},
                 InAnotherFunctionStatck<false>{const_cast<YieldResumeFunction*>(this)} };
    }

    template<bool V>
    inline void YieldResumeFunction::InAnotherFunctionStatck<V>::operator()() const noexcept {
        if constexpr (V) {
            super->resumeWithException();
        } else {
            super->resume();
        }
    }

    class _YieldResumeFunctionPrivate final {
    public:
        YieldResumeFunction * super;
        inline void yield() const {
            super->yield();
        }
        inline bool hasException() const {
            return super->hasException();
        }
    };

}/*namespace sstd*/

#ifndef sstd_function_yield
#define sstd_function_yield(...) \
    ::sstd::_YieldResumeFunctionPrivate{this}.yield(); \
    if (::sstd::_YieldResumeFunctionPrivate{this}.hasException()) { \
        return; \
    } static_assert(true)
#endif








