
win32-msvc*{
    INCLUDEPATH          += $$PWD/msvc/build/include
    INCLUDEPATH          += $$PWD/msvc/build/include/external
    DEFINES              *= BOTAN_USE_MSVC_
}

win32-g++*{
    INCLUDEPATH          += $$PWD/mingw_gcc/build/include
    INCLUDEPATH          += $$PWD/mingw_gcc/build/include/external
    DEFINES              *= BOTAN_USE_MINGW_GCC_
}

linux-g++*{
    INCLUDEPATH          += $$PWD/linux_gcc/build/include
    INCLUDEPATH          += $$PWD/linux_gcc/build/include/external
    DEFINES              *= BOTAN_USE_LINUX_GCC_
}


INCLUDEPATH += $$PWD
