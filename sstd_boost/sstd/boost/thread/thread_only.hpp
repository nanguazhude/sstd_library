#ifndef BOOST_THREAD_THREAD_ONLY_HPP
#define BOOST_THREAD_THREAD_ONLY_HPP

//  thread.hpp
//
//  (C) Copyright 2013 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/thread/detail/platform.hpp>

#if defined(BOOST_THREAD_PLATFORM_WIN32)
#include <sstd/boost/thread/win32/thread_data.hpp>
#elif defined(BOOST_THREAD_PLATFORM_PTHREAD)
#include <sstd/boost/thread/pthread/thread_data.hpp>
#else
#error "Boost threads unavailable on this platform"
#endif

#include <sstd/boost/thread/detail/thread.hpp>
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
#include <sstd/boost/thread/detail/thread_interruption.hpp>
#endif
#include <sstd/boost/thread/condition_variable.hpp>


#endif
