#pragma once

#include <memory>
#include "../sstd_library.hpp"

namespace sstd {

    /*运行时内存分配器，
    结束时回收所有已经分配的内存,
    非线程安全*/
    class SSTD_SYMBOL_DECL RuntimeMemory {
        void * thisData;
    public:
        void * sstdMalloc(std::size_t, std::size_t = alignof (void *));
        void sstdFree(void *);
    public:
        RuntimeMemory();
        ~RuntimeMemory();
    public:
        RuntimeMemory(RuntimeMemory &&);
        RuntimeMemory&operator=(RuntimeMemory&&);
    public:
        RuntimeMemory(const RuntimeMemory &)=delete;
        RuntimeMemory&operator=(const RuntimeMemory &)=delete;
    private:
        sstd_class(RuntimeMemory);
    };

}/*namespace sstd*/














