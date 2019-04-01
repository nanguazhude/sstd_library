
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


#if defined(BOTAN_HAS_X509_CERTIFICATES)

namespace Botan {
namespace PKCS11 {

X509_CertificateProperties::X509_CertificateProperties(const std::vector<uint8_t>& subject, const std::vector<uint8_t>& value)
   : CertificateProperties(CertificateType::X509), m_subject(subject), m_value(value)
   {
   add_binary(AttributeType::Subject, m_subject);
   add_binary(AttributeType::Value, m_value);
   }

PKCS11_X509_Certificate::PKCS11_X509_Certificate(Session& session, ObjectHandle handle)
   : Object(session, handle), X509_Certificate(unlock(get_attribute_value(AttributeType::Value)))
   {
   }

PKCS11_X509_Certificate::PKCS11_X509_Certificate(Session& session, const X509_CertificateProperties& props)
   : Object(session, props), X509_Certificate(props.value())
   {
   }

}

}

#endif
/*
* Derived from poly1305-donna-64.h by Andrew Moon <liquidsun@gmail.com>
* in https://github.com/floodyberry/poly1305-donna
*
* (C) 2014 Andrew Moon
* (C) 2014 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
