
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

size_t ecp_work_factor(size_t bits)
   {
   return bits / 2;
   }

namespace {

size_t nfs_workfactor(size_t bits, double k)
   {
   // approximates natural logarithm of integer of given bitsize
   const double log2_e = std::log2(std::exp(1));
   const double log_p = bits / log2_e;

   const double log_log_p = std::log(log_p);

   // RFC 3766: k * e^((1.92 + o(1)) * cubrt(ln(n) * (ln(ln(n)))^2))
   const double est = 1.92 * std::pow(log_p * log_log_p * log_log_p, 1.0/3.0);

   // return log2 of the workfactor
   return static_cast<size_t>(std::log2(k) + log2_e * est);
   }

}

size_t if_work_factor(size_t bits)
   {
   // RFC 3766 estimates k at .02 and o(1) to be effectively zero for sizes of interest

   return nfs_workfactor(bits, .02);
   }

size_t dl_work_factor(size_t bits)
   {
   // Lacking better estimates...
   return if_work_factor(bits);
   }

size_t dl_exponent_size(size_t bits)
   {
   /*
   This uses a slightly tweaked version of the standard work factor
   function above. It assumes k is 1 (thus overestimating the strength
   of the prime group by 5-6 bits), and always returns at least 128 bits
   (this only matters for very small primes).
   */
   const size_t MIN_WORKFACTOR = 64;

   return 2 * std::max<size_t>(MIN_WORKFACTOR, nfs_workfactor(bits, 1));
   }

}
/*
* X.509 Public Key
* (C) 1999-2010 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
