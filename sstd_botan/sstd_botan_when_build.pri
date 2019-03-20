
win32-msvc*{
    SOURCES              += $$PWD/msvc/botan_all.cpp
    HEADERS              += $$PWD/msvc/botan_all.h
    INCLUDEPATH          += $$PWD/msvc/build/include
    INCLUDEPATH          += $$PWD/msvc/build/include/external
    DEFINES              *= BOTAN_USE_MSVC_
    QMAKE_CXXFLAGS       += /bigobj
    DEFINES              *= _ENABLE_EXTENDED_ALIGNED_STORAGE
    DEFINES              *= _CRT_SECURE_NO_WARNINGS
    LIBS                 += user32.lib ws2_32.lib
}

win32-g++*{
    SOURCES              += $$PWD/mingw_gcc/botan_all.cpp
    HEADERS              += $$PWD/mingw_gcc/botan_all.h
    INCLUDEPATH          += $$PWD/mingw_gcc/build/include
    INCLUDEPATH          += $$PWD/mingw_gcc/build/include/external
    DEFINES              *= BOTAN_USE_MINGW_GCC_
    LIBS                 += -lws2_32
    DEFINES              *= _REENTRANT
    CONFIG(debug,debug|release){
        QMAKE_CXXFLAGS += -Wa,-mbig-obj
    }
}

linux-g++*{
    SOURCES              += $$PWD/linux_gcc/botan_all.cpp
    HEADERS              += $$PWD/linux_gcc/botan_all.h
    INCLUDEPATH          += $$PWD/linux_gcc/build/include
    INCLUDEPATH          += $$PWD/linux_gcc/build/include/external
    DEFINES              *= BOTAN_USE_LINUX_GCC_
    DEFINES              *= _REENTRANT
    CONFIG(debug,debug|release){
        QMAKE_CXXFLAGS += -Wa,-mbig-obj
    }
}

HEADERS += $$PWD/sstd_botan.hpp
SOURCES += $$PWD/sstd_botan.cpp



