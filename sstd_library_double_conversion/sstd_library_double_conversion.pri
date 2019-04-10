SOURCES += \
    $$PWD/double-conversion/bignum.cc \
    $$PWD/double-conversion/bignum-dtoa.cc \
    $$PWD/double-conversion/cached-powers.cc \
    $$PWD/double-conversion/diy-fp.cc \
    $$PWD/double-conversion/double-conversion.cc \
    $$PWD/double-conversion/fast-dtoa.cc \
    $$PWD/double-conversion/fixed-dtoa.cc \
    $$PWD/double-conversion/strtod.cc

INCLUDEPATH += $$PWD

SOURCES += $$PWD/sstd_library_double_conversion.cpp
HEADERS += $$PWD/sstd_library_double_conversion.hpp

