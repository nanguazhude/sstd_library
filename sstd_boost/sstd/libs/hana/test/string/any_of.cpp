// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/any_of.hpp>
#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/not.hpp>
#include <sstd/boost/hana/string.hpp>
namespace hana = boost::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::any_of(
        BOOST_HANA_STRING("abcd"),
        hana::equal.to(hana::char_c<'b'>)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::any_of(
        BOOST_HANA_STRING(""),
        hana::always(hana::true_c)
    )));

    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::any_of(
        BOOST_HANA_STRING("abcd"),
        hana::equal.to(hana::char_c<'z'>)
    )));
}
