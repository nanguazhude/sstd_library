// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/core/make.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/optional.hpp>

#include <laws/base.hpp>
namespace hana = boost::hana;
using hana::test::ct_eq;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make<hana::optional_tag>(),
        hana::nothing
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make<hana::optional_tag>(ct_eq<3>{}),
        hana::just(ct_eq<3>{})
    ));

    // Check that make_optional == make<optional_tag>
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make_optional(),
        hana::make<hana::optional_tag>()
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make_optional(ct_eq<3>{}),
        hana::make<hana::optional_tag>(ct_eq<3>{})
    ));
}
