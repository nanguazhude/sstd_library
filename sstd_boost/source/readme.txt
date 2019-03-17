


windows msvc :
b2 -d+2 --build-type=complete --toolset=msvc address-model=64 link=shared runtime-link=shared threading=multi

windows gcc :
b2 -d+2 --build-type=complete --toolset=gcc  address-model=64 link=shared runtime-link=shared threading=multi

linux gcc :
b2 -d+2 --toolset=gcc  address-model=64 link=shared runtime-link=shared threading=multi

only build some module
--with-context

















