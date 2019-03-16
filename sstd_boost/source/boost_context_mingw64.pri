
ASM_FILES_TOBUILD += $$PWD/sstd/libs/context/src/asm/make_x86_64_ms_pe_masm.asm
ASM_FILES_TOBUILD += $$PWD/sstd/libs/context/src/asm/jump_x86_64_ms_pe_masm.asm
ASM_FILES_TOBUILD += $$PWD/sstd/libs/context/src/asm/ontop_x86_64_ms_pe_masm.asm

DISTFILES +=   $$ASM_FILES_TOBUILD

#use gcc to build .S files
asm_gcc.input =         ASM_FILES_TOBUILD
asm_gcc.output =        ${QMAKE_FILE_BASE}.obj
asm_gcc.variable_out =  OBJECTS
asm_gcc.commands =      ml64 /nologo /Cp /Cx /Zp4 /DBOOST_CONTEXT_EXPORT=EXPORT /Fo ${QMAKE_FILE_OUT} /c ${QMAKE_FILE_NAME}


