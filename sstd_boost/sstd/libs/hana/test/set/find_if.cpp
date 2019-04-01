// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/at_key.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/find_if.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/set.hpp>

#include <laws/base.hpp>
namespace hana = boost::hana;
using hana::test::ct_eq;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(hana::make_set(), hana::equal.to(ct_eq<1>{})),
        hana::nothing
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(hana::make_set(ct_eq<1>{}), hana::equal.to(ct_eq<1>{})),
        hana::just(ct_eq<1>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(hana::make_set(ct_eq<1>{}), hana::equal.to(ct_eq<2>{})),
        hana::nothing
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(hana::make_set(ct_eq<1>{}, ct_eq<2>{}), hana::equal.to(ct_eq<1>{})),
        hana::just(ct_eq<1>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(hana::make_set(ct_eq<1>{}, ct_eq<2>{}), hana::equal.to(ct_eq<2>{})),
        hana::just(ct_eq<2>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(hana::make_set(ct_eq<1>{}, ct_eq<2>{}), hana::equal.to(ct_eq<3>{})),
        hana::nothing
    ));

    // find with operators
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make_set(ct_eq<1>{})[ct_eq<1>{}],
        ct_eq<1>{}
    ));
}

