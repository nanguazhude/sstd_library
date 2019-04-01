// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/not.hpp>
#include <sstd/boost/hana/not_equal.hpp> // for operator !=
#include <sstd/boost/hana/optional.hpp>

#include <laws/base.hpp>
namespace hana = boost::hana;


int main() {
    hana::test::ct_eq<3> x{};
    hana::test::ct_eq<4> y{};

    BOOST_HANA_CONSTANT_CHECK(hana::equal(hana::nothing, hana::nothing));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(hana::nothing, hana::just(x))));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(hana::just(x), hana::nothing)));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(hana::just(x), hana::just(x)));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(hana::just(x), hana::just(y))));

    BOOST_HANA_CONSTANT_CHECK(hana::nothing == hana::nothing);
    BOOST_HANA_CONSTANT_CHECK(hana::just(x) == hana::just(x));
    BOOST_HANA_CONSTANT_CHECK(hana::just(x) != hana::just(y));
    BOOST_HANA_CONSTANT_CHECK(hana::just(x) != hana::nothing);
    BOOST_HANA_CONSTANT_CHECK(hana::nothing != hana::just(x));
}

