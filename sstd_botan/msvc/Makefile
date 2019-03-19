# Paths to relevant programs

CXX            = cl
LINKER         = link
AR             = lib
AR_OPTIONS     = /nologo
PYTHON_EXE     = python.exe

# Compiler Flags

ABI_FLAGS      =  /MD /bigobj
LANG_FLAGS     = /EHs /GR /D_ENABLE_EXTENDED_ALIGNED_STORAGE
CXXFLAGS       = /O2 /Oi
WARN_FLAGS     = /W4 /wd4250 /wd4251 /wd4275
LIB_FLAGS      =  /DBOTAN_DLL=__declspec(dllexport)
LDFLAGS        = 

EXE_LINK_CMD   = $(LINKER)
POST_LINK_CMD  = 

LIB_LINKS_TO   = user32.lib ws2_32.lib
EXE_LINKS_TO   = .\botan.lib $(LIB_LINKS_TO)

BUILD_FLAGS    = $(ABI_FLAGS) $(LANG_FLAGS) $(CXXFLAGS) $(WARN_FLAGS)

SCRIPTS_DIR    = src/scripts
INSTALLED_LIB_DIR = c:\Botan/lib

# The primary target
all: libs cli tests docs

# Executable targets
CLI           = .\botan-cli.exe
TEST          = .\botan-test.exe
LIBRARIES     = .\botan.dll

cli: $(CLI)
tests: $(TEST)
libs: $(LIBRARIES)
docs: build\doc.stamp

# Misc targets


