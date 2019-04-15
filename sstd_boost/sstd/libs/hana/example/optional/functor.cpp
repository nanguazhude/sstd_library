// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/functional/placeholder.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/transform.hpp>
namespace hana = boost::hana;


BOOST_HANA_CONSTANT_CHECK(hana::transform(hana::nothing, hana::_ + 1) == hana::nothing);
static_assert(hana::transform(hana::just(1), hana::_ + 1) == hana::just(2), "");

int main() { }
