# Paths to relevant programs

CXX            = g++
LINKER         = $(CXX)
AR             = ar
AR_OPTIONS     = crs
PYTHON_EXE     = python.exe

# Compiler Flags

ABI_FLAGS      =  -fstack-protector -pthread
LANG_FLAGS     = -std=c++11 -D_REENTRANT
CXXFLAGS       = -O3
WARN_FLAGS     = -Wall -Wextra -Wpedantic -Wstrict-aliasing -Wcast-align -Wmissing-declarations -Wpointer-arith -Wcast-qual -Wzero-as-null-pointer-constant -Wnon-virtual-dtor
LIB_FLAGS      = 
LDFLAGS        = 

EXE_LINK_CMD   = $(LINKER)
POST_LINK_CMD  = 

LIB_LINKS_TO   = -lws2_32
EXE_LINKS_TO   = -L. -lbotan-2 $(LIB_LINKS_TO)

BUILD_FLAGS    = $(ABI_FLAGS) $(LANG_FLAGS) $(CXXFLAGS) $(WARN_FLAGS)

SCRIPTS_DIR    = src/scripts
INSTALLED_LIB_DIR = /mingw/lib

# The primary target
all: libs cli tests docs

# Executable targets
CLI           = botan.exe
TEST          = botan-test.exe
LIBRARIES     = libbotan-2.a

cli: $(CLI)
tests: $(TEST)
libs: $(LIBRARIES)
docs: build\doc.stamp

# Misc targets

.PHONY = all cli libs tests docs clean distclean install

