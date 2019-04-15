// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/power.hpp>
namespace hana = boost::hana;


BOOST_HANA_CONSTANT_CHECK(hana::power(hana::int_c<3>, hana::int_c<2>) == hana::int_c<3 * 3>);
static_assert(hana::power(2, hana::int_c<4>) == 16, "");

int main() { }
