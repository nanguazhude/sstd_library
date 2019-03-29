
TEMPLATE = app

QT -= core
QT -= gui

CONFIG += console

include($$PWD/../sstd_library.pri)

SOURCES += $$PWD/source/lua_lua.cpp

TARGET = lua
DESTDIR = $$SSTD_LIBRARY_OUTPUT_PATH


