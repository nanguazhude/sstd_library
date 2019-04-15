// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/unpack.hpp>

#include <laws/base.hpp>
namespace hana = boost::hana;


int main() {
    hana::test::ct_eq<2> x{};
    hana::test::_injection<0> f{};

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::unpack(hana::nothing, f),
        f()
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::unpack(hana::just(x), f),
        f(x)
    ));

    // Previously, there was a bug that would make this fail.
    auto non_const_nothing = hana::nothing;
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::unpack(non_const_nothing, f),
        f()
    ));
}
