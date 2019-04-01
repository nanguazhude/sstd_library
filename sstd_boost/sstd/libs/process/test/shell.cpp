// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MAIN
#define BOOST_TEST_IGNORE_SIGCHLD
#include <sstd/boost/test/included/unit_test.hpp>
#include <iostream>


#include <sstd/boost/process/cmd.hpp>
#include <sstd/boost/process/args.hpp>
#include <sstd/boost/process/pipe.hpp>
#include <sstd/boost/process/io.hpp>
#include <sstd/boost/process/error.hpp>
#include <sstd/boost/process/child.hpp>
#include <sstd/boost/process/shell.hpp>

namespace bp = boost::process;

BOOST_AUTO_TEST_CASE(shell_simple, *boost::unit_test::timeout(5))
{
    using boost::unit_test::framework::master_test_suite;

    std::error_code ec;
    BOOST_CHECK(!ec);

    bp::ipstream p;

    bp::child c(master_test_suite().argv[1],
            bp::shell,
            bp::args+={"test", "--echo-stdout", "hello"},
            ec,
            bp::std_out > p);
    BOOST_CHECK(!ec);

    if (ec)
        std::cerr << ec.message() << std::endl;
    std::string s;

    BOOST_TEST_CHECKPOINT("Starting read");
    p >> s;
    BOOST_TEST_CHECKPOINT("Finished read");

    BOOST_CHECK_EQUAL(s, "hello");
}

BOOST_AUTO_TEST_CASE(shell_error, *boost::unit_test::timeout(5))
{
    std::error_code ec;


    auto c2 = bp::child("doesnt-exist", bp::shell, ec);
    BOOST_CHECK(!ec);

    c2.wait();
    BOOST_CHECK(c2.exit_code() != 0);
}

