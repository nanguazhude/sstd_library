// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/transform.hpp>
#include <sstd/boost/hana/tuple.hpp>
#include <sstd/boost/hana/value.hpp>
namespace hana = boost::hana;


int main() {
    constexpr auto xs = hana::tuple_c<int, 1, 2, 3, 4, 5>;
    constexpr auto vs = hana::transform(xs, hana::value_of);
    static_assert(vs == hana::make_tuple(1, 2, 3, 4, 5), "");
}
