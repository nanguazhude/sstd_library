#include "sstd_library_application.hpp"
#include <mutex>
#include <vector>
#include <list>

namespace sstd {

    class Manager {
    public:

        using string = std::basic_string<char, std::char_traits<char>, sstd::allocator<char>>;

        std::mutex thisMutex;
        std::atomic< bool > isConstruct{ false };
        std::atomic< bool > isQuit{ false };
        std::list< std::function<void(void)>, sstd::allocator< std::function<void(void)> > > callOnConstruct;
        std::list< std::function<void(void)>, sstd::allocator< std::function<void(void)> > > callOnDestruct;
        std::vector< string, sstd::allocator<string> > args;

        sstd_class(Manager);

    };

    inline Manager * getManager();

    namespace detail {

        SSTD_SYMBOL_DECL void callOnceAfterStart(std::function<void(void)> arg) {
            auto varManager = getManager();
            if (varManager->isConstruct.load()) {
                sstd_try{
                   arg();
                }sstd_catch(...) {
                    sstd_on_exception();
                }/*direct call*/
                return;
            }
            std::unique_lock varLock{ varManager->thisMutex };
            if (varManager->isConstruct.load()) {
                sstd_try{
                   arg();
                }sstd_catch(...) {
                    sstd_on_exception();
                }/*direct call*/
                return;
            }
            varManager->callOnConstruct.push_back(std::move(arg));
        }

        SSTD_SYMBOL_DECL void callOnceBeforeQuit(std::function<void(void)> arg) {
            auto varManager = getManager();
            if (varManager->isQuit.load()) {
                return/*do not call this ...*/;
            }
            std::unique_lock varLock{ varManager->thisMutex };
            if (varManager->isQuit.load()) {
                return/*do not call this ...*/;
            }
            varManager->callOnConstruct.push_front(std::move(arg));
        }

    }/*namespace detail*/

    Application::Application(int argc, char ** argv) : isRef(false) {

        auto varManager = getManager();

        if (varManager->isConstruct) {
            assert(false && "the application can not construct more than once !!!");
            return;
        }

        std::unique_lock varLock{ varManager->thisMutex };

        if (varManager->isConstruct) {
            assert(false && "the application can not construct more than once !!!");
            return;
        }

        for (auto & varI : varManager->callOnConstruct) {
            sstd_try{
                varI();
            }sstd_catch(...) {
                sstd_on_exception();
            }
        }

        varManager->callOnConstruct.clear();

        varManager->args.reserve(argc);
        for (int i = 0; i < argc; ++i) {
            varManager->args.push_back(argv[i]);
        }

        varManager->isConstruct.store(true);

    }

    Application::Application() : isRef(true) {
    }

    bool Application::isConstruct() {
        return getManager()->isConstruct.load();
    }

    bool Application::isDestruct() {
        return getManager()->isQuit.load();
    }

    const std::vector< Application::string, sstd::allocator< Application::string> > * Application::getArgs() {
        assert(getManager()->isConstruct.load());
        return &(getManager()->args);
    }

    Application::~Application() {
        if (!isRef) {

            auto varManager = getManager();

            if (varManager->isQuit.load()) {
                assert(false && "the application can not destruct more than once !!!");
                return;
            }
            std::unique_lock varLock{ getManager()->thisMutex };
            if (varManager->isQuit.load()) {
                assert(false && "the application can not destruct more than once !!!");
                return;
            }

            for (auto & varI : varManager->callOnDestruct) {
                sstd_try{
                    varI();
                }sstd_catch(...) {
                    sstd_on_exception();
                }
            }
            varManager->callOnDestruct.clear();

            varManager->isQuit.store(true);

        }
    }

    inline Manager * getManager() {
        static auto varAns = new Manager;
        return varAns;
    }

}/*namespace sstd*/
















