
win32-msvc*{
#    CONFIG += utf8_source

    QMAKE_CXXFLAGS += /std:c++latest
    CONFIG += suppress_vcproj_warnings
}else{
    CONFIG += c++17
    QMAKE_CFLAGS += -std=c11
    LIBS += -lstdc++fs
    LIBS += -lpthread
    LIBS += -lz
    LIBS += -lwsock32
}

!win32{
    LIBS += -ldl
    LIBS += -lrt
}else{
    LIBS += -lws2_32
}

CONFIG(debug,debug|release) {
    DEFINES *= _DEBUG
}else{
    DEFINES *= NDEBUG
}

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}
