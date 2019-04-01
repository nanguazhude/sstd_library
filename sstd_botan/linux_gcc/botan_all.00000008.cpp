
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
* Create an AlgorithmIdentifier
*/
AlgorithmIdentifier::AlgorithmIdentifier(const OID& alg_id,
                                         const std::vector<uint8_t>& param) :
   oid(alg_id),
   parameters(param)
   {}

/*
* Create an AlgorithmIdentifier
*/
AlgorithmIdentifier::AlgorithmIdentifier(const std::string& alg_id,
                                         const std::vector<uint8_t>& param) :
   oid(OIDS::lookup(alg_id)),
   parameters(param)
   {}

/*
* Create an AlgorithmIdentifier
*/
AlgorithmIdentifier::AlgorithmIdentifier(const OID& alg_id,
                                         Encoding_Option option) :
   oid(alg_id),
   parameters()
   {
   const uint8_t DER_NULL[] = { 0x05, 0x00 };

   if(option == USE_NULL_PARAM)
      parameters.assign(DER_NULL, DER_NULL + 2);
   }

/*
* Create an AlgorithmIdentifier
*/
AlgorithmIdentifier::AlgorithmIdentifier(const std::string& alg_id,
                                         Encoding_Option option) :
   oid(OIDS::lookup(alg_id)),
   parameters()
   {
   const uint8_t DER_NULL[] = { 0x05, 0x00 };

   if(option == USE_NULL_PARAM)
      parameters.assign(DER_NULL, DER_NULL + 2);
   }

/*
* Compare two AlgorithmIdentifiers
*/
namespace {

bool param_null_or_empty(const std::vector<uint8_t>& p)
   {
   if(p.size() == 2 && (p[0] == 0x05) && (p[1] == 0x00))
      return true;
   return p.empty();
   }

}

bool operator==(const AlgorithmIdentifier& a1, const AlgorithmIdentifier& a2)
   {
   if(a1.get_oid() != a2.get_oid())
      return false;

   if(param_null_or_empty(a1.get_parameters()) &&
      param_null_or_empty(a2.get_parameters()))
      return true;

   return (a1.get_parameters() == a2.get_parameters());
   }

/*
* Compare two AlgorithmIdentifiers
*/
bool operator!=(const AlgorithmIdentifier& a1, const AlgorithmIdentifier& a2)
   {
   return !(a1 == a2);
   }

/*
* DER encode an AlgorithmIdentifier
*/
void AlgorithmIdentifier::encode_into(DER_Encoder& codec) const
   {
   codec.start_cons(SEQUENCE)
      .encode(get_oid())
      .raw_bytes(get_parameters())
   .end_cons();
   }

/*
* Decode a BER encoded AlgorithmIdentifier
*/
void AlgorithmIdentifier::decode_from(BER_Decoder& codec)
   {
   codec.start_cons(SEQUENCE)
      .decode(oid)
      .raw_bytes(parameters)
   .end_cons();
   }

}
/*
* Attribute
* (C) 1999-2007 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
