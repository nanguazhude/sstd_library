// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/optional.hpp>

#include <laws/base.hpp>
namespace hana = boost::hana;
using hana::test::ct_eq;


struct object {
    ct_eq<3> member;
};

int main() {
    auto lvalue = hana::just(object{});
    ct_eq<3>& ref = lvalue->member;
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        ref,
        ct_eq<3>{}
    ));

    auto const const_lvalue = hana::just(object{});
    ct_eq<3> const& const_ref = const_lvalue->member;
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        const_ref,
        ct_eq<3>{}
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::just(object{})->member,
        ct_eq<3>{}
    ));
}

