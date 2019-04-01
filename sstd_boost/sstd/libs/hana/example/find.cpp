// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/find.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/map.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/pair.hpp>
#include <sstd/boost/hana/tuple.hpp>
#include <sstd/boost/hana/type.hpp>
namespace hana = boost::hana;


BOOST_HANA_CONSTANT_CHECK(
    hana::find(hana::make_tuple(hana::int_c<1>, hana::type_c<int>, '3'), hana::type_c<int>) == hana::just(hana::type_c<int>)
);
BOOST_HANA_CONSTANT_CHECK(
    hana::find(hana::make_tuple(hana::int_c<1>, hana::type_c<int>, '3'), hana::type_c<void>) == hana::nothing
);

constexpr auto m = hana::make_map(
    hana::make_pair(hana::int_c<2>, 2),
    hana::make_pair(hana::type_c<float>, 3.3),
    hana::make_pair(hana::type_c<char>, hana::type_c<int>)
);
static_assert(hana::find(m, hana::type_c<float>) == hana::just(3.3), "");

int main() { }

