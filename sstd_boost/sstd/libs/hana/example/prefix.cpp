// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/prefix.hpp>
#include <sstd/boost/hana/tuple.hpp>

#include <string>
namespace hana = boost::hana;
using namespace std::literals;


int main() {
    BOOST_HANA_RUNTIME_CHECK(
        hana::prefix(hana::make_tuple("dog"s, "car"s, "house"s), "my"s)
            ==
        hana::make_tuple("my", "dog", "my", "car", "my", "house")
    );
}
