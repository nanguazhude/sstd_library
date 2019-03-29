
TEMPLATE = app

include($$PWD/../sstd_library.pri)

SOURCES += $$PWD/source/lua_lua.cpp

TARGET = lua
DESTDIR = $$SSTD_LIBRARY_OUTPUT_PATH


