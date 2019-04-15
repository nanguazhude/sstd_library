// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/fill.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/tuple.hpp>
namespace hana = boost::hana;


int main() {
    static_assert(
        hana::fill(hana::make_tuple(1, '2', 3.3, nullptr), 'x')
            ==
        hana::make_tuple('x', 'x', 'x', 'x')
    , "");

    BOOST_HANA_CONSTANT_CHECK(hana::fill(hana::nothing, 'x') == hana::nothing);
    static_assert(hana::fill(hana::just('y'), 'x') == hana::just('x'), "");
}
