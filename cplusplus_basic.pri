
win32-msvc*{
    QMAKE_CXXFLAGS += /std:c++latest
    CONFIG += utf8_source
}else{
    CONFIG += c++17
    LIBS += -lstdc++fs
}

win32-msvc*{
    CONFIG+=suppress_vcproj_warnings
}else{
    QMAKE_CFLAGS += -std=c11
}

CONFIG(debug,debug|release) {
    DEFINES *= _DEBUG
}else{
    DEFINES *= NDEBUG
}


















