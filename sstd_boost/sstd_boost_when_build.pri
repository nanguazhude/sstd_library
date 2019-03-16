
win32{
    DEFINES *= BOOST_USE_WINDOWS_H
}

DEFINES *= BOOST_ATOMIC_SOURCE
DEFINES *= BOOST_CHRONO_SOURCE
DEFINES *= BOOST_DATE_TIME_SOURCE
DEFINES *= BOOST_SYSTEM_SOURCE
DEFINES *= BOOST_THREAD_BUILD_DLL
DEFINES *= BOOST_CONTEXT_SOURCE

SOURCES += $$PWD/source/boost_atomic.cpp
SOURCES += $$PWD/source/boost_chrono.cpp
SOURCES += $$PWD/source/boost_system.cpp
SOURCES += $$PWD/source/boost_exception.cpp
SOURCES += $$PWD/source/boost_date_time.cpp
SOURCES += $$PWD/source/boost_thread.cpp
SOURCES += $$PWD/source/boost_context.cpp

win32-msvc*{

ASM_FILES_TOBUILD += $$PWD/sstd/libs/context/src/asm/make_x86_64_ms_pe_masm.asm
ASM_FILES_TOBUILD += $$PWD/sstd/libs/context/src/asm/jump_x86_64_ms_pe_masm.asm
ASM_FILES_TOBUILD += $$PWD/sstd/libs/context/src/asm/ontop_x86_64_ms_pe_masm.asm

DISTFILES +=   $$ASM_FILES_TOBUILD

#use ml64 to build asm files
asm_cl.input =         ASM_FILES_TOBUILD
asm_cl.output =        ${QMAKE_FILE_BASE}.obj
asm_cl.variable_out =  OBJECTS
asm_cl.commands =      ml64 /nologo /Cp /Cx /Zp4 /DBOOST_CONTEXT_EXPORT=EXPORT /Fo ${QMAKE_FILE_OUT} /c ${QMAKE_FILE_NAME}

QMAKE_EXTRA_COMPILERS += asm_cl
export(QMAKE_EXTRA_COMPILERS)

} else {

win32-g++*{

ASM_FILES_TOBUILD += $$PWD/sstd/libs/context/src/asm/make_x86_64_ms_pe_masm.asm
ASM_FILES_TOBUILD += $$PWD/sstd/libs/context/src/asm/jump_x86_64_ms_pe_masm.asm
ASM_FILES_TOBUILD += $$PWD/sstd/libs/context/src/asm/ontop_x86_64_ms_pe_masm.asm

DISTFILES +=   $$ASM_FILES_TOBUILD

#use gcc to build .S files
asm_gcc.input =         ASM_FILES_TOBUILD
asm_gcc.output =        ${QMAKE_FILE_BASE}.obj
asm_gcc.variable_out =  OBJECTS
asm_gcc.commands =      ml64 /nologo /Cp /Cx /Zp4 /DBOOST_CONTEXT_EXPORT=EXPORT /Fo ${QMAKE_FILE_OUT} /c ${QMAKE_FILE_NAME}

} else {


}#not win32-g++*

}#not win32-msvc*







