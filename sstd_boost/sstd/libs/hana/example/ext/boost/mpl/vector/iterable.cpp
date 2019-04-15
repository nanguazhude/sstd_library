// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/drop_front.hpp>
#include <sstd/boost/hana/drop_while.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/ext/boost/mpl/vector.hpp>
#include <sstd/boost/hana/ext/std/integral_constant.hpp>
#include <sstd/boost/hana/front.hpp>
#include <sstd/boost/hana/type.hpp>

#include <sstd/boost/mpl/vector.hpp>
#include <type_traits>
namespace hana = boost::hana;
namespace mpl = boost::mpl;


BOOST_HANA_CONSTANT_CHECK(hana::front(mpl::vector<int, char, void>{}) == hana::type_c<int>);

BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::drop_front(mpl::vector<int, char, void>{}),
    mpl::vector<char, void>{}
));

BOOST_HANA_CONSTANT_CHECK(hana::equal(
    hana::drop_while(mpl::vector<float, double const, int, float&>{},
                     hana::trait<std::is_floating_point>),
    mpl::vector<int, float&>{}
));

int main() { }
