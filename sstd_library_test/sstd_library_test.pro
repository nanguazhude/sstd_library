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

SOURCES += $$PWD/constexpr_test.cpp
SOURCES += $$PWD/tuple_test.cpp
SOURCES += $$PWD/static_type_test.cpp
SOURCES += $$PWD/gc_manager_test.cpp
SOURCES += $$PWD/number_conversion.cpp

include($$PWD/../sstd_library.pri)
DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}





