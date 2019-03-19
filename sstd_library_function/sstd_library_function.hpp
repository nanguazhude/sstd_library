#pragma once

#include "../sstd_library.hpp"

namespace sstd{

    /*T should have ->start() noexcept ; */
    template <typename T>
    class StartFunction{
        T thisFunction;
    public:

        template<typename U>
        inline StartFunction(U && arg) :
            thisFunction{ std::forward<U>(arg) } {
        }

        inline void operator()() noexcept {
            this->start();
        }

        inline void start() noexcept {
            thisFunction->start();
        }

    public:
        sstd_delete_copy_create(StartFunction);
    private:
        sstd_class(StartFunction);
    };

    template <typename U,typename ... Args>
    inline StartFunction< std::shared_ptr<U> > makeStartFunction( Args && ... args ){
        return StartFunction< std::shared_ptr<U> >{
            sstd_make_shared<U>(std::forward<Args>(args)...)
        };
    }

}/*namespace sstd*/

template <typename U,typename ... Args>
inline sstd::StartFunction< std::shared_ptr<U> > sstd_make_start_function( Args && ... args ){
    return sstd::makeStartFunction<U>(std::forward<Args>(args)...);
}

namespace sstd{
    class SSTD_SYMBOL_DECL YieldFunctionBasic{
        sstd_delete_copy_create(YieldFunctionBasic);
    public:
        YieldFunctionBasic();
        virtual ~YieldFunctionBasic();
    protected:
        virtual void doRun() = 0;
        virtual void directRun() noexcept = 0;
    private:
        sstd_class(YieldFunctionBasic);
    };
}/*namespace sstd*/

namespace sstd {

    class YieldResumeFunctionPrivate;
    class SSTD_SYMBOL_DECL YieldResumeFunction :
        public YieldFunctionBasic,
        public std::enable_shared_from_this<YieldResumeFunction> {
        YieldResumeFunctionPrivate * const thisPrivate;
        sstd_delete_copy_create(YieldResumeFunction);
    public:
        YieldResumeFunction(std::size_t=1024uLL*1024uLL*64uLL);
        virtual ~YieldResumeFunction();
    public:
        void start() noexcept;
    protected:
        void yield() noexcept;
        void resume() noexcept;
    protected:
        void directRun() noexcept override;
    private:
        void directYield() noexcept;
        void directResume() noexcept;
    private:
        sstd_class(YieldResumeFunction);
    };

}/*namespace sstd*/











