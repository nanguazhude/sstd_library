//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_HPP
#define BOOST_COMPUTE_HPP

#include <sstd/boost/compute/algorithm.hpp>
#include <sstd/boost/compute/allocator.hpp>
#include <sstd/boost/compute/async.hpp>
#include <sstd/boost/compute/buffer.hpp>
#include <sstd/boost/compute/cl.hpp>
#include <sstd/boost/compute/command_queue.hpp>
#include <sstd/boost/compute/config.hpp>
#include <sstd/boost/compute/container.hpp>
#include <sstd/boost/compute/context.hpp>
#include <sstd/boost/compute/device.hpp>
#include <sstd/boost/compute/functional.hpp>
#include <sstd/boost/compute/image.hpp>
#include <sstd/boost/compute/iterator.hpp>
#include <sstd/boost/compute/kernel.hpp>
#include <sstd/boost/compute/lambda.hpp>
#include <sstd/boost/compute/pipe.hpp>
#include <sstd/boost/compute/platform.hpp>
#include <sstd/boost/compute/program.hpp>
#include <sstd/boost/compute/random.hpp>
#include <sstd/boost/compute/svm.hpp>
#include <sstd/boost/compute/system.hpp>
#include <sstd/boost/compute/types.hpp>
#include <sstd/boost/compute/user_event.hpp>
#include <sstd/boost/compute/utility.hpp>
#include <sstd/boost/compute/version.hpp>

#ifdef BOOST_COMPUTE_HAVE_HDR_CL_EXT
#include <sstd/boost/compute/cl_ext.hpp>
#endif

#endif // BOOST_COMPUTE_HPP
