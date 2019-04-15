// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/if.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/minus.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/pair.hpp>
#include <sstd/boost/hana/tuple.hpp>
#include <sstd/boost/hana/unfold_right.hpp>
namespace hana = boost::hana;


BOOST_HANA_CONSTANT_CHECK(
    hana::unfold_right<hana::tuple_tag>(hana::int_c<10>, [](auto x) {
        return hana::if_(x == hana::int_c<0>,
            hana::nothing,
            hana::just(hana::make_pair(x, x - hana::int_c<1>))
        );
    })
    ==
    hana::tuple_c<int, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1>
);

int main() { }
