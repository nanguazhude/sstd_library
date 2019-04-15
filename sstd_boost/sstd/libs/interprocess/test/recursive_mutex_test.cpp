//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2004-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <sstd/boost/interprocess/detail/config_begin.hpp>
#include <sstd/boost/interprocess/detail/workaround.hpp>
#if defined(BOOST_INTERPROCESS_WINDOWS)
#include <sstd/boost/interprocess/sync/windows/recursive_mutex.hpp>
#include <sstd/boost/interprocess/sync/spin/recursive_mutex.hpp>
#endif
#include <sstd/boost/interprocess/sync/interprocess_recursive_mutex.hpp>
#include <sstd/boost/interprocess/sync/scoped_lock.hpp>
#include "mutex_test_template.hpp"

int main ()
{
   using namespace boost::interprocess;
   #if defined(BOOST_INTERPROCESS_WINDOWS)
      //
      test::test_all_lock<ipcdetail::windows_recursive_mutex>();
      test::test_all_mutex<ipcdetail::windows_recursive_mutex>();
      test::test_all_recursive_lock<ipcdetail::windows_recursive_mutex>();
      //
      test::test_all_lock<ipcdetail::spin_recursive_mutex>();
      test::test_all_mutex<ipcdetail::spin_recursive_mutex>();
      test::test_all_recursive_lock<ipcdetail::spin_recursive_mutex>();
   #endif
   //
   test::test_all_lock<interprocess_recursive_mutex>();
   test::test_all_mutex<interprocess_recursive_mutex>();
   test::test_all_recursive_lock<interprocess_recursive_mutex>();

   return 0;
}

#include <sstd/boost/interprocess/detail/config_end.hpp>
