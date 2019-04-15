// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/size.hpp>
#include <sstd/boost/hana/tuple.hpp>
namespace hana = boost::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::size(hana::make_tuple()) == hana::size_c<0>);
    BOOST_HANA_CONSTANT_CHECK(hana::size(hana::make_tuple(1, '2', 3.0)) == hana::size_c<3>);

    BOOST_HANA_CONSTANT_CHECK(hana::size(hana::nothing) == hana::size_c<0>);
    BOOST_HANA_CONSTANT_CHECK(hana::size(hana::just('x')) == hana::size_c<1>);
}
