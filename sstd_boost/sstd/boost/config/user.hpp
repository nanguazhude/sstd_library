
#pragma once

#ifndef BOOST_ALL_DYN_LINK
#define BOOST_ALL_DYN_LINK               (1u)
#endif

#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB                 (1u)
#endif

//#ifndef BOOST_ASIO_DYN_LINK
//#define BOOST_ASIO_DYN_LINK              (1u)
//#endif

#if defined(SSTD_BUILD_BOOST_SOURCE)

#if defined(_WIN32)

#ifndef BOOST_USE_WINDOWS_H
#define BOOST_USE_WINDOWS_H              (1u)
#endif

#endif

#endif

//BOOST_ATOMIC_SOURCE
//BOOST_CHRONO_SOURCE
//BOOST_DATE_TIME_SOURCE
//BOOST_SYSTEM_SOURCE
//BOOST_THREAD_BUILD_DLL
//BOOST_CONTEXT_SOURCE
//BOOST_REGEX_SOURCE
