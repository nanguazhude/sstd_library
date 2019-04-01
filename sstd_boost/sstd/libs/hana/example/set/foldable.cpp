// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/maximum.hpp>
#include <sstd/boost/hana/minimum.hpp>
#include <sstd/boost/hana/set.hpp>
#include <sstd/boost/hana/sum.hpp>
namespace hana = boost::hana;


int main() {
    constexpr auto xs = hana::make_set(hana::int_c<0>, hana::int_c<1>, hana::int_c<2>);
    static_assert(hana::minimum(xs) == hana::int_c<0>, "");
    static_assert(hana::maximum(xs) == hana::int_c<2>, "");
    static_assert(hana::sum<>(xs) == hana::int_c<3>, "");
}

