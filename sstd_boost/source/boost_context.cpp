
#include "../sstd/libs/context/src/dummy.cpp"
#include "../sstd/libs/context/src/execution_context.cpp"

#if defined(_WINI32)
#include "../sstd/libs/context/src/windows/stack_traits.cpp"
#else
#include "../sstd/libs/context/src/posix/stack_traits.cpp"
#endif
