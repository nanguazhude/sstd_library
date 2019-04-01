// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/back.hpp>
#include <sstd/boost/hana/drop_front.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/front.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/is_empty.hpp>
#include <sstd/boost/hana/not.hpp>
#include <sstd/boost/hana/range.hpp>
namespace hana = boost::hana;


constexpr auto r = hana::make_range(hana::int_c<0>, hana::int_c<1000>);
BOOST_HANA_CONSTANT_CHECK(hana::front(r) == hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::back(r) == hana::int_c<999>);
BOOST_HANA_CONSTANT_CHECK(hana::drop_front(r) == hana::make_range(hana::int_c<1>, hana::int_c<1000>));
BOOST_HANA_CONSTANT_CHECK(!hana::is_empty(r));
BOOST_HANA_CONSTANT_CHECK(hana::is_empty(hana::make_range(hana::int_c<3>, hana::int_c<3>)));

int main() { }

