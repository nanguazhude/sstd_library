
TEMPLATE = app

QT -= gui
QT -= core

CONFIG += console

SOURCES += main.cpp

CONFIG(debug,debug|release){
    TARGET = sstd_boost_helper_debug
}else{
    TARGET = sstd_boost_helper
}

include($$PWD/../../cplusplus_basic.pri)

include($$PWD/../../sstd_build_path.pri)
DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}
