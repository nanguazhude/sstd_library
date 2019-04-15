// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/ext/std/integral_constant.hpp>
#include <sstd/boost/hana/functional/compose.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/remove_if.hpp>
#include <sstd/boost/hana/tuple.hpp>
#include <sstd/boost/hana/type.hpp>

#include <type_traits>
namespace hana = boost::hana;


// First get the type of the object, and then call the trait on it.
constexpr auto is_integral = hana::compose(hana::trait<std::is_integral>, hana::typeid_);

static_assert(hana::remove_if(hana::make_tuple(1, 2.0, 3, 4.0), is_integral) == hana::make_tuple(2.0, 4.0), "");
static_assert(hana::remove_if(hana::just(3.0), is_integral) == hana::just(3.0), "");
BOOST_HANA_CONSTANT_CHECK(hana::remove_if(hana::just(3), is_integral) == hana::nothing);

int main() { }
