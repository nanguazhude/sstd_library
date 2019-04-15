// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/core/make.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/tuple.hpp>

#include <string>
namespace hana = boost::hana;


int main() {
    auto xs = hana::make<hana::tuple_tag>(1, 2, '3', std::string{"456"});

    constexpr auto ys = hana::make<hana::tuple_tag>(1, '2', 3.456);
    static_assert(ys == hana::make_tuple(1, '2', 3.456), "");
}
