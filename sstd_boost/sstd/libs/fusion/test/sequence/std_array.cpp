//
// Copyright (C) 2013 Mateusz Loskot <mateusz@loskot.net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
#include <sstd/boost/config.hpp>

#ifdef BOOST_NO_CXX11_HDR_ARRAY
#   error "does not meet requirements"
#endif

#ifdef BOOST_MSVC
#pragma warning(disable:4180)
#endif
#include <sstd/boost/detail/lightweight_test.hpp>

#include <sstd/boost/fusion/adapted/std_array.hpp>
#include <array>

#include <sstd/boost/fusion/sequence/intrinsic.hpp>
#include <sstd/boost/fusion/support/is_sequence.hpp>
#include <sstd/boost/fusion/support/is_view.hpp>
#include <sstd/boost/fusion/iterator.hpp>

#include <sstd/boost/mpl/assert.hpp>

int main()
{
    using namespace boost::fusion;
    typedef std::array<int,3> array_type;

    BOOST_MPL_ASSERT((traits::is_sequence<array_type>));
    BOOST_MPL_ASSERT_NOT((traits::is_view<array_type>));
    BOOST_STATIC_ASSERT(traits::is_sequence<array_type>::value);
    BOOST_STATIC_ASSERT(!traits::is_view<array_type>::value);

    array_type arr = {{1,2,3}};

    BOOST_TEST(*boost::fusion::begin(arr) == 1);
    BOOST_TEST(*boost::fusion::next(boost::fusion::begin(arr)) == 2);
    BOOST_TEST(*advance_c<2>(boost::fusion::begin(arr)) == 3);
    BOOST_TEST(prior(boost::fusion::next(boost::fusion::begin(arr))) == boost::fusion::begin(arr));
    BOOST_TEST(*prior(boost::fusion::end(arr)) == 3);
    BOOST_TEST(at_c<2>(arr) == 3);
    BOOST_TEST(boost::fusion::size(arr) == 3);
    BOOST_TEST(distance(boost::fusion::begin(arr), boost::fusion::end(arr)) == 3);

    return boost::report_errors();
}

