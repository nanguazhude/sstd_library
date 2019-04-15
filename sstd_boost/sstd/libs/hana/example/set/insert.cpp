// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/insert.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/set.hpp>
#include <sstd/boost/hana/string.hpp>
#include <sstd/boost/hana/type.hpp>
namespace hana = boost::hana;


int main() {
    constexpr auto xs = hana::make_set(hana::int_c<0>, hana::type_c<int>);
    BOOST_HANA_CONSTANT_CHECK(
        hana::insert(xs, BOOST_HANA_STRING("abc")) ==
        hana::make_set(hana::int_c<0>, hana::type_c<int>, BOOST_HANA_STRING("abc"))
    );

    BOOST_HANA_CONSTANT_CHECK(
        hana::insert(xs, hana::int_c<0>) == hana::make_set(hana::int_c<0>, hana::type_c<int>)
    );
}
