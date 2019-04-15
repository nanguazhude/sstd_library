// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/div.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/ext/std/ratio.hpp>
#include <sstd/boost/hana/minus.hpp>
#include <sstd/boost/hana/mod.hpp>
#include <sstd/boost/hana/mult.hpp>
#include <sstd/boost/hana/one.hpp>
#include <sstd/boost/hana/plus.hpp>
#include <sstd/boost/hana/zero.hpp>

#include <ratio>
namespace hana = boost::hana;


BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::plus(std::ratio<5, 3>{}, std::ratio<3, 12>{}),
    std::ratio<23, 12>{}
));

BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::minus(std::ratio<5, 3>{}, std::ratio<3, 13>{}),
    std::ratio<56, 39>{}
));

BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::mult(std::ratio<5, 3>{}, std::ratio<3, 13>{}),
    std::ratio<15, 39>{}
));

BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::div(std::ratio<5, 3>{}, std::ratio<3, 13>{}),
    std::ratio<65, 9>{}
));

// The mod of two ratios is always 0, because they can always be
// divided without remainder.
BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::mod(std::ratio<5, 3>{}, std::ratio<3, 13>{}),
    std::ratio<0>{}
));

BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::zero<hana::ext::std::ratio_tag>(),
    std::ratio<0>{}
));

BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::one<hana::ext::std::ratio_tag>(),
    std::ratio<1>{}
));

int main() { }
