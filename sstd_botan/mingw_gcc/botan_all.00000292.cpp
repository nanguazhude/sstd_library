
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


// Based on code by Pierre Gaston (http://p9as.blogspot.com/2012/06/c11-semaphores.html)

namespace Botan {

void Semaphore::release(size_t n)
   {
   for(size_t i = 0; i != n; ++i)
      {
      std::lock_guard<std::mutex> lock(m_mutex);

      if(m_value++ < 0)
         {
         ++m_wakeups;
         m_cond.notify_one();
         }
      }
   }

void Semaphore::acquire()
   {
   std::unique_lock<std::mutex> lock(m_mutex);
   if(m_value-- <= 0)
       {
       m_cond.wait(lock, [this] { return m_wakeups > 0; });
       --m_wakeups;
       }
   }

}
/*
* (C) 2019 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
