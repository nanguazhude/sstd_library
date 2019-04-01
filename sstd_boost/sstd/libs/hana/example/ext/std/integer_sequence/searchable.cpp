// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/ext/std/integer_sequence.hpp>
#include <sstd/boost/hana/ext/std/integral_constant.hpp>
#include <sstd/boost/hana/find.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/optional.hpp>

#include <type_traits>
#include <utility>
namespace hana = boost::hana;


constexpr std::integer_sequence<int, 1, 2, 3, 4> xs{};

BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::find(xs, hana::int_c<3>),
    hana::just(std::integral_constant<int, 3>{})
));

int main() { }

