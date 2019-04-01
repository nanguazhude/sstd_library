
// Copyright Aleksey Gurtovoy 2002-2010
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <sstd/boost/mpl/zip_view.hpp>

#include <sstd/boost/mpl/transform_view.hpp>
#include <sstd/boost/mpl/filter_view.hpp>
#include <sstd/boost/mpl/range_c.hpp>
#include <sstd/boost/mpl/vector.hpp>
#include <sstd/boost/mpl/at.hpp>
#include <sstd/boost/mpl/equal.hpp>
#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/unpack_args.hpp>
#include <sstd/boost/mpl/math/is_even.hpp>

#include <sstd/boost/mpl/aux_/test.hpp>

#include <sstd/boost/type_traits/is_same.hpp>


MPL_TEST_CASE()
{
    typedef transform_view<
          zip_view< vector< range_c<int,0,10>, range_c<int,10,20> > >
        , unpack_args< plus<> >
        > result;

    MPL_ASSERT(( equal<
          result
        , filter_view< range_c<int,10,30>, is_even<_> >
        , equal_to<_,_>
        > ));

    MPL_ASSERT(( boost::is_same< zip_view<vector<> >, zip_view<vector<> >::type > ));
}

