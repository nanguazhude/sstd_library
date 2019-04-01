
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
* Update an ANSI X9.19 MAC Calculation
*/
void ANSI_X919_MAC::add_data(const uint8_t input[], size_t length)
   {
   verify_key_set(m_state.empty() == false);

   size_t xored = std::min(8 - m_position, length);
   xor_buf(&m_state[m_position], input, xored);
   m_position += xored;

   if(m_position < 8) return;

   m_des1->encrypt(m_state);
   input += xored;
   length -= xored;
   while(length >= 8)
      {
      xor_buf(m_state, input, 8);
      m_des1->encrypt(m_state);
      input += 8;
      length -= 8;
      }

   xor_buf(m_state, input, length);
   m_position = length;
   }

/*
* Finalize an ANSI X9.19 MAC Calculation
*/
void ANSI_X919_MAC::final_result(uint8_t mac[])
   {
   if(m_position)
      m_des1->encrypt(m_state);
   m_des2->decrypt(m_state.data(), mac);
   m_des1->encrypt(mac);
   zeroise(m_state);
   m_position = 0;
   }

/*
* ANSI X9.19 MAC Key Schedule
*/
void ANSI_X919_MAC::key_schedule(const uint8_t key[], size_t length)
   {
   m_state.resize(8);

   m_des1->set_key(key, 8);

   if(length == 16)
      key += 8;

   m_des2->set_key(key, 8);
   }

/*
* Clear memory of sensitive data
*/
void ANSI_X919_MAC::clear()
   {
   m_des1->clear();
   m_des2->clear();
   zap(m_state);
   m_position = 0;
   }

std::string ANSI_X919_MAC::name() const
   {
   return "X9.19-MAC";
   }

MessageAuthenticationCode* ANSI_X919_MAC::clone() const
   {
   return new ANSI_X919_MAC;
   }

