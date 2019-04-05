#include "sstd_library_application.hpp"
#include <mutex>

namespace sstd {

    class Manager {
    public:
        std::mutex thisMutex;
        std::atomic< bool > isConstruct{ false };
        std::atomic< bool > isQuit{ false };
        std::vector< std::function<void(void)>, sstd::allocator< std::function<void(void)> > > callOnConstruct;
        std::vector< std::function<void(void)>, sstd::allocator< std::function<void(void)> > > callOnDestruct;
    };

    inline Manager * getManager();

    SSTD_SYMBOL_DECL void callOnceAfterStart(std::function<void(void)> arg) {
        auto varManager = getManager();
        if ( varManager->isConstruct.load() ) {
            arg()/*direct call*/;
            return;
        }
        std::unique_lock varLock{ varManager->thisMutex };
        if (varManager->isConstruct.load()) {
            arg()/*direct call*/;
            return;
        }
        varManager->callOnConstruct.push_back( std::move(arg) );
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
        varManager->callOnConstruct.push_back( std::move(arg) );
    }

    Application::Application(int argc, char ** argv) : isRef(false) {

        auto varManager = getManager();
       
        if (varManager->isQuit) {
            return;
        }

        if (varManager->isConstruct) {
            return;
        }
 
        std::unique_lock varLock{ varManager->thisMutex };

        if (varManager->isQuit) {
            return;
        }

        if (varManager->isConstruct) {
            return;
        }




        varManager->isConstruct.store(true);

    }

    Application::Application() : isRef(true) {
    }

    Application::~Application() {
        if (!isRef) {
            auto varManager = getManager();
            if (varManager->isQuit.load()) {
                return;
            }
            std::unique_lock varLock{ getManager()->thisMutex };
            if (varManager->isQuit.load()) {
                return;
            }
            
        }
    }

   

    inline Manager * getManager() {
        static auto varAns = new Manager;
        return varAns;
    }

}/*namespace sstd*/
















