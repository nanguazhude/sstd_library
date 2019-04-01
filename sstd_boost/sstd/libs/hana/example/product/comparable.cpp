// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/not_equal.hpp>
#include <sstd/boost/hana/pair.hpp>

#include <string>
namespace hana = boost::hana;
using namespace std::literals;


int main() {
    BOOST_HANA_RUNTIME_CHECK(hana::make_pair(1, "234"s) == hana::make_pair(1ll, "234"s));
    static_assert(hana::make_pair('x', 2) != hana::make_pair('y', 2), "");
}

