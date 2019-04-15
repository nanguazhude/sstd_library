
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

#include <sstd/boost/static_assert.hpp>
#include <sstd/boost/mpl/filter_view.hpp>
#include <sstd/boost/mpl/transform_view.hpp>
#include <sstd/boost/mpl/max_element.hpp>
#include <sstd/boost/mpl/list.hpp>
#include <sstd/boost/mpl/sizeof.hpp>
#include <sstd/boost/mpl/deref.hpp>
#include <sstd/boost/mpl/equal.hpp>
#include <sstd/boost/mpl/aux_/test.hpp>

#include <sstd/boost/type_traits/is_float.hpp>
#include <sstd/boost/type_traits/is_same.hpp>

MPL_TEST_CASE()
{
    typedef mpl::list<int,float,long,float,char[50],long double,char> types;
    typedef mpl::list<float,float,long double> floats;

    MPL_ASSERT(( equal< mpl::filter_view< types,boost::is_float<_> >::type,floats > ));

    typedef mpl::max_element<
          mpl::transform_view<
              mpl::filter_view< types,boost::is_float<_> >
            , mpl::sizeof_<_>
            >
        >::type iter;

    MPL_ASSERT((is_same<mpl::deref<iter::base>::type, long double>));
}
