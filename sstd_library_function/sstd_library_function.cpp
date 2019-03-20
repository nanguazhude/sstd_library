#include "sstd_library_function.hpp"

#include <sstd/boost/context/fiber.hpp>
#include <sstd/boost/context/protected_fixedsize_stack.hpp>

namespace sstd {

    class YieldResumeFunctionPrivate {
    public:
        using fiber_t = boost::context::fiber;
        std::optional< fiber_t > fiber;
        fiber_t * fiberFunction{ nullptr };
        bool hasException{ false };
        bool isFinished{ false };
        bool isOutter{ true };
        bool isStart{ false };
    private:
        sstd_class(YieldResumeFunctionPrivate);
    };

    YieldResumeFunction::YieldResumeFunction(std::size_t argStackSize) :
        thisPrivate{ sstd_new<YieldResumeFunctionPrivate>() } {
        using fiber_t = YieldResumeFunctionPrivate::fiber_t;
        thisPrivate->fiber.emplace(std::allocator_arg,
            boost::context::protected_fixedsize_stack{ argStackSize },
            [this](fiber_t &&f)->fiber_t {
            thisPrivate->fiberFunction = &f;
            this->directRun();
            return std::move(f);
        });
    }

    YieldResumeFunction::~YieldResumeFunction() {
        delete thisPrivate;
    }

    void YieldResumeFunction::start() noexcept {
        if (!thisPrivate->isOutter) {
            return;
        }
        this->resume();
    }

    void YieldResumeFunction::quit() noexcept {
        thisPrivate->hasException = true;
        if (thisPrivate->isStart) {
            this->start();
        }
    }

    void YieldResumeFunction::yield() noexcept {
        this->directYield();
    }

    void YieldResumeFunction::innerYield() noexcept {
        thisPrivate->isOutter = false;
        this->yield();
    }

    void YieldResumeFunction::outerYield() noexcept {
        thisPrivate->isOutter = true;
        this->yield();
    }

    void YieldResumeFunction::resume() noexcept {
        this->directResume();
    }

    std::shared_ptr<YieldResumeFunction> YieldResumeFunction::copyThisToAnotherStack() noexcept {
        return shared_super::shared_from_this();
    }

    void YieldResumeFunction::directRun() noexcept {
        sstd_try{
            this->doRun();
        }sstd_catch(...) {
            this->doException();
            thisPrivate->hasException = true;
        }
        thisPrivate->isFinished = true;
    }

    bool YieldResumeFunction::hasException() const noexcept {
        return thisPrivate->hasException;
    }

    bool YieldResumeFunction::isFinished() const noexcept {
        return thisPrivate->isFinished;
    }

    bool YieldResumeFunction::isStarted() const noexcept {
        return thisPrivate->isStart;
    }

    bool YieldResumeFunction::isOuter() const noexcept {
        return thisPrivate->isOutter;
    }

    void YieldResumeFunction::directResume() noexcept {
        thisPrivate->isOutter = false;
        thisPrivate->isStart = true;
        if (thisPrivate->isFinished) {
            return;
        }
        assert(thisPrivate->fiber);
        assert(*(thisPrivate->fiber));
        *(thisPrivate->fiber) = std::move(*(thisPrivate->fiber)).resume();
    }

    void YieldResumeFunction::directYield() noexcept {
        assert(thisPrivate->fiberFunction);
        assert(*(thisPrivate->fiberFunction));
        *(thisPrivate->fiberFunction) = std::move(*(thisPrivate->fiberFunction)).resume();
    }

    void YieldResumeFunction::resumeWithException() noexcept {
        this->doException();
        thisPrivate->hasException = true;
        this->resume();
    }

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






