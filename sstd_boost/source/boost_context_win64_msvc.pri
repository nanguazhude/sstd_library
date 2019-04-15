
ASM_FILES_TOBUILD = $$PWD/../sstd/libs/context/src/asm/make_x86_64_ms_pe_masm.asm \
    $$PWD/../sstd/libs/context/src/asm/jump_x86_64_ms_pe_masm.asm \
    $$PWD/../sstd/libs/context/src/asm/ontop_x86_64_ms_pe_masm.asm

#use ml64 to build asm files
asm_cl64.input =         ASM_FILES_TOBUILD
asm_cl64.output =        boost_${QMAKE_FILE_BASE}.obj
asm_cl64.variable_out =  OBJECTS
asm_cl64.commands =      ml64 /Cp /Cx /Zp4 /DBOOST_CONTEXT_EXPORT=EXPORT /Fo ${QMAKE_FILE_OUT} /c ${QMAKE_FILE_NAME}

QMAKE_EXTRA_COMPILERS += asm_cl64
export(QMAKE_EXTRA_COMPILERS)
