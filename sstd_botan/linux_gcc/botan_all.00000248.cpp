
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


namespace Botan {

size_t Intel_Rdrand::poll(RandomNumberGenerator& rng)
   {
   if(BOTAN_ENTROPY_INTEL_RNG_POLLS > 0 && RDRAND_RNG::available())
      {
      RDRAND_RNG rdrand_rng;
      secure_vector<uint8_t> buf(4 * BOTAN_ENTROPY_INTEL_RNG_POLLS);

      rdrand_rng.randomize(buf.data(), buf.size());
      rng.add_entropy(buf.data(), buf.size());
      }

   // RDRAND is used but not trusted
   return 0;
   }

}
/*
* RDRAND RNG
* (C) 2016 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
