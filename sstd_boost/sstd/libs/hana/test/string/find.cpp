// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/find.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/string.hpp>
namespace hana = boost::hana;


struct invalid { };

int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find(BOOST_HANA_STRING("abcd"), hana::char_c<'a'>),
        hana::just(hana::char_c<'a'>)
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find(BOOST_HANA_STRING("abcd"), hana::char_c<'c'>),
        hana::just(hana::char_c<'c'>)
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find(BOOST_HANA_STRING("abcd"), invalid{}),
        hana::nothing
    ));
}
