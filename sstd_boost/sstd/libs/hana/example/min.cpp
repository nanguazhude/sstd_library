// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/min.hpp>
namespace hana = boost::hana;


static_assert(hana::min(1, 4) == 1, "");
BOOST_HANA_CONSTANT_CHECK(hana::min(hana::int_c<7>, hana::int_c<5>) == hana::int_c<5>);

int main() { }

