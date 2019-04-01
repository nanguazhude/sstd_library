
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

#include <sstd/boost/mpl/fold.hpp>
#include <sstd/boost/mpl/reverse_fold.hpp>
//#include <sstd/boost/mpl/vector.hpp>
#include <sstd/boost/mpl/list.hpp>
#include <sstd/boost/mpl/list_c.hpp>
#include <sstd/boost/mpl/equal.hpp>
#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/next.hpp>
#include <sstd/boost/mpl/push_front.hpp>
#include <sstd/boost/mpl/if.hpp>
#include <sstd/boost/mpl/less.hpp>
#include <sstd/boost/mpl/int.hpp>
#include <sstd/boost/mpl/at.hpp>
#include <sstd/boost/mpl/size.hpp>
#include <sstd/boost/type_traits/is_float.hpp>

#include <sstd/boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef list<long,float,short,double,float,long,long double> types;
    typedef fold<
          types
        , int_<0>
        , if_< boost::is_float<_2>,next<_1>,_1 >
        >::type number_of_floats;

    MPL_ASSERT_RELATION( number_of_floats::value, ==, 4 );
}

MPL_TEST_CASE()
{
    typedef list_c<int,5,-1,0,-7,-2,0,-5,4> numbers;
    typedef list_c<int,-1,-7,-2,-5> negatives;
    typedef reverse_fold<
          numbers
        , list_c<int>
        , if_< less< _2,int_<0> >, push_front<_1,_2>, _1 >
        >::type result;

    MPL_ASSERT(( equal< result,negatives,equal_to<_1,_2> > ));
}

