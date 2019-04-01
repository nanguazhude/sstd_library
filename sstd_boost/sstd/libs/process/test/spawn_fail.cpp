// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/system/error_code.hpp>

#include <sstd/boost/asio.hpp>
#include <sstd/boost/algorithm/string/predicate.hpp>

#include <sstd/boost/process/error.hpp>
#include <sstd/boost/process/io.hpp>
#include <sstd/boost/process/args.hpp>
#include <sstd/boost/process/spawn.hpp>
#include <sstd/boost/process/async_pipe.hpp>
#include <sstd/boost/process/async.hpp>
#include <system_error>

#include <sstd/boost/filesystem.hpp>

#include <string>
#include <istream>
#include <cstdlib>
#if defined(BOOST_WINDOWS_API)
#   include <windows.h>
typedef boost::asio::windows::stream_handle pipe_end;
#elif defined(BOOST_POSIX_API)
#   include <sys/wait.h>
#   include <unistd.h>
typedef boost::asio::posix::stream_descriptor pipe_end;
#endif

namespace fs = boost::filesystem;
namespace bp = boost::process;

int main()
{
    std::error_code ec;

    boost::asio::io_context ios;

    bp::spawn(
        "dummy",
        bp::on_exit([](int, const std::error_code&){}),
        ios,
        ec
    );
}




