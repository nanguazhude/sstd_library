#pragma once

#include "../sstd_library.hpp"
#include <sstd/boost/fiber/fiber.hpp>

namespace _theSSTDLibraryFunctionFile {

    /*判断一个类是否包含 .quit() 函数*/
    template<typename T, typename = void>
    class HasQuit : public std::false_type {
    };

    template<typename T>
    class HasQuit< T, std::void_t< decltype(std::declval<
        std::remove_cv_t<
        std::remove_reference_t< T > > >().quit()) > > : public std::true_type {
    };

    /*包装一个包含 .quit() 的类，保证其在析构的时候执行quit() */
    template<typename T>
    class QuitWrap {
        sstd_delete_copy_create(QuitWrap);
    public:
        using U = std::remove_cv_t<
            std::remove_reference_t< T > >;
        U thisData;

        inline QuitWrap() : thisData{} {
        }

        template<typename A0, typename ... Args,
            typename = std::enable_if_t< std::is_constructible_v< U, A0&&, Args&&... > >
        >inline QuitWrap(A0&&a0, Args&&...args) : thisData(std::forward<A0>(a0),
            std::forward<Args>(args)...) {
        }

        template<typename A0, typename ... Args,
            typename = void ******,
            typename = std::enable_if_t< !std::is_constructible_v< U, A0&&, Args&&... > >
        >inline QuitWrap(A0&&a0, Args&&...args) : thisData{ std::forward<A0>(a0),
            std::forward<Args>(args)... } {
        }

        inline ~QuitWrap() {
            thisData.quit();
        }

    private:
        sstd_class(QuitWrap);
    };

}/**/

namespace sstd {

    /*T should have ->start()  ; */
    template <typename T>
    class StartFunction {
        T thisFunction;
    public:

        template<typename U,
            typename = std::enable_if_t< std::is_constructible_v< T, U&& > >
        > inline StartFunction(U && arg) :
            thisFunction{ std::forward<U>(arg) } {
        }

        inline void operator()() const {
            this->start();
        }

        inline void start() const {
            (const_cast<StartFunction *>(this)->thisFunction)->start();
        }

        template< typename = std::enable_if_t<
            _theSSTDLibraryFunctionFile::HasQuit<
            decltype(*(std::declval<T>())) >::value > >
            inline void quit() const {
            (const_cast<StartFunction *>(this)->thisFunction)->quit();
        }

    public:
        sstd_default_copy_create(StartFunction);
    private:
        sstd_class(StartFunction);
    };

    template <typename U, typename T, typename E, typename N, typename S>
    class BindDataWithFunction {
        U thisOtherData/*保存userData*/;
        T thisFunction/*当前函数*/;
        E thisExceptionFun/*发生异常*/;
        N thisNormalFun/*无异常*/;
        S thisSkipFun/*跳过异常*/;
    public:
        template<typename A0, typename A1, typename A2, typename A3, typename A4>
        inline BindDataWithFunction(A0&&argOther, A1 && argFun, A2 && argEFun, A3 && argNFun, A4 && argSFun) :
            thisOtherData(std::forward<A0>(argOther)),
            thisFunction(std::forward<A1>(argFun)),
            thisExceptionFun(std::forward<A2>(argEFun)),
            thisNormalFun(std::forward<A3>(argNFun)),
            thisSkipFun(std::forward<A4>(argSFun)) {
        }
        inline void operator()() const {
            sstd_try{
                (const_cast<BindDataWithFunction *>(this)->thisFunction)();
            }sstd_catch(const boost::context::detail::forced_unwind &) {
                thisSkipFun()；
                    throw;
            }sstd_catch(...) {
                (const_cast<BindDataWithFunction *>(this)->thisExceptionFun)();
                return;
            }
            (const_cast<BindDataWithFunction *>(this)->thisNormalFun)();
        }
    public:
        sstd_default_copy_create(BindDataWithFunction);
    private:
        sstd_class(BindDataWithFunction);
    };

