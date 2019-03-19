
win32-msvc*{
    SOURCES              += $$PWD/msvc/botan_all.cpp
    INCLUDEPATH          += $$PWD/msvc/build/include
    INCLUDEPATH          += $$PWD/msvc/build/include/external
    DEFINES              *= BOTAN_USE_MSVC_
    QMAKE_CXXFLAGS       += /bigobj
    DEFINES              *= BOTAN_DLL=__declspec(dllexport)
    DEFINES              *= _ENABLE_EXTENDED_ALIGNED_STORAGE
    DEFINES              *= _CRT_SECURE_NO_WARNINGS
    LIBS                 += user32.lib ws2_32.lib
}

win32-g++*{
    SOURCES              += $$PWD/mingw_gcc/botan_all.cpp
    INCLUDEPATH          += $$PWD/mingw_gcc/build/include
    INCLUDEPATH          += $$PWD/mingw_gcc/build/include/external
    DEFINES              *= BOTAN_USE_MINGW_GCC_
    LIBS                 += ws2_32.lib
    DEFINES              *= _REENTRANT
}

HEADERS += $$PWD/sstd_botan.hpp

