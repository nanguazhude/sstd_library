
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
* Update an CBC-MAC Calculation
*/
void CBC_MAC::add_data(const uint8_t input[], size_t length)
   {
   verify_key_set(m_state.empty() == false);

   size_t xored = std::min(output_length() - m_position, length);
   xor_buf(&m_state[m_position], input, xored);
   m_position += xored;

   if(m_position < output_length())
      return;

   m_cipher->encrypt(m_state);
   input += xored;
   length -= xored;
   while(length >= output_length())
      {
      xor_buf(m_state, input, output_length());
      m_cipher->encrypt(m_state);
      input += output_length();
      length -= output_length();
      }

   xor_buf(m_state, input, length);
   m_position = length;
   }

/*
* Finalize an CBC-MAC Calculation
*/
void CBC_MAC::final_result(uint8_t mac[])
   {
   verify_key_set(m_state.empty() == false);

   if(m_position)
      m_cipher->encrypt(m_state);

   copy_mem(mac, m_state.data(), m_state.size());
   zeroise(m_state);
   m_position = 0;
   }

/*
* CBC-MAC Key Schedule
*/
void CBC_MAC::key_schedule(const uint8_t key[], size_t length)
   {
   m_state.resize(m_cipher->block_size());
   m_cipher->set_key(key, length);
   }

/*
* Clear memory of sensitive data
*/
void CBC_MAC::clear()
   {
   m_cipher->clear();
   zap(m_state);
   m_position = 0;
   }

/*
* Return the name of this type
*/
std::string CBC_MAC::name() const
   {
   return "CBC-MAC(" + m_cipher->name() + ")";
   }

/*
* Return a clone of this object
*/
MessageAuthenticationCode* CBC_MAC::clone() const
   {
   return new CBC_MAC(m_cipher->clone());
   }

/*
* CBC-MAC Constructor
*/
CBC_MAC::CBC_MAC(BlockCipher* cipher) :
   m_cipher(cipher)
   {
   }

}
/*
* CCM Mode Encryption
* (C) 2013,2018 Jack Lloyd
* (C) 2016 Daniel Neus, Rohde & Schwarz Cybersecurity
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
