// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/insert_range.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/tuple.hpp>

#include <string>
namespace hana = boost::hana;
using namespace hana::literals;
using namespace std::literals;


int main() {
    auto xs = hana::make_tuple("Hello"s, "world!"s);
    BOOST_HANA_RUNTIME_CHECK(
        hana::insert_range(xs, 1_c, hana::make_tuple(1, 2, 3)) == hana::make_tuple("Hello"s, 1, 2, 3, "world!"s)
    );
}
