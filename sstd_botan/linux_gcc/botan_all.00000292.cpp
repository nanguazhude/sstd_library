
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

extern const uint64_t STREEBOG_Ax[8][256];
extern const uint64_t STREEBOG_C[12][8];

std::unique_ptr<HashFunction> Streebog::copy_state() const
   {
   return std::unique_ptr<HashFunction>(new Streebog(*this));
   }

Streebog::Streebog(size_t output_bits) :
   m_output_bits(output_bits),
   m_count(0),
   m_position(0),
   m_buffer(64),
   m_h(8),
   m_S(8)
   {
   if(output_bits != 256 && output_bits != 512)
      throw Invalid_Argument("Streebog: Invalid output length " +
                             std::to_string(output_bits));

   clear();
   }

std::string Streebog::name() const
   {
   return "Streebog-" + std::to_string(m_output_bits);
   }

/*
* Clear memory of sensitive data
*/
void Streebog::clear()
   {
   m_count = 0;
   m_position = 0;
   zeroise(m_buffer);
   zeroise(m_S);

   const uint64_t fill = (m_output_bits == 512) ? 0 : 0x0101010101010101;
   std::fill(m_h.begin(), m_h.end(), fill);
   }

/*
* Update the hash
*/
void Streebog::add_data(const uint8_t input[], size_t length)
   {
   const size_t block_size = m_buffer.size();

   if(m_position)
      {
      buffer_insert(m_buffer, m_position, input, length);

      if(m_position + length >= block_size)
         {
         compress(m_buffer.data());
         m_count += 512;
         input += (block_size - m_position);
         length -= (block_size - m_position);
         m_position = 0;
         }
      }

   const size_t full_blocks = length / block_size;
   const size_t remaining   = length % block_size;

   for(size_t i = 0; i != full_blocks; ++i)
      {
      compress(input + block_size * i);
      m_count += 512;
      }

   buffer_insert(m_buffer, m_position, input + full_blocks * block_size, remaining);
   m_position += remaining;
   }

/*
* Finalize a hash
*/
void Streebog::final_result(uint8_t output[])
   {
   m_buffer[m_position++] = 0x01;

   if(m_position != m_buffer.size())
      clear_mem(&m_buffer[m_position], m_buffer.size() - m_position);

   compress(m_buffer.data());
   m_count += (m_position - 1) * 8;

   zeroise(m_buffer);
   store_le(m_count, m_buffer.data());
   compress(m_buffer.data(), true);

   compress_64(m_S.data(), true);
   // FIXME
   std::memcpy(output, &m_h[8 - output_length() / 8], output_length());
   clear();
   }

namespace {

inline uint64_t force_le(uint64_t x)
   {
#if defined(BOTAN_TARGET_CPU_IS_LITTLE_ENDIAN)
   return x;
#elif defined(BOTAN_TARGET_CPU_IS_BIG_ENDIAN)
   return reverse_bytes(x);
#else
   store_le(x, reinterpret_cast<uint8_t*>(&x));
   return x;
#endif
   }

inline void lps(uint64_t block[8])
   {
   uint8_t r[64];
   // FIXME
   std::memcpy(r, block, 64);

   for(int i = 0; i < 8; ++i)
      {
      block[i] = force_le(STREEBOG_Ax[0][r[i + 0*8]]) ^
                 force_le(STREEBOG_Ax[1][r[i + 1*8]]) ^
                 force_le(STREEBOG_Ax[2][r[i + 2*8]]) ^
                 force_le(STREEBOG_Ax[3][r[i + 3*8]]) ^
                 force_le(STREEBOG_Ax[4][r[i + 4*8]]) ^
                 force_le(STREEBOG_Ax[5][r[i + 5*8]]) ^
                 force_le(STREEBOG_Ax[6][r[i + 6*8]]) ^
                 force_le(STREEBOG_Ax[7][r[i + 7*8]]);
      }
   }

} //namespace

void Streebog::compress(const uint8_t input[], bool last_block)
   {
   uint64_t M[8];
   std::memcpy(M, input, 64);

   compress_64(M, last_block);
   }

