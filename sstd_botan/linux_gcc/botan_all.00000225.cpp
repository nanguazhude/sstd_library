
#include "botan_all.h"
#include "botan_all_internal.h"

/*
* Adler32
* (C) 1999-2007 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>
#include <utility>
#include "botan_parts_detail.hpp"


namespace Botan {

namespace PKCS11 {

Module::Module(const std::string& file_path, C_InitializeArgs init_args)
   : m_file_path(file_path)
   {
   reload(init_args);
   }

Module::~Module() noexcept
   {
   try
      {
      m_low_level->C_Finalize(nullptr, nullptr);
      }
   catch(...)
      {
      // we are noexcept and must swallow any exception here
      }
   }

void Module::reload(C_InitializeArgs init_args)
   {
   if(m_low_level)
      {
      m_low_level->C_Finalize(nullptr);
      }

   m_library.reset(new Dynamically_Loaded_Library(m_file_path));
   LowLevel::C_GetFunctionList(*m_library, &m_func_list);
   m_low_level.reset(new LowLevel(m_func_list));

   m_low_level->C_Initialize(&init_args);
   }

}
}
/*
* PKCS#11 Object
* (C) 2016 Daniel Neus, Sirrix AG
* (C) 2016 Philipp Weber, Sirrix AG
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
