
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

namespace TLS {

std::string Protocol_Version::to_string() const
   {
   const uint8_t maj = major_version();
   const uint8_t min = minor_version();

   if(maj == 3 && min == 0)
      return "SSL v3";

   if(maj == 3 && min >= 1) // TLS v1.x
      return "TLS v1." + std::to_string(min-1);

   if(maj == 254) // DTLS 1.x
      return "DTLS v1." + std::to_string(255 - min);

   // Some very new or very old protocol (or bogus data)
   return "Unknown " + std::to_string(maj) + "." + std::to_string(min);
   }

bool Protocol_Version::is_datagram_protocol() const
   {
   return major_version() == 254;
   }

bool Protocol_Version::operator>(const Protocol_Version& other) const
   {
   if(this->is_datagram_protocol() != other.is_datagram_protocol())
      throw TLS_Exception(Alert::PROTOCOL_VERSION,
                          "Version comparing " + to_string() +
                          " with " + other.to_string());

   if(this->is_datagram_protocol())
      return m_version < other.m_version; // goes backwards

   return m_version > other.m_version;
   }

bool Protocol_Version::known_version() const
   {
   return (m_version == Protocol_Version::TLS_V10 ||
           m_version == Protocol_Version::TLS_V11 ||
           m_version == Protocol_Version::TLS_V12 ||
           m_version == Protocol_Version::DTLS_V10 ||
           m_version == Protocol_Version::DTLS_V12);
   }

bool Protocol_Version::supports_negotiable_signature_algorithms() const
   {
   return (m_version != Protocol_Version::TLS_V10 &&
           m_version != Protocol_Version::TLS_V11 &&
           m_version != Protocol_Version::DTLS_V10);
   }

bool Protocol_Version::supports_explicit_cbc_ivs() const
   {
   return (m_version != Protocol_Version::TLS_V10);
   }

bool Protocol_Version::supports_ciphersuite_specific_prf() const
   {
   return (m_version != Protocol_Version::TLS_V10 &&
           m_version != Protocol_Version::TLS_V11 &&
           m_version != Protocol_Version::DTLS_V10);
   }

bool Protocol_Version::supports_aead_modes() const
   {
   return (m_version != Protocol_Version::TLS_V10 &&
           m_version != Protocol_Version::TLS_V11 &&
           m_version != Protocol_Version::DTLS_V10);
   }

}

}
/*
* TLS CBC Record Handling
* (C) 2012,2013,2014,2015,2016 Jack Lloyd
* (C) 2016 Juraj Somorovsky
* (C) 2016 Matthias Gierlings
* (C) 2016 Daniel Neus, Rohde & Schwarz Cybersecurity
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
