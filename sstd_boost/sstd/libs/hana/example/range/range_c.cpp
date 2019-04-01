// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/back.hpp>
#include <sstd/boost/hana/drop_front.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/front.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/range.hpp>
namespace hana = boost::hana;


BOOST_HANA_CONSTANT_CHECK(hana::front(hana::range_c<int, 0, 5>) == hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::back(hana::range_c<unsigned long, 0, 5>) == hana::ulong_c<4>);
BOOST_HANA_CONSTANT_CHECK(hana::drop_front(hana::range_c<int, 0, 5>) == hana::make_range(hana::int_c<1>, hana::int_c<5>));

int main() { }

