
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <sstd/boost/mpl/reverse.hpp>

#include <sstd/boost/mpl/list_c.hpp>
#include <sstd/boost/mpl/range_c.hpp>
#include <sstd/boost/mpl/equal.hpp>
#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/at.hpp>

#include <sstd/boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef list_c<int,9,8,7,6,5,4,3,2,1,0> numbers;
    typedef reverse< numbers >::type result;

    typedef range_c<int,0,10> answer;

    MPL_ASSERT(( equal< result,answer,equal_to<_1,_2> > ));
}

