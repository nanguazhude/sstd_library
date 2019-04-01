// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/at_key.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/find.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/set.hpp>
namespace hana = boost::hana;


int main() {
    constexpr auto xs = hana::make_set(hana::int_c<0>, hana::int_c<1>, hana::int_c<2>);
    BOOST_HANA_CONSTANT_CHECK(hana::find(xs, hana::int_c<0>) == hana::just(hana::int_c<0>));
    BOOST_HANA_CONSTANT_CHECK(hana::find(xs, hana::int_c<3>) == hana::nothing);

    // operator[] is equivalent to at_key
    BOOST_HANA_CONSTANT_CHECK(xs[hana::int_c<2>] == hana::int_c<2>);

    // long_c<0> == int_<0>, and therefore int_<0> is found
    BOOST_HANA_CONSTANT_CHECK(xs[hana::long_c<0>] == hana::int_c<0>);
}

