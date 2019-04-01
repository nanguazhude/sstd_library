/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <sstd/boost/detail/lightweight_test.hpp>
#include <sstd/boost/phoenix/core.hpp>
#include <sstd/boost/phoenix/operator.hpp>

namespace phoenix = boost::phoenix;

int
main()
{
    using phoenix::val;

    {
        BOOST_TEST(!(val(123) == 456)());
        BOOST_TEST((val(123) != 456)());
        BOOST_TEST(!(val(123) > 456)());
        BOOST_TEST((val(123) < 456)());
        BOOST_TEST(!(val(123) > 456)());
        BOOST_TEST((val(123) <= 123)());
        BOOST_TEST((val(123) >= 123)());
    }

    return boost::report_errors();
}

