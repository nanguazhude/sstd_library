/*
   Copyright (c) Marshall Clow 2014.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#include <iostream>

#include <sstd/boost/config.hpp>
#include <sstd/boost/algorithm/algorithm.hpp>

#define BOOST_TEST_MAIN
#include <sstd/boost/test/unit_test.hpp>

namespace ba = boost::algorithm;

BOOST_AUTO_TEST_CASE( test_main )
{
//  Second argument must be an integral value
    BOOST_CHECK ( ba::power(1, 1.0) == 1);
}
