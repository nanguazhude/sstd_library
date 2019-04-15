
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

secure_vector<uint8_t> EME_Raw::pad(const uint8_t in[], size_t in_length,
                                 size_t,
                                 RandomNumberGenerator&) const
   {
   return secure_vector<uint8_t>(in, in + in_length);
   }

secure_vector<uint8_t> EME_Raw::unpad(uint8_t& valid_mask,
                                   const uint8_t in[], size_t in_length) const
   {
   valid_mask = 0xFF;
   return CT::strip_leading_zeros(in, in_length);
   }

size_t EME_Raw::maximum_input_size(size_t keybits) const
   {
   return keybits / 8;
   }
}
/*
* EMSA1
* (C) 1999-2007 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
