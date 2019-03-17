
ASM_FILES_TOBUILD = $$PWD/../sstd/libs/context/src/asm/make_x86_64_ms_pe_masm.asm \
    $$PWD/../sstd/libs/context/src/asm/jump_x86_64_ms_pe_masm.asm \
    $$PWD/../sstd/libs/context/src/asm/ontop_x86_64_ms_pe_masm.asm

#use ml64 to build asm files
asm_cl.input =         ASM_FILES_TOBUILD
asm_cl.output =        ${QMAKE_FILE_BASE}.obj
asm_cl.variable_out =  OBJECTS
asm_cl.commands =      ml64 /nologo /Cp /Cx /Zp4 /DBOOST_CONTEXT_EXPORT=EXPORT /Fo ${QMAKE_FILE_OUT} /c ${QMAKE_FILE_NAME}
asm_cl.dependency_type = TYPE_C

QMAKE_EXTRA_COMPILERS += asm_cl
export(QMAKE_EXTRA_COMPILERS)

