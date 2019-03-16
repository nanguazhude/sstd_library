TEMPLATE = app

QT -= core
QT -= gui

CONFIG(debug,debug|release){
    TARGET = test_sstd_library_debug
}else{
    TARGET = test_sstd_library
}

CONFIG += console

SOURCES += main.cpp

include($$PWD/../sstd_library.pri)
DESTDIR = $${SSTD_LIBRARY_OUTPUT_PATH}





