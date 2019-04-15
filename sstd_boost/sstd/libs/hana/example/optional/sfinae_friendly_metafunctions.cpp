// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/not.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/traits.hpp>
#include <sstd/boost/hana/type.hpp>

#include <type_traits>
#include <utility>
namespace hana = boost::hana;


template <typename ...>
using void_t = void;

template <typename T, typename = void>
struct has_type : std::false_type { };

template <typename T>
struct has_type<T, void_t<typename T::type>>
    : std::true_type
{ };

auto common_type_impl = hana::sfinae([](auto t, auto u) -> hana::type<
    decltype(true ? hana::traits::declval(t) : hana::traits::declval(u))
> { return {}; });

template <typename T, typename U>
using common_type = decltype(common_type_impl(hana::type_c<T>, hana::type_c<U>));

BOOST_HANA_CONSTANT_CHECK(
  common_type_impl(hana::type_c<int>, hana::type_c<float>)
    ==
  hana::just(hana::type_c<float>)
);

static_assert(!has_type<common_type<int, int*>>{}, "");
static_assert(std::is_same<common_type<int, float>::type, float>{}, "");

int main() { }
