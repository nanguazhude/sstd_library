
#cplusplus version
include($$PWD/cplusplus_basic.pri)

#boost
INCLUDEPATH += $$PWD/sstd_boost
include($$PWD/sstd_boost/sstd_boost.pri)

#import
include($$PWD/sstd_build_path.pri)
CONFIG(debug,debug|release){
    LIBS += -L$${SSTD_LIBRARY_OUTPUT_PATH} -lsstd_library_debug
}else{
    LIBS += -L$${SSTD_LIBRARY_OUTPUT_PATH} -lsstd_library
}




