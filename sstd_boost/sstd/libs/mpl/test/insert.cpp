
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License,Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <sstd/boost/mpl/insert.hpp>

#include <sstd/boost/mpl/find.hpp>
#include <sstd/boost/mpl/vector_c.hpp>
#include <sstd/boost/mpl/size.hpp>
#include <sstd/boost/mpl/range_c.hpp>
#include <sstd/boost/mpl/equal.hpp>
#include <sstd/boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef vector_c<int,0,1,3,4,5,6,7,8,9> numbers;
    typedef find< numbers,integral_c<int,3> >::type pos;
    typedef insert< numbers,pos,integral_c<int,2> >::type range;

    MPL_ASSERT_RELATION( size<range>::value, ==, 10 );
    MPL_ASSERT(( equal< range,range_c<int,0,10> > ));
}
