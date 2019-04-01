﻿//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_SPIN_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_DETAIL_SPIN_SEMAPHORE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <sstd/boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <sstd/boost/interprocess/detail/config_begin.hpp>
#include <sstd/boost/interprocess/detail/workaround.hpp>
#include <sstd/boost/interprocess/detail/atomic.hpp>
#include <sstd/boost/interprocess/detail/os_thread_functions.hpp>
#include <sstd/boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <sstd/boost/interprocess/sync/detail/common_algorithms.hpp>
#include <sstd/boost/interprocess/sync/detail/locks.hpp>
#include <sstd/boost/cstdint.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class spin_semaphore
{
   spin_semaphore(const spin_semaphore &);
   spin_semaphore &operator=(const spin_semaphore &);

   public:
   spin_semaphore(unsigned int initialCount);
   ~spin_semaphore();

   void post();
   void wait();
   bool try_wait();
   bool timed_wait(const boost::posix_time::ptime &abs_time);

//   int get_count() const;
   private:
   volatile boost::uint32_t m_count;
};


inline spin_semaphore::~spin_semaphore()
{}

inline spin_semaphore::spin_semaphore(unsigned int initialCount)
{  ipcdetail::atomic_write32(&this->m_count, boost::uint32_t(initialCount));  }

inline void spin_semaphore::post()
{
   ipcdetail::atomic_inc32(&m_count);
}

inline void spin_semaphore::wait()
{
   ipcdetail::lock_to_wait<spin_semaphore> lw(*this);
   return ipcdetail::try_based_lock(lw);
}

inline bool spin_semaphore::try_wait()
{
   return ipcdetail::atomic_add_unless32(&m_count, boost::uint32_t(-1), boost::uint32_t(0));
}

inline bool spin_semaphore::timed_wait(const boost::posix_time::ptime &abs_time)
{
   ipcdetail::lock_to_wait<spin_semaphore> lw(*this);
   return ipcdetail::try_based_timed_lock(lw, abs_time);
}

//inline int spin_semaphore::get_count() const
//{
   //return (int)ipcdetail::atomic_read32(&m_count);
//}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <sstd/boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_SPIN_SEMAPHORE_HPP
