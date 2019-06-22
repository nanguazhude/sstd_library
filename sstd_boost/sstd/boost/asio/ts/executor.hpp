//
// ts/executor.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TS_EXECUTOR_HPP
#define BOOST_ASIO_TS_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <sstd/boost/asio/async_result.hpp>
#include <sstd/boost/asio/associated_allocator.hpp>
#include <sstd/boost/asio/execution_context.hpp>
#include <sstd/boost/asio/is_executor.hpp>
#include <sstd/boost/asio/associated_executor.hpp>
#include <sstd/boost/asio/bind_executor.hpp>
#include <sstd/boost/asio/executor_work_guard.hpp>
#include <sstd/boost/asio/system_executor.hpp>
#include <sstd/boost/asio/executor.hpp>
#include <sstd/boost/asio/dispatch.hpp>
#include <sstd/boost/asio/post.hpp>
#include <sstd/boost/asio/defer.hpp>
#include <sstd/boost/asio/strand.hpp>
#include <sstd/boost/asio/packaged_task.hpp>
#include <sstd/boost/asio/use_future.hpp>

#endif // BOOST_ASIO_TS_EXECUTOR_HPP
