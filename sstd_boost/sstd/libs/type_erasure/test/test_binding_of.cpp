// Boost.TypeErasure library
//
// Copyright 2011 Steven Watanabe
//
// Distributed under the Boost Software License Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#include <sstd/boost/type_erasure/any.hpp>
#include <sstd/boost/type_erasure/tuple.hpp>
#include <sstd/boost/type_erasure/builtin.hpp>
#include <sstd/boost/type_erasure/operators.hpp>
#include <sstd/boost/type_erasure/any_cast.hpp>
#include <sstd/boost/type_erasure/binding_of.hpp>
#include <sstd/boost/mpl/vector.hpp>

#define BOOST_TEST_MAIN
#include <sstd/boost/test/unit_test.hpp>

using namespace boost::type_erasure;

template<class T = _self>
struct common : ::boost::mpl::vector<
    copy_constructible<T>,
    typeid_<T>
> {};

BOOST_AUTO_TEST_CASE(test_binding_of)
{
    typedef ::boost::mpl::vector<common<> > test_concept;
    any<test_concept> x(2);
    binding<test_concept> b = binding_of(x);
    binding<test_concept> expected(
        make_binding<
            ::boost::mpl::map< ::boost::mpl::pair<_self, int> >
        >());
    BOOST_CHECK(b == expected);
}

