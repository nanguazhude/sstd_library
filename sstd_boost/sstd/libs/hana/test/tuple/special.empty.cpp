// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/empty.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/tuple.hpp>
namespace hana = boost::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::empty<hana::tuple_tag>(),
        hana::tuple_c<int>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::empty<hana::tuple_tag>(),
        hana::tuple_c<long>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::empty<hana::tuple_tag>(),
        hana::tuple_c<void>
    ));
}

