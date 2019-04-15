//
// Copyright 2013 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#include <sstd/boost/gil.hpp>
#include <sstd/boost/gil/extension/toolbox/metafunctions/is_bit_aligned.hpp>

#include <sstd/boost/test/unit_test.hpp>
#include <sstd/boost/type_traits/is_same.hpp>

using namespace boost;
using namespace gil;

BOOST_AUTO_TEST_SUITE( toolbox_tests )

BOOST_AUTO_TEST_CASE( is_bit_aligned_test )
{
    typedef bit_aligned_image1_type< 4, gray_layout_t>::type image_t;
    BOOST_STATIC_ASSERT(( is_bit_aligned< image_t::view_t::value_type >::value ));
}

BOOST_AUTO_TEST_SUITE_END()
