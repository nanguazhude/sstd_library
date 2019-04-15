
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

size_t KDF1::kdf(uint8_t key[], size_t key_len,
                 const uint8_t secret[], size_t secret_len,
                 const uint8_t salt[], size_t salt_len,
                 const uint8_t label[], size_t label_len) const
   {
   m_hash->update(secret, secret_len);
   m_hash->update(label, label_len);
   m_hash->update(salt, salt_len);

   if(key_len < m_hash->output_length())
      {
      secure_vector<uint8_t> v = m_hash->final();
      copy_mem(key, v.data(), key_len);
      return key_len;
      }

   m_hash->final(key);
   return m_hash->output_length();
   }

}
/*
* KDF1 from ISO 18033-2
* (C) 2016 Philipp Weber
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