build\doc.stamp: doc/manual/*.rst
	$(PYTHON_EXE) $(SCRIPTS_DIR)/build_docs.py --build-dir="build"

clean:
	$(PYTHON_EXE) $(SCRIPTS_DIR)/cleanup.py --build-dir="build"

distclean:
	$(PYTHON_EXE) $(SCRIPTS_DIR)/cleanup.py --build-dir="build" --distclean

install: libs cli docs
	$(PYTHON_EXE) $(SCRIPTS_DIR)/install.py --prefix="c:\Botan" --build-dir="build" --bindir=bin --libdir=lib --docdir=docs --includedir=include

# Object Files
LIBOBJS = build\obj\lib\botan_all.obj

CLIOBJS = build\obj\cli\asn1.obj build\obj\cli\bcrypt.obj build\obj\cli\cc_enc.obj build\obj\cli\cli.obj build\obj\cli\cli_rng.obj build\obj\cli\codec.obj build\obj\cli\compress.obj build\obj\cli\encryption.obj build\obj\cli\hash.obj build\obj\cli\hmac.obj build\obj\cli\main.obj build\obj\cli\math.obj build\obj\cli\pbkdf.obj build\obj\cli\pk_crypt.obj build\obj\cli\psk.obj build\obj\cli\pubkey.obj build\obj\cli\sandbox.obj build\obj\cli\speed.obj build\obj\cli\timing_tests.obj build\obj\cli\tls_client.obj build\obj\cli\tls_http_server.obj build\obj\cli\tls_proxy.obj build\obj\cli\tls_server.obj build\obj\cli\tls_utils.obj build\obj\cli\tss.obj build\obj\cli\utils.obj build\obj\cli\x509.obj

TESTOBJS = build\obj\test\main.obj build\obj\test\test_aead.obj build\obj\test\test_asn1.obj build\obj\test\test_bigint.obj build\obj\test\test_block.obj build\obj\test\test_blowfish.obj build\obj\test\test_c25519.obj build\obj\test\test_certstor.obj build\obj\test\test_certstor_macos.obj build\obj\test\test_compression.obj build\obj\test\test_cryptobox.obj build\obj\test\test_datastore.obj build\obj\test\test_dh.obj build\obj\test\test_dl_group.obj build\obj\test\test_dlies.obj build\obj\test\test_dsa.obj build\obj\test\test_ecc_pointmul.obj build\obj\test\test_ecdh.obj build\obj\test\test_ecdsa.obj build\obj\test\test_ecgdsa.obj build\obj\test\test_ecies.obj build\obj\test\test_eckcdsa.obj build\obj\test\test_ed25519.obj build\obj\test\test_elg.obj build\obj\test\test_entropy.obj build\obj\test\test_ffi.obj build\obj\test\test_filters.obj build\obj\test\test_fpe.obj build\obj\test\test_gf2m.obj build\obj\test\test_gost_3410.obj build\obj\test\test_hash.obj build\obj\test\test_hash_id.obj build\obj\test\test_kdf.obj build\obj\test\test_keywrap.obj build\obj\test\test_mac.obj build\obj\test\test_mceliece.obj build\obj\test\test_modes.obj build\obj\test\test_mp.obj build\obj\test\test_name_constraint.obj build\obj\test\test_newhope.obj build\obj\test\test_ocb.obj build\obj\test\test_ocsp.obj build\obj\test\test_octetstring.obj build\obj\test\test_oid.obj build\obj\test\test_os_utils.obj build\obj\test\test_otp.obj build\obj\test\test_package_transform.obj build\obj\test\test_pad.obj build\obj\test\test_passhash.obj build\obj\test\test_pbkdf.obj build\obj\test\test_pem.obj build\obj\test\test_pk_pad.obj build\obj\test\test_pkcs11_high_level.obj build\obj\test\test_pkcs11_low_level.obj build\obj\test\test_psk_db.obj build\obj\test\test_pubkey.obj build\obj\test\test_rfc6979.obj build\obj\test\test_rng.obj build\obj\test\test_rng_kat.obj build\obj\test\test_rsa.obj build\obj\test\test_runner.obj build\obj\test\test_simd.obj build\obj\test\test_siv.obj build\obj\test\test_sm2.obj build\obj\test\test_srp6.obj build\obj\test\test_stream.obj build\obj\test\test_tests.obj build\obj\test\test_thread_utils.obj build\obj\test\test_tls.obj build\obj\test\test_tls_messages.obj build\obj\test\test_tpm.obj build\obj\test\test_tss.obj build\obj\test\test_utils.obj build\obj\test\test_workfactor.obj build\obj\test\test_x509_dn.obj build\obj\test\test_x509_path.obj build\obj\test\test_xmss.obj build\obj\test\tests.obj build\obj\test\unit_ecc.obj build\obj\test\unit_ecdh.obj build\obj\test\unit_ecdsa.obj build\obj\test\unit_tls.obj build\obj\test\unit_tls_policy.obj build\obj\test\unit_x509.obj

# Executable targets

$(CLI): $(LIBRARIES) $(CLIOBJS)
	$(EXE_LINK_CMD) $(ABI_FLAGS) $(LDFLAGS) $(CLIOBJS) $(EXE_LINKS_TO) /OUT:$@
	$(POST_LINK_CMD)

$(TEST): $(LIBRARIES) $(TESTOBJS)
	$(EXE_LINK_CMD) $(ABI_FLAGS) $(LDFLAGS) $(TESTOBJS) $(EXE_LINKS_TO) /OUT:$@
	$(POST_LINK_CMD)


# Library targets



./botan.dll: $(LIBOBJS)
	$(LINKER) /DLL $(ABI_FLAGS) $(LDFLAGS) $(LIBOBJS) $(LIB_LINKS_TO) /OUT:$@

# Build Commands

build\obj\lib\botan_all.obj: botan_all.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c botan_all.cpp /Fo$@



build\obj\cli\asn1.obj: src/cli/asn1.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/asn1.cpp /Fo$@

build\obj\cli\bcrypt.obj: src/cli/bcrypt.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/bcrypt.cpp /Fo$@

build\obj\cli\cc_enc.obj: src/cli/cc_enc.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/cc_enc.cpp /Fo$@

build\obj\cli\cli.obj: src/cli/cli.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/cli.cpp /Fo$@

build\obj\cli\cli_rng.obj: src/cli/cli_rng.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/cli_rng.cpp /Fo$@

build\obj\cli\codec.obj: src/cli/codec.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/codec.cpp /Fo$@

build\obj\cli\compress.obj: src/cli/compress.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/compress.cpp /Fo$@

build\obj\cli\encryption.obj: src/cli/encryption.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/encryption.cpp /Fo$@

build\obj\cli\hash.obj: src/cli/hash.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/hash.cpp /Fo$@

build\obj\cli\hmac.obj: src/cli/hmac.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/hmac.cpp /Fo$@

build\obj\cli\main.obj: src/cli/main.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/main.cpp /Fo$@

build\obj\cli\math.obj: src/cli/math.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/math.cpp /Fo$@

build\obj\cli\pbkdf.obj: src/cli/pbkdf.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/pbkdf.cpp /Fo$@

build\obj\cli\pk_crypt.obj: src/cli/pk_crypt.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/pk_crypt.cpp /Fo$@

build\obj\cli\psk.obj: src/cli/psk.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/psk.cpp /Fo$@

build\obj\cli\pubkey.obj: src/cli/pubkey.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/pubkey.cpp /Fo$@

build\obj\cli\sandbox.obj: src/cli/sandbox.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/sandbox.cpp /Fo$@

build\obj\cli\speed.obj: src/cli/speed.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/speed.cpp /Fo$@

build\obj\cli\timing_tests.obj: src/cli/timing_tests.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/timing_tests.cpp /Fo$@

build\obj\cli\tls_client.obj: src/cli/tls_client.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/tls_client.cpp /Fo$@

build\obj\cli\tls_http_server.obj: src/cli/tls_http_server.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/tls_http_server.cpp /Fo$@

build\obj\cli\tls_proxy.obj: src/cli/tls_proxy.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/tls_proxy.cpp /Fo$@

build\obj\cli\tls_server.obj: src/cli/tls_server.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/tls_server.cpp /Fo$@

build\obj\cli\tls_utils.obj: src/cli/tls_utils.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/tls_utils.cpp /Fo$@

build\obj\cli\tss.obj: src/cli/tss.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/tss.cpp /Fo$@

build\obj\cli\utils.obj: src/cli/utils.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/utils.cpp /Fo$@

build\obj\cli\x509.obj: src/cli/x509.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/cli/x509.cpp /Fo$@



build\obj\test\main.obj: src/tests/main.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/main.cpp /Fo$@

build\obj\test\test_aead.obj: src/tests/test_aead.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_aead.cpp /Fo$@

build\obj\test\test_asn1.obj: src/tests/test_asn1.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_asn1.cpp /Fo$@

build\obj\test\test_bigint.obj: src/tests/test_bigint.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_bigint.cpp /Fo$@

build\obj\test\test_block.obj: src/tests/test_block.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_block.cpp /Fo$@

build\obj\test\test_blowfish.obj: src/tests/test_blowfish.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_blowfish.cpp /Fo$@

build\obj\test\test_c25519.obj: src/tests/test_c25519.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_c25519.cpp /Fo$@

build\obj\test\test_certstor.obj: src/tests/test_certstor.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_certstor.cpp /Fo$@

build\obj\test\test_certstor_macos.obj: src/tests/test_certstor_macos.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_certstor_macos.cpp /Fo$@

build\obj\test\test_compression.obj: src/tests/test_compression.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_compression.cpp /Fo$@

build\obj\test\test_cryptobox.obj: src/tests/test_cryptobox.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_cryptobox.cpp /Fo$@

build\obj\test\test_datastore.obj: src/tests/test_datastore.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_datastore.cpp /Fo$@

build\obj\test\test_dh.obj: src/tests/test_dh.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_dh.cpp /Fo$@

build\obj\test\test_dl_group.obj: src/tests/test_dl_group.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_dl_group.cpp /Fo$@

build\obj\test\test_dlies.obj: src/tests/test_dlies.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_dlies.cpp /Fo$@

build\obj\test\test_dsa.obj: src/tests/test_dsa.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_dsa.cpp /Fo$@

build\obj\test\test_ecc_pointmul.obj: src/tests/test_ecc_pointmul.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_ecc_pointmul.cpp /Fo$@

build\obj\test\test_ecdh.obj: src/tests/test_ecdh.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_ecdh.cpp /Fo$@

build\obj\test\test_ecdsa.obj: src/tests/test_ecdsa.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_ecdsa.cpp /Fo$@

build\obj\test\test_ecgdsa.obj: src/tests/test_ecgdsa.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_ecgdsa.cpp /Fo$@

build\obj\test\test_ecies.obj: src/tests/test_ecies.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_ecies.cpp /Fo$@

build\obj\test\test_eckcdsa.obj: src/tests/test_eckcdsa.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_eckcdsa.cpp /Fo$@

build\obj\test\test_ed25519.obj: src/tests/test_ed25519.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_ed25519.cpp /Fo$@

build\obj\test\test_elg.obj: src/tests/test_elg.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_elg.cpp /Fo$@

build\obj\test\test_entropy.obj: src/tests/test_entropy.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_entropy.cpp /Fo$@

build\obj\test\test_ffi.obj: src/tests/test_ffi.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_ffi.cpp /Fo$@

build\obj\test\test_filters.obj: src/tests/test_filters.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_filters.cpp /Fo$@

build\obj\test\test_fpe.obj: src/tests/test_fpe.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_fpe.cpp /Fo$@

build\obj\test\test_gf2m.obj: src/tests/test_gf2m.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_gf2m.cpp /Fo$@

build\obj\test\test_gost_3410.obj: src/tests/test_gost_3410.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_gost_3410.cpp /Fo$@

build\obj\test\test_hash.obj: src/tests/test_hash.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_hash.cpp /Fo$@

build\obj\test\test_hash_id.obj: src/tests/test_hash_id.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_hash_id.cpp /Fo$@

build\obj\test\test_kdf.obj: src/tests/test_kdf.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_kdf.cpp /Fo$@

build\obj\test\test_keywrap.obj: src/tests/test_keywrap.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_keywrap.cpp /Fo$@

build\obj\test\test_mac.obj: src/tests/test_mac.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_mac.cpp /Fo$@

build\obj\test\test_mceliece.obj: src/tests/test_mceliece.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_mceliece.cpp /Fo$@

build\obj\test\test_modes.obj: src/tests/test_modes.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_modes.cpp /Fo$@

build\obj\test\test_mp.obj: src/tests/test_mp.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_mp.cpp /Fo$@

build\obj\test\test_name_constraint.obj: src/tests/test_name_constraint.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_name_constraint.cpp /Fo$@

build\obj\test\test_newhope.obj: src/tests/test_newhope.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_newhope.cpp /Fo$@

build\obj\test\test_ocb.obj: src/tests/test_ocb.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_ocb.cpp /Fo$@

build\obj\test\test_ocsp.obj: src/tests/test_ocsp.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_ocsp.cpp /Fo$@

build\obj\test\test_octetstring.obj: src/tests/test_octetstring.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_octetstring.cpp /Fo$@

build\obj\test\test_oid.obj: src/tests/test_oid.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_oid.cpp /Fo$@

build\obj\test\test_os_utils.obj: src/tests/test_os_utils.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_os_utils.cpp /Fo$@

build\obj\test\test_otp.obj: src/tests/test_otp.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_otp.cpp /Fo$@

build\obj\test\test_package_transform.obj: src/tests/test_package_transform.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_package_transform.cpp /Fo$@

build\obj\test\test_pad.obj: src/tests/test_pad.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_pad.cpp /Fo$@

build\obj\test\test_passhash.obj: src/tests/test_passhash.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_passhash.cpp /Fo$@

build\obj\test\test_pbkdf.obj: src/tests/test_pbkdf.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_pbkdf.cpp /Fo$@

build\obj\test\test_pem.obj: src/tests/test_pem.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_pem.cpp /Fo$@

build\obj\test\test_pk_pad.obj: src/tests/test_pk_pad.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_pk_pad.cpp /Fo$@

build\obj\test\test_pkcs11_high_level.obj: src/tests/test_pkcs11_high_level.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_pkcs11_high_level.cpp /Fo$@

build\obj\test\test_pkcs11_low_level.obj: src/tests/test_pkcs11_low_level.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_pkcs11_low_level.cpp /Fo$@

build\obj\test\test_psk_db.obj: src/tests/test_psk_db.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_psk_db.cpp /Fo$@

build\obj\test\test_pubkey.obj: src/tests/test_pubkey.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_pubkey.cpp /Fo$@

build\obj\test\test_rfc6979.obj: src/tests/test_rfc6979.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_rfc6979.cpp /Fo$@

build\obj\test\test_rng.obj: src/tests/test_rng.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_rng.cpp /Fo$@

build\obj\test\test_rng_kat.obj: src/tests/test_rng_kat.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_rng_kat.cpp /Fo$@

build\obj\test\test_rsa.obj: src/tests/test_rsa.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_rsa.cpp /Fo$@

build\obj\test\test_runner.obj: src/tests/test_runner.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_runner.cpp /Fo$@

build\obj\test\test_simd.obj: src/tests/test_simd.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_simd.cpp /Fo$@

build\obj\test\test_siv.obj: src/tests/test_siv.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_siv.cpp /Fo$@

build\obj\test\test_sm2.obj: src/tests/test_sm2.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_sm2.cpp /Fo$@

build\obj\test\test_srp6.obj: src/tests/test_srp6.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_srp6.cpp /Fo$@

build\obj\test\test_stream.obj: src/tests/test_stream.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_stream.cpp /Fo$@

build\obj\test\test_tests.obj: src/tests/test_tests.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_tests.cpp /Fo$@

build\obj\test\test_thread_utils.obj: src/tests/test_thread_utils.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_thread_utils.cpp /Fo$@

build\obj\test\test_tls.obj: src/tests/test_tls.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_tls.cpp /Fo$@

build\obj\test\test_tls_messages.obj: src/tests/test_tls_messages.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_tls_messages.cpp /Fo$@

build\obj\test\test_tpm.obj: src/tests/test_tpm.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_tpm.cpp /Fo$@

build\obj\test\test_tss.obj: src/tests/test_tss.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_tss.cpp /Fo$@

build\obj\test\test_utils.obj: src/tests/test_utils.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_utils.cpp /Fo$@

build\obj\test\test_workfactor.obj: src/tests/test_workfactor.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_workfactor.cpp /Fo$@

build\obj\test\test_x509_dn.obj: src/tests/test_x509_dn.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_x509_dn.cpp /Fo$@

build\obj\test\test_x509_path.obj: src/tests/test_x509_path.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_x509_path.cpp /Fo$@

build\obj\test\test_xmss.obj: src/tests/test_xmss.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/test_xmss.cpp /Fo$@

build\obj\test\tests.obj: src/tests/tests.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/tests.cpp /Fo$@

build\obj\test\unit_ecc.obj: src/tests/unit_ecc.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/unit_ecc.cpp /Fo$@

build\obj\test\unit_ecdh.obj: src/tests/unit_ecdh.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/unit_ecdh.cpp /Fo$@

build\obj\test\unit_ecdsa.obj: src/tests/unit_ecdsa.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/unit_ecdsa.cpp /Fo$@

build\obj\test\unit_tls.obj: src/tests/unit_tls.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/unit_tls.cpp /Fo$@

build\obj\test\unit_tls_policy.obj: src/tests/unit_tls_policy.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/unit_tls_policy.cpp /Fo$@

build\obj\test\unit_x509.obj: src/tests/unit_x509.cpp
	$(CXX) $(BUILD_FLAGS)  /Ibuild\include /Ibuild\include\external /nologo /c src/tests/unit_x509.cpp /Fo$@





