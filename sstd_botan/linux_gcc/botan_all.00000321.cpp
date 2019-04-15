
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

namespace TLS {

/**
* Return a TLS Handshake Hash
*/
secure_vector<uint8_t> Handshake_Hash::final(Protocol_Version version,
                                          const std::string& mac_algo) const
   {
   std::string hash_algo = mac_algo;
   if(!version.supports_ciphersuite_specific_prf())
      hash_algo = "Parallel(MD5,SHA-160)";
   else if(mac_algo == "MD5" || mac_algo == "SHA-1")
      hash_algo = "SHA-256";

   std::unique_ptr<HashFunction> hash(HashFunction::create_or_throw(hash_algo));
   hash->update(m_data);
   return hash->final();
   }

}

}
/*
* TLS Handshake IO
* (C) 2012,2014,2015 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
