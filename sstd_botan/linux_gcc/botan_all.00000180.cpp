
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

void mgf1_mask(HashFunction& hash,
               const uint8_t in[], size_t in_len,
               uint8_t out[], size_t out_len)
   {
   uint32_t counter = 0;

   secure_vector<uint8_t> buffer(hash.output_length());
   while(out_len)
      {
      hash.update(in, in_len);
      hash.update_be(counter);
      hash.final(buffer.data());

      const size_t xored = std::min<size_t>(buffer.size(), out_len);
      xor_buf(out, buffer.data(), xored);
      out += xored;
      out_len -= xored;

      ++counter;
      }
   }

}
/*
* MISTY1
* (C) 1999-2009 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