    template <typename U, typename ... Args>
    inline StartFunction< std::shared_ptr<U> > makeStartFunction(Args && ... args) {
        if constexpr (!_theSSTDLibraryFunctionFile::HasQuit<U>::value) {
            return StartFunction< std::shared_ptr<U> >{
                sstd_make_shared<U>(std::forward<Args>(args)...)
            };
        } else {
            using QuitWrapType =
                _theSSTDLibraryFunctionFile::QuitWrap<U>;
            auto varAns = sstd_new< QuitWrapType >();
            assert(reinterpret_cast<QuitWrapType*>(&(varAns->thisData)) == varAns);
            return StartFunction< std::shared_ptr<U> >{
                std::shared_ptr<U>{ &(varAns->thisData),
                    [](auto ptr) { delete reinterpret_cast<QuitWrapType*>(ptr); },
                    sstd_allocator<U>{}
                }};
        }
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
        virtual void doException();
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

        enum class InAnotherFunctionStackType {
            Exception,
            NoException,
            SkipException
        };

        template<InAnotherFunctionStackType/*has exception*/>
        class InAnotherFunctionStatck {
            YieldResumeFunction * super;
        public:
            sstd_default_copy_create(InAnotherFunctionStatck);
        public:
            inline InAnotherFunctionStatck(YieldResumeFunction * arg) : super(arg) {
            }
            inline void operator()() const;
        };

    public:
        YieldResumeFunction(std::size_t = 1024uLL * 1024uLL * 64uLL);
        virtual ~YieldResumeFunction();
    public:
        void start();
        void quit();
        template<typename T>
        using BindDataFunction = BindDataWithFunction< std::shared_ptr<const void>,
            std::remove_cv_t< std::remove_reference_t<T> >,
            InAnotherFunctionStatck<InAnotherFunctionStackType::Exception>,
            InAnotherFunctionStatck<InAnotherFunctionStackType::NoException>,
            InAnotherFunctionStatck<InAnotherFunctionStackType::SkipException>>;
    protected:
        template<typename T>
        inline BindDataFunction<T> bindFunctionWithThis(T &&) const;
    public:
        bool hasException() const;
        bool isFinished() const;
        bool isStarted() const;
        bool isOuter() const;
    private:
        void yield();
        void innerYield();
        void outerYield();
        void resume();
        void directRun();
        void resumeWithException();
        void skipException();
        void directYield();
        void directResume();
    private:
        using shared_super::shared_from_this;
        using shared_super::weak_from_this;
        /*如果拷贝到当前栈区会形成循环引用*/
        std::shared_ptr<YieldResumeFunction> copyThisToAnotherStack();
    private:
        sstd_class(YieldResumeFunction);
    };

    template<typename T>
    inline YieldResumeFunction::BindDataFunction<T> YieldResumeFunction::bindFunctionWithThis(T && arg) const {
        return { const_cast<YieldResumeFunction*>(this)->copyThisToAnotherStack() ,
                 std::forward<T>(arg) ,
                 InAnotherFunctionStatck<InAnotherFunctionStackType::Exception>{const_cast<YieldResumeFunction*>(this)},
                 InAnotherFunctionStatck<InAnotherFunctionStackType::NoException>{const_cast<YieldResumeFunction*>(this)},
                 InAnotherFunctionStatck<InAnotherFunctionStackType::SkipException>{const_cast<YieldResumeFunction*>(this)} };
    }

    template<YieldResumeFunction::InAnotherFunctionStackType V>
    inline void YieldResumeFunction::InAnotherFunctionStatck<V>::operator()() const {
        if constexpr (V == InAnotherFunctionStackType::Exception) {
            super->resumeWithException();
        } else if constexpr (V == InAnotherFunctionStackType::NoException) {
            super->resume();
        } else if constexpr (V == InAnotherFunctionStackType::SkipException) {
            super->skipException();
        }
    }

    class _YieldResumeFunctionPrivate final {
    public:
        YieldResumeFunction * super;
        inline void innerYield() const {
            super->innerYield();
        }
        inline void outerYield() const {
            super->outerYield();
        }
        inline bool hasException() const {
            return super->hasException();
        }
    };

}/*namespace sstd*/

#ifndef sstd_function_inner_yield
#define sstd_function_inner_yield(...)                              \
    ::sstd::_YieldResumeFunctionPrivate{this}.innerYield();         \
    if (::sstd::_YieldResumeFunctionPrivate{this}.hasException()) { \
        return;                                                     \
    } assert( __func__ == "doRun"sv );                              \
    static_assert(true)
#endif

#ifndef sstd_function_outer_yield
#define sstd_function_outer_yield(...)                              \
    ::sstd::_YieldResumeFunctionPrivate{this}.outerYield();         \
    if (::sstd::_YieldResumeFunctionPrivate{this}.hasException()) { \
        return;                                                     \
    } assert( __func__ == "doRun"sv );                              \
    static_assert(true)
#endif






