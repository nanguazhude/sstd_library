#pragma once

#if defined(BOTAN_USE_MSVC_)
#include "msvc/botan_all.h"
#endif

#if defined(BOTAN_USE_MINGW_GCC_)
#include "mingw_gcc/botan_all.h"
#endif

#if defined(BOTAN_USE_LINUX_GCC_)
#include "linux_gcc/botan_all.h"
#endif

namespace _theSSTDBotanFile{
}/*_theSSTDBotanFile*/

namespace sstd{
    
}/*namespace sstd*/










