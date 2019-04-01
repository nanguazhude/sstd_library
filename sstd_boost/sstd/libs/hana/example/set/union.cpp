// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/set.hpp>
#include <sstd/boost/hana/string.hpp>
#include <sstd/boost/hana/type.hpp>
#include <sstd/boost/hana/union.hpp>
namespace hana = boost::hana;
using namespace hana::literals;


constexpr auto xs = hana::make_set(hana::int_c<1>, hana::type_c<void>, hana::int_c<2>);
constexpr auto ys = hana::make_set(hana::int_c<2>, hana::type_c<int>, hana::int_c<3>);

BOOST_HANA_CONSTANT_CHECK(hana::union_(xs, ys) == hana::make_set(
    hana::int_c<1>, hana::int_c<2>, hana::int_c<3>, hana::type_c<void>, hana::type_c<int>
));

int main() { }