build\doc.stamp: doc/manual/*.rst
	$(PYTHON_EXE) $(SCRIPTS_DIR)/build_docs.py --build-dir="build"

clean:
	$(PYTHON_EXE) $(SCRIPTS_DIR)/cleanup.py --build-dir="build"

distclean:
	$(PYTHON_EXE) $(SCRIPTS_DIR)/cleanup.py --build-dir="build" --distclean

install: libs cli docs
	$(PYTHON_EXE) $(SCRIPTS_DIR)/install.py --prefix="/mingw" --build-dir="build" --bindir=bin --libdir=lib --docdir=share/doc --includedir=include

# Object Files
LIBOBJS = build\obj\lib\botan_all.o

CLIOBJS = build\obj\cli\asn1.o build\obj\cli\bcrypt.o build\obj\cli\cc_enc.o build\obj\cli\cli.o build\obj\cli\cli_rng.o build\obj\cli\codec.o build\obj\cli\compress.o build\obj\cli\encryption.o build\obj\cli\hash.o build\obj\cli\hmac.o build\obj\cli\main.o build\obj\cli\math.o build\obj\cli\pbkdf.o build\obj\cli\pk_crypt.o build\obj\cli\psk.o build\obj\cli\pubkey.o build\obj\cli\sandbox.o build\obj\cli\speed.o build\obj\cli\timing_tests.o build\obj\cli\tls_client.o build\obj\cli\tls_http_server.o build\obj\cli\tls_proxy.o build\obj\cli\tls_server.o build\obj\cli\tls_utils.o build\obj\cli\tss.o build\obj\cli\utils.o build\obj\cli\x509.o

TESTOBJS = build\obj\test\main.o build\obj\test\test_aead.o build\obj\test\test_asn1.o build\obj\test\test_bigint.o build\obj\test\test_block.o build\obj\test\test_blowfish.o build\obj\test\test_c25519.o build\obj\test\test_certstor.o build\obj\test\test_certstor_macos.o build\obj\test\test_compression.o build\obj\test\test_cryptobox.o build\obj\test\test_datastore.o build\obj\test\test_dh.o build\obj\test\test_dl_group.o build\obj\test\test_dlies.o build\obj\test\test_dsa.o build\obj\test\test_ecc_pointmul.o build\obj\test\test_ecdh.o build\obj\test\test_ecdsa.o build\obj\test\test_ecgdsa.o build\obj\test\test_ecies.o build\obj\test\test_eckcdsa.o build\obj\test\test_ed25519.o build\obj\test\test_elg.o build\obj\test\test_entropy.o build\obj\test\test_ffi.o build\obj\test\test_filters.o build\obj\test\test_fpe.o build\obj\test\test_gf2m.o build\obj\test\test_gost_3410.o build\obj\test\test_hash.o build\obj\test\test_hash_id.o build\obj\test\test_kdf.o build\obj\test\test_keywrap.o build\obj\test\test_mac.o build\obj\test\test_mceliece.o build\obj\test\test_modes.o build\obj\test\test_mp.o build\obj\test\test_name_constraint.o build\obj\test\test_newhope.o build\obj\test\test_ocb.o build\obj\test\test_ocsp.o build\obj\test\test_octetstring.o build\obj\test\test_oid.o build\obj\test\test_os_utils.o build\obj\test\test_otp.o build\obj\test\test_package_transform.o build\obj\test\test_pad.o build\obj\test\test_passhash.o build\obj\test\test_pbkdf.o build\obj\test\test_pem.o build\obj\test\test_pk_pad.o build\obj\test\test_pkcs11_high_level.o build\obj\test\test_pkcs11_low_level.o build\obj\test\test_psk_db.o build\obj\test\test_pubkey.o build\obj\test\test_rfc6979.o build\obj\test\test_rng.o build\obj\test\test_rng_kat.o build\obj\test\test_rsa.o build\obj\test\test_runner.o build\obj\test\test_simd.o build\obj\test\test_siv.o build\obj\test\test_sm2.o build\obj\test\test_srp6.o build\obj\test\test_stream.o build\obj\test\test_tests.o build\obj\test\test_thread_utils.o build\obj\test\test_tls.o build\obj\test\test_tls_messages.o build\obj\test\test_tpm.o build\obj\test\test_tss.o build\obj\test\test_utils.o build\obj\test\test_workfactor.o build\obj\test\test_x509_dn.o build\obj\test\test_x509_path.o build\obj\test\test_xmss.o build\obj\test\tests.o build\obj\test\unit_ecc.o build\obj\test\unit_ecdh.o build\obj\test\unit_ecdsa.o build\obj\test\unit_tls.o build\obj\test\unit_tls_policy.o build\obj\test\unit_x509.o

# Executable targets

$(CLI): $(LIBRARIES) $(CLIOBJS)
	$(EXE_LINK_CMD) $(ABI_FLAGS) $(LDFLAGS) $(CLIOBJS) $(EXE_LINKS_TO) -o $@
	$(POST_LINK_CMD)

$(TEST): $(LIBRARIES) $(TESTOBJS)
	$(EXE_LINK_CMD) $(ABI_FLAGS) $(LDFLAGS) $(TESTOBJS) $(EXE_LINKS_TO) -o $@
	$(POST_LINK_CMD)


# Library targets


./libbotan-2.a: $(LIBOBJS)
	$(AR) $(AR_OPTIONS) $@ $(LIBOBJS)



# Build Commands

build\obj\lib\botan_all.o: botan_all.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c botan_all.cpp -o $@



build\obj\cli\asn1.o: src/cli/asn1.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/asn1.cpp -o $@

build\obj\cli\bcrypt.o: src/cli/bcrypt.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/bcrypt.cpp -o $@

build\obj\cli\cc_enc.o: src/cli/cc_enc.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/cc_enc.cpp -o $@

build\obj\cli\cli.o: src/cli/cli.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/cli.cpp -o $@

build\obj\cli\cli_rng.o: src/cli/cli_rng.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/cli_rng.cpp -o $@

build\obj\cli\codec.o: src/cli/codec.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/codec.cpp -o $@

build\obj\cli\compress.o: src/cli/compress.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/compress.cpp -o $@

build\obj\cli\encryption.o: src/cli/encryption.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/encryption.cpp -o $@

build\obj\cli\hash.o: src/cli/hash.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/hash.cpp -o $@

build\obj\cli\hmac.o: src/cli/hmac.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/hmac.cpp -o $@

build\obj\cli\main.o: src/cli/main.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/main.cpp -o $@

build\obj\cli\math.o: src/cli/math.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/math.cpp -o $@

build\obj\cli\pbkdf.o: src/cli/pbkdf.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/pbkdf.cpp -o $@

build\obj\cli\pk_crypt.o: src/cli/pk_crypt.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/pk_crypt.cpp -o $@

build\obj\cli\psk.o: src/cli/psk.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/psk.cpp -o $@

build\obj\cli\pubkey.o: src/cli/pubkey.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/pubkey.cpp -o $@

build\obj\cli\sandbox.o: src/cli/sandbox.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/sandbox.cpp -o $@

build\obj\cli\speed.o: src/cli/speed.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/speed.cpp -o $@

build\obj\cli\timing_tests.o: src/cli/timing_tests.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/timing_tests.cpp -o $@

build\obj\cli\tls_client.o: src/cli/tls_client.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/tls_client.cpp -o $@

build\obj\cli\tls_http_server.o: src/cli/tls_http_server.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/tls_http_server.cpp -o $@

build\obj\cli\tls_proxy.o: src/cli/tls_proxy.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/tls_proxy.cpp -o $@

build\obj\cli\tls_server.o: src/cli/tls_server.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/tls_server.cpp -o $@

build\obj\cli\tls_utils.o: src/cli/tls_utils.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/tls_utils.cpp -o $@

build\obj\cli\tss.o: src/cli/tss.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/tss.cpp -o $@

build\obj\cli\utils.o: src/cli/utils.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/utils.cpp -o $@

build\obj\cli\x509.o: src/cli/x509.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/cli/x509.cpp -o $@



build\obj\test\main.o: src/tests/main.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/main.cpp -o $@

build\obj\test\test_aead.o: src/tests/test_aead.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_aead.cpp -o $@

build\obj\test\test_asn1.o: src/tests/test_asn1.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_asn1.cpp -o $@

build\obj\test\test_bigint.o: src/tests/test_bigint.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_bigint.cpp -o $@

build\obj\test\test_block.o: src/tests/test_block.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_block.cpp -o $@

build\obj\test\test_blowfish.o: src/tests/test_blowfish.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_blowfish.cpp -o $@

build\obj\test\test_c25519.o: src/tests/test_c25519.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_c25519.cpp -o $@

build\obj\test\test_certstor.o: src/tests/test_certstor.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_certstor.cpp -o $@

build\obj\test\test_certstor_macos.o: src/tests/test_certstor_macos.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_certstor_macos.cpp -o $@

build\obj\test\test_compression.o: src/tests/test_compression.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_compression.cpp -o $@

build\obj\test\test_cryptobox.o: src/tests/test_cryptobox.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_cryptobox.cpp -o $@

build\obj\test\test_datastore.o: src/tests/test_datastore.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_datastore.cpp -o $@

build\obj\test\test_dh.o: src/tests/test_dh.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_dh.cpp -o $@

build\obj\test\test_dl_group.o: src/tests/test_dl_group.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_dl_group.cpp -o $@

build\obj\test\test_dlies.o: src/tests/test_dlies.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_dlies.cpp -o $@

build\obj\test\test_dsa.o: src/tests/test_dsa.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_dsa.cpp -o $@

build\obj\test\test_ecc_pointmul.o: src/tests/test_ecc_pointmul.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_ecc_pointmul.cpp -o $@

build\obj\test\test_ecdh.o: src/tests/test_ecdh.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_ecdh.cpp -o $@

build\obj\test\test_ecdsa.o: src/tests/test_ecdsa.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_ecdsa.cpp -o $@

build\obj\test\test_ecgdsa.o: src/tests/test_ecgdsa.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_ecgdsa.cpp -o $@

build\obj\test\test_ecies.o: src/tests/test_ecies.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_ecies.cpp -o $@

build\obj\test\test_eckcdsa.o: src/tests/test_eckcdsa.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_eckcdsa.cpp -o $@

build\obj\test\test_ed25519.o: src/tests/test_ed25519.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_ed25519.cpp -o $@

build\obj\test\test_elg.o: src/tests/test_elg.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_elg.cpp -o $@

build\obj\test\test_entropy.o: src/tests/test_entropy.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_entropy.cpp -o $@

build\obj\test\test_ffi.o: src/tests/test_ffi.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_ffi.cpp -o $@

build\obj\test\test_filters.o: src/tests/test_filters.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_filters.cpp -o $@

build\obj\test\test_fpe.o: src/tests/test_fpe.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_fpe.cpp -o $@

build\obj\test\test_gf2m.o: src/tests/test_gf2m.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_gf2m.cpp -o $@

build\obj\test\test_gost_3410.o: src/tests/test_gost_3410.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_gost_3410.cpp -o $@

build\obj\test\test_hash.o: src/tests/test_hash.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_hash.cpp -o $@

build\obj\test\test_hash_id.o: src/tests/test_hash_id.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_hash_id.cpp -o $@

build\obj\test\test_kdf.o: src/tests/test_kdf.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_kdf.cpp -o $@

build\obj\test\test_keywrap.o: src/tests/test_keywrap.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_keywrap.cpp -o $@

build\obj\test\test_mac.o: src/tests/test_mac.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_mac.cpp -o $@

build\obj\test\test_mceliece.o: src/tests/test_mceliece.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_mceliece.cpp -o $@

build\obj\test\test_modes.o: src/tests/test_modes.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_modes.cpp -o $@

build\obj\test\test_mp.o: src/tests/test_mp.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_mp.cpp -o $@

build\obj\test\test_name_constraint.o: src/tests/test_name_constraint.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_name_constraint.cpp -o $@

build\obj\test\test_newhope.o: src/tests/test_newhope.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_newhope.cpp -o $@

build\obj\test\test_ocb.o: src/tests/test_ocb.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_ocb.cpp -o $@

build\obj\test\test_ocsp.o: src/tests/test_ocsp.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_ocsp.cpp -o $@

build\obj\test\test_octetstring.o: src/tests/test_octetstring.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_octetstring.cpp -o $@

build\obj\test\test_oid.o: src/tests/test_oid.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_oid.cpp -o $@

build\obj\test\test_os_utils.o: src/tests/test_os_utils.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_os_utils.cpp -o $@

build\obj\test\test_otp.o: src/tests/test_otp.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_otp.cpp -o $@

build\obj\test\test_package_transform.o: src/tests/test_package_transform.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_package_transform.cpp -o $@

build\obj\test\test_pad.o: src/tests/test_pad.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_pad.cpp -o $@

build\obj\test\test_passhash.o: src/tests/test_passhash.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_passhash.cpp -o $@

build\obj\test\test_pbkdf.o: src/tests/test_pbkdf.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_pbkdf.cpp -o $@

build\obj\test\test_pem.o: src/tests/test_pem.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_pem.cpp -o $@

build\obj\test\test_pk_pad.o: src/tests/test_pk_pad.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_pk_pad.cpp -o $@

build\obj\test\test_pkcs11_high_level.o: src/tests/test_pkcs11_high_level.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_pkcs11_high_level.cpp -o $@

build\obj\test\test_pkcs11_low_level.o: src/tests/test_pkcs11_low_level.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_pkcs11_low_level.cpp -o $@

build\obj\test\test_psk_db.o: src/tests/test_psk_db.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_psk_db.cpp -o $@

build\obj\test\test_pubkey.o: src/tests/test_pubkey.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_pubkey.cpp -o $@

build\obj\test\test_rfc6979.o: src/tests/test_rfc6979.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_rfc6979.cpp -o $@

build\obj\test\test_rng.o: src/tests/test_rng.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_rng.cpp -o $@

build\obj\test\test_rng_kat.o: src/tests/test_rng_kat.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_rng_kat.cpp -o $@

build\obj\test\test_rsa.o: src/tests/test_rsa.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_rsa.cpp -o $@

build\obj\test\test_runner.o: src/tests/test_runner.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_runner.cpp -o $@

build\obj\test\test_simd.o: src/tests/test_simd.cpp
	$(CXX) $(BUILD_FLAGS) -msse2 -Ibuild\include -Ibuild\include\external -c src/tests/test_simd.cpp -o $@

build\obj\test\test_siv.o: src/tests/test_siv.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_siv.cpp -o $@

build\obj\test\test_sm2.o: src/tests/test_sm2.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_sm2.cpp -o $@

build\obj\test\test_srp6.o: src/tests/test_srp6.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_srp6.cpp -o $@

build\obj\test\test_stream.o: src/tests/test_stream.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_stream.cpp -o $@

build\obj\test\test_tests.o: src/tests/test_tests.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_tests.cpp -o $@

build\obj\test\test_thread_utils.o: src/tests/test_thread_utils.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_thread_utils.cpp -o $@

build\obj\test\test_tls.o: src/tests/test_tls.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_tls.cpp -o $@

build\obj\test\test_tls_messages.o: src/tests/test_tls_messages.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_tls_messages.cpp -o $@

build\obj\test\test_tpm.o: src/tests/test_tpm.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_tpm.cpp -o $@

build\obj\test\test_tss.o: src/tests/test_tss.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_tss.cpp -o $@

build\obj\test\test_utils.o: src/tests/test_utils.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_utils.cpp -o $@

build\obj\test\test_workfactor.o: src/tests/test_workfactor.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_workfactor.cpp -o $@

build\obj\test\test_x509_dn.o: src/tests/test_x509_dn.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_x509_dn.cpp -o $@

build\obj\test\test_x509_path.o: src/tests/test_x509_path.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_x509_path.cpp -o $@

build\obj\test\test_xmss.o: src/tests/test_xmss.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/test_xmss.cpp -o $@

build\obj\test\tests.o: src/tests/tests.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/tests.cpp -o $@

build\obj\test\unit_ecc.o: src/tests/unit_ecc.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/unit_ecc.cpp -o $@

build\obj\test\unit_ecdh.o: src/tests/unit_ecdh.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/unit_ecdh.cpp -o $@

build\obj\test\unit_ecdsa.o: src/tests/unit_ecdsa.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/unit_ecdsa.cpp -o $@

build\obj\test\unit_tls.o: src/tests/unit_tls.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/unit_tls.cpp -o $@

build\obj\test\unit_tls_policy.o: src/tests/unit_tls_policy.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/unit_tls_policy.cpp -o $@

build\obj\test\unit_x509.o: src/tests/unit_x509.cpp
	$(CXX) $(BUILD_FLAGS)  -Ibuild\include -Ibuild\include\external -c src/tests/unit_x509.cpp -o $@





