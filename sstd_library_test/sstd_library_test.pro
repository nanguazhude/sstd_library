TEMPLATE = app

QT -= core
QT -= gui

CONFIG(debug,debug|release){
    TARGET = test_sstd_library_debug
}else{
    TARGET = test_sstd_library
}

CONFIG += console

SOURCES += $$PWD/main.cpp

SOURCES += $$PWD/lua_full_test.cpp
HEADERS += $$PWD/lua_full_test.hpp

include($$PWD/../sstd_library.pri)
DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}





