#include "sstd_library_memory.hpp"

namespace _theSSTDLibraryMemoryFile {

    inline void * auto_malloc(std::size_t n){
        return ::operator new(n);
    }

     inline void auto_free(void * ptr){
         ::operator delete(ptr);
     }

     inline void * auto_malloc(std::size_t c, std::align_val_t a){
         return ::operator new(c, a);
     }

     inline void auto_free(void* ptr, std::align_val_t al){
        return ::operator delete(ptr, al);
     }

}/*namespace _theSSTDLibraryMemoryFile*/

namespace sstd {

    void* StaticMemoryObject::operator new (std::size_t count){
        return _theSSTDLibraryMemoryFile::auto_malloc(count);
    }

    void StaticMemoryObject::operator delete(void * ptr){
        return _theSSTDLibraryMemoryFile::auto_free(ptr);
    }

    void* StaticMemoryObject::operator new[](std::size_t count){
        return _theSSTDLibraryMemoryFile::auto_malloc(count);
    }

    void StaticMemoryObject::operator delete[](void * ptr){
        return _theSSTDLibraryMemoryFile::auto_free(ptr);
    }

    void* StaticMemoryObject::operator new(std::size_t count, std::align_val_t al){
        return _theSSTDLibraryMemoryFile::auto_malloc(count,al);
    }

    void StaticMemoryObject::operator delete(void* ptr, std::align_val_t al){
        return _theSSTDLibraryMemoryFile::auto_free(ptr,al);
    }

    void* StaticMemoryObject::operator new[](std::size_t count, std::align_val_t al){
        return _theSSTDLibraryMemoryFile::auto_malloc(count,al);
    }

    void StaticMemoryObject::operator delete[](void* ptr, std::align_val_t al){
        return _theSSTDLibraryMemoryFile::auto_free(ptr,al);
    }

}/*namespace sstd*/


/*
#pragma pack(push, 2)
#pragma pack(pop)
*/
















