
win32{
    DEFINES *= BOOST_USE_WINDOWS_H
}

DEFINES *= BOOST_ATOMIC_SOURCE
DEFINES *= BOOST_CHRONO_SOURCE
DEFINES *= BOOST_DATE_TIME_SOURCE
DEFINES *= BOOST_SYSTEM_SOURCE
DEFINES *= BOOST_THREAD_BUILD_DLL
DEFINES *= BOOST_CONTEXT_SOURCE

SOURCES += $$PWD/source/boost_atomic.cpp
SOURCES += $$PWD/source/boost_chrono.cpp
SOURCES += $$PWD/source/boost_system.cpp
SOURCES += $$PWD/source/boost_exception.cpp
SOURCES += $$PWD/source/boost_date_time.cpp
SOURCES += $$PWD/source/boost_thread.cpp
SOURCES += $$PWD/source/boost_context.cpp

win32-msvc*{

#win64MSVC_ML64

}








