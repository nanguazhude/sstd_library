
ASM_FILES_TOBUILD = $$PWD/../sstd/libs/context/src/asm/make_x86_64_sysv_elf_gas.S \
    $$PWD/../sstd/libs/context/src/asm/jump_x86_64_sysv_elf_gas.S \
    $$PWD/../sstd/libs/context/src/asm/ontop_x86_64_sysv_elf_gas.S

#use gcc to build .S files
asm_gcc.input =         ASM_FILES_TOBUILD
asm_gcc.output =        boost_${QMAKE_FILE_BASE}.o
asm_gcc.variable_out =  OBJECTS
asm_gcc.commands =      g++ -x assembler-with-cpp -fPIC -m64 -pthread -O3 -finline-functions -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}

QMAKE_EXTRA_COMPILERS += asm_gcc
export(QMAKE_EXTRA_COMPILERS)
