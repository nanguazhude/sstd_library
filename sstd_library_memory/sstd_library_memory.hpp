#pragma once

#include "../global_sstd_library.hpp"

#include <new>
#include <memory>
#include <utility>

namespace _theSSTDLibraryMemoryFile {
}/*namespace _theSSTDLibraryMemoryFile*/

namespace sstd {
    class SSTD_SYMBOL_DECL StaticMemoryObject{
    public:
        sstd_default_copy_create(StaticMemoryObject);
        StaticMemoryObject()=default;
        ~StaticMemoryObject()=default;
    };
}/*namespace sstd*/