/*
* ANSI X9.19 MAC Constructor
*/
ANSI_X919_MAC::ANSI_X919_MAC() :
   m_des1(BlockCipher::create("DES")),
   m_des2(m_des1->clone()),
   m_position(0)
   {
   }

}
/*
 * XMSS Common Ops
 * Operations shared by XMSS signature generation and verification operations.
 * (C) 2016,2017 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

void
XMSS_Common_Ops::randomize_tree_hash(secure_vector<uint8_t>& result,
                                     const secure_vector<uint8_t>& left,
                                     const secure_vector<uint8_t>& right,
                                     XMSS_Address& adrs,
                                     const secure_vector<uint8_t>& seed,
                                     XMSS_Hash& hash)
   {
   adrs.set_key_mask_mode(XMSS_Address::Key_Mask::Key_Mode);
   secure_vector<uint8_t> key { hash.prf(seed, adrs.bytes()) };

   adrs.set_key_mask_mode(XMSS_Address::Key_Mask::Mask_MSB_Mode);
   secure_vector<uint8_t> bitmask_l { hash.prf(seed, adrs.bytes()) };

   adrs.set_key_mask_mode(XMSS_Address::Key_Mask::Mask_LSB_Mode);
   secure_vector<uint8_t> bitmask_r { hash.prf(seed, adrs.bytes()) };

   BOTAN_ASSERT(bitmask_l.size() == left.size() &&
                bitmask_r.size() == right.size(),
                "Bitmask size doesn't match node size.");

   secure_vector<uint8_t> concat_xor(m_xmss_params.element_size() * 2);
   for(size_t i = 0; i < left.size(); i++)
      {
      concat_xor[i] = left[i] ^ bitmask_l[i];
      concat_xor[i + left.size()] = right[i] ^ bitmask_r[i];
      }

   hash.h(result, key, concat_xor);
   }


void
XMSS_Common_Ops::create_l_tree(secure_vector<uint8_t>& result,
                               wots_keysig_t pk,
                               XMSS_Address& adrs,
                               const secure_vector<uint8_t>& seed,
                               XMSS_Hash& hash)
   {
   size_t l = m_xmss_params.len();
   adrs.set_tree_height(0);

   while(l > 1)
      {
      for(size_t i = 0; i < l >> 1; i++)
         {
         adrs.set_tree_index(static_cast<uint32_t>(i));
         randomize_tree_hash(pk[i], pk[2 * i], pk[2 * i + 1], adrs, seed, hash);
         }
      if(l & 0x01)
         {
         pk[l >> 1] = pk[l - 1];
         }
      l = (l >> 1) + (l & 0x01);
      adrs.set_tree_height(adrs.get_tree_height() + 1);
      }
   result = pk[0];
   }

}
/*
 * XMSS Hash
 * A collection of pseudorandom hash functions required for XMSS and WOTS
 * computations.
 * (C) 2016,2017 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

XMSS_Hash::XMSS_Hash(const XMSS_Hash& hash)
   : XMSS_Hash(hash.m_hash_func_name)
   {
   }

XMSS_Hash::XMSS_Hash(const std::string& h_func_name) :
   m_hash(HashFunction::create(h_func_name)),
   m_hash_func_name(h_func_name)
   {
   if(!m_hash)
      throw Lookup_Error("XMSS cannot use hash " + h_func_name +
                         " because it is unavailable");

   m_output_length = m_hash->output_length();
   BOTAN_ASSERT(m_output_length > 0, "Hash output length of zero is invalid.");

   m_zero_padding.resize(m_output_length - 1);
   m_msg_hash.reset(m_hash->clone());
   }

void
XMSS_Hash::h(secure_vector<uint8_t>& result,
             const secure_vector<uint8_t>& key,
             const secure_vector<uint8_t>& data)
   {
   m_hash->update(m_zero_padding);
   m_hash->update(m_id_h);
   m_hash->update(key);
   m_hash->update(data);
   m_hash->final(result);
   }

void XMSS_Hash::h_msg_init(const secure_vector<uint8_t>& randomness,
                           const secure_vector<uint8_t>& root,
                           const secure_vector<uint8_t>& index_bytes)
   {
   m_msg_hash->clear();
   m_msg_hash->update(m_zero_padding);
   m_msg_hash->update(m_id_hmsg);
   m_msg_hash->update(randomness);
   m_msg_hash->update(root);
   m_msg_hash->update(index_bytes);
   }

void XMSS_Hash::h_msg_update(const uint8_t data[], size_t size)
   {
   m_msg_hash->update(data, size);
   }

secure_vector<uint8_t> XMSS_Hash::h_msg_final()
   {
   return m_msg_hash->final();
   }

secure_vector<uint8_t>
XMSS_Hash::h_msg(const secure_vector<uint8_t>& randomness,
                 const secure_vector<uint8_t>& root,
                 const secure_vector<uint8_t>& index_bytes,
                 const secure_vector<uint8_t>& data)
   {
   h_msg_init(randomness, root, index_bytes);
   m_msg_hash->update(data);
   return m_msg_hash->final();
   }

}
/*
 * XMSS Index Registry
 * A registry for XMSS private keys, keeps track of the leaf index for
 * independend copies of the same key.
 * (C) 2016 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

const std::string XMSS_Index_Registry::m_index_hash_function = "SHA-256";

uint64_t XMSS_Index_Registry::make_key_id(
   const secure_vector<uint8_t>& private_seed,
   const secure_vector<uint8_t>& prf) const
   {
   std::unique_ptr<HashFunction> hash =
      HashFunction::create(m_index_hash_function);
   BOTAN_ASSERT(hash != nullptr, "XMSS_Index_Registry requires SHA-256");
   hash->update(private_seed);
   hash->update(prf);
   secure_vector<uint8_t> result = hash->final();
   uint64_t key_id = 0;
   for(size_t i = 0; i < sizeof(key_id); i++)
      {
      key_id = ((key_id << 8) | result[i]);
      }

   return key_id;
   }

std::shared_ptr<Atomic<size_t>>
XMSS_Index_Registry::get(const secure_vector<uint8_t>& private_seed,
                         const secure_vector<uint8_t>& prf)
   {
   size_t pos = get(make_key_id(private_seed, prf));

   if(pos < std::numeric_limits<size_t>::max())
      {
      return m_leaf_indices[pos];
      }
   else
      {
      return m_leaf_indices[add(make_key_id(private_seed, prf))];
      }
   }

size_t XMSS_Index_Registry::get(uint64_t id) const
   {
   for(size_t i = 0; i < m_key_ids.size(); i++)
      {
      if(m_key_ids[i] == id)
         {
         return i;
         }
      }

   return std::numeric_limits<size_t>::max();
   }

size_t XMSS_Index_Registry::add(uint64_t id, size_t last_unused)
   {
   lock_guard_type<mutex_type> lock(m_mutex);
   size_t pos = get(id);
   if(pos < m_key_ids.size())
      {
      if(last_unused > *(m_leaf_indices[pos]))
         {
         m_leaf_indices[pos] = std::make_shared<Atomic<size_t>>(last_unused);
         }
      return pos;
      }

   m_key_ids.push_back(id);
   m_leaf_indices.push_back(std::make_shared<Atomic<size_t>>(last_unused));
   return m_key_ids.size() - 1;
   }

}
/*
 * XMSS Parameters
 * Descibes a signature method for XMSS, as defined in:
 * [1] XMSS: Extended Hash-Based Signatures,
 *     draft-itrf-cfrg-xmss-hash-based-signatures-06
 *     Release: July 2016.
 *     https://datatracker.ietf.org/doc/
 *     draft-irtf-cfrg-xmss-hash-based-signatures/?include_text=1
 *
 * (C) 2016,2017 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

XMSS_Parameters::xmss_algorithm_t XMSS_Parameters::xmss_id_from_string(const std::string& param_set)
   {
   if(param_set == "XMSS_SHA2-256_W16_H10")
      { return XMSS_SHA2_256_W16_H10; }
   if(param_set == "XMSS_SHA2-256_W16_H16")
      { return XMSS_SHA2_256_W16_H16; }
   if(param_set == "XMSS_SHA2-256_W16_H20")
      { return XMSS_SHA2_256_W16_H20; }
   if(param_set == "XMSS_SHA2-512_W16_H10")
      { return XMSS_SHA2_512_W16_H10; }
   if(param_set == "XMSS_SHA2-512_W16_H16")
      { return XMSS_SHA2_512_W16_H16; }
   if(param_set == "XMSS_SHA2-512_W16_H20")
      { return XMSS_SHA2_512_W16_H20; }
   if(param_set == "XMSS_SHAKE128_W16_H10")
      { return XMSS_SHAKE128_W16_H10; }
   if(param_set == "XMSS_SHAKE128_W16_H16")
      { return XMSS_SHAKE128_W16_H16; }
   if(param_set == "XMSS_SHAKE128_W16_H20")
      { return XMSS_SHAKE128_W16_H20; }
   if(param_set == "XMSS_SHAKE256_W16_H10")
      { return XMSS_SHAKE256_W16_H10; }
   if(param_set == "XMSS_SHAKE256_W16_H16")
      { return XMSS_SHAKE256_W16_H16; }
   if(param_set == "XMSS_SHAKE256_W16_H20")
      { return XMSS_SHAKE256_W16_H20; }
   throw Lookup_Error("Unknown XMSS algorithm param '" + param_set + "'");
   }

XMSS_Parameters::XMSS_Parameters(const std::string& param_set)
   : XMSS_Parameters(XMSS_Parameters::xmss_id_from_string(param_set))
   {
   }

XMSS_Parameters::XMSS_Parameters(xmss_algorithm_t oid)
   : m_oid(oid)
   {
   switch(oid)
      {
      case XMSS_SHA2_256_W16_H10:
         m_element_size = 32;
         m_w = 16;
         m_len = 67;
         m_tree_height = 10;
         m_name = "XMSS_SHA2-256_W16_H10";
         m_hash_name = "SHA-256";
         m_strength = 256;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHA2_256_W16;
         break;
      case XMSS_SHA2_256_W16_H16:
         m_element_size = 32;
         m_w = 16;
         m_len = 67;
         m_tree_height = 16;
         m_name = "XMSS_SHA2-256_W16_H16";
         m_hash_name = "SHA-256";
         m_strength = 256;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHA2_256_W16;
         break;
      case XMSS_SHA2_256_W16_H20:
         m_element_size = 32;
         m_w = 16;
         m_len = 67;
         m_tree_height = 20;
         m_name = "XMSS_SHA2-256_W16_H20";
         m_hash_name = "SHA-256";
         m_strength = 256;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHA2_256_W16;
         break;
      case XMSS_SHA2_512_W16_H10:
         m_element_size = 64;
         m_w = 16;
         m_len = 131;
         m_tree_height = 10;
         m_name = "XMSS_SHA2-512_W16_H10";
         m_hash_name = "SHA-512";
         m_strength = 512;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHA2_512_W16;
         break;
      case XMSS_SHA2_512_W16_H16:
         m_element_size = 64;
         m_w = 16;
         m_len = 131;
         m_tree_height = 16;
         m_name = "XMSS_SHA2-512_W16_H16";
         m_hash_name = "SHA-512";
         m_strength = 512;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHA2_512_W16;
         break;
      case XMSS_SHA2_512_W16_H20:
         m_element_size = 64;
         m_w = 16;
         m_len = 131;
         m_tree_height = 20;
         m_name = "XMSS_SHA2-512_W16_H20";
         m_hash_name = "SHA-512";
         m_strength = 512;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHA2_512_W16;
         break;
      case XMSS_SHAKE128_W16_H10:
         m_element_size = 32;
         m_w = 16;
         m_len = 67;
         m_tree_height = 10;
         m_name = "XMSS_SHAKE128_W16_H10";
         m_hash_name = "SHAKE-128(256)";
         m_strength = 256;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHAKE128_W16;
         break;
      case XMSS_SHAKE128_W16_H16:
         m_element_size = 32;
         m_w = 16;
         m_len = 67;
         m_tree_height = 16;
         m_name = "XMSS_SHAKE128_W16_H16";
         m_hash_name = "SHAKE-128(256)";
         m_strength = 256;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHAKE128_W16;
         break;
      case XMSS_SHAKE128_W16_H20:
         m_element_size = 32;
         m_w = 16;
         m_len = 67;
         m_tree_height = 20;
         m_name = "XMSS_SHAKE128_W16_H20";
         m_hash_name = "SHAKE-128(256)";
         m_strength = 256;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHAKE128_W16;
         break;
      case XMSS_SHAKE256_W16_H10:
         m_element_size = 64;
         m_w = 16;
         m_len = 131;
         m_tree_height = 10;
         m_name = "XMSS_SHAKE256_W16_H10";
         m_hash_name = "SHAKE-256(512)";
         m_strength = 512;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHAKE256_W16;
         break;
      case XMSS_SHAKE256_W16_H16:
         m_element_size = 64;
         m_w = 16;
         m_len = 131;
         m_tree_height = 16;
         m_name = "XMSS_SHAKE256_W16_H16";
         m_hash_name = "SHAKE-256(512)";
         m_strength = 512;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHAKE256_W16;
         break;
      case XMSS_SHAKE256_W16_H20:
         m_element_size = 64;
         m_w = 16;
         m_len = 131;
         m_tree_height = 20;
         m_name = "XMSS_SHAKE256_W16_H20";
         m_hash_name = "SHAKE-256(512)";
         m_strength = 512;
         m_wots_oid = XMSS_WOTS_Parameters::ots_algorithm_t::WOTSP_SHAKE256_W16;
         break;
      default:
         throw Not_Implemented("Algorithm id does not match any known XMSS algorithm id.");
         break;
      }
   }

}
/*
 * XMSS Private Key
 * An XMSS: Extended Hash-Based Siganture private key.
 * The XMSS private key does not support the X509 and PKCS7 standard. Instead
 * the raw format described in [1] is used.
 *
 *   [1] XMSS: Extended Hash-Based Signatures,
 *       draft-itrf-cfrg-xmss-hash-based-signatures-06
 *       Release: July 2016.
 *       https://datatracker.ietf.org/doc/
 *       draft-irtf-cfrg-xmss-hash-based-signatures/?include_text=1
 *
 * (C) 2016,2017 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/

#if defined(BOTAN_TARGET_OS_HAS_THREADS)
#endif

namespace Botan {

XMSS_PrivateKey::XMSS_PrivateKey(const secure_vector<uint8_t>& raw_key)
   : XMSS_PublicKey(unlock(raw_key)),
     XMSS_Common_Ops(XMSS_PublicKey::m_xmss_params.oid()),
     m_wots_priv_key(m_wots_params.oid(), m_public_seed),
     m_index_reg(XMSS_Index_Registry::get_instance())
   {
   BOTAN_ASSERT(sizeof(size_t) >= std::ceil(
      static_cast<float>(XMSS_PublicKey::m_xmss_params.tree_height()) / 8.f),
      "System type \"size_t\" not big enough to support"
      " leaf index.");

   if(raw_key.size() != size())
      {
      throw Decoding_Error("Invalid XMSS private key size detected.");
      }

   // extract & copy unused leaf index from raw_key.
   uint64_t unused_leaf = 0;
   auto begin = (raw_key.begin() + XMSS_PublicKey::size());
   auto end = raw_key.begin() + XMSS_PublicKey::size() + sizeof(uint64_t);

   for(auto& i = begin; i != end; i++)
      {
      unused_leaf = ((unused_leaf << 8) | *i);
      }

   if(unused_leaf >= (1ull << XMSS_PublicKey::m_xmss_params.tree_height()))
      {
      throw Decoding_Error("XMSS private key leaf index out of bounds");
      }

   begin = end;
   end = begin + XMSS_PublicKey::m_xmss_params.element_size();
   m_prf.clear();
   m_prf.reserve(XMSS_PublicKey::m_xmss_params.element_size());
   std::copy(begin, end, std::back_inserter(m_prf));

   begin = end;
   end = begin + m_wots_params.element_size();
   m_wots_priv_key.set_private_seed(secure_vector<uint8_t>(begin, end));
   set_unused_leaf_index(static_cast<size_t>(unused_leaf));
   }

XMSS_PrivateKey::XMSS_PrivateKey(
   XMSS_Parameters::xmss_algorithm_t xmss_algo_id,
   RandomNumberGenerator& rng)
   : XMSS_PublicKey(xmss_algo_id, rng),
     XMSS_Common_Ops(xmss_algo_id),
     m_wots_priv_key(XMSS_PublicKey::m_xmss_params.ots_oid(),
                     public_seed(),
                     rng),
     m_prf(rng.random_vec(XMSS_PublicKey::m_xmss_params.element_size())),
     m_index_reg(XMSS_Index_Registry::get_instance())
   {
   XMSS_Address adrs;
   set_root(tree_hash(0,
                      XMSS_PublicKey::m_xmss_params.tree_height(),
                      adrs));
   }

secure_vector<uint8_t>
XMSS_PrivateKey::tree_hash(size_t start_idx,
                           size_t target_node_height,
                           XMSS_Address& adrs)
   {
   BOTAN_ASSERT((start_idx % (1 << target_node_height)) == 0,
                "Start index must be divisible by 2^{target node height}.");

#if defined(BOTAN_TARGET_OS_HAS_THREADS)
   // dertermine number of parallel tasks to split the tree_hashing into.
   size_t split_level = std::min(
      {
      target_node_height,
      static_cast<size_t>(
         std::ceil(std::log2(XMSS_Tools::max_threads())))
      });

   // skip parallelization overhead for leaf nodes.
   if(split_level == 0)
      {
#endif
      secure_vector<uint8_t> result;
      tree_hash_subtree(result, start_idx, target_node_height, adrs);
      return result;
#if defined(BOTAN_TARGET_OS_HAS_THREADS)
      }

   const size_t subtrees = static_cast<size_t>(1) << split_level;
   const size_t last_idx = (static_cast<size_t>(1) << (target_node_height)) + start_idx;
   const size_t offs = (last_idx - start_idx) / subtrees;
   uint8_t level = split_level; // current level in the tree

   BOTAN_ASSERT((last_idx - start_idx) % subtrees == 0,
                "Number of worker threads in tree_hash need to divide range "
                "of calculated nodes.");

   std::vector<secure_vector<uint8_t>> nodes(
       subtrees,
       secure_vector<uint8_t>(XMSS_PublicKey::m_xmss_params.element_size()));
   std::vector<XMSS_Address> node_addresses(subtrees, adrs);
   std::vector<XMSS_Hash> xmss_hash(subtrees, m_hash);
   std::vector<std::thread> threads;
   threads.reserve(subtrees);

   // Calculate multiple subtrees in parallel.
   for(size_t i = 0; i < subtrees; i++)
      {
      using tree_hash_subtree_fn_t =
         void (XMSS_PrivateKey::*)(secure_vector<uint8_t>&,
                                   size_t,
                                   size_t,
                                   XMSS_Address&,
                                   XMSS_Hash&);

      threads.emplace_back(
         std::thread(
            static_cast<tree_hash_subtree_fn_t>(
               &XMSS_PrivateKey::tree_hash_subtree),
            this,
            std::ref(nodes[i]),
            start_idx + i * offs,
            target_node_height - split_level,
            std::ref(node_addresses[i]),
            std::ref(xmss_hash[i])));
      }

   for(auto& t : threads)
      {
      t.join();
      }

   threads.clear();

   // Parallelize the top tree levels horizontally
   while(level-- > 1)
      {
      std::vector<secure_vector<uint8_t>> ro_nodes(
         nodes.begin(), nodes.begin() + (1 << (level+1)));

      for(size_t i = 0; i < (1U << level); i++)
         {
         node_addresses[i].set_tree_height(target_node_height - (level + 1));
         node_addresses[i].set_tree_index(
            (node_addresses[2 * i + 1].get_tree_index() - 1) >> 1);
         using rnd_tree_hash_fn_t =
            void (XMSS_PrivateKey::*)(secure_vector<uint8_t>&,
                                      const secure_vector<uint8_t>&,
                                      const secure_vector<uint8_t>&,
                                      XMSS_Address& adrs,
                                      const secure_vector<uint8_t>&,
                                      XMSS_Hash&);

         threads.emplace_back(
            std::thread(
               static_cast<rnd_tree_hash_fn_t>(
                  &XMSS_PrivateKey::randomize_tree_hash),
               this,
               std::ref(nodes[i]),
               std::ref(ro_nodes[2 * i]),
               std::ref(ro_nodes[2 * i + 1]),
               std::ref(node_addresses[i]),
               std::ref(this->public_seed()),
               std::ref(xmss_hash[i])));
         }
      for(auto &t : threads)
         {
         t.join();
         }
      threads.clear();
      }

   // Avoid creation an extra thread to calculate root node.
   node_addresses[0].set_tree_height(target_node_height - 1);
   node_addresses[0].set_tree_index(
      (node_addresses[1].get_tree_index() - 1) >> 1);
   randomize_tree_hash(nodes[0],
                       nodes[0],
                       nodes[1],
                       node_addresses[0],
                       this->public_seed());
   return nodes[0];
#endif
   }

void
XMSS_PrivateKey::tree_hash_subtree(secure_vector<uint8_t>& result,
                                   size_t start_idx,
                                   size_t target_node_height,
                                   XMSS_Address& adrs,
                                   XMSS_Hash& hash)
   {
   const secure_vector<uint8_t>& seed = this->public_seed();

   std::vector<secure_vector<uint8_t>> nodes(
      target_node_height + 1,
      secure_vector<uint8_t>(XMSS_PublicKey::m_xmss_params.element_size()));

   // node stack, holds all nodes on stack and one extra "pending" node. This
   // temporary node referred to as "node" in the XMSS standard document stays
   // a pending element, meaning it is not regarded as element on the stack
   // until level is increased.
   std::vector<uint8_t> node_levels(target_node_height + 1);

   uint8_t level = 0; // current level on the node stack.
   XMSS_WOTS_PublicKey pk(m_wots_priv_key.wots_parameters().oid(), seed);
   const size_t last_idx = (static_cast<size_t>(1) << target_node_height) + start_idx;

   for(size_t i = start_idx; i < last_idx; i++)
      {
      adrs.set_type(XMSS_Address::Type::OTS_Hash_Address);
      adrs.set_ots_address(i);
      this->wots_private_key().generate_public_key(
         pk,
         // getWOTS_SK(SK, s + i), reference implementation uses adrs
         // instead of zero padded index s + i.
         this->wots_private_key().at(adrs, hash),
         adrs,
         hash);
      adrs.set_type(XMSS_Address::Type::LTree_Address);
      adrs.set_ltree_address(i);
      create_l_tree(nodes[level], pk, adrs, seed, hash);
      node_levels[level] = 0;

      adrs.set_type(XMSS_Address::Type::Hash_Tree_Address);
      adrs.set_tree_height(0);
      adrs.set_tree_index(i);

      while(level > 0 && node_levels[level] ==
            node_levels[level - 1])
         {
         adrs.set_tree_index(((adrs.get_tree_index() - 1) >> 1));
         randomize_tree_hash(nodes[level - 1],
                             nodes[level - 1],
                             nodes[level],
                             adrs,
                             seed,
                             hash);
         node_levels[level - 1]++;
         level--; //Pop stack top element
         adrs.set_tree_height(adrs.get_tree_height() + 1);
         }
      level++; //push temporary node to stack
      }
   result = nodes[level - 1];
   }

std::shared_ptr<Atomic<size_t>>
XMSS_PrivateKey::recover_global_leaf_index() const
   {
   BOTAN_ASSERT(m_wots_priv_key.private_seed().size() ==
                XMSS_PublicKey::m_xmss_params.element_size() &&
                m_prf.size() == XMSS_PublicKey::m_xmss_params.element_size(),
                "Trying to retrieve index for partially initialized "
                "key.");
   return m_index_reg.get(m_wots_priv_key.private_seed(),
                          m_prf);
   }

secure_vector<uint8_t> XMSS_PrivateKey::raw_private_key() const
   {
   std::vector<uint8_t> pk { raw_public_key() };
   secure_vector<uint8_t> result(pk.begin(), pk.end());
   result.reserve(size());

   for(int i = 7; i >= 0; i--)
      {
      result.push_back(
         static_cast<uint8_t>(
            static_cast<uint64_t>(unused_leaf_index()) >> 8 * i));
      }

   std::copy(m_prf.begin(), m_prf.end(), std::back_inserter(result));
   std::copy(m_wots_priv_key.private_seed().begin(),
             m_wots_priv_key.private_seed().end(),
             std::back_inserter(result));

   return result;
   }

std::unique_ptr<PK_Ops::Signature>
XMSS_PrivateKey::create_signature_op(RandomNumberGenerator&,
                                     const std::string&,
                                     const std::string& provider) const
   {
   if(provider == "base" || provider.empty())
      return std::unique_ptr<PK_Ops::Signature>(
         new XMSS_Signature_Operation(*this));

   throw Provider_Not_Found(algo_name(), provider);
   }

}
/*
 * XMSS Public Key
 * An XMSS: Extended Hash-Based Siganture public key.
 * The XMSS public key does not support the X509 standard. Instead the
 * raw format described in [1] is used.
 *
 *   [1] XMSS: Extended Hash-Based Signatures,
 *       draft-itrf-cfrg-xmss-hash-based-signatures-06
 *       Release: July 2016.
 *       https://datatracker.ietf.org/doc/
 *       draft-irtf-cfrg-xmss-hash-based-signatures/?include_text=1
 *
 * (C) 2016,2017 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

XMSS_PublicKey::XMSS_PublicKey(const std::vector<uint8_t>& raw_key)
   : m_xmss_params(XMSS_PublicKey::deserialize_xmss_oid(raw_key)),
     m_wots_params(m_xmss_params.ots_oid())
   {
   if(raw_key.size() < size())
      {
      throw Decoding_Error("Invalid XMSS public key size detected.");
      }

   // extract & copy root from raw key.
   m_root.clear();
   m_root.reserve(m_xmss_params.element_size());
   auto begin = raw_key.begin() + sizeof(uint32_t);
   auto end = begin + m_xmss_params.element_size();
   std::copy(begin, end, std::back_inserter(m_root));

   // extract & copy public seed from raw key.
   begin = end;
   end = begin + m_xmss_params.element_size();
   m_public_seed.clear();
   m_public_seed.reserve(m_xmss_params.element_size());
   std::copy(begin, end, std::back_inserter(m_public_seed));
   }

XMSS_Parameters::xmss_algorithm_t
XMSS_PublicKey::deserialize_xmss_oid(const std::vector<uint8_t>& raw_key)
   {
   if(raw_key.size() < 4)
      {
      throw Decoding_Error("XMSS signature OID missing.");
      }

   // extract and convert algorithm id to enum type
   uint32_t raw_id = 0;
   for(size_t i = 0; i < 4; i++)
      { raw_id = ((raw_id << 8) | raw_key[i]); }

   return static_cast<XMSS_Parameters::xmss_algorithm_t>(raw_id);
   }

std::unique_ptr<PK_Ops::Verification>
XMSS_PublicKey::create_verification_op(const std::string&,
                                       const std::string& provider) const
   {
   if(provider == "base" || provider.empty())
      {
      return std::unique_ptr<PK_Ops::Verification>(
                new XMSS_Verification_Operation(*this));
      }
   throw Provider_Not_Found(algo_name(), provider);
   }

std::vector<uint8_t> XMSS_PublicKey::raw_public_key() const
   {
   std::vector<uint8_t> result
      {
      static_cast<uint8_t>(m_xmss_params.oid() >> 24),
      static_cast<uint8_t>(m_xmss_params.oid() >> 16),
      static_cast<uint8_t>(m_xmss_params.oid() >>  8),
      static_cast<uint8_t>(m_xmss_params.oid())
      };

   std::copy(m_root.begin(), m_root.end(), std::back_inserter(result));
   std::copy(m_public_seed.begin(),
             m_public_seed.end(),
             std::back_inserter(result));

   return result;
   }

}
/*
 * XMSS Signature
 * (C) 2016,2017,2018 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

XMSS_Signature::XMSS_Signature(XMSS_Parameters::xmss_algorithm_t oid,
                               const secure_vector<uint8_t>& raw_sig)
   : m_leaf_idx(0), m_randomness(0, 0x00), m_tree_sig()
   {
   XMSS_Parameters xmss_params(oid);

   if(raw_sig.size() != (xmss_params.len() + xmss_params.tree_height() + 1)
                        * xmss_params.element_size() + sizeof(m_leaf_idx))
   {
      throw Decoding_Error("XMSS signature size invalid.");
   }

   for(size_t i = 0; i < 8; i++)
      { m_leaf_idx = ((m_leaf_idx << 8) | raw_sig[i]); }

   if(m_leaf_idx >= (1ull << xmss_params.tree_height()))
      {
      throw Decoding_Error("XMSS signature leaf index out of bounds.");
      }

   auto begin = raw_sig.begin() + sizeof(m_leaf_idx);
   auto end = begin + xmss_params.element_size();
   std::copy(begin, end, std::back_inserter(m_randomness));

   for(size_t i = 0; i < xmss_params.len(); i++)
      {
      begin = end;
      end = begin + xmss_params.element_size();
      m_tree_sig.ots_signature().push_back(secure_vector<uint8_t>(0));
      m_tree_sig.ots_signature().back().reserve(
         xmss_params.element_size());
      std::copy(begin,
                end,
                std::back_inserter(m_tree_sig.ots_signature().back()));
      }

   for(size_t i = 0; i < xmss_params.tree_height(); i++)
      {
      begin = end;
      end = begin + xmss_params.element_size();
      m_tree_sig.authentication_path().push_back(secure_vector<uint8_t>(0));
      m_tree_sig.authentication_path().back().reserve(
         xmss_params.element_size());
      std::copy(begin,
                end,
                std::back_inserter(m_tree_sig.authentication_path().back()));
      }
   }

secure_vector<uint8_t> XMSS_Signature::bytes() const
   {
   secure_vector<uint8_t> result
      {
      static_cast<uint8_t>(m_leaf_idx >> 56U),
      static_cast<uint8_t>(m_leaf_idx >> 48U),
      static_cast<uint8_t>(m_leaf_idx >> 40U),
      static_cast<uint8_t>(m_leaf_idx >> 32U),
      static_cast<uint8_t>(m_leaf_idx >> 24U),
      static_cast<uint8_t>(m_leaf_idx >> 16U),
      static_cast<uint8_t>(m_leaf_idx >>  8U),
      static_cast<uint8_t>(m_leaf_idx)
      };

   std::copy(m_randomness.begin(),
             m_randomness.end(),
             std::back_inserter(result));

   for(const auto& sig : tree().ots_signature())
      {
      std::copy(sig.begin(),
                sig.end(),
                std::back_inserter(result));
      }

   for(const auto& auth : tree().authentication_path())
      {
      std::copy(auth.begin(),
                auth.end(),
                std::back_inserter(result));
      }
   return result;
   }

}
/*
 * XMSS Signature Operation
 * Signature generation operation for Extended Hash-Based Signatures (XMSS) as
 * defined in:
 *
 * [1] XMSS: Extended Hash-Based Signatures,
 *     draft-itrf-cfrg-xmss-hash-based-signatures-06
 *     Release: July 2016.
 *     https://datatracker.ietf.org/doc/
 *     draft-irtf-cfrg-xmss-hash-based-signatures/?include_text=1
 *
 * (C) 2016,2017 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

XMSS_Signature_Operation::XMSS_Signature_Operation(
   const XMSS_PrivateKey& private_key)
   : XMSS_Common_Ops(private_key.xmss_oid()),
     m_priv_key(private_key),
     m_randomness(0),
     m_leaf_idx(0),
     m_is_initialized(false)
   {}

XMSS_WOTS_PublicKey::TreeSignature
XMSS_Signature_Operation::generate_tree_signature(const secure_vector<uint8_t>& msg,
      XMSS_PrivateKey& xmss_priv_key,
      XMSS_Address& adrs)
   {

   wots_keysig_t auth_path = build_auth_path(xmss_priv_key, adrs);
   adrs.set_type(XMSS_Address::Type::OTS_Hash_Address);
   adrs.set_ots_address(m_leaf_idx);

   wots_keysig_t sig_ots = xmss_priv_key.wots_private_key().sign(msg, adrs);
   return XMSS_WOTS_PublicKey::TreeSignature(sig_ots, auth_path);
   }

XMSS_Signature
XMSS_Signature_Operation::sign(const secure_vector<uint8_t>& msg_hash,
                               XMSS_PrivateKey& xmss_priv_key)
   {
   XMSS_Address adrs;
   XMSS_Signature sig(m_leaf_idx,
                      m_randomness,
                      generate_tree_signature(msg_hash, xmss_priv_key,adrs));
   return sig;
   }

size_t XMSS_Signature_Operation::signature_length() const
   {
   return sizeof(uint64_t) + // size of leaf index
          m_xmss_params.element_size() +
          m_xmss_params.len() * m_xmss_params.element_size() +
          m_xmss_params.tree_height() * m_xmss_params.element_size();
   }

wots_keysig_t
XMSS_Signature_Operation::build_auth_path(XMSS_PrivateKey& priv_key,
      XMSS_Address& adrs)
   {
   wots_keysig_t auth_path(m_xmss_params.tree_height());
   adrs.set_type(XMSS_Address::Type::Hash_Tree_Address);

   for(size_t j = 0; j < m_xmss_params.tree_height(); j++)
      {
      size_t k = (m_leaf_idx / (1ULL << j)) ^ 0x01;
      auth_path[j] = priv_key.tree_hash(k * (1ULL << j), j, adrs);
      }

   return auth_path;
   }

void XMSS_Signature_Operation::update(const uint8_t msg[], size_t msg_len)
   {
   initialize();
   m_hash.h_msg_update(msg, msg_len);
   }

secure_vector<uint8_t>
XMSS_Signature_Operation::sign(RandomNumberGenerator&)
   {
   initialize();
   secure_vector<uint8_t> signature(sign(m_hash.h_msg_final(),
                                         m_priv_key).bytes());
   m_is_initialized = false;
   return signature;
   }

void XMSS_Signature_Operation::initialize()
   {
   // return if we already initialized and reserved a leaf index for signing.
   if(m_is_initialized)
      { return; }

   secure_vector<uint8_t> index_bytes;
   // reserve leaf index so it can not be reused in by another signature
   // operation using the same private key.
   m_leaf_idx = m_priv_key.reserve_unused_leaf_index();

   // write prefix for message hashing into buffer.
   XMSS_Tools::concat(index_bytes, m_leaf_idx, 32);
   m_randomness = m_hash.prf(m_priv_key.prf(), index_bytes);
   index_bytes.clear();
   XMSS_Tools::concat(index_bytes, m_leaf_idx,
                      m_priv_key.xmss_parameters().element_size());
   m_hash.h_msg_init(m_randomness,
                     m_priv_key.root(),
                     index_bytes);
   m_is_initialized = true;
   }

}

/*
 * XMSS Tools
 * (C) 2017 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

#if defined(BOTAN_TARGET_OS_HAS_THREADS)

size_t XMSS_Tools::max_threads()
   {
   static const size_t threads { bench_threads() };
   return threads;
   }

size_t XMSS_Tools::bench_threads()
   {
   const size_t hardware_concurrency = std::thread::hardware_concurrency();

   if(hardware_concurrency <= 1)
      {
      return 1;
      }
   const size_t BENCH_ITERATIONS = 1000;
   std::vector<std::thread> threads;
   threads.reserve(hardware_concurrency);
   std::vector<std::chrono::nanoseconds> durations;

   std::vector<size_t> concurrency { hardware_concurrency,
                                     hardware_concurrency / 2 };

   for(const auto& cc : concurrency)
      {
      std::vector<XMSS_Hash> hash(hardware_concurrency,
                                  XMSS_Hash("SHA-256"));

      const std::vector<uint8_t> buffer(hash[0].output_length());
      std::vector<secure_vector<uint8_t>> data(
          hardware_concurrency,
          secure_vector<uint8_t>(hash[0].output_length()));
      auto start = std::chrono::high_resolution_clock::now();
      for(size_t i = 0; i < cc; ++i)
         {
         auto& hs = hash[i];
         auto& d = data[i];

         const size_t n_iters = BENCH_ITERATIONS * (hardware_concurrency / cc);
         threads.emplace_back(std::thread([n_iters, &hs, &d]()
               {
               for(size_t n = 0; n < n_iters; n++)
                  {
                  hs.h(d, d, d);
                  }
               }
            ));
         }
      durations.emplace_back(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start));
      for(auto& t : threads)
         {
         t.join();
         }
      threads.clear();
      }

      if(durations[0].count() < durations[1].count())
         {
#if defined(BOTAN_TEST_MODE)
         return 4;
#else
         return concurrency[0];
#endif
         }
      else
         {
#if defined(BOTAN_TEST_MODE)
         return 4;
#else
         return concurrency[1];
#endif
         }
  }

#endif

}

/*
 * XMSS Verification Operation
 * Provides signature verification capabilities for Extended Hash-Based
 * Signatures (XMSS).
 *
 * (C) 2016,2017 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

XMSS_Verification_Operation::XMSS_Verification_Operation(
   const XMSS_PublicKey& public_key)
   : XMSS_Common_Ops(public_key.xmss_oid()),
     m_pub_key(public_key),
     m_msg_buf(0)
   {
   }

secure_vector<uint8_t>
XMSS_Verification_Operation::root_from_signature(const XMSS_Signature& sig,
      const secure_vector<uint8_t>& msg,
      XMSS_Address& adrs,
      const secure_vector<uint8_t>& seed)
   {
   adrs.set_type(XMSS_Address::Type::OTS_Hash_Address);
   adrs.set_ots_address(sig.unused_leaf_index());

   XMSS_WOTS_PublicKey pub_key_ots(m_pub_key.wots_parameters().oid(),
                                   msg,
                                   sig.tree().ots_signature(),
                                   adrs,
                                   seed);

   adrs.set_type(XMSS_Address::Type::LTree_Address);
   adrs.set_ltree_address(sig.unused_leaf_index());

   std::array<secure_vector<uint8_t>, 2> node;
   create_l_tree(node[0], pub_key_ots, adrs, seed);

   adrs.set_type(XMSS_Address::Type::Hash_Tree_Address);
   adrs.set_tree_index(sig.unused_leaf_index());

   for(size_t k = 0; k < m_xmss_params.tree_height(); k++)
      {
      adrs.set_tree_height(k);
      if(((sig.unused_leaf_index() / (1 << k)) & 0x01) == 0)
         {
         adrs.set_tree_index(adrs.get_tree_index() >> 1);
         randomize_tree_hash(node[1],
                             node[0],
                             sig.tree().authentication_path()[k],
                             adrs,
                             seed);
         }
      else
         {
         adrs.set_tree_index((adrs.get_tree_index() - 1) >> 1);
         randomize_tree_hash(node[1],
                             sig.tree().authentication_path()[k],
                             node[0],
                             adrs,
                             seed);
         }
      node[0] = node[1];
      }
   return node[0];
   }

bool
XMSS_Verification_Operation::verify(const XMSS_Signature& sig,
                                    const secure_vector<uint8_t>& msg,
                                    const XMSS_PublicKey& public_key)
   {
   XMSS_Address adrs;
   secure_vector<uint8_t> index_bytes;
   XMSS_Tools::concat(index_bytes,
                      sig.unused_leaf_index(),
                      m_xmss_params.element_size());
   secure_vector<uint8_t> msg_digest =
      m_hash.h_msg(sig.randomness(),
                   public_key.root(),
                   index_bytes,
                   msg);

   secure_vector<uint8_t> node = root_from_signature(sig,
                                 msg_digest,
                                 adrs,
                                 public_key.public_seed());

   return (node == public_key.root());
   }

// FIXME: XMSS signature verification requires the "randomness" parameter out
// of the XMSS signature, which is part of the prefix that is hashed before
// msg. Since the signature is unknown till sign() is called all message
// content has to be buffered. For large messages this can be inconvenient or
// impossible.
// Possible solution: Change PK_Ops::Verification interface to take the
// signature as constructor argument, make sign a parameterless member call.
void XMSS_Verification_Operation::update(const uint8_t msg[], size_t msg_len)
   {
   std::copy(msg, msg + msg_len, std::back_inserter(m_msg_buf));
   }

bool XMSS_Verification_Operation::is_valid_signature(const uint8_t sig[],
      size_t sig_len)
   {
   try
      {
      XMSS_Signature signature(m_pub_key.xmss_parameters().oid(),
                               secure_vector<uint8_t>(sig, sig + sig_len));
      bool result = verify(signature, m_msg_buf, m_pub_key);
      m_msg_buf.clear();
      return result;
      }
   catch(...)
      {
      m_msg_buf.clear();
      return false;
      }
   }

}

/*
 * XMSS WOTS Parameters
 * Descibes a signature method for XMSS Winternitz One Time Signatures,
 * as defined in:
 * [1] XMSS: Extended Hash-Based Signatures,
 *     draft-itrf-cfrg-xmss-hash-based-signatures-06
 *     Release: July 2016.
 *     https://datatracker.ietf.org/doc/
 *     draft-irtf-cfrg-xmss-hash-based-signatures/?include_text=1
 *
 * (C) 2016,2017 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

XMSS_WOTS_Parameters::ots_algorithm_t
XMSS_WOTS_Parameters::xmss_wots_id_from_string(const std::string& param_set)
   {
   if(param_set == "WOTSP_SHA2-256_W16")
      { return WOTSP_SHA2_256_W16; }
   if(param_set == "WOTSP_SHA2-512_W16")
      { return WOTSP_SHA2_512_W16; }
   if(param_set == "WOTSP_SHAKE128_W16")
      { return WOTSP_SHAKE128_W16; }
   if(param_set == "WOTSP_SHAKE256_W16")
      { return WOTSP_SHAKE256_W16; }
   throw Invalid_Argument("Unknown XMSS-WOTS algorithm param '" + param_set + "'");
   }

XMSS_WOTS_Parameters::XMSS_WOTS_Parameters(const std::string& param_set)
   : XMSS_WOTS_Parameters(xmss_wots_id_from_string(param_set))
   {}

XMSS_WOTS_Parameters::XMSS_WOTS_Parameters(ots_algorithm_t oid)
   : m_oid(oid)
   {
   switch(oid)
      {
      case WOTSP_SHA2_256_W16:
         m_element_size = 32;
         m_w = 16;
         m_len = 67;
         m_name = "WOTSP_SHA2-256_W16";
         m_hash_name = "SHA-256";
         m_strength = 256;
         break;
      case WOTSP_SHA2_512_W16:
         m_element_size = 64;
         m_w = 16;
         m_len = 131;
         m_name = "WOTSP_SHA2-512_W16";
         m_hash_name = "SHA-512";
         m_strength = 512;
         break;
      case WOTSP_SHAKE128_W16:
         m_element_size = 32;
         m_w = 16;
         m_len = 67;
         m_name = "WOTSP_SHAKE128_W16";
         m_hash_name = "SHAKE-128(256)";
         m_strength = 256;
         break;
      case WOTSP_SHAKE256_W16:
         m_element_size = 64;
         m_w = 16;
         m_len = 131;
         m_name = "WOTSP_SHAKE256_W16";
         m_hash_name = "SHAKE-256(512)";
         m_strength = 512;
         break;
      default:
         throw Not_Implemented("Algorithm id does not match any known XMSS WOTS algorithm id.");
         break;
      }

   m_lg_w = (m_w == 16) ? 4 : 2;
   m_len_1 = static_cast<size_t>(std::ceil((8 * element_size()) / m_lg_w));
   m_len_2 = static_cast<size_t>(
                floor(log2(m_len_1 * (wots_parameter() - 1)) / m_lg_w) + 1);
   BOTAN_ASSERT(m_len == m_len_1 + m_len_2, "Invalid XMSS WOTS parameter "
                "\"len\" detedted.");
   }

secure_vector<uint8_t>
XMSS_WOTS_Parameters::base_w(const secure_vector<uint8_t>& msg, size_t out_size) const
   {
   secure_vector<uint8_t> result;
   size_t in = 0;
   size_t total = 0;
   size_t bits = 0;

   for(size_t i = 0; i < out_size; i++)
      {
      if(bits == 0)
         {
         total = msg[in];
         in++;
         bits += 8;
         }
      bits -= m_lg_w;
      result.push_back(static_cast<uint8_t>((total >> bits) & (m_w - 1)));
      }
   return result;
   }

secure_vector<uint8_t>
XMSS_WOTS_Parameters::base_w(size_t value) const
   {
   value <<= (8 - ((m_len_2 * m_lg_w) % 8));
   size_t len_2_bytes = static_cast<size_t>(
                           std::ceil(static_cast<float>(m_len_2 * m_lg_w) / 8.f));
   secure_vector<uint8_t> result;
   XMSS_Tools::concat(result, value, len_2_bytes);
   return base_w(result, m_len_2);
   }

void
XMSS_WOTS_Parameters::append_checksum(secure_vector<uint8_t>& data)
   {
   size_t csum = 0;

   for(size_t i = 0; i < data.size(); i++)
      {
      csum += wots_parameter() - 1 - data[i];
      }

   secure_vector<uint8_t> csum_bytes = base_w(csum);
   std::move(csum_bytes.begin(), csum_bytes.end(), std::back_inserter(data));
   }

}
/*
 * XMSS WOTS Private Key
 * A Winternitz One Time Signature private key for use with Extended Hash-Based
 * Signatures.
 *
 * (C) 2016,2017 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

wots_keysig_t
XMSS_WOTS_PrivateKey::generate(const secure_vector<uint8_t>& priv_seed,
                               XMSS_Hash& hash)
   {
   wots_keysig_t priv_key(m_wots_params.len(),
                          secure_vector<uint8_t>(0));

   for(size_t i = 0; i < m_wots_params.len(); i++)
      {
      XMSS_Tools::concat<size_t>(priv_key[i], i, 32);
      hash.prf(priv_key[i], priv_seed, priv_key[i]);
      }
   return priv_key;
   }


XMSS_WOTS_PublicKey
XMSS_WOTS_PrivateKey::generate_public_key(XMSS_Address& adrs)
   {
   XMSS_WOTS_PublicKey pub_key(m_wots_params.oid(),
                               public_seed());
   generate_public_key(pub_key, wots_keysig_t((*this)[adrs]), adrs);
   return pub_key;
   }

void
XMSS_WOTS_PrivateKey::generate_public_key(XMSS_WOTS_PublicKey& pub_key,
                                          wots_keysig_t&& in_key_data,
                                          XMSS_Address& adrs,
                                          XMSS_Hash& hash)
   {
   BOTAN_ASSERT(wots_parameters() == pub_key.wots_parameters() &&
                public_seed() == pub_key.public_seed(),
                "Conflicting public key data.");

   pub_key.set_key_data(std::move(in_key_data));
   for(size_t i = 0; i < m_wots_params.len(); i++)
      {
      adrs.set_chain_address(i);
      chain(pub_key[i], 0, m_wots_params.wots_parameter() - 1, adrs,
            public_seed(), hash);
      }
   }

wots_keysig_t
XMSS_WOTS_PrivateKey::sign(const secure_vector<uint8_t>& msg,
                           XMSS_Address& adrs,
                           XMSS_Hash& hash)

   {
   secure_vector<uint8_t> msg_digest
      {
      m_wots_params.base_w(msg, m_wots_params.len_1())
      };

   m_wots_params.append_checksum(msg_digest);
   wots_keysig_t sig(this->at(adrs, hash));

   for(size_t i = 0; i < m_wots_params.len(); i++)
      {
      adrs.set_chain_address(i);
      chain(sig[i], 0 , msg_digest[i], adrs, m_public_seed, hash);
      }

   return sig;
   }

}
/*
 * XMSS WOTS Public Key
 * A Winternitz One Time Signature public key for use with Extended Hash-Based
 * Signatures.
 *
 * (C) 2016,2017 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


namespace Botan {

void
XMSS_WOTS_PublicKey::chain(secure_vector<uint8_t>& result,
                           size_t start_idx,
                           size_t steps,
                           XMSS_Address& adrs,
                           const secure_vector<uint8_t>& seed,
                           XMSS_Hash& hash)
   {
   secure_vector<uint8_t> prf_output(hash.output_length());

   for(size_t i = start_idx;
         i < (start_idx + steps) && i < m_wots_params.wots_parameter();
         i++)
      {
      adrs.set_hash_address(i);

      //Calculate tmp XOR bitmask
      adrs.set_key_mask_mode(XMSS_Address::Key_Mask::Mask_Mode);
      hash.prf(prf_output, seed, adrs.bytes());
      xor_buf(result, prf_output, result.size());

      // Calculate key
      adrs.set_key_mask_mode(XMSS_Address::Key_Mask::Key_Mode);

      //Calculate f(key, tmp XOR bitmask)
      hash.prf(prf_output, seed, adrs.bytes());
      hash.f(result, prf_output, result);
      }
   }

wots_keysig_t
XMSS_WOTS_PublicKey::pub_key_from_signature(const secure_vector<uint8_t>& msg,
                                            const wots_keysig_t& sig,
                                            XMSS_Address& adrs,
                                            const secure_vector<uint8_t>& seed)
   {
   secure_vector<uint8_t> msg_digest
      {
      m_wots_params.base_w(msg, m_wots_params.len_1())
      };

   m_wots_params.append_checksum(msg_digest);
   wots_keysig_t result(sig);

   for(size_t i = 0; i < m_wots_params.len(); i++)
      {
      adrs.set_chain_address(i);
      chain(result[i],
            msg_digest[i],
            m_wots_params.wots_parameter() - 1 - msg_digest[i],
            adrs,
            seed);
      }
   return result;
   }

}
/*
* XTEA
* (C) 1999-2009,2016 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
