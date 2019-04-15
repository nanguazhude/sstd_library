
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
* Create an Attribute
*/
Attribute::Attribute(const OID& attr_oid, const std::vector<uint8_t>& attr_value) :
   oid(attr_oid),
   parameters(attr_value)
   {}

/*
* Create an Attribute
*/
Attribute::Attribute(const std::string& attr_oid,
                     const std::vector<uint8_t>& attr_value) :
   oid(OIDS::lookup(attr_oid)),
   parameters(attr_value)
   {}

/*
* DER encode a Attribute
*/
void Attribute::encode_into(DER_Encoder& codec) const
   {
   codec.start_cons(SEQUENCE)
      .encode(oid)
      .start_cons(SET)
         .raw_bytes(parameters)
      .end_cons()
   .end_cons();
   }

/*
* Decode a BER encoded Attribute
*/
void Attribute::decode_from(BER_Decoder& codec)
   {
   codec.start_cons(SEQUENCE)
      .decode(oid)
      .start_cons(SET)
         .raw_bytes(parameters)
      .end_cons()
   .end_cons();
   }

}
/*
* ASN.1 Internals
* (C) 1999-2007,2018 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
