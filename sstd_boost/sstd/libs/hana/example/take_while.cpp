// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/less.hpp>
#include <sstd/boost/hana/take_while.hpp>
#include <sstd/boost/hana/tuple.hpp>
namespace hana = boost::hana;
using namespace hana::literals;


BOOST_HANA_CONSTANT_CHECK(
    hana::take_while(hana::tuple_c<int, 0, 1, 2, 3>, hana::less.than(2_c))
    ==
    hana::tuple_c<int, 0, 1>
);

int main() { }

