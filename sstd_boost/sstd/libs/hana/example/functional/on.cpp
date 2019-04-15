// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/first.hpp>
#include <sstd/boost/hana/functional/on.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/less.hpp>
#include <sstd/boost/hana/pair.hpp>
#include <sstd/boost/hana/plus.hpp>
#include <sstd/boost/hana/sort.hpp>
#include <sstd/boost/hana/tuple.hpp>
#include <sstd/boost/hana/type.hpp>
namespace hana = boost::hana;


// infix application
constexpr auto sorted = hana::sort.by(hana::less ^hana::on^ hana::first, hana::make_tuple(
    hana::make_pair(hana::int_c<3>, 'x'),
    hana::make_pair(hana::int_c<1>, hana::type_c<void>),
    hana::make_pair(hana::int_c<2>, 9876)
));

static_assert(sorted == hana::make_tuple(
    hana::make_pair(hana::int_c<1>, hana::type_c<void>),
    hana::make_pair(hana::int_c<2>, 9876),
    hana::make_pair(hana::int_c<3>, 'x')
), "");


// function call syntax
constexpr auto x = hana::make_pair(1, 2);
constexpr auto y = hana::make_pair(10, 20);
static_assert(hana::on(hana::plus, hana::first)(x, y) == 1 + 10, "");

int main() { }
