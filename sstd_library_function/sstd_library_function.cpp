#include "sstd_library_function.hpp"

#include <sstd/boost/context/fiber.hpp>
#include <sstd/boost/context/protected_fixedsize_stack.hpp>

namespace _theSSTDLibraryFunctionFile {
    class QuitException final {
    public:
        inline QuitException() = default;
        sstd_default_copy_create(QuitException);
    private:
        sstd_class(QuitException);
    };
}

namespace sstd {

    using SkipException = boost::context::detail::forced_unwind;

    class YieldResumeFunctionPrivate {
    public:
        using fiber_t = boost::context::fiber;
        std::optional< fiber_t > fiber;
        std::optional< fiber_t > fiberFunction;
        std::optional< std::exception_ptr > exception;
        bool foreQuit{ false };
        bool hasException{ false };
        bool isFinished{ false };
        bool isOutter{ true };
        bool isStart{ false };
    private:
        sstd_class(YieldResumeFunctionPrivate);
    };

    void YieldFunctionBasic::doRun() {
    }

    void YieldFunctionBasic::doException() noexcept {
        sstd_on_exception();
    }

    YieldFunctionBasic::YieldFunctionBasic() {
    }

    YieldFunctionBasic::~YieldFunctionBasic() {
    }

}/*namespace sstd*/

namespace sstd {

    YieldResumeFunction::YieldResumeFunction(std::size_t arg) :
        thisPrivate{ sstd_new<YieldResumeFunctionPrivate>() } {
        using FiberType = YieldResumeFunctionPrivate::fiber_t;
        auto & the = *thisPrivate;
        the.fiber.emplace(
            std::allocator_arg,
            boost::context::protected_fixedsize_stack{ arg },
            [this](FiberType && arg)->FiberType {
            thisPrivate->fiberFunction.emplace(std::move(arg));
            sstd_try{
                this->doRun();
            }sstd_catch(const SkipException &) {
                thisPrivate->hasException = true;
                thisPrivate->isFinished = true;
                this->doQuit();
                sstd_throw();
            }sstd_catch(const _theSSTDLibraryFunctionFile::QuitException &) {
                thisPrivate->hasException = true;
                this->doQuit();
            }sstd_catch(...) {
                thisPrivate->hasException = true;
                this->doException();
            }
            thisPrivate->isFinished = true;
            return std::move(*(thisPrivate->fiberFunction));
        });
    }

    void YieldResumeFunction::resume() {
        if (thisPrivate->isFinished) {
            return;
        }
        thisPrivate->isOutter = false;
        this->directResume();
    }

    void YieldResumeFunction::directResume() {
        auto & varFiber = (*(thisPrivate->fiber));
        varFiber = std::move(varFiber).resume();
    }

    void YieldResumeFunction::directYield() {
        auto & varFiber = (*(thisPrivate->fiberFunction));
        varFiber = std::move(varFiber).resume();
        /****************************************/
        if (thisPrivate->foreQuit) {
            sstd_throw( _theSSTDLibraryFunctionFile::QuitException{} );
        } else if (thisPrivate->exception) {
            auto varException = std::move(*thisPrivate->exception);
            thisPrivate->exception.reset();
            std::rethrow_exception(std::move(varException));
        }
    }

    void YieldResumeFunction::innerYield() {
        thisPrivate->isOutter = false;
        this->directYield();
    }

    void YieldResumeFunction::outerYiled() {
        thisPrivate->isOutter = true;
        this->directYield();
    }

    YieldResumeFunction::~YieldResumeFunction() {
        delete thisPrivate;
    }

    void YieldResumeFunction::start() {
        if (!thisPrivate->isOutter) {
            return;
        }
        thisPrivate->isStart = true;
        this->resume();
    }

    void YieldResumeFunction::quit() {

        if (!thisPrivate->isStart) {
            return;
        }

        if (thisPrivate->isFinished) {
            return;
        }

        if (thisPrivate->hasException) {
            return;
        }

        thisPrivate->foreQuit = true;
        this->start();

    }

    void YieldResumeFunction::resumeWithException() {

        thisPrivate->exception.emplace(std::current_exception());
        this->start();

    }

    void YieldResumeFunction::doQuit() noexcept {
    }

    bool YieldResumeFunction::isOuter() const {
        return thisPrivate->isOutter;
    }

    bool YieldResumeFunction::isFinished() const {
        return thisPrivate->isFinished;
    }

    bool YieldResumeFunction::hasException() const {
        return thisPrivate->hasException;
    }

    bool YieldResumeFunction::isStart() const {
        return thisPrivate->isStart;
    }

}/*namespace sstd*/




