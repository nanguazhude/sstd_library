
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

/*
* Randomize this number
*/
void BigInt::randomize(RandomNumberGenerator& rng,
                       size_t bitsize, bool set_high_bit)
   {
   set_sign(Positive);

   if(bitsize == 0)
      {
      clear();
      }
   else
      {
      secure_vector<uint8_t> array = rng.random_vec(round_up(bitsize, 8) / 8);

      // Always cut unwanted bits
      if(bitsize % 8)
         array[0] &= 0xFF >> (8 - (bitsize % 8));

      // Set the highest bit if wanted
      if (set_high_bit)
         array[0] |= 0x80 >> ((bitsize % 8) ? (8 - bitsize % 8) : 0);

      binary_decode(array);
      }
   }

/*
* Generate a random integer within given range
*/
BigInt BigInt::random_integer(RandomNumberGenerator& rng,
                              const BigInt& min, const BigInt& max)
   {
   if(min.is_negative() || max.is_negative() || max <= min)
      throw Invalid_Argument("BigInt::random_integer invalid range");

   BigInt r;

   const size_t bits = max.bits();

   do
      {
      r.randomize(rng, bits, false);
      }
   while(r < min || r >= max);

   return r;
   }

}
/*
* BigInt Base
* (C) 1999-2011,2012,2014,2019 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
