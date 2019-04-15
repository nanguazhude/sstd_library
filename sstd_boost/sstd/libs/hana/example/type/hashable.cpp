// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/hash.hpp>
#include <sstd/boost/hana/type.hpp>
namespace hana = boost::hana;


// `hana::hash` is the identity on `hana::type`s.
BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::hash(hana::type_c<int>),
    hana::type_c<int>
));

BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::hash(hana::type_c<void>),
    hana::type_c<void>
));

int main() { }
