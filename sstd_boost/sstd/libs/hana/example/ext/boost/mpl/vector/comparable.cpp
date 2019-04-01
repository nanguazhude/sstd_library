﻿// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/ext/boost/mpl/vector.hpp>
#include <sstd/boost/hana/not_equal.hpp>

#include <sstd/boost/mpl/vector.hpp>
namespace hana = boost::hana;
namespace mpl = boost::mpl;


BOOST_HANA_CONSTANT_CHECK(
    hana::equal(mpl::vector2<int, char>{}, mpl::vector<int, char>{})
);
BOOST_HANA_CONSTANT_CHECK(
    hana::not_equal(mpl::vector2<int, char>{}, mpl::vector<int, char, float>{})
);

int main() { }
