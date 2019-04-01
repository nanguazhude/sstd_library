// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/greater.hpp>
#include <sstd/boost/hana/greater_equal.hpp>
#include <sstd/boost/hana/less.hpp>
#include <sstd/boost/hana/less_equal.hpp>
#include <sstd/boost/hana/not.hpp>
#include <sstd/boost/hana/optional.hpp>

#include <laws/base.hpp>
namespace hana = boost::hana;
using hana::test::ct_ord;


struct undefined { };

int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::nothing < hana::just(undefined{}));
    BOOST_HANA_CONSTANT_CHECK(hana::just(ct_ord<3>{}) < hana::just(ct_ord<4>{}));
    BOOST_HANA_CONSTANT_CHECK(hana::just(ct_ord<3>{}) <= hana::just(ct_ord<4>{}));
    BOOST_HANA_CONSTANT_CHECK(hana::just(ct_ord<4>{}) > hana::just(ct_ord<3>{}));
    BOOST_HANA_CONSTANT_CHECK(hana::just(ct_ord<4>{}) >= hana::just(ct_ord<3>{}));

    BOOST_HANA_CONSTANT_CHECK(hana::less(
        hana::nothing,
        hana::just(undefined{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::less(
        hana::just(undefined{}),
        hana::nothing
    )));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::less(
        hana::nothing,
        hana::nothing
    )));

    BOOST_HANA_CONSTANT_CHECK(hana::less(
        hana::just(ct_ord<3>{}),
        hana::just(ct_ord<4>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::less(
        hana::just(ct_ord<3>{}),
        hana::just(ct_ord<3>{})
    )));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::less(
        hana::just(ct_ord<4>{}),
        hana::just(ct_ord<3>{})
    )));
}

