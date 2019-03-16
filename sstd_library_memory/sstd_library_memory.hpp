#pragma once

#include "../global_sstd_library.hpp"

#include <new>
#include <memory>
#include <utility>

#if __has_include(<memory_resource>)
#include <memory_resource>
#endif

namespace _theSSTDLibraryMemoryFile {
}/*namespace _theSSTDLibraryMemoryFile*/

namespace sstd {
    class SSTD_SYMBOL_DECL StaticMemoryObject{
    public:
        sstd_default_copy_create(StaticMemoryObject);
        StaticMemoryObject()=default;
        ~StaticMemoryObject()=default;
    public:
        static void* operator new (std::size_t count);
        static void operator delete(void * ptr);

        static void* operator new[](std::size_t count);
        static void operator delete[](void * ptr);

        static void* operator new(std::size_t count, std::align_val_t al);
        static void operator delete(void* ptr, std::align_val_t al);

        static void* operator new[](std::size_t count, std::align_val_t al);
        static void operator delete[](void* ptr, std::align_val_t al);

        static inline void* operator new  (std::size_t, void* ptr) noexcept {
            return ptr;
        }
        static inline void* operator new[](std::size_t, void* ptr) noexcept {
            return ptr;
        }

        static constexpr inline void operator delete  (void *, void *) noexcept {
        }
        static constexpr inline void operator delete[](void *, void *) noexcept {
        }
    };
}/*namespace sstd*/








