
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <sstd/boost/mpl/unique.hpp>
#include <sstd/boost/mpl/list.hpp>
#include <sstd/boost/mpl/equal.hpp>
#include <sstd/boost/type_traits/is_same.hpp>

#include <sstd/boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef list<int,float,float,char,int,int,int,double> types;
    typedef unique< types, is_same<_1,_2> >::type result;

    typedef list<int,float,char,int,double>::type answer;
    MPL_ASSERT(( equal< result,answer > ));
}

