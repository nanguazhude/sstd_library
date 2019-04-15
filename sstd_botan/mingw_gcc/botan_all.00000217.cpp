
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

const std::map<const std::string, std::vector<std::string>> allowed_signature_paddings =
   {
   { "DSA", {"EMSA1"} },
   { "ECDSA", {"EMSA1"} },
   { "ECGDSA", {"EMSA1"} },
   { "ECKCDSA", {"EMSA1"} },
   { "GOST-34.10", {"EMSA1"} },
   { "RSA", {"EMSA4", "EMSA3"} },
   };

const std::vector<std::string> get_sig_paddings(const std::string algo)
   {
   if(allowed_signature_paddings.count(algo) > 0)
      return allowed_signature_paddings.at(algo);
   return {};
   }

bool sig_algo_and_pad_ok(const std::string algo, const std::string padding)
   {
   std::vector<std::string> pads = get_sig_paddings(algo);
   return std::find(pads.begin(), pads.end(), padding) != pads.end();
   }
}
/*
* PKCS#11
* (C) 2016 Daniel Neus, Sirrix AG
* (C) 2016 Philipp Weber, Sirrix AG
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
