//
// Copyright 2013 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#include <sstd/boost/test/unit_test.hpp>

#include <sstd/boost/type_traits/is_same.hpp>

#include <sstd/boost/gil.hpp>
#include <sstd/boost/gil/extension/toolbox/color_converters/gray_to_rgba.hpp>

using namespace boost;
using namespace gil;

BOOST_AUTO_TEST_SUITE( toolbox_tests )

BOOST_AUTO_TEST_CASE( gray_to_rgba_test )
{
    gray8_pixel_t a( 45 );
    rgba8_pixel_t b;

    color_convert( a, b );
}

BOOST_AUTO_TEST_SUITE_END()
