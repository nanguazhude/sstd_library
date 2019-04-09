
win32-msvc*{
    QMAKE_CXXFLAGS += /std:c++latest
#    CONFIG += utf8_source
    CONFIG += suppress_vcproj_warnings
}else{
    CONFIG += c++17
    QMAKE_CFLAGS += -std=c11
    LIBS += -lstdc++fs
    LIBS += -lpthread
    LIBS += -lz
}

!win32{
    LIBS += -ldl
    LIBS += -lrt
}

CONFIG(debug,debug|release) {
    DEFINES *= _DEBUG
}else{
    DEFINES *= NDEBUG
}

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}

















