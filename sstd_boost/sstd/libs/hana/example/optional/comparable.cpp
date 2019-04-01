// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/not_equal.hpp>
#include <sstd/boost/hana/optional.hpp>
namespace hana = boost::hana;


BOOST_HANA_CONSTANT_CHECK(hana::nothing == hana::nothing);
static_assert(hana::just('x') == hana::just('x'), "");
static_assert(hana::just('x') != hana::just('y'), "");
BOOST_HANA_CONSTANT_CHECK(hana::just('x') != hana::nothing);

int main() { }

