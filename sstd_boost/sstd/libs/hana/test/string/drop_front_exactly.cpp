// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/drop_front_exactly.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/string.hpp>
namespace hana = boost::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_front_exactly(BOOST_HANA_STRING("a")),
        BOOST_HANA_STRING("")
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_front_exactly(BOOST_HANA_STRING("ab")),
        BOOST_HANA_STRING("b")
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_front_exactly(BOOST_HANA_STRING("abc")),
        BOOST_HANA_STRING("bc")
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_front_exactly(BOOST_HANA_STRING("abcdefghijk")),
        BOOST_HANA_STRING("bcdefghijk")
    ));


    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_front_exactly(BOOST_HANA_STRING("abc"), hana::size_c<2>),
        BOOST_HANA_STRING("c")
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_front_exactly(BOOST_HANA_STRING("abcdefghijk"), hana::size_c<3>),
        BOOST_HANA_STRING("defghijk")
    ));
}
