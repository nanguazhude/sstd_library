// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/core/make.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/tuple.hpp>
namespace hana = boost::hana;


BOOST_HANA_CONSTANT_CHECK(hana::make<hana::tuple_tag>() == hana::make_tuple());
static_assert(hana::make<hana::tuple_tag>(1, '2', 3.3) == hana::make_tuple(1, '2', 3.3), "");

int main() { }
