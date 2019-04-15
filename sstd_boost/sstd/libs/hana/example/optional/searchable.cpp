// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/all_of.hpp>
#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/find_if.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/mod.hpp>
#include <sstd/boost/hana/not_equal.hpp>
#include <sstd/boost/hana/optional.hpp>
namespace hana = boost::hana;


auto odd = [](auto x) {
    return x % hana::int_c<2> != hana::int_c<0>;
};

BOOST_HANA_CONSTANT_CHECK(hana::find_if(hana::just(hana::int_c<3>), odd) == hana::just(hana::int_c<3>));
BOOST_HANA_CONSTANT_CHECK(hana::find_if(hana::just(hana::int_c<2>), odd) == hana::nothing);
BOOST_HANA_CONSTANT_CHECK(hana::find_if(hana::nothing, odd) == hana::nothing);

BOOST_HANA_CONSTANT_CHECK(hana::all_of(hana::just(hana::int_c<3>), odd));
BOOST_HANA_CONSTANT_CHECK(hana::all_of(hana::nothing, odd));

int main() { }
