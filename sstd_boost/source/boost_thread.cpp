
#include "../sstd/libs/thread/src/future.cpp"
#include "../sstd/libs/thread/src/tss_null.cpp"

#if defined(_WIN32)
#include "../sstd/libs/thread/src/win32/thread.cpp"
#include "../sstd/libs/thread/src/win32/thread_primitives.cpp"
#include "../sstd/libs/thread/src/win32/tss_dll.cpp"
#include "../sstd/libs/thread/src/win32/tss_pe.cpp"
#else
#include "../sstd/libs/thread/src/pthread/thread.cpp"
#include "../sstd/libs/thread/src/pthread/once.cpp"
/*#include "../sstd/libs/thread/src/pthread/once_atomic.cpp"*/
#endif



