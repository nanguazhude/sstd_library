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
    hana::tuple<int, char, double, std::string> ts{1, '2', 3.3, "abcd"};
    BOOST_HANA_RUNTIME_CHECK(ts == hana::make_tuple(1, '2', 3.3, std::string{"abcd"}));

    // std::string has no notion of tag, but it still works with make<>
    std::string foo{"foo"};
    BOOST_HANA_RUNTIME_CHECK(hana::make<std::string>("foo") == foo);
}
