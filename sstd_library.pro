TEMPLATE = lib

QT -= gui
QT -= core

CONFIG(debug,debug|release){
    TARGET = sstd_library_debug
}else{
    TARGET = sstd_library
}

#boost
INCLUDEPATH += $$PWD/sstd_boost
include($$PWD/cplusplus_basic.pri)
include($$PWD/sstd_boost/sstd_boost.pri)
include($$PWD/sstd_boost/sstd_boost_when_build.pri)
include($$PWD/sstd_botan/sstd_botan.pri)

#output path
include($$PWD/sstd_build_path.pri)
DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}

equals(TEMPLATE, "vclib") {
    SOURCES += $$ASM_FILES_TOBUILD
}else{
    DISTFILES += $$ASM_FILES_TOBUILD
}

DEFINES *= SSTD_BUILD_SOURCE
HEADERS += $$PWD/sstd_library.hpp
HEADERS += $$PWD/global_sstd_library.hpp

HEADERS += $$PWD/sstd_library_memory/sstd_library_memory.hpp
SOURCES += $$PWD/sstd_library_memory/sstd_library_memory.cpp

HEADERS += $$PWD/sstd_library_exception/sstd_library_exception.hpp
SOURCES += $$PWD/sstd_library_exception/sstd_library_exception.cpp

HEADERS += $$PWD/sstd_library_function/sstd_library_function.hpp
SOURCES += $$PWD/sstd_library_function/sstd_library_function.cpp

#remove some build warning
win32-msvc*{
    QMAKE_CXXFLAGS += /wd"4251"
    QMAKE_CXXFLAGS += /wd"4250"
    QMAKE_CXXFLAGS += /wd"4275"
    QMAKE_CXXFLAGS += /wd"26439"
    QMAKE_CXXFLAGS += /wd"26444"
    QMAKE_CXXFLAGS += /wd"26495"
    QMAKE_CXXFLAGS += /wd"4244"
    QMAKE_CXXFLAGS += /wd"4267"
    QMAKE_CXXFLAGS += /wd"4334"
}else{
    QMAKE_CXXFLAGS += -Wno-unused-parameter
    QMAKE_CXXFLAGS += -Wno-deprecated-declarations
}

