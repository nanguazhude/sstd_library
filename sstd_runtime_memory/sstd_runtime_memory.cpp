#include "sstd_runtime_memory.hpp"
#include "../sstd_library.hpp"

#include <unordered_set>

namespace sstd {

    namespace _theSSTDRuntimeMemory {

        class Cookie {
        public:
            void * data;
        };

        inline void * directMalloc(std::size_t argSize, std::size_t argAlign) {

            if (argAlign < alignof(void*)) {
                argAlign = alignof(void *);
            }

            assert((argAlign&(argAlign - 1)) == 0);

            auto varMallocSize = argSize + argAlign + sizeof(Cookie);

            auto varRawAns =
                sstd::StaticMemoryObject::operator new(varMallocSize);

            auto varCookie =
                reinterpret_cast<Cookie*>(
                (reinterpret_cast<std::uintptr_t>(varRawAns) + sizeof(Cookie) + argAlign)&(argAlign - 1)) - 1;

            assert(reinterpret_cast<char *>(varCookie) >= reinterpret_cast<char *>(varRawAns));

            varCookie->data = varRawAns;

            return  varCookie + 1;

        }

        inline void directFree(void * arg) {
            sstd::StaticMemoryObject::operator delete(
                (reinterpret_cast<Cookie *>(arg) - 1)->data);
        }

        class RuntimeMemoryPrivate {
            std::unordered_set<void *, std::hash<void *>, std::equal_to<>, sstd::allocator<void *>>
                thisAllElements;
        public:
            inline void insert( void * arg ) {
                thisAllElements.insert(arg);
            }
            inline void erase( void * arg ) {
                thisAllElements.erase( arg);
            }
            inline RuntimeMemoryPrivate() {
            }
            inline ~RuntimeMemoryPrivate() {
                for ( const auto & varI : thisAllElements ) {
                    directFree(varI);
                }
            }
        private:
            sstd_class( RuntimeMemoryPrivate );
        };

    }/*_theSSTDRuntimeMemory*/

    void * RuntimeMemory::sstdMalloc(std::size_t argSize, std::size_t argAlign) {
        using namespace _theSSTDRuntimeMemory;
        auto varAns = directMalloc( argSize ,argAlign );
        reinterpret_cast<RuntimeMemoryPrivate *>(thisData)->insert(varAns);
        return varAns;
    }

    void RuntimeMemory::sstdFree(void * arg) {
        using namespace _theSSTDRuntimeMemory;
        reinterpret_cast<RuntimeMemoryPrivate *>(thisData)->erase(arg);
        directFree( arg );
    }

    RuntimeMemory::RuntimeMemory() {
        using namespace _theSSTDRuntimeMemory;
        thisData = sstd_new<RuntimeMemoryPrivate>() ;
    }

    RuntimeMemory::~RuntimeMemory() {
        using namespace _theSSTDRuntimeMemory;
        delete
            reinterpret_cast<RuntimeMemoryPrivate *>(thisData);
    }

    RuntimeMemory::RuntimeMemory(RuntimeMemory && arg) : thisData(arg.thisData) {
        arg.thisData = nullptr;
    }

    RuntimeMemory&RuntimeMemory::operator=(RuntimeMemory&& arg) {
        using namespace _theSSTDRuntimeMemory;

        if (this == &arg) {
            return *this;
        }

        delete
            reinterpret_cast<RuntimeMemoryPrivate *>(thisData);

        thisData = arg.thisData;
        arg.thisData = nullptr;

        return *this;

    }

}/*namespace sstd*/








