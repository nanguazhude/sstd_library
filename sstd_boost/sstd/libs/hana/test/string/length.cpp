// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/length.hpp>
#include <sstd/boost/hana/string.hpp>
namespace hana = boost::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::length(BOOST_HANA_STRING("")),
        hana::size_c<0>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::length(BOOST_HANA_STRING("a")),
        hana::size_c<1>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::length(BOOST_HANA_STRING("ab")),
        hana::size_c<2>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::length(BOOST_HANA_STRING("abc")),
        hana::size_c<3>
    ));
}
