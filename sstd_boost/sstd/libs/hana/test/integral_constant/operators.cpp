// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/integral_constant.hpp>

#include <sstd/boost/hana/and.hpp>
#include <sstd/boost/hana/div.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/greater.hpp>
#include <sstd/boost/hana/greater_equal.hpp>
#include <sstd/boost/hana/less.hpp>
#include <sstd/boost/hana/less_equal.hpp>
#include <sstd/boost/hana/minus.hpp>
#include <sstd/boost/hana/mod.hpp>
#include <sstd/boost/hana/mult.hpp>
#include <sstd/boost/hana/negate.hpp>
#include <sstd/boost/hana/not.hpp>
#include <sstd/boost/hana/not_equal.hpp>
#include <sstd/boost/hana/or.hpp>
#include <sstd/boost/hana/plus.hpp>
namespace hana = boost::hana;


// Arithmetic operators
BOOST_HANA_CONSTANT_CHECK(+hana::int_c<1> == hana::int_c<1>);
BOOST_HANA_CONSTANT_CHECK(-hana::int_c<1> == hana::int_c<-1>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<1> + hana::int_c<2> == hana::int_c<3>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<1> - hana::int_c<2> == hana::int_c<-1>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<3> * hana::int_c<2> == hana::int_c<6>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<6> / hana::int_c<3> == hana::int_c<2>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<6> % hana::int_c<4> == hana::int_c<2>);
BOOST_HANA_CONSTANT_CHECK(~hana::int_c<6> == hana::int_c<~6>);
BOOST_HANA_CONSTANT_CHECK((hana::int_c<6> & hana::int_c<3>) == hana::int_c<6 & 3>);
BOOST_HANA_CONSTANT_CHECK((hana::int_c<4> | hana::int_c<2>) == hana::int_c<4 | 2>);
BOOST_HANA_CONSTANT_CHECK((hana::int_c<6> ^ hana::int_c<3>) == hana::int_c<6 ^ 3>);
BOOST_HANA_CONSTANT_CHECK((hana::int_c<6> << hana::int_c<3>) == hana::int_c<(6 << 3)>);
BOOST_HANA_CONSTANT_CHECK((hana::int_c<6> >> hana::int_c<3>) == hana::int_c<(6 >> 3)>);

// Comparison operators
BOOST_HANA_CONSTANT_CHECK(hana::int_c<0> == hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<1> != hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<0> < hana::int_c<1>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<0> <= hana::int_c<1>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<0> <= hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<1> > hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<1> >= hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<0> >= hana::int_c<0>);

// Logical operators
BOOST_HANA_CONSTANT_CHECK(hana::int_c<3> || hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<3> && hana::int_c<1>);
BOOST_HANA_CONSTANT_CHECK(!hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(!!hana::int_c<3>);

int main() { }

