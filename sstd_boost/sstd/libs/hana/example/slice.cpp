// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/core/to.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/filter.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/length.hpp>
#include <sstd/boost/hana/mod.hpp>
#include <sstd/boost/hana/range.hpp>
#include <sstd/boost/hana/slice.hpp>
#include <sstd/boost/hana/tuple.hpp>
#include <sstd/boost/hana/type.hpp>
namespace hana = boost::hana;
using namespace hana::literals;


// Slice a contiguous range
constexpr auto xs = hana::make_tuple(0, '1', 2.2, 3_c, hana::type_c<float>);

static_assert(
    hana::slice(xs, hana::tuple_c<std::size_t, 1, 2, 3>) ==
    hana::make_tuple('1', 2.2, 3_c)
, "");


// A more complex example with a non-contiguous range
constexpr auto letters = hana::to_tuple(hana::range_c<char, 'a', 'z'>);
constexpr auto indices = hana::to_tuple(hana::make_range(hana::size_c<0>, hana::length(letters)));

auto even_indices = hana::filter(indices, [](auto n) {
    return n % hana::size_c<2> == hana::size_c<0>;
});

BOOST_HANA_CONSTANT_CHECK(
    hana::slice(letters, even_indices) == hana::tuple_c<char,
        'a', 'c', 'e', 'g', 'i', 'k', 'm', 'o', 'q', 's', 'u', 'w', 'y'
    >
);

int main() { }