void Streebog::compress_64(const uint64_t M[], bool last_block)
   {
   uint64_t N = force_le(last_block ? 0ULL : m_count);

   uint64_t hN[8];
   uint64_t A[8];

   copy_mem(hN, m_h.data(), 8);
   hN[0] ^= N;
   lps(hN);

   copy_mem(A, hN, 8);

   for(size_t i = 0; i != 8; ++i)
      {
      hN[i] ^= M[i];
      }

   for(size_t i = 0; i < 12; ++i)
      {
      for(size_t j = 0; j != 8; ++j)
         A[j] ^= force_le(STREEBOG_C[i][j]);
      lps(A);

      lps(hN);
      for(size_t j = 0; j != 8; ++j)
         hN[j] ^= A[j];
      }

   for(size_t i = 0; i != 8; ++i)
      {
      m_h[i] ^= hN[i] ^ M[i];
      }

   if(!last_block)
      {
      uint64_t carry = 0;
      for(int i = 0; i < 8; i++)
         {
         const uint64_t m = force_le(M[i]);
         const uint64_t hi = force_le(m_S[i]);
         const uint64_t t = hi + m;

         m_S[i] = force_le(t + carry);
         carry = (t < hi ? 1 : 0) | (t < m ? 1 : 0);
         }
      }
   }

}
/*
 * Derived from:
 * https://github.com/degtyarevalexey/streebog
 *
 * Copyright (c) 2013, Alexey Degtyarev <alexey@renatasystems.org>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


namespace Botan {

extern const uint64_t STREEBOG_Ax[8][256] =
   {
      {
      0xd01f715b5c7ef8e6ULL, 0x16fa240980778325ULL, 0xa8a42e857ee049c8ULL,
      0x6ac1068fa186465bULL, 0x6e417bd7a2e9320bULL, 0x665c8167a437daabULL,
      0x7666681aa89617f6ULL, 0x4b959163700bdcf5ULL, 0xf14be6b78df36248ULL,
      0xc585bd689a625cffULL, 0x9557d7fca67d82cbULL, 0x89f0b969af6dd366ULL,
      0xb0833d48749f6c35ULL, 0xa1998c23b1ecbc7cULL, 0x8d70c431ac02a736ULL,
      0xd6dfbc2fd0a8b69eULL, 0x37aeb3e551fa198bULL, 0x0b7d128a40b5cf9cULL,
      0x5a8f2008b5780cbcULL, 0xedec882284e333e5ULL, 0xd25fc177d3c7c2ceULL,
      0x5e0f5d50b61778ecULL, 0x1d873683c0c24cb9ULL, 0xad040bcbb45d208cULL,
      0x2f89a0285b853c76ULL, 0x5732fff6791b8d58ULL, 0x3e9311439ef6ec3fULL,
      0xc9183a809fd3c00fULL, 0x83adf3f5260a01eeULL, 0xa6791941f4e8ef10ULL,
      0x103ae97d0ca1cd5dULL, 0x2ce948121dee1b4aULL, 0x39738421dbf2bf53ULL,
      0x093da2a6cf0cf5b4ULL, 0xcd9847d89cbcb45fULL, 0xf9561c078b2d8ae8ULL,
      0x9c6a755a6971777fULL, 0xbc1ebaa0712ef0c5ULL, 0x72e61542abf963a6ULL,
      0x78bb5fde229eb12eULL, 0x14ba94250fceb90dULL, 0x844d6697630e5282ULL,
      0x98ea08026a1e032fULL, 0xf06bbea144217f5cULL, 0xdb6263d11ccb377aULL,
      0x641c314b2b8ee083ULL, 0x320e96ab9b4770cfULL, 0x1ee7deb986a96b85ULL,
      0xe96cf57a878c47b5ULL, 0xfdd6615f8842feb8ULL, 0xc83862965601dd1bULL,
      0x2ea9f83e92572162ULL, 0xf876441142ff97fcULL, 0xeb2c455608357d9dULL,
      0x5612a7e0b0c9904cULL, 0x6c01cbfb2d500823ULL, 0x4548a6a7fa037a2dULL,
      0xabc4c6bf388b6ef4ULL, 0xbade77d4fdf8bebdULL, 0x799b07c8eb4cac3aULL,
      0x0c9d87e805b19cf0ULL, 0xcb588aac106afa27ULL, 0xea0c1d40c1e76089ULL,
      0x2869354a1e816f1aULL, 0xff96d17307fbc490ULL, 0x9f0a9d602f1a5043ULL,
      0x96373fc6e016a5f7ULL, 0x5292dab8b3a6e41cULL, 0x9b8ae0382c752413ULL,
      0x4f15ec3b7364a8a5ULL, 0x3fb349555724f12bULL, 0xc7c50d4415db66d7ULL,
      0x92b7429ee379d1a7ULL, 0xd37f99611a15dfdaULL, 0x231427c05e34a086ULL,
      0xa439a96d7b51d538ULL, 0xb403401077f01865ULL, 0xdda2aea5901d7902ULL,
      0x0a5d4a9c8967d288ULL, 0xc265280adf660f93ULL, 0x8bb0094520d4e94eULL,
      0x2a29856691385532ULL, 0x42a833c5bf072941ULL, 0x73c64d54622b7eb2ULL,
      0x07e095624504536cULL, 0x8a905153e906f45aULL, 0x6f6123c16b3b2f1fULL,
      0xc6e55552dc097bc3ULL, 0x4468feb133d16739ULL, 0xe211e7f0c7398829ULL,
      0xa2f96419f7879b40ULL, 0x19074bdbc3ad38e9ULL, 0xf4ebc3f9474e0b0cULL,
      0x43886bd376d53455ULL, 0xd8028beb5aa01046ULL, 0x51f23282f5cdc320ULL,
      0xe7b1c2be0d84e16dULL, 0x081dfab006dee8a0ULL, 0x3b33340d544b857bULL,
      0x7f5bcabc679ae242ULL, 0x0edd37c48a08a6d8ULL, 0x81ed43d9a9b33bc6ULL,
      0xb1a3655ebd4d7121ULL, 0x69a1eeb5e7ed6167ULL, 0xf6ab73d5c8f73124ULL,
      0x1a67a3e185c61fd5ULL, 0x2dc91004d43c065eULL, 0x0240b02c8fb93a28ULL,
      0x90f7f2b26cc0eb8fULL, 0x3cd3a16f114fd617ULL, 0xaae49ea9f15973e0ULL,
      0x06c0cd748cd64e78ULL, 0xda423bc7d5192a6eULL, 0xc345701c16b41287ULL,
      0x6d2193ede4821537ULL, 0xfcf639494190e3acULL, 0x7c3b228621f1c57eULL,
      0xfb16ac2b0494b0c0ULL, 0xbf7e529a3745d7f9ULL, 0x6881b6a32e3f7c73ULL,
      0xca78d2bad9b8e733ULL, 0xbbfe2fc2342aa3a9ULL, 0x0dbddffecc6381e4ULL,
      0x70a6a56e2440598eULL, 0xe4d12a844befc651ULL, 0x8c509c2765d0ba22ULL,
      0xee8c6018c28814d9ULL, 0x17da7c1f49a59e31ULL, 0x609c4c1328e194d3ULL,
      0xb3e3d57232f44b09ULL, 0x91d7aaa4a512f69bULL, 0x0ffd6fd243dabbccULL,
      0x50d26a943c1fde34ULL, 0x6be15e9968545b4fULL, 0x94778fea6faf9fdfULL,
      0x2b09dd7058ea4826ULL, 0x677cd9716de5c7bfULL, 0x49d5214fffb2e6ddULL,
      0x0360e83a466b273cULL, 0x1fc786af4f7b7691ULL, 0xa0b9d435783ea168ULL,
      0xd49f0c035f118cb6ULL, 0x01205816c9d21d14ULL, 0xac2453dd7d8f3d98ULL,
      0x545217cc3f70aa64ULL, 0x26b4028e9489c9c2ULL, 0xdec2469fd6765e3eULL,
      0x04807d58036f7450ULL, 0xe5f17292823ddb45ULL, 0xf30b569b024a5860ULL,
      0x62dcfc3fa758aefbULL, 0xe84cad6c4e5e5aa1ULL, 0xccb81fce556ea94bULL,
      0x53b282ae7a74f908ULL, 0x1b47fbf74c1402c1ULL, 0x368eebf39828049fULL,
      0x7afbeff2ad278b06ULL, 0xbe5e0a8cfe97caedULL, 0xcfd8f7f413058e77ULL,
      0xf78b2bc301252c30ULL, 0x4d555c17fcdd928dULL, 0x5f2f05467fc565f8ULL,
      0x24f4b2a21b30f3eaULL, 0x860dd6bbecb768aaULL, 0x4c750401350f8f99ULL,
      0x0000000000000000ULL, 0xecccd0344d312ef1ULL, 0xb5231806be220571ULL,
      0xc105c030990d28afULL, 0x653c695de25cfd97ULL, 0x159acc33c61ca419ULL,
      0xb89ec7f872418495ULL, 0xa9847693b73254dcULL, 0x58cf90243ac13694ULL,
      0x59efc832f3132b80ULL, 0x5c4fed7c39ae42c4ULL, 0x828dabe3efd81cfaULL,
      0xd13f294d95ace5f2ULL, 0x7d1b7a90e823d86aULL, 0xb643f03cf849224dULL,
      0x3df3f979d89dcb03ULL, 0x7426d836272f2ddeULL, 0xdfe21e891fa4432aULL,
      0x3a136c1b9d99986fULL, 0xfa36f43dcd46add4ULL, 0xc025982650df35bbULL,
      0x856d3e81aadc4f96ULL, 0xc4a5e57e53b041ebULL, 0x4708168b75ba4005ULL,
      0xaf44bbe73be41aa4ULL, 0x971767d029c4b8e3ULL, 0xb9be9feebb939981ULL,
      0x215497ecd18d9aaeULL, 0x316e7e91dd2c57f3ULL, 0xcef8afe2dad79363ULL,
      0x3853dc371220a247ULL, 0x35ee03c9de4323a3ULL, 0xe6919aa8c456fc79ULL,
      0xe05157dc4880b201ULL, 0x7bdbb7e464f59612ULL, 0x127a59518318f775ULL,
      0x332ecebd52956ddbULL, 0x8f30741d23bb9d1eULL, 0xd922d3fd93720d52ULL,
      0x7746300c61440ae2ULL, 0x25d4eab4d2e2eefeULL, 0x75068020eefd30caULL,
      0x135a01474acaea61ULL, 0x304e268714fe4ae7ULL, 0xa519f17bb283c82cULL,
      0xdc82f6b359cf6416ULL, 0x5baf781e7caa11a8ULL, 0xb2c38d64fb26561dULL,
      0x34ce5bdf17913eb7ULL, 0x5d6fb56af07c5fd0ULL, 0x182713cd0a7f25fdULL,
      0x9e2ac576e6c84d57ULL, 0x9aaab82ee5a73907ULL, 0xa3d93c0f3e558654ULL,
      0x7e7b92aaae48ff56ULL, 0x872d8ead256575beULL, 0x41c8dbfff96c0e7dULL,
      0x99ca5014a3cc1e3bULL, 0x40e883e930be1369ULL, 0x1ca76e95091051adULL,
      0x4e35b42dbab6b5b1ULL, 0x05a0254ecabd6944ULL, 0xe1710fca8152af15ULL,
      0xf22b0e8dcb984574ULL, 0xb763a82a319b3f59ULL, 0x63fca4296e8ab3efULL,
      0x9d4a2d4ca0a36a6bULL, 0xe331bfe60eeb953dULL, 0xd5bf541596c391a2ULL,
      0xf5cb9bef8e9c1618ULL, 0x46284e9dbc685d11ULL, 0x2074cffa185f87baULL,
      0xbd3ee2b6b8fcedd1ULL, 0xae64e3f1f23607b0ULL, 0xfeb68965ce29d984ULL,
      0x55724fdaf6a2b770ULL, 0x29496d5cd753720eULL, 0xa75941573d3af204ULL,
      0x8e102c0bea69800aULL, 0x111ab16bc573d049ULL, 0xd7ffe439197aab8aULL,
      0xefac380e0b5a09cdULL, 0x48f579593660fbc9ULL, 0x22347fd697e6bd92ULL,
      0x61bc1405e13389c7ULL, 0x4ab5c975b9d9c1e1ULL, 0x80cd1bcf606126d2ULL,
      0x7186fd78ed92449aULL, 0x93971a882aabccb3ULL, 0x88d0e17f66bfce72ULL,
      0x27945a985d5bd4d6ULL
      },
      {
      0xde553f8c05a811c8ULL, 0x1906b59631b4f565ULL, 0x436e70d6b1964ff7ULL,
      0x36d343cb8b1e9d85ULL, 0x843dfacc858aab5aULL, 0xfdfc95c299bfc7f9ULL,
      0x0f634bdea1d51fa2ULL, 0x6d458b3b76efb3cdULL, 0x85c3f77cf8593f80ULL,
      0x3c91315fbe737cb2ULL, 0x2148b03366ace398ULL, 0x18f8b8264c6761bfULL,
      0xc830c1c495c9fb0fULL, 0x981a76102086a0aaULL, 0xaa16012142f35760ULL,
      0x35cc54060c763cf6ULL, 0x42907d66cc45db2dULL, 0x8203d44b965af4bcULL,
      0x3d6f3cefc3a0e868ULL, 0xbc73ff69d292bda7ULL, 0x8722ed0102e20a29ULL,
      0x8f8185e8cd34deb7ULL, 0x9b0561dda7ee01d9ULL, 0x5335a0193227fad6ULL,
      0xc9cecc74e81a6fd5ULL, 0x54f5832e5c2431eaULL, 0x99e47ba05d553470ULL,
      0xf7bee756acd226ceULL, 0x384e05a5571816fdULL, 0xd1367452a47d0e6aULL,
      0xf29fde1c386ad85bULL, 0x320c77316275f7caULL, 0xd0c879e2d9ae9ab0ULL,
      0xdb7406c69110ef5dULL, 0x45505e51a2461011ULL, 0xfc029872e46c5323ULL,
      0xfa3cb6f5f7bc0cc5ULL, 0x031f17cd8768a173ULL, 0xbd8df2d9af41297dULL,
      0x9d3b4f5ab43e5e3fULL, 0x4071671b36feee84ULL, 0x716207e7d3e3b83dULL,
      0x48d20ff2f9283a1aULL, 0x27769eb4757cbc7eULL, 0x5c56ebc793f2e574ULL,
      0xa48b474f9ef5dc18ULL, 0x52cbada94ff46e0cULL, 0x60c7da982d8199c6ULL,
      0x0e9d466edc068b78ULL, 0x4eec2175eaf865fcULL, 0x550b8e9e21f7a530ULL,
      0x6b7ba5bc653fec2bULL, 0x5eb7f1ba6949d0ddULL, 0x57ea94e3db4c9099ULL,
      0xf640eae6d101b214ULL, 0xdd4a284182c0b0bbULL, 0xff1d8fbf6304f250ULL,
      0xb8accb933bf9d7e8ULL, 0xe8867c478eb68c4dULL, 0x3f8e2692391bddc1ULL,
      0xcb2fd60912a15a7cULL, 0xaec935dbab983d2fULL, 0xf55ffd2b56691367ULL,
      0x80e2ce366ce1c115ULL, 0x179bf3f8edb27e1dULL, 0x01fe0db07dd394daULL,
      0xda8a0b76ecc37b87ULL, 0x44ae53e1df9584cbULL, 0xb310b4b77347a205ULL,
      0xdfab323c787b8512ULL, 0x3b511268d070b78eULL, 0x65e6e3d2b9396753ULL,
      0x6864b271e2574d58ULL, 0x259784c98fc789d7ULL, 0x02e11a7dfabb35a9ULL,
      0x8841a6dfa337158bULL, 0x7ade78c39b5dcdd0ULL, 0xb7cf804d9a2cc84aULL,
      0x20b6bd831b7f7742ULL, 0x75bd331d3a88d272ULL, 0x418f6aab4b2d7a5eULL,
      0xd9951cbb6babdaf4ULL, 0xb6318dfde7ff5c90ULL, 0x1f389b112264aa83ULL,
      0x492c024284fbaec0ULL, 0xe33a0363c608f9a0ULL, 0x2688930408af28a4ULL,
      0xc7538a1a341ce4adULL, 0x5da8e677ee2171aeULL, 0x8c9e92254a5c7fc4ULL,
      0x63d8cd55aae938b5ULL, 0x29ebd8daa97a3706ULL, 0x959827b37be88aa1ULL,
      0x1484e4356adadf6eULL, 0xa7945082199d7d6bULL, 0xbf6ce8a455fa1cd4ULL,
      0x9cc542eac9edcae5ULL, 0x79c16f0e1c356ca3ULL, 0x89bfab6fdee48151ULL,
      0xd4174d1830c5f0ffULL, 0x9258048415eb419dULL, 0x6139d72850520d1cULL,
      0x6a85a80c18ec78f1ULL, 0xcd11f88e0171059aULL, 0xcceff53e7ca29140ULL,
      0xd229639f2315af19ULL, 0x90b91ef9ef507434ULL, 0x5977d28d074a1be1ULL,
      0x311360fce51d56b9ULL, 0xc093a92d5a1f2f91ULL, 0x1a19a25bb6dc5416ULL,
      0xeb996b8a09de2d3eULL, 0xfee3820f1ed7668aULL, 0xd7085ad5b7ad518cULL,
      0x7fff41890fe53345ULL, 0xec5948bd67dde602ULL, 0x2fd5f65dbaaa68e0ULL,
      0xa5754affe32648c2ULL, 0xf8ddac880d07396cULL, 0x6fa491468c548664ULL,
      0x0c7c5c1326bdbed1ULL, 0x4a33158f03930fb3ULL, 0x699abfc19f84d982ULL,
      0xe4fa2054a80b329cULL, 0x6707f9af438252faULL, 0x08a368e9cfd6d49eULL,
      0x47b1442c58fd25b8ULL, 0xbbb3dc5ebc91769bULL, 0x1665fe489061eac7ULL,
      0x33f27a811fa66310ULL, 0x93a609346838d547ULL, 0x30ed6d4c98cec263ULL,
      0x1dd9816cd8df9f2aULL, 0x94662a03063b1e7bULL, 0x83fdd9fbeb896066ULL,
      0x7b207573e68e590aULL, 0x5f49fc0a149a4407ULL, 0x343259b671a5a82cULL,
      0xfbc2bb458a6f981fULL, 0xc272b350a0a41a38ULL, 0x3aaf1fd8ada32354ULL,
      0x6cbb868b0b3c2717ULL, 0xa2b569c88d2583feULL, 0xf180c9d1bf027928ULL,
      0xaf37386bd64ba9f5ULL, 0x12bacab2790a8088ULL, 0x4c0d3b0810435055ULL,
      0xb2eeb9070e9436dfULL, 0xc5b29067cea7d104ULL, 0xdcb425f1ff132461ULL,
      0x4f122cc5972bf126ULL, 0xac282fa651230886ULL, 0xe7e537992f6393efULL,
      0xe61b3a2952b00735ULL, 0x709c0a57ae302ce7ULL, 0xe02514ae416058d3ULL,
      0xc44c9dd7b37445deULL, 0x5a68c5408022ba92ULL, 0x1c278cdca50c0bf0ULL,
      0x6e5a9cf6f18712beULL, 0x86dce0b17f319ef3ULL, 0x2d34ec2040115d49ULL,
      0x4bcd183f7e409b69ULL, 0x2815d56ad4a9a3dcULL, 0x24698979f2141d0dULL,
      0x0000000000000000ULL, 0x1ec696a15fb73e59ULL, 0xd86b110b16784e2eULL,
      0x8e7f8858b0e74a6dULL, 0x063e2e8713d05fe6ULL, 0xe2c40ed3bbdb6d7aULL,
      0xb1f1aeca89fc97acULL, 0xe1db191e3cb3cc09ULL, 0x6418ee62c4eaf389ULL,
      0xc6ad87aa49cf7077ULL, 0xd6f65765ca7ec556ULL, 0x9afb6c6dda3d9503ULL,
      0x7ce05644888d9236ULL, 0x8d609f95378feb1eULL, 0x23a9aa4e9c17d631ULL,
      0x6226c0e5d73aac6fULL, 0x56149953a69f0443ULL, 0xeeb852c09d66d3abULL,
      0x2b0ac2a753c102afULL, 0x07c023376e03cb3cULL, 0x2ccae1903dc2c993ULL,
      0xd3d76e2f5ec63bc3ULL, 0x9e2458973356ff4cULL, 0xa66a5d32644ee9b1ULL,
      0x0a427294356de137ULL, 0x783f62be61e6f879ULL, 0x1344c70204d91452ULL,
      0x5b96c8f0fdf12e48ULL, 0xa90916ecc59bf613ULL, 0xbe92e5142829880eULL,
      0x727d102a548b194eULL, 0x1be7afebcb0fc0ccULL, 0x3e702b2244c8491bULL,
      0xd5e940a84d166425ULL, 0x66f9f41f3e51c620ULL, 0xabe80c913f20c3baULL,
      0xf07ec461c2d1edf2ULL, 0xf361d3ac45b94c81ULL, 0x0521394a94b8fe95ULL,
      0xadd622162cf09c5cULL, 0xe97871f7f3651897ULL, 0xf4a1f09b2bba87bdULL,
      0x095d6559b2054044ULL, 0x0bbc7f2448be75edULL, 0x2af4cf172e129675ULL,
      0x157ae98517094bb4ULL, 0x9fda55274e856b96ULL, 0x914713499283e0eeULL,
      0xb952c623462a4332ULL, 0x74433ead475b46a8ULL, 0x8b5eb112245fb4f8ULL,
      0xa34b6478f0f61724ULL, 0x11a5dd7ffe6221fbULL, 0xc16da49d27ccbb4bULL,
      0x76a224d0bde07301ULL, 0x8aa0bca2598c2022ULL, 0x4df336b86d90c48fULL,
      0xea67663a740db9e4ULL, 0xef465f70e0b54771ULL, 0x39b008152acb8227ULL,
      0x7d1e5bf4f55e06ecULL, 0x105bd0cf83b1b521ULL, 0x775c2960c033e7dbULL,
      0x7e014c397236a79fULL, 0x811cc386113255cfULL, 0xeda7450d1a0e72d8ULL,
      0x5889df3d7a998f3bULL, 0x2e2bfbedc779fc3aULL, 0xce0eef438619a4e9ULL,
      0x372d4e7bf6cd095fULL, 0x04df34fae96b6a4fULL, 0xf923a13870d4adb6ULL,
      0xa1aa7e050a4d228dULL, 0xa8f71b5cb84862c9ULL, 0xb52e9a306097fde3ULL,
      0x0d8251a35b6e2a0bULL, 0x2257a7fee1c442ebULL, 0x73831d9a29588d94ULL,
      0x51d4ba64c89ccf7fULL, 0x502ab7d4b54f5ba5ULL, 0x97793dce8153bf08ULL,
      0xe5042de4d5d8a646ULL, 0x9687307efc802bd2ULL, 0xa05473b5779eb657ULL,
      0xb4d097801d446939ULL, 0xcff0e2f3fbca3033ULL, 0xc38cbee0dd778ee2ULL,
      0x464f499c252eb162ULL, 0xcad1dbb96f72cea6ULL, 0xba4dd1eec142e241ULL,
      0xb00fa37af42f0376ULL
      },
      {
      0xcce4cd3aa968b245ULL, 0x089d5484e80b7fafULL, 0x638246c1b3548304ULL,
      0xd2fe0ec8c2355492ULL, 0xa7fbdf7ff2374eeeULL, 0x4df1600c92337a16ULL,
      0x84e503ea523b12fbULL, 0x0790bbfd53ab0c4aULL, 0x198a780f38f6ea9dULL,
      0x2ab30c8f55ec48cbULL, 0xe0f7fed6b2c49db5ULL, 0xb6ecf3f422cadbdcULL,
      0x409c9a541358df11ULL, 0xd3ce8a56dfde3fe3ULL, 0xc3e9224312c8c1a0ULL,
      0x0d6dfa58816ba507ULL, 0xddf3e1b179952777ULL, 0x04c02a42748bb1d9ULL,
      0x94c2abff9f2decb8ULL, 0x4f91752da8f8acf4ULL, 0x78682befb169bf7bULL,
      0xe1c77a48af2ff6c4ULL, 0x0c5d7ec69c80ce76ULL, 0x4cc1e4928fd81167ULL,
      0xfeed3d24d9997b62ULL, 0x518bb6dfc3a54a23ULL, 0x6dbf2d26151f9b90ULL,
      0xb5bc624b05ea664fULL, 0xe86aaa525acfe21aULL, 0x4801ced0fb53a0beULL,
      0xc91463e6c00868edULL, 0x1027a815cd16fe43ULL, 0xf67069a0319204cdULL,
      0xb04ccc976c8abce7ULL, 0xc0b9b3fc35e87c33ULL, 0xf380c77c58f2de65ULL,
      0x50bb3241de4e2152ULL, 0xdf93f490435ef195ULL, 0xf1e0d25d62390887ULL,
      0xaf668bfb1a3c3141ULL, 0xbc11b251f00a7291ULL, 0x73a5eed47e427d47ULL,
      0x25bee3f6ee4c3b2eULL, 0x43cc0beb34786282ULL, 0xc824e778dde3039cULL,
      0xf97d86d98a327728ULL, 0xf2b043e24519b514ULL, 0xe297ebf7880f4b57ULL,
      0x3a94a49a98fab688ULL, 0x868516cb68f0c419ULL, 0xeffa11af0964ee50ULL,
      0xa4ab4ec0d517f37dULL, 0xa9c6b498547c567aULL, 0x8e18424f80fbbbb6ULL,
      0x0bcdc53bcf2bc23cULL, 0x137739aaea3643d0ULL, 0x2c1333ec1bac2ff0ULL,
      0x8d48d3f0a7db0625ULL, 0x1e1ac3f26b5de6d7ULL, 0xf520f81f16b2b95eULL,
      0x9f0f6ec450062e84ULL, 0x0130849e1deb6b71ULL, 0xd45e31ab8c7533a9ULL,
      0x652279a2fd14e43fULL, 0x3209f01e70f1c927ULL, 0xbe71a770cac1a473ULL,
      0x0e3d6be7a64b1894ULL, 0x7ec8148cff29d840ULL, 0xcb7476c7fac3be0fULL,
      0x72956a4a63a91636ULL, 0x37f95ec21991138fULL, 0x9e3fea5a4ded45f5ULL,
      0x7b38ba50964902e8ULL, 0x222e580bbde73764ULL, 0x61e253e0899f55e6ULL,
      0xfc8d2805e352ad80ULL, 0x35994be3235ac56dULL, 0x09add01af5e014deULL,
      0x5e8659a6780539c6ULL, 0xb17c48097161d796ULL, 0x026015213acbd6e2ULL,
      0xd1ae9f77e515e901ULL, 0xb7dc776a3f21b0adULL, 0xaba6a1b96eb78098ULL,
      0x9bcf4486248d9f5dULL, 0x582666c536455efdULL, 0xfdbdac9bfeb9c6f1ULL,
      0xc47999be4163cdeaULL, 0x765540081722a7efULL, 0x3e548ed8ec710751ULL,
      0x3d041f67cb51bac2ULL, 0x7958af71ac82d40aULL, 0x36c9da5c047a78feULL,
      0xed9a048e33af38b2ULL, 0x26ee7249c96c86bdULL, 0x900281bdeba65d61ULL,
      0x11172c8bd0fd9532ULL, 0xea0abf73600434f8ULL, 0x42fc8f75299309f3ULL,
      0x34a9cf7d3eb1ae1cULL, 0x2b838811480723baULL, 0x5ce64c8742ceef24ULL,
      0x1adae9b01fd6570eULL, 0x3c349bf9d6bad1b3ULL, 0x82453c891c7b75c0ULL,
      0x97923a40b80d512bULL, 0x4a61dbf1c198765cULL, 0xb48ce6d518010d3eULL,
      0xcfb45c858e480fd6ULL, 0xd933cbf30d1e96aeULL, 0xd70ea014ab558e3aULL,
      0xc189376228031742ULL, 0x9262949cd16d8b83ULL, 0xeb3a3bed7def5f89ULL,
      0x49314a4ee6b8cbcfULL, 0xdcc3652f647e4c06ULL, 0xda635a4c2a3e2b3dULL,
      0x470c21a940f3d35bULL, 0x315961a157d174b4ULL, 0x6672e81dda3459acULL,
      0x5b76f77a1165e36eULL, 0x445cb01667d36ec8ULL, 0xc5491d205c88a69bULL,
      0x456c34887a3805b9ULL, 0xffddb9bac4721013ULL, 0x99af51a71e4649bfULL,
      0xa15be01cbc7729d5ULL, 0x52db2760e485f7b0ULL, 0x8c78576eba306d54ULL,
      0xae560f6507d75a30ULL, 0x95f22f6182c687c9ULL, 0x71c5fbf54489aba5ULL,
      0xca44f259e728d57eULL, 0x88b87d2ccebbdc8dULL, 0xbab18d32be4a15aaULL,
      0x8be8ec93e99b611eULL, 0x17b713e89ebdf209ULL, 0xb31c5d284baa0174ULL,
      0xeeca9531148f8521ULL, 0xb8d198138481c348ULL, 0x8988f9b2d350b7fcULL,
      0xb9e11c8d996aa839ULL, 0x5a4673e40c8e881fULL, 0x1687977683569978ULL,
      0xbf4123eed72acf02ULL, 0x4ea1f1b3b513c785ULL, 0xe767452be16f91ffULL,
      0x7505d1b730021a7cULL, 0xa59bca5ec8fc980cULL, 0xad069eda20f7e7a3ULL,
      0x38f4b1bba231606aULL, 0x60d2d77e94743e97ULL, 0x9affc0183966f42cULL,
      0x248e6768f3a7505fULL, 0xcdd449a4b483d934ULL, 0x87b59255751baf68ULL,
      0x1bea6d2e023d3c7fULL, 0x6b1f12455b5ffcabULL, 0x743555292de9710dULL,
      0xd8034f6d10f5fddfULL, 0xc6198c9f7ba81b08ULL, 0xbb8109aca3a17edbULL,
      0xfa2d1766ad12cabbULL, 0xc729080166437079ULL, 0x9c5fff7b77269317ULL,
      0x0000000000000000ULL, 0x15d706c9a47624ebULL, 0x6fdf38072fd44d72ULL,
      0x5fb6dd3865ee52b7ULL, 0xa33bf53d86bcff37ULL, 0xe657c1b5fc84fa8eULL,
      0xaa962527735cebe9ULL, 0x39c43525bfda0b1bULL, 0x204e4d2a872ce186ULL,
      0x7a083ece8ba26999ULL, 0x554b9c9db72efbfaULL, 0xb22cd9b656416a05ULL,
      0x96a2bedea5e63a5aULL, 0x802529a826b0a322ULL, 0x8115ad363b5bc853ULL,
      0x8375b81701901eb1ULL, 0x3069e53f4a3a1fc5ULL, 0xbd2136cfede119e0ULL,
      0x18bafc91251d81ecULL, 0x1d4a524d4c7d5b44ULL, 0x05f0aedc6960daa8ULL,
      0x29e39d3072ccf558ULL, 0x70f57f6b5962c0d4ULL, 0x989fd53903ad22ceULL,
      0xf84d024797d91c59ULL, 0x547b1803aac5908bULL, 0xf0d056c37fd263f6ULL,
      0xd56eb535919e58d8ULL, 0x1c7ad6d351963035ULL, 0x2e7326cd2167f912ULL,
      0xac361a443d1c8cd2ULL, 0x697f076461942a49ULL, 0x4b515f6fdc731d2dULL,
      0x8ad8680df4700a6fULL, 0x41ac1eca0eb3b460ULL, 0x7d988533d80965d3ULL,
      0xa8f6300649973d0bULL, 0x7765c4960ac9cc9eULL, 0x7ca801adc5e20ea2ULL,
      0xdea3700e5eb59ae4ULL, 0xa06b6482a19c42a4ULL, 0x6a2f96db46b497daULL,
      0x27def6d7d487edccULL, 0x463ca5375d18b82aULL, 0xa6cb5be1efdc259fULL,
      0x53eba3fef96e9cc1ULL, 0xce84d81b93a364a7ULL, 0xf4107c810b59d22fULL,
      0x333974806d1aa256ULL, 0x0f0def79bba073e5ULL, 0x231edc95a00c5c15ULL,
      0xe437d494c64f2c6cULL, 0x91320523f64d3610ULL, 0x67426c83c7df32ddULL,
      0x6eefbc99323f2603ULL, 0x9d6f7be56acdf866ULL, 0x5916e25b2bae358cULL,
      0x7ff89012e2c2b331ULL, 0x035091bf2720bd93ULL, 0x561b0d22900e4669ULL,
      0x28d319ae6f279e29ULL, 0x2f43a2533c8c9263ULL, 0xd09e1be9f8fe8270ULL,
      0xf740ed3e2c796fbcULL, 0xdb53ded237d5404cULL, 0x62b2c25faebfe875ULL,
      0x0afd41a5d2c0a94dULL, 0x6412fd3ce0ff8f4eULL, 0xe3a76f6995e42026ULL,
      0x6c8fa9b808f4f0e1ULL, 0xc2d9a6dd0f23aad1ULL, 0x8f28c6d19d10d0c7ULL,
      0x85d587744fd0798aULL, 0xa20b71a39b579446ULL, 0x684f83fa7c7f4138ULL,
      0xe507500adba4471dULL, 0x3f640a46f19a6c20ULL, 0x1247bd34f7dd28a1ULL,
      0x2d23b77206474481ULL, 0x93521002cc86e0f2ULL, 0x572b89bc8de52d18ULL,
      0xfb1d93f8b0f9a1caULL, 0xe95a2ecc4724896bULL, 0x3ba420048511ddf9ULL,
      0xd63e248ab6bee54bULL, 0x5dd6c8195f258455ULL, 0x06a03f634e40673bULL,
      0x1f2a476c76b68da6ULL, 0x217ec9b49ac78af7ULL, 0xecaa80102e4453c3ULL,
      0x14e78257b99d4f9aULL
      },
      {
      0x20329b2cc87bba05ULL, 0x4f5eb6f86546a531ULL, 0xd4f44775f751b6b1ULL,
      0x8266a47b850dfa8bULL, 0xbb986aa15a6ca985ULL, 0xc979eb08f9ae0f99ULL,
      0x2da6f447a2375ea1ULL, 0x1e74275dcd7d8576ULL, 0xbc20180a800bc5f8ULL,
      0xb4a2f701b2dc65beULL, 0xe726946f981b6d66ULL, 0x48e6c453bf21c94cULL,
      0x42cad9930f0a4195ULL, 0xefa47b64aacccd20ULL, 0x71180a8960409a42ULL,
      0x8bb3329bf6a44e0cULL, 0xd34c35de2d36daccULL, 0xa92f5b7cbc23dc96ULL,
      0xb31a85aa68bb09c3ULL, 0x13e04836a73161d2ULL, 0xb24dfc4129c51d02ULL,
      0x8ae44b70b7da5acdULL, 0xe671ed84d96579a7ULL, 0xa4bb3417d66f3832ULL,
      0x4572ab38d56d2de8ULL, 0xb1b47761ea47215cULL, 0xe81c09cf70aba15dULL,
      0xffbdb872ce7f90acULL, 0xa8782297fd5dc857ULL, 0x0d946f6b6a4ce4a4ULL,
      0xe4df1f4f5b995138ULL, 0x9ebc71edca8c5762ULL, 0x0a2c1dc0b02b88d9ULL,
      0x3b503c115d9d7b91ULL, 0xc64376a8111ec3a2ULL, 0xcec199a323c963e4ULL,
      0xdc76a87ec58616f7ULL, 0x09d596e073a9b487ULL, 0x14583a9d7d560dafULL,
      0xf4c6dc593f2a0cb4ULL, 0xdd21d19584f80236ULL, 0x4a4836983ddde1d3ULL,
      0xe58866a41ae745f9ULL, 0xf591a5b27e541875ULL, 0x891dc05074586693ULL,
      0x5b068c651810a89eULL, 0xa30346bc0c08544fULL, 0x3dbf3751c684032dULL,
      0x2a1e86ec785032dcULL, 0xf73f5779fca830eaULL, 0xb60c05ca30204d21ULL,
      0x0cc316802b32f065ULL, 0x8770241bdd96be69ULL, 0xb861e18199ee95dbULL,
      0xf805cad91418fcd1ULL, 0x29e70dccbbd20e82ULL, 0xc7140f435060d763ULL,
      0x0f3a9da0e8b0cc3bULL, 0xa2543f574d76408eULL, 0xbd7761e1c175d139ULL,
      0x4b1f4f737ca3f512ULL, 0x6dc2df1f2fc137abULL, 0xf1d05c3967b14856ULL,
      0xa742bf3715ed046cULL, 0x654030141d1697edULL, 0x07b872abda676c7dULL,
      0x3ce84eba87fa17ecULL, 0xc1fb0403cb79afdfULL, 0x3e46bc7105063f73ULL,
      0x278ae987121cd678ULL, 0xa1adb4778ef47cd0ULL, 0x26dd906c5362c2b9ULL,
      0x05168060589b44e2ULL, 0xfbfc41f9d79ac08fULL, 0x0e6de44ba9ced8faULL,
      0x9feb08068bf243a3ULL, 0x7b341749d06b129bULL, 0x229c69e74a87929aULL,
      0xe09ee6c4427c011bULL, 0x5692e30e725c4c3aULL, 0xda99a33e5e9f6e4bULL,
      0x353dd85af453a36bULL, 0x25241b4c90e0fee7ULL, 0x5de987258309d022ULL,
      0xe230140fc0802984ULL, 0x93281e86a0c0b3c6ULL, 0xf229d719a4337408ULL,
      0x6f6c2dd4ad3d1f34ULL, 0x8ea5b2fbae3f0aeeULL, 0x8331dd90c473ee4aULL,
      0x346aa1b1b52db7aaULL, 0xdf8f235e06042aa9ULL, 0xcc6f6b68a1354b7bULL,
      0x6c95a6f46ebf236aULL, 0x52d31a856bb91c19ULL, 0x1a35ded6d498d555ULL,
      0xf37eaef2e54d60c9ULL, 0x72e181a9a3c2a61cULL, 0x98537aad51952fdeULL,
      0x16f6c856ffaa2530ULL, 0xd960281e9d1d5215ULL, 0x3a0745fa1ce36f50ULL,
      0x0b7b642bf1559c18ULL, 0x59a87eae9aec8001ULL, 0x5e100c05408bec7cULL,
      0x0441f98b19e55023ULL, 0xd70dcc5534d38aefULL, 0x927f676de1bea707ULL,
      0x9769e70db925e3e5ULL, 0x7a636ea29115065aULL, 0x468b201816ef11b6ULL,
      0xab81a9b73edff409ULL, 0xc0ac7de88a07bb1eULL, 0x1f235eb68c0391b7ULL,
      0x6056b074458dd30fULL, 0xbe8eeac102f7ed67ULL, 0xcd381283e04b5fbaULL,
      0x5cbefecec277c4e3ULL, 0xd21b4c356c48ce0dULL, 0x1019c31664b35d8cULL,
      0x247362a7d19eea26ULL, 0xebe582efb3299d03ULL, 0x02aef2cb82fc289fULL,
      0x86275df09ce8aaa8ULL, 0x28b07427faac1a43ULL, 0x38a9b7319e1f47cfULL,
      0xc82e92e3b8d01b58ULL, 0x06ef0b409b1978bcULL, 0x62f842bfc771fb90ULL,
      0x9904034610eb3b1fULL, 0xded85ab5477a3e68ULL, 0x90d195a663428f98ULL,
      0x5384636e2ac708d8ULL, 0xcbd719c37b522706ULL, 0xae9729d76644b0ebULL,
      0x7c8c65e20a0c7ee6ULL, 0x80c856b007f1d214ULL, 0x8c0b40302cc32271ULL,
      0xdbcedad51fe17a8aULL, 0x740e8ae938dbdea0ULL, 0xa615c6dc549310adULL,
      0x19cc55f6171ae90bULL, 0x49b1bdb8fe5fdd8dULL, 0xed0a89af2830e5bfULL,
      0x6a7aadb4f5a65bd6ULL, 0x7e22972988f05679ULL, 0xf952b3325566e810ULL,
      0x39fecedadf61530eULL, 0x6101c99f04f3c7ceULL, 0x2e5f7f6761b562ffULL,
      0xf08725d226cf5c97ULL, 0x63af3b54860fef51ULL, 0x8ff2cb10ef411e2fULL,
      0x884ab9bb35267252ULL, 0x4df04433e7ba8daeULL, 0x9afd8866d3690741ULL,
      0x66b9bb34de94abb3ULL, 0x9baaf18d92171380ULL, 0x543c11c5f0a064a5ULL,
      0x17a1b1bdbed431f1ULL, 0xb5f58eeaf3a2717fULL, 0xc355f6c849858740ULL,
      0xec5df044694ef17eULL, 0xd83751f5dc6346d4ULL, 0xfc4433520dfdacf2ULL,
      0x0000000000000000ULL, 0x5a51f58e596ebc5fULL, 0x3285aaf12e34cf16ULL,
      0x8d5c39db6dbd36b0ULL, 0x12b731dde64f7513ULL, 0x94906c2d7aa7dfbbULL,
      0x302b583aacc8e789ULL, 0x9d45facd090e6b3cULL, 0x2165e2c78905aec4ULL,
      0x68d45f7f775a7349ULL, 0x189b2c1d5664fdcaULL, 0xe1c99f2f030215daULL,
      0x6983269436246788ULL, 0x8489af3b1e148237ULL, 0xe94b702431d5b59cULL,
      0x33d2d31a6f4adbd7ULL, 0xbfd9932a4389f9a6ULL, 0xb0e30e8aab39359dULL,
      0xd1e2c715afcaf253ULL, 0x150f43763c28196eULL, 0xc4ed846393e2eb3dULL,
      0x03f98b20c3823c5eULL, 0xfd134ab94c83b833ULL, 0x556b682eb1de7064ULL,
      0x36c4537a37d19f35ULL, 0x7559f30279a5ca61ULL, 0x799ae58252973a04ULL,
      0x9c12832648707ffdULL, 0x78cd9c6913e92ec5ULL, 0x1d8dac7d0effb928ULL,
      0x439da0784e745554ULL, 0x413352b3cc887dcbULL, 0xbacf134a1b12bd44ULL,
      0x114ebafd25cd494dULL, 0x2f08068c20cb763eULL, 0x76a07822ba27f63fULL,
      0xeab2fb04f25789c2ULL, 0xe3676de481fe3d45ULL, 0x1b62a73d95e6c194ULL,
      0x641749ff5c68832cULL, 0xa5ec4dfc97112cf3ULL, 0xf6682e92bdd6242bULL,
      0x3f11c59a44782bb2ULL, 0x317c21d1edb6f348ULL, 0xd65ab5be75ad9e2eULL,
      0x6b2dd45fb4d84f17ULL, 0xfaab381296e4d44eULL, 0xd0b5befeeeb4e692ULL,
      0x0882ef0b32d7a046ULL, 0x512a91a5a83b2047ULL, 0x963e9ee6f85bf724ULL,
      0x4e09cf132438b1f0ULL, 0x77f701c9fb59e2feULL, 0x7ddb1c094b726a27ULL,
      0x5f4775ee01f5f8bdULL, 0x9186ec4d223c9b59ULL, 0xfeeac1998f01846dULL,
      0xac39db1ce4b89874ULL, 0xb75b7c21715e59e0ULL, 0xafc0503c273aa42aULL,
      0x6e3b543fec430bf5ULL, 0x704f7362213e8e83ULL, 0x58ff0745db9294c0ULL,
      0x67eec2df9feabf72ULL, 0xa0facd9ccf8a6811ULL, 0xb936986ad890811aULL,
      0x95c715c63bd9cb7aULL, 0xca8060283a2c33c7ULL, 0x507de84ee9453486ULL,
      0x85ded6d05f6a96f6ULL, 0x1cdad5964f81ade9ULL, 0xd5a33e9eb62fa270ULL,
      0x40642b588df6690aULL, 0x7f75eec2c98e42b8ULL, 0x2cf18dace3494a60ULL,
      0x23cb100c0bf9865bULL, 0xeef3028febb2d9e1ULL, 0x4425d2d394133929ULL,
      0xaad6d05c7fa1e0c8ULL, 0xad6ea2f7a5c68cb5ULL, 0xc2028f2308fb9381ULL,
      0x819f2f5b468fc6d5ULL, 0xc5bafd88d29cfffcULL, 0x47dc59f357910577ULL,
      0x2b49ff07392e261dULL, 0x57c59ae5332258fbULL, 0x73b6f842e2bcb2ddULL,
      0xcf96e04862b77725ULL, 0x4ca73dd8a6c4996fULL, 0x015779eb417e14c1ULL,
      0x37932a9176af8bf4ULL
      },
      {
      0x190a2c9b249df23eULL, 0x2f62f8b62263e1e9ULL, 0x7a7f754740993655ULL,
      0x330b7ba4d5564d9fULL, 0x4c17a16a46672582ULL, 0xb22f08eb7d05f5b8ULL,
      0x535f47f40bc148ccULL, 0x3aec5d27d4883037ULL, 0x10ed0a1825438f96ULL,
      0x516101f72c233d17ULL, 0x13cc6f949fd04eaeULL, 0x739853c441474bfdULL,
      0x653793d90d3f5b1bULL, 0x5240647b96b0fc2fULL, 0x0c84890ad27623e0ULL,
      0xd7189b32703aaea3ULL, 0x2685de3523bd9c41ULL, 0x99317c5b11bffefaULL,
      0x0d9baa854f079703ULL, 0x70b93648fbd48ac5ULL, 0xa80441fce30bc6beULL,
      0x7287704bdc36ff1eULL, 0xb65384ed33dc1f13ULL, 0xd36417343ee34408ULL,
      0x39cd38ab6e1bf10fULL, 0x5ab861770a1f3564ULL, 0x0ebacf09f594563bULL,
      0xd04572b884708530ULL, 0x3cae9722bdb3af47ULL, 0x4a556b6f2f5cbaf2ULL,
      0xe1704f1f76c4bd74ULL, 0x5ec4ed7144c6dfcfULL, 0x16afc01d4c7810e6ULL,
      0x283f113cd629ca7aULL, 0xaf59a8761741ed2dULL, 0xeed5a3991e215facULL,
      0x3bf37ea849f984d4ULL, 0xe413e096a56ce33cULL, 0x2c439d3a98f020d1ULL,
      0x637559dc6404c46bULL, 0x9e6c95d1e5f5d569ULL, 0x24bb9836045fe99aULL,
      0x44efa466dac8ecc9ULL, 0xc6eab2a5c80895d6ULL, 0x803b50c035220cc4ULL,
      0x0321658cba93c138ULL, 0x8f9ebc465dc7ee1cULL, 0xd15a5137190131d3ULL,
      0x0fa5ec8668e5e2d8ULL, 0x91c979578d1037b1ULL, 0x0642ca05693b9f70ULL,
      0xefca80168350eb4fULL, 0x38d21b24f36a45ecULL, 0xbeab81e1af73d658ULL,
      0x8cbfd9cae7542f24ULL, 0xfd19cc0d81f11102ULL, 0x0ac6430fbb4dbc90ULL,
      0x1d76a09d6a441895ULL, 0x2a01573ff1cbbfa1ULL, 0xb572e161894fde2bULL,
      0x8124734fa853b827ULL, 0x614b1fdf43e6b1b0ULL, 0x68ac395c4238cc18ULL,
      0x21d837bfd7f7b7d2ULL, 0x20c714304a860331ULL, 0x5cfaab726324aa14ULL,
      0x74c5ba4eb50d606eULL, 0xf3a3030474654739ULL, 0x23e671bcf015c209ULL,
      0x45f087e947b9582aULL, 0xd8bd77b418df4c7bULL, 0xe06f6c90ebb50997ULL,
      0x0bd96080263c0873ULL, 0x7e03f9410e40dcfeULL, 0xb8e94be4c6484928ULL,
      0xfb5b0608e8ca8e72ULL, 0x1a2b49179e0e3306ULL, 0x4e29e76961855059ULL,
      0x4f36c4e6fcf4e4baULL, 0x49740ee395cf7bcaULL, 0xc2963ea386d17f7dULL,
      0x90d65ad810618352ULL, 0x12d34c1b02a1fa4dULL, 0xfa44258775bb3a91ULL,
      0x18150f14b9ec46ddULL, 0x1491861e6b9a653dULL, 0x9a1019d7ab2c3fc2ULL,
      0x3668d42d06fe13d7ULL, 0xdcc1fbb25606a6d0ULL, 0x969490dd795a1c22ULL,
      0x3549b1a1bc6dd2efULL, 0xc94f5e23a0ed770eULL, 0xb9f6686b5b39fdcbULL,
      0xc4d4f4a6efeae00dULL, 0xe732851a1fff2204ULL, 0x94aad6de5eb869f9ULL,
      0x3f8ff2ae07206e7fULL, 0xfe38a9813b62d03aULL, 0xa7a1ad7a8bee2466ULL,
      0x7b6056c8dde882b6ULL, 0x302a1e286fc58ca7ULL, 0x8da0fa457a259bc7ULL,
      0xb3302b64e074415bULL, 0x5402ae7eff8b635fULL, 0x08f8050c9cafc94bULL,
      0xae468bf98a3059ceULL, 0x88c355cca98dc58fULL, 0xb10e6d67c7963480ULL,
      0xbad70de7e1aa3cf3ULL, 0xbfb4a26e320262bbULL, 0xcb711820870f02d5ULL,
      0xce12b7a954a75c9dULL, 0x563ce87dd8691684ULL, 0x9f73b65e7884618aULL,
      0x2b1e74b06cba0b42ULL, 0x47cec1ea605b2df1ULL, 0x1c698312f735ac76ULL,
      0x5fdbcefed9b76b2cULL, 0x831a354c8fb1cdfcULL, 0x820516c312c0791fULL,
      0xb74ca762aeadabf0ULL, 0xfc06ef821c80a5e1ULL, 0x5723cbf24518a267ULL,
      0x9d4df05d5f661451ULL, 0x588627742dfd40bfULL, 0xda8331b73f3d39a0ULL,
      0x17b0e392d109a405ULL, 0xf965400bcf28fba9ULL, 0x7c3dbf4229a2a925ULL,
      0x023e460327e275dbULL, 0x6cd0b55a0ce126b3ULL, 0xe62da695828e96e7ULL,
      0x42ad6e63b3f373b9ULL, 0xe50cc319381d57dfULL, 0xc5cbd729729b54eeULL,
      0x46d1e265fd2a9912ULL, 0x6428b056904eeff8ULL, 0x8be23040131e04b7ULL,
      0x6709d5da2add2ec0ULL, 0x075de98af44a2b93ULL, 0x8447dcc67bfbe66fULL,
      0x6616f655b7ac9a23ULL, 0xd607b8bded4b1a40ULL, 0x0563af89d3a85e48ULL,
      0x3db1b4ad20c21ba4ULL, 0x11f22997b8323b75ULL, 0x292032b34b587e99ULL,
      0x7f1cdace9331681dULL, 0x8e819fc9c0b65affULL, 0xa1e3677fe2d5bb16ULL,
      0xcd33d225ee349da5ULL, 0xd9a2543b85aef898ULL, 0x795e10cbfa0af76dULL,
      0x25a4bbb9992e5d79ULL, 0x78413344677b438eULL, 0xf0826688cef68601ULL,
      0xd27b34bba392f0ebULL, 0x551d8df162fad7bcULL, 0x1e57c511d0d7d9adULL,
      0xdeffbdb171e4d30bULL, 0xf4feea8e802f6caaULL, 0xa480c8f6317de55eULL,
      0xa0fc44f07fa40ff5ULL, 0x95b5f551c3c9dd1aULL, 0x22f952336d6476eaULL,
      0x0000000000000000ULL, 0xa6be8ef5169f9085ULL, 0xcc2cf1aa73452946ULL,
      0x2e7ddb39bf12550aULL, 0xd526dd3157d8db78ULL, 0x486b2d6c08becf29ULL,
      0x9b0f3a58365d8b21ULL, 0xac78cdfaadd22c15ULL, 0xbc95c7e28891a383ULL,
      0x6a927f5f65dab9c3ULL, 0xc3891d2c1ba0cb9eULL, 0xeaa92f9f50f8b507ULL,
      0xcf0d9426c9d6e87eULL, 0xca6e3baf1a7eb636ULL, 0xab25247059980786ULL,
      0x69b31ad3df4978fbULL, 0xe2512a93cc577c4cULL, 0xff278a0ea61364d9ULL,
      0x71a615c766a53e26ULL, 0x89dc764334fc716cULL, 0xf87a638452594f4aULL,
      0xf2bc208be914f3daULL, 0x8766b94ac1682757ULL, 0xbbc82e687cdb8810ULL,
      0x626a7a53f9757088ULL, 0xa2c202f358467a2eULL, 0x4d0882e5db169161ULL,
      0x09e7268301de7da8ULL, 0xe897699c771ac0dcULL, 0xc8507dac3d9cc3edULL,
      0xc0a878a0a1330aa6ULL, 0x978bb352e42ba8c1ULL, 0xe9884a13ea6b743fULL,
      0x279afdbabecc28a2ULL, 0x047c8c064ed9eaabULL, 0x507e2278b15289f4ULL,
      0x599904fbb08cf45cULL, 0xbd8ae46d15e01760ULL, 0x31353da7f2b43844ULL,
      0x8558ff49e68a528cULL, 0x76fbfc4d92ef15b5ULL, 0x3456922e211c660cULL,
      0x86799ac55c1993b4ULL, 0x3e90d1219a51da9cULL, 0x2d5cbeb505819432ULL,
      0x982e5fd48cce4a19ULL, 0xdb9c1238a24c8d43ULL, 0xd439febecaa96f9bULL,
      0x418c0bef0960b281ULL, 0x158ea591f6ebd1deULL, 0x1f48e69e4da66d4eULL,
      0x8afd13cf8e6fb054ULL, 0xf5e1c9011d5ed849ULL, 0xe34e091c5126c8afULL,
      0xad67ee7530a398f6ULL, 0x43b24dec2e82c75aULL, 0x75da99c1287cd48dULL,
      0x92e81cdb3783f689ULL, 0xa3dd217cc537cecdULL, 0x60543c50de970553ULL,
      0x93f73f54aaf2426aULL, 0xa91b62737e7a725dULL, 0xf19d4507538732e2ULL,
      0x77e4dfc20f9ea156ULL, 0x7d229ccdb4d31dc6ULL, 0x1b346a98037f87e5ULL,
      0xedf4c615a4b29e94ULL, 0x4093286094110662ULL, 0xb0114ee85ae78063ULL,
      0x6ff1d0d6b672e78bULL, 0x6dcf96d591909250ULL, 0xdfe09e3eec9567e8ULL,
      0x3214582b4827f97cULL, 0xb46dc2ee143e6ac8ULL, 0xf6c0ac8da7cd1971ULL,
      0xebb60c10cd8901e4ULL, 0xf7df8f023abcad92ULL, 0x9c52d3d2c217a0b2ULL,
      0x6b8d5cd0f8ab0d20ULL, 0x3777f7a29b8fa734ULL, 0x011f238f9d71b4e3ULL,
      0xc1b75b2f3c42be45ULL, 0x5de588fdfe551ef7ULL, 0x6eeef3592b035368ULL,
      0xaa3a07ffc4e9b365ULL, 0xecebe59a39c32a77ULL, 0x5ba742f8976e8187ULL,
      0x4b4a48e0b22d0e11ULL, 0xddded83dcb771233ULL, 0xa59feb79ac0c51bdULL,
      0xc7f5912a55792135ULL
      },
      {
      0x6d6ae04668a9b08aULL, 0x3ab3f04b0be8c743ULL, 0xe51e166b54b3c908ULL,
      0xbe90a9eb35c2f139ULL, 0xb2c7066637f2bec1ULL, 0xaa6945613392202cULL,
      0x9a28c36f3b5201ebULL, 0xddce5a93ab536994ULL, 0x0e34133ef6382827ULL,
      0x52a02ba1ec55048bULL, 0xa2f88f97c4b2a177ULL, 0x8640e513ca2251a5ULL,
      0xcdf1d36258137622ULL, 0xfe6cb708dedf8ddbULL, 0x8a174a9ec8121e5dULL,
      0x679896036b81560eULL, 0x59ed033395795feeULL, 0x1dd778ab8b74edafULL,
      0xee533ef92d9f926dULL, 0x2a8c79baf8a8d8f5ULL, 0x6bcf398e69b119f6ULL,
      0xe20491742fafdd95ULL, 0x276488e0809c2aecULL, 0xea955b82d88f5cceULL,
      0x7102c63a99d9e0c4ULL, 0xf9763017a5c39946ULL, 0x429fa2501f151b3dULL,
      0x4659c72bea05d59eULL, 0x984b7fdccf5a6634ULL, 0xf742232953fbb161ULL,
      0x3041860e08c021c7ULL, 0x747bfd9616cd9386ULL, 0x4bb1367192312787ULL,
      0x1b72a1638a6c44d3ULL, 0x4a0e68a6e8359a66ULL, 0x169a5039f258b6caULL,
      0xb98a2ef44edee5a4ULL, 0xd9083fe85e43a737ULL, 0x967f6ce239624e13ULL,
      0x8874f62d3c1a7982ULL, 0x3c1629830af06e3fULL, 0x9165ebfd427e5a8eULL,
      0xb5dd81794ceeaa5cULL, 0x0de8f15a7834f219ULL, 0x70bd98ede3dd5d25ULL,
      0xaccc9ca9328a8950ULL, 0x56664eda1945ca28ULL, 0x221db34c0f8859aeULL,
      0x26dbd637fa98970dULL, 0x1acdffb4f068f932ULL, 0x4585254f64090fa0ULL,
      0x72de245e17d53afaULL, 0x1546b25d7c546cf4ULL, 0x207e0ffffb803e71ULL,
      0xfaaad2732bcf4378ULL, 0xb462dfae36ea17bdULL, 0xcf926fd1ac1b11fdULL,
      0xe0672dc7dba7ba4aULL, 0xd3fa49ad5d6b41b3ULL, 0x8ba81449b216a3bcULL,
      0x14f9ec8a0650d115ULL, 0x40fc1ee3eb1d7ce2ULL, 0x23a2ed9b758ce44fULL,
      0x782c521b14fddc7eULL, 0x1c68267cf170504eULL, 0xbcf31558c1ca96e6ULL,
      0xa781b43b4ba6d235ULL, 0xf6fd7dfe29ff0c80ULL, 0xb0a4bad5c3fad91eULL,
      0xd199f51ea963266cULL, 0x414340349119c103ULL, 0x5405f269ed4dadf7ULL,
      0xabd61bb649969dcdULL, 0x6813dbeae7bdc3c8ULL, 0x65fb2ab09f8931d1ULL,
      0xf1e7fae152e3181dULL, 0xc1a67cef5a2339daULL, 0x7a4feea8e0f5bba1ULL,
      0x1e0b9acf05783791ULL, 0x5b8ebf8061713831ULL, 0x80e53cdbcb3af8d9ULL,
      0x7e898bd315e57502ULL, 0xc6bcfbf0213f2d47ULL, 0x95a38e86b76e942dULL,
      0x092e94218d243cbaULL, 0x8339debf453622e7ULL, 0xb11be402b9fe64ffULL,
      0x57d9100d634177c9ULL, 0xcc4e8db52217cbc3ULL, 0x3b0cae9c71ec7aa2ULL,
      0xfb158ca451cbfe99ULL, 0x2b33276d82ac6514ULL, 0x01bf5ed77a04bde1ULL,
      0xc5601994af33f779ULL, 0x75c4a3416cc92e67ULL, 0xf3844652a6eb7fc2ULL,
      0x3487e375fdd0ef64ULL, 0x18ae430704609eedULL, 0x4d14efb993298efbULL,
      0x815a620cb13e4538ULL, 0x125c354207487869ULL, 0x9eeea614ce42cf48ULL,
      0xce2d3106d61fac1cULL, 0xbbe99247bad6827bULL, 0x071a871f7b1c149dULL,
      0x2e4a1cc10db81656ULL, 0x77a71ff298c149b8ULL, 0x06a5d9c80118a97cULL,
      0xad73c27e488e34b1ULL, 0x443a7b981e0db241ULL, 0xe3bbcfa355ab6074ULL,
      0x0af276450328e684ULL, 0x73617a896dd1871bULL, 0x58525de4ef7de20fULL,
      0xb7be3dcab8e6cd83ULL, 0x19111dd07e64230cULL, 0x842359a03e2a367aULL,
      0x103f89f1f3401fb6ULL, 0xdc710444d157d475ULL, 0xb835702334da5845ULL,
      0x4320fc876511a6dcULL, 0xd026abc9d3679b8dULL, 0x17250eee885c0b2bULL,
      0x90dab52a387ae76fULL, 0x31fed8d972c49c26ULL, 0x89cba8fa461ec463ULL,
      0x2ff5421677bcabb7ULL, 0x396f122f85e41d7dULL, 0xa09b332430bac6a8ULL,
      0xc888e8ced7070560ULL, 0xaeaf201ac682ee8fULL, 0x1180d7268944a257ULL,
      0xf058a43628e7a5fcULL, 0xbd4c4b8fbbce2b07ULL, 0xa1246df34abe7b49ULL,
      0x7d5569b79be9af3cULL, 0xa9b5a705bd9efa12ULL, 0xdb6b835baa4bc0e8ULL,
      0x05793bac8f147342ULL, 0x21c1512881848390ULL, 0xfdb0556c50d357e5ULL,
      0x613d4fcb6a99ff72ULL, 0x03dce2648e0cda3eULL, 0xe949b9e6568386f0ULL,
      0xfc0f0bbb2ad7ea04ULL, 0x6a70675913b5a417ULL, 0x7f36d5046fe1c8e3ULL,
      0x0c57af8d02304ff8ULL, 0x32223abdfcc84618ULL, 0x0891caf6f720815bULL,
      0xa63eeaec31a26fd4ULL, 0x2507345374944d33ULL, 0x49d28ac266394058ULL,
      0xf5219f9aa7f3d6beULL, 0x2d96fea583b4cc68ULL, 0x5a31e1571b7585d0ULL,
      0x8ed12fe53d02d0feULL, 0xdfade6205f5b0e4bULL, 0x4cabb16ee92d331aULL,
      0x04c6657bf510cea3ULL, 0xd73c2cd6a87b8f10ULL, 0xe1d87310a1a307abULL,
      0x6cd5be9112ad0d6bULL, 0x97c032354366f3f2ULL, 0xd4e0ceb22677552eULL,
      0x0000000000000000ULL, 0x29509bde76a402cbULL, 0xc27a9e8bd42fe3e4ULL,
      0x5ef7842cee654b73ULL, 0xaf107ecdbc86536eULL, 0x3fcacbe784fcb401ULL,
      0xd55f90655c73e8cfULL, 0xe6c2f40fdabf1336ULL, 0xe8f6e7312c873b11ULL,
      0xeb2a0555a28be12fULL, 0xe4a148bc2eb774e9ULL, 0x9b979db84156bc0aULL,
      0x6eb60222e6a56ab4ULL, 0x87ffbbc4b026ec44ULL, 0xc703a5275b3b90a6ULL,
      0x47e699fc9001687fULL, 0x9c8d1aa73a4aa897ULL, 0x7cea3760e1ed12ddULL,
      0x4ec80ddd1d2554c5ULL, 0x13e36b957d4cc588ULL, 0x5d2b66486069914dULL,
      0x92b90999cc7280b0ULL, 0x517cc9c56259deb5ULL, 0xc937b619ad03b881ULL,
      0xec30824ad997f5b2ULL, 0xa45d565fc5aa080bULL, 0xd6837201d27f32f1ULL,
      0x635ef3789e9198adULL, 0x531f75769651b96aULL, 0x4f77530a6721e924ULL,
      0x486dd4151c3dfdb9ULL, 0x5f48dafb9461f692ULL, 0x375b011173dc355aULL,
      0x3da9775470f4d3deULL, 0x8d0dcd81b30e0ac0ULL, 0x36e45fc609d888bbULL,
      0x55baacbe97491016ULL, 0x8cb29356c90ab721ULL, 0x76184125e2c5f459ULL,
      0x99f4210bb55edbd5ULL, 0x6f095cf59ca1d755ULL, 0x9f51f8c3b44672a9ULL,
      0x3538bda287d45285ULL, 0x50c39712185d6354ULL, 0xf23b1885dcefc223ULL,
      0x79930ccc6ef9619fULL, 0xed8fdc9da3934853ULL, 0xcb540aaa590bdf5eULL,
      0x5c94389f1a6d2cacULL, 0xe77daad8a0bbaed7ULL, 0x28efc5090ca0bf2aULL,
      0xbf2ff73c4fc64cd8ULL, 0xb37858b14df60320ULL, 0xf8c96ec0dfc724a7ULL,
      0x828680683f329f06ULL, 0x941cd051cd6a29ccULL, 0xc3c5c05cae2b5e05ULL,
      0xb601631dc2e27062ULL, 0xc01922382027843bULL, 0x24b86a840e90f0d2ULL,
      0xd245177a276ffc52ULL, 0x0f8b4de98c3c95c6ULL, 0x3e759530fef809e0ULL,
      0x0b4d2892792c5b65ULL, 0xc4df4743d5374a98ULL, 0xa5e20888bfaeb5eaULL,
      0xba56cc90c0d23f9aULL, 0x38d04cf8ffe0a09cULL, 0x62e1adafe495254cULL,
      0x0263bcb3f40867dfULL, 0xcaeb547d230f62bfULL, 0x6082111c109d4293ULL,
      0xdad4dd8cd04f7d09ULL, 0xefec602e579b2f8cULL, 0x1fb4c4187f7c8a70ULL,
      0xffd3e9dfa4db303aULL, 0x7bf0b07f9af10640ULL, 0xf49ec14dddf76b5fULL,
      0x8f6e713247066d1fULL, 0x339d646a86ccfbf9ULL, 0x64447467e58d8c30ULL,
      0x2c29a072f9b07189ULL, 0xd8b7613f24471ad6ULL, 0x6627c8d41185ebefULL,
      0xa347d140beb61c96ULL, 0xde12b8f7255fb3aaULL, 0x9d324470404e1576ULL,
      0x9306574eb6763d51ULL, 0xa80af9d2c79a47f3ULL, 0x859c0777442e8b9bULL,
      0x69ac853d9db97e29ULL
      },
      {
      0xc3407dfc2de6377eULL, 0x5b9e93eea4256f77ULL, 0xadb58fdd50c845e0ULL,
      0x5219ff11a75bed86ULL, 0x356b61cfd90b1de9ULL, 0xfb8f406e25abe037ULL,
      0x7a5a0231c0f60796ULL, 0x9d3cd216e1f5020bULL, 0x0c6550fb6b48d8f3ULL,
      0xf57508c427ff1c62ULL, 0x4ad35ffa71cb407dULL, 0x6290a2da1666aa6dULL,
      0xe284ec2349355f9fULL, 0xb3c307c53d7c84ecULL, 0x05e23c0468365a02ULL,
      0x190bac4d6c9ebfa8ULL, 0x94bbbee9e28b80faULL, 0xa34fc777529cb9b5ULL,
      0xcc7b39f095bcd978ULL, 0x2426addb0ce532e3ULL, 0x7e79329312ce4fc7ULL,
      0xab09a72eebec2917ULL, 0xf8d15499f6b9d6c2ULL, 0x1a55b8babf8c895dULL,
      0xdb8add17fb769a85ULL, 0xb57f2f368658e81bULL, 0x8acd36f18f3f41f6ULL,
      0x5ce3b7bba50f11d3ULL, 0x114dcc14d5ee2f0aULL, 0xb91a7fcded1030e8ULL,
      0x81d5425fe55de7a1ULL, 0xb6213bc1554adeeeULL, 0x80144ef95f53f5f2ULL,
      0x1e7688186db4c10cULL, 0x3b912965db5fe1bcULL, 0xc281715a97e8252dULL,
      0x54a5d7e21c7f8171ULL, 0x4b12535ccbc5522eULL, 0x1d289cefbea6f7f9ULL,
      0x6ef5f2217d2e729eULL, 0xe6a7dc819b0d17ceULL, 0x1b94b41c05829b0eULL,
      0x33d7493c622f711eULL, 0xdcf7f942fa5ce421ULL, 0x600fba8b7f7a8ecbULL,
      0x46b60f011a83988eULL, 0x235b898e0dcf4c47ULL, 0x957ab24f588592a9ULL,
      0x4354330572b5c28cULL, 0xa5f3ef84e9b8d542ULL, 0x8c711e02341b2d01ULL,
      0x0b1874ae6a62a657ULL, 0x1213d8e306fc19ffULL, 0xfe6d7c6a4d9dba35ULL,
      0x65ed868f174cd4c9ULL, 0x88522ea0e6236550ULL, 0x899322065c2d7703ULL,
      0xc01e690bfef4018bULL, 0x915982ed8abddaf8ULL, 0xbe675b98ec3a4e4cULL,
      0xa996bf7f82f00db1ULL, 0xe1daf8d49a27696aULL, 0x2effd5d3dc8986e7ULL,
      0xd153a51f2b1a2e81ULL, 0x18caa0ebd690adfbULL, 0x390e3134b243c51aULL,
      0x2778b92cdff70416ULL, 0x029f1851691c24a6ULL, 0x5e7cafeacc133575ULL,
      0xfa4e4cc89fa5f264ULL, 0x5a5f9f481e2b7d24ULL, 0x484c47ab18d764dbULL,
      0x400a27f2a1a7f479ULL, 0xaeeb9b2a83da7315ULL, 0x721c626879869734ULL,
      0x042330a2d2384851ULL, 0x85f672fd3765aff0ULL, 0xba446b3a3e02061dULL,
      0x73dd6ecec3888567ULL, 0xffac70ccf793a866ULL, 0xdfa9edb5294ed2d4ULL,
      0x6c6aea7014325638ULL, 0x834a5a0e8c41c307ULL, 0xcdba35562fb2cb2bULL,
      0x0ad97808d06cb404ULL, 0x0f3b440cb85aee06ULL, 0xe5f9c876481f213bULL,
      0x98deee1289c35809ULL, 0x59018bbfcd394bd1ULL, 0xe01bf47220297b39ULL,
      0xde68e1139340c087ULL, 0x9fa3ca4788e926adULL, 0xbb85679c840c144eULL,
      0x53d8f3b71d55ffd5ULL, 0x0da45c5dd146caa0ULL, 0x6f34fe87c72060cdULL,
      0x57fbc315cf6db784ULL, 0xcee421a1fca0fddeULL, 0x3d2d0196607b8d4bULL,
      0x642c8a29ad42c69aULL, 0x14aff010bdd87508ULL, 0xac74837beac657b3ULL,
      0x3216459ad821634dULL, 0x3fb219c70967a9edULL, 0x06bc28f3bb246cf7ULL,
      0xf2082c9126d562c6ULL, 0x66b39278c45ee23cULL, 0xbd394f6f3f2878b9ULL,
      0xfd33689d9e8f8cc0ULL, 0x37f4799eb017394fULL, 0x108cc0b26fe03d59ULL,
      0xda4bd1b1417888d6ULL, 0xb09d1332ee6eb219ULL, 0x2f3ed975668794b4ULL,
      0x58c0871977375982ULL, 0x7561463d78ace990ULL, 0x09876cff037e82f1ULL,
      0x7fb83e35a8c05d94ULL, 0x26b9b58a65f91645ULL, 0xef20b07e9873953fULL,
      0x3148516d0b3355b8ULL, 0x41cb2b541ba9e62aULL, 0x790416c613e43163ULL,
      0xa011d380818e8f40ULL, 0x3a5025c36151f3efULL, 0xd57095bdf92266d0ULL,
      0x498d4b0da2d97688ULL, 0x8b0c3a57353153a5ULL, 0x21c491df64d368e1ULL,
      0x8f2f0af5e7091bf4ULL, 0x2da1c1240f9bb012ULL, 0xc43d59a92ccc49daULL,
      0xbfa6573e56345c1fULL, 0x828b56a8364fd154ULL, 0x9a41f643e0df7cafULL,
      0xbcf843c985266aeaULL, 0x2b1de9d7b4bfdce5ULL, 0x20059d79dedd7ab2ULL,
      0x6dabe6d6ae3c446bULL, 0x45e81bf6c991ae7bULL, 0x6351ae7cac68b83eULL,
      0xa432e32253b6c711ULL, 0xd092a9b991143cd2ULL, 0xcac711032e98b58fULL,
      0xd8d4c9e02864ac70ULL, 0xc5fc550f96c25b89ULL, 0xd7ef8dec903e4276ULL,
      0x67729ede7e50f06fULL, 0xeac28c7af045cf3dULL, 0xb15c1f945460a04aULL,
      0x9cfddeb05bfb1058ULL, 0x93c69abce3a1fe5eULL, 0xeb0380dc4a4bdd6eULL,
      0xd20db1e8f8081874ULL, 0x229a8528b7c15e14ULL, 0x44291750739fbc28ULL,
      0xd3ccbd4e42060a27ULL, 0xf62b1c33f4ed2a97ULL, 0x86a8660ae4779905ULL,
      0xd62e814a2a305025ULL, 0x477703a7a08d8addULL, 0x7b9b0e977af815c5ULL,
      0x78c51a60a9ea2330ULL, 0xa6adfb733aaae3b7ULL, 0x97e5aa1e3199b60fULL,
      0x0000000000000000ULL, 0xf4b404629df10e31ULL, 0x5564db44a6719322ULL,
      0x9207961a59afec0dULL, 0x9624a6b88b97a45cULL, 0x363575380a192b1cULL,
      0x2c60cd82b595a241ULL, 0x7d272664c1dc7932ULL, 0x7142769faa94a1c1ULL,
      0xa1d0df263b809d13ULL, 0x1630e841d4c451aeULL, 0xc1df65ad44fa13d8ULL,
      0x13d2d445bcf20bacULL, 0xd915c546926abe23ULL, 0x38cf3d92084dd749ULL,
      0xe766d0272103059dULL, 0xc7634d5effde7f2fULL, 0x077d2455012a7ea4ULL,
      0xedbfa82ff16fb199ULL, 0xaf2a978c39d46146ULL, 0x42953fa3c8bbd0dfULL,
      0xcb061da59496a7dcULL, 0x25e7a17db6eb20b0ULL, 0x34aa6d6963050fbaULL,
      0xa76cf7d580a4f1e4ULL, 0xf7ea10954ee338c4ULL, 0xfcf2643b24819e93ULL,
      0xcf252d0746aeef8dULL, 0x4ef06f58a3f3082cULL, 0x563acfb37563a5d7ULL,
      0x5086e740ce47c920ULL, 0x2982f186dda3f843ULL, 0x87696aac5e798b56ULL,
      0x5d22bb1d1f010380ULL, 0x035e14f7d31236f5ULL, 0x3cec0d30da759f18ULL,
      0xf3c920379cdb7095ULL, 0xb8db736b571e22bbULL, 0xdd36f5e44052f672ULL,
      0xaac8ab8851e23b44ULL, 0xa857b3d938fe1fe2ULL, 0x17f1e4e76eca43fdULL,
      0xec7ea4894b61a3caULL, 0x9e62c6e132e734feULL, 0xd4b1991b432c7483ULL,
      0x6ad6c283af163acfULL, 0x1ce9904904a8e5aaULL, 0x5fbda34c761d2726ULL,
      0xf910583f4cb7c491ULL, 0xc6a241f845d06d7cULL, 0x4f3163fe19fd1a7fULL,
      0xe99c988d2357f9c8ULL, 0x8eee06535d0709a7ULL, 0x0efa48aa0254fc55ULL,
      0xb4be23903c56fa48ULL, 0x763f52caabbedf65ULL, 0xeee1bcd8227d876cULL,
      0xe345e085f33b4dccULL, 0x3e731561b369bbbeULL, 0x2843fd2067adea10ULL,
      0x2adce5710eb1ceb6ULL, 0xb7e03767ef44ccbdULL, 0x8db012a48e153f52ULL,
      0x61ceb62dc5749c98ULL, 0xe85d942b9959eb9bULL, 0x4c6f7709caef2c8aULL,
      0x84377e5b8d6bbda3ULL, 0x30895dcbb13d47ebULL, 0x74a04a9bc2a2fbc3ULL,
      0x6b17ce251518289cULL, 0xe438c4d0f2113368ULL, 0x1fb784bed7bad35fULL,
      0x9b80fae55ad16efcULL, 0x77fe5e6c11b0cd36ULL, 0xc858095247849129ULL,
      0x08466059b97090a2ULL, 0x01c10ca6ba0e1253ULL, 0x6988d6747c040c3aULL,
      0x6849dad2c60a1e69ULL, 0x5147ebe67449db73ULL, 0xc99905f4fd8a837aULL,
      0x991fe2b433cd4a5aULL, 0xf09734c04fc94660ULL, 0xa28ecbd1e892abe6ULL,
      0xf1563866f5c75433ULL, 0x4dae7baf70e13ed9ULL, 0x7ce62ac27bd26b61ULL,
      0x70837a39109ab392ULL, 0x90988e4b30b3c8abULL, 0xb2020b63877296bfULL,
      0x156efcb607d6675bULL
      },
      {
      0xe63f55ce97c331d0ULL, 0x25b506b0015bba16ULL, 0xc8706e29e6ad9ba8ULL,
      0x5b43d3775d521f6aULL, 0x0bfa3d577035106eULL, 0xab95fc172afb0e66ULL,
      0xf64b63979e7a3276ULL, 0xf58b4562649dad4bULL, 0x48f7c3dbae0c83f1ULL,
      0xff31916642f5c8c5ULL, 0xcbb048dc1c4a0495ULL, 0x66b8f83cdf622989ULL,
      0x35c130e908e2b9b0ULL, 0x7c761a61f0b34fa1ULL, 0x3601161cf205268dULL,
      0x9e54ccfe2219b7d6ULL, 0x8b7d90a538940837ULL, 0x9cd403588ea35d0bULL,
      0xbc3c6fea9ccc5b5aULL, 0xe5ff733b6d24aeedULL, 0xceed22de0f7eb8d2ULL,
      0xec8581cab1ab545eULL, 0xb96105e88ff8e71dULL, 0x8ca03501871a5eadULL,
      0x76ccce65d6db2a2fULL, 0x5883f582a7b58057ULL, 0x3f7be4ed2e8adc3eULL,
      0x0fe7be06355cd9c9ULL, 0xee054e6c1d11be83ULL, 0x1074365909b903a6ULL,
      0x5dde9f80b4813c10ULL, 0x4a770c7d02b6692cULL, 0x5379c8d5d7809039ULL,
      0xb4067448161ed409ULL, 0x5f5e5026183bd6cdULL, 0xe898029bf4c29df9ULL,
      0x7fb63c940a54d09cULL, 0xc5171f897f4ba8bcULL, 0xa6f28db7b31d3d72ULL,
      0x2e4f3be7716eaa78ULL, 0x0d6771a099e63314ULL, 0x82076254e41bf284ULL,
      0x2f0fd2b42733df98ULL, 0x5c9e76d3e2dc49f0ULL, 0x7aeb569619606cdbULL,
      0x83478b07b2468764ULL, 0xcfadcb8d5923cd32ULL, 0x85dac7f05b95a41eULL,
      0xb5469d1b4043a1e9ULL, 0xb821ecbbd9a592fdULL, 0x1b8e0b0e798c13c8ULL,
      0x62a57b6d9a0be02eULL, 0xfcf1b793b81257f8ULL, 0x9d94ea0bd8fe28ebULL,
      0x4cea408aeb654a56ULL, 0x23284a47e888996cULL, 0x2d8f1d128b893545ULL,
      0xf4cbac3132c0d8abULL, 0xbd7c86b9ca912ebaULL, 0x3a268eef3dbe6079ULL,
      0xf0d62f6077a9110cULL, 0x2735c916ade150cbULL, 0x89fd5f03942ee2eaULL,
      0x1acee25d2fd16628ULL, 0x90f39bab41181bffULL, 0x430dfe8cde39939fULL,
      0xf70b8ac4c8274796ULL, 0x1c53aeaac6024552ULL, 0x13b410acf35e9c9bULL,
      0xa532ab4249faa24fULL, 0x2b1251e5625a163fULL, 0xd7e3e676da4841c7ULL,
      0xa7b264e4e5404892ULL, 0xda8497d643ae72d3ULL, 0x861ae105a1723b23ULL,
      0x38a6414991048aa4ULL, 0x6578dec92585b6b4ULL, 0x0280cfa6acbaeaddULL,
      0x88bdb650c273970aULL, 0x9333bd5ebbff84c2ULL, 0x4e6a8f2c47dfa08bULL,
      0x321c954db76cef2aULL, 0x418d312a72837942ULL, 0xb29b38bfffcdf773ULL,
      0x6c022c38f90a4c07ULL, 0x5a033a240b0f6a8aULL, 0x1f93885f3ce5da6fULL,
      0xc38a537e96988bc6ULL, 0x39e6a81ac759ff44ULL, 0x29929e43cee0fce2ULL,
      0x40cdd87924de0ca2ULL, 0xe9d8ebc8a29fe819ULL, 0x0c2798f3cfbb46f4ULL,
      0x55e484223e53b343ULL, 0x4650948ecd0d2fd8ULL, 0x20e86cb2126f0651ULL,
      0x6d42c56baf5739e7ULL, 0xa06fc1405ace1e08ULL, 0x7babbfc54f3d193bULL,
      0x424d17df8864e67fULL, 0xd8045870ef14980eULL, 0xc6d7397c85ac3781ULL,
      0x21a885e1443273b1ULL, 0x67f8116f893f5c69ULL, 0x24f5efe35706cff6ULL,
      0xd56329d076f2ab1aULL, 0x5e1eb9754e66a32dULL, 0x28d2771098bd8902ULL,
      0x8f6013f47dfdc190ULL, 0x17a993fdb637553cULL, 0xe0a219397e1012aaULL,
      0x786b9930b5da8606ULL, 0x6e82e39e55b0a6daULL, 0x875a0856f72f4ec3ULL,
      0x3741ff4fa458536dULL, 0xac4859b3957558fcULL, 0x7ef6d5c75c09a57cULL,
      0xc04a758b6c7f14fbULL, 0xf9acdd91ab26ebbfULL, 0x7391a467c5ef9668ULL,
      0x335c7c1ee1319acaULL, 0xa91533b18641e4bbULL, 0xe4bf9a683b79db0dULL,
      0x8e20faa72ba0b470ULL, 0x51f907737b3a7ae4ULL, 0x2268a314bed5ec8cULL,
      0xd944b123b949edeeULL, 0x31dcb3b84d8b7017ULL, 0xd3fe65279f218860ULL,
      0x097af2f1dc8ffab3ULL, 0x9b09a6fc312d0b91ULL, 0xcc6ded78a3c4520fULL,
      0x3481d9ba5ebfcc50ULL, 0x4f2a667f1182d56bULL, 0xdfd9fdd4509ace94ULL,
      0x26752045fbbc252bULL, 0xbffc491f662bc467ULL, 0xdd593272fc202449ULL,
      0x3cbbc218d46d4303ULL, 0x91b372f817456e1fULL, 0x681faf69bc6385a0ULL,
      0xb686bbeebaa43ed4ULL, 0x1469b5084cd0ca01ULL, 0x98c98009cbca94acULL,
      0x6438379a73d8c354ULL, 0xc2caba2dc0c5fe26ULL, 0x3e3b0dbe78d7a9deULL,
      0x50b9ee202d670f04ULL, 0x4590b27b37eab0e5ULL, 0x6025b4cb36b10af3ULL,
      0xfb2c1237079c0162ULL, 0xa12f28130c936be8ULL, 0x4b37e52e54eb1cccULL,
      0x083a1ba28ad28f53ULL, 0xc10a9cd83a22611bULL, 0x9f1425ad7444c236ULL,
      0x069d4cf7e9d3237aULL, 0xedc56899e7f621beULL, 0x778c273680865fcfULL,
      0x309c5aeb1bd605f7ULL, 0x8de0dc52d1472b4dULL, 0xf8ec34c2fd7b9e5fULL,
      0xea18cd3d58787724ULL, 0xaad515447ca67b86ULL, 0x9989695a9d97e14cULL,
      0x0000000000000000ULL, 0xf196c63321f464ecULL, 0x71116bc169557cb5ULL,
      0xaf887f466f92c7c1ULL, 0x972e3e0ffe964d65ULL, 0x190ec4a8d536f915ULL,
      0x95aef1a9522ca7b8ULL, 0xdc19db21aa7d51a9ULL, 0x94ee18fa0471d258ULL,
      0x8087adf248a11859ULL, 0xc457f6da2916dd5cULL, 0xfa6cfb6451c17482ULL,
      0xf256e0c6db13fbd1ULL, 0x6a9f60cf10d96f7dULL, 0x4daaa9d9bd383fb6ULL,
      0x03c026f5fae79f3dULL, 0xde99148706c7bb74ULL, 0x2a52b8b6340763dfULL,
      0x6fc20acd03edd33aULL, 0xd423c08320afdefaULL, 0xbbe1ca4e23420dc0ULL,
      0x966ed75ca8cb3885ULL, 0xeb58246e0e2502c4ULL, 0x055d6a021334bc47ULL,
      0xa47242111fa7d7afULL, 0xe3623fcc84f78d97ULL, 0x81c744a11efc6db9ULL,
      0xaec8961539cfb221ULL, 0xf31609958d4e8e31ULL, 0x63e5923ecc5695ceULL,
      0x47107ddd9b505a38ULL, 0xa3afe7b5a0298135ULL, 0x792b7063e387f3e6ULL,
      0x0140e953565d75e0ULL, 0x12f4f9ffa503e97bULL, 0x750ce8902c3cb512ULL,
      0xdbc47e8515f30733ULL, 0x1ed3610c6ab8af8fULL, 0x5239218681dde5d9ULL,
      0xe222d69fd2aaf877ULL, 0xfe71783514a8bd25ULL, 0xcaf0a18f4a177175ULL,
      0x61655d9860ec7f13ULL, 0xe77fbc9dc19e4430ULL, 0x2ccff441ddd440a5ULL,
      0x16e97aaee06a20dcULL, 0xa855dae2d01c915bULL, 0x1d1347f9905f30b2ULL,
      0xb7c652bdecf94b34ULL, 0xd03e43d265c6175dULL, 0xfdb15ec0ee4f2218ULL,
      0x57644b8492e9599eULL, 0x07dda5a4bf8e569aULL, 0x54a46d71680ec6a3ULL,
      0x5624a2d7c4b42c7eULL, 0xbebca04c3076b187ULL, 0x7d36f332a6ee3a41ULL,
      0x3b6667bc6be31599ULL, 0x695f463aea3ef040ULL, 0xad08b0e0c3282d1cULL,
      0xb15b1e4a052a684eULL, 0x44d05b2861b7c505ULL, 0x15295c5b1a8dbfe1ULL,
      0x744c01c37a61c0f2ULL, 0x59c31cd1f1e8f5b7ULL, 0xef45a73f4b4ccb63ULL,
      0x6bdf899c46841a9dULL, 0x3dfb2b4b823036e3ULL, 0xa2ef0ee6f674f4d5ULL,
      0x184e2dfb836b8cf5ULL, 0x1134df0a5fe47646ULL, 0xbaa1231d751f7820ULL,
      0xd17eaa81339b62bdULL, 0xb01bf71953771daeULL, 0x849a2ea30dc8d1feULL,
      0x705182923f080955ULL, 0x0ea757556301ac29ULL, 0x041d83514569c9a7ULL,
      0x0abad4042668658eULL, 0x49b72a88f851f611ULL, 0x8a3d79f66ec97dd7ULL,
      0xcd2d042bf59927efULL, 0xc930877ab0f0ee48ULL, 0x9273540deda2f122ULL,
      0xc797d02fd3f14261ULL, 0xe1e2f06a284d674aULL, 0xd2be8c74c97cfd80ULL,
      0x9a494faf67707e71ULL, 0xb3dbd1eca9908293ULL, 0x72d14d3493b2e388ULL,
      0xd6a30f258c153427ULL
      }
   };

extern const uint64_t STREEBOG_C[12][8] =
   {
      {
      0xdd806559f2a64507ULL,
      0x05767436cc744d23ULL,
      0xa2422a08a460d315ULL,
      0x4b7ce09192676901ULL,
      0x714eb88d7585c4fcULL,
      0x2f6a76432e45d016ULL,
      0xebcb2f81c0657c1fULL,
      0xb1085bda1ecadae9ULL
      },
      {
      0xe679047021b19bb7ULL,
      0x55dda21bd7cbcd56ULL,
      0x5cb561c2db0aa7caULL,
      0x9ab5176b12d69958ULL,
      0x61d55e0f16b50131ULL,
      0xf3feea720a232b98ULL,
      0x4fe39d460f70b5d7ULL,
      0x6fa3b58aa99d2f1aULL
      },
      {
      0x991e96f50aba0ab2ULL,
      0xc2b6f443867adb31ULL,
      0xc1c93a376062db09ULL,
      0xd3e20fe490359eb1ULL,
      0xf2ea7514b1297b7bULL,
      0x06f15e5f529c1f8bULL,
      0x0a39fc286a3d8435ULL,
      0xf574dcac2bce2fc7ULL
      },
      {
      0x220cbebc84e3d12eULL,
      0x3453eaa193e837f1ULL,
      0xd8b71333935203beULL,
      0xa9d72c82ed03d675ULL,
      0x9d721cad685e353fULL,
      0x488e857e335c3c7dULL,
      0xf948e1a05d71e4ddULL,
      0xef1fdfb3e81566d2ULL
      },
      {
      0x601758fd7c6cfe57ULL,
      0x7a56a27ea9ea63f5ULL,
      0xdfff00b723271a16ULL,
      0xbfcd1747253af5a3ULL,
      0x359e35d7800fffbdULL,
      0x7f151c1f1686104aULL,
      0x9a3f410c6ca92363ULL,
      0x4bea6bacad474799ULL
      },
      {
      0xfa68407a46647d6eULL,
      0xbf71c57236904f35ULL,
      0x0af21f66c2bec6b6ULL,
      0xcffaa6b71c9ab7b4ULL,
      0x187f9ab49af08ec6ULL,
      0x2d66c4f95142a46cULL,
      0x6fa4c33b7a3039c0ULL,
      0xae4faeae1d3ad3d9ULL
      },
      {
      0x8886564d3a14d493ULL,
      0x3517454ca23c4af3ULL,
      0x06476983284a0504ULL,
      0x0992abc52d822c37ULL,
      0xd3473e33197a93c9ULL,
      0x399ec6c7e6bf87c9ULL,
      0x51ac86febf240954ULL,
      0xf4c70e16eeaac5ecULL
      },
      {
      0xa47f0dd4bf02e71eULL,
      0x36acc2355951a8d9ULL,
      0x69d18d2bd1a5c42fULL,
      0xf4892bcb929b0690ULL,
      0x89b4443b4ddbc49aULL,
      0x4eb7f8719c36de1eULL,
      0x03e7aa020c6e4141ULL,
      0x9b1f5b424d93c9a7ULL
      },
      {
      0x7261445183235adbULL,
      0x0e38dc92cb1f2a60ULL,
      0x7b2b8a9aa6079c54ULL,
      0x800a440bdbb2ceb1ULL,
      0x3cd955b7e00d0984ULL,
      0x3a7d3a1b25894224ULL,
      0x944c9ad8ec165fdeULL,
      0x378f5a541631229bULL
      },
      {
      0x74b4c7fb98459cedULL,
      0x3698fad1153bb6c3ULL,
      0x7a1e6c303b7652f4ULL,
      0x9fe76702af69334bULL,
      0x1fffe18a1b336103ULL,
      0x8941e71cff8a78dbULL,
      0x382ae548b2e4f3f3ULL,
      0xabbedea680056f52ULL
      },
      {
      0x6bcaa4cd81f32d1bULL,
      0xdea2594ac06fd85dULL,
      0xefbacd1d7d476e98ULL,
      0x8a1d71efea48b9caULL,
      0x2001802114846679ULL,
      0xd8fa6bbbebab0761ULL,
      0x3002c6cd635afe94ULL,
      0x7bcd9ed0efc889fbULL
      },
      {
      0x48bc924af11bd720ULL,
      0xfaf417d5d9b21b99ULL,
      0xe71da4aa88e12852ULL,
      0x5d80ef9d1891cc86ULL,
      0xf82012d430219f9bULL,
      0xcda43c32bcdf1d77ULL,
      0xd21380b00449b17aULL,
      0x378ee767f11631baULL
      }
   };

}
/*
* System RNG
* (C) 2014,2015,2017,2018 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/
