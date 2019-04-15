// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/fill.hpp>
#include <sstd/boost/hana/tuple.hpp>
#include <sstd/boost/hana/type.hpp>
namespace hana = boost::hana;


struct x1;
struct x2;
struct x3;
struct z;

int main() {
    // fill a tuple_t with a hana::type
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::fill(hana::tuple_t<>, hana::type_c<z>),
        hana::tuple_t<>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::fill(hana::tuple_t<x1>, hana::type_c<z>),
        hana::tuple_t<z>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::fill(hana::tuple_t<x1, x2>, hana::type_c<z>),
        hana::tuple_t<z, z>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::fill(hana::tuple_t<x1, x2, x3>, hana::type_c<z>),
        hana::tuple_t<z, z, z>
    ));
}
