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

















