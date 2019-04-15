// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/contains.hpp>
#include <sstd/boost/hana/core/is_a.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/find_if.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/tuple.hpp>

#include <string>
namespace hana = boost::hana;
using namespace std::string_literals;


int main() {
    BOOST_HANA_RUNTIME_CHECK(
        hana::find_if(hana::make_tuple(1, '2', 3.3, "abc"s), hana::is_a<std::string>) == hana::just("abc"s)
    );

    BOOST_HANA_RUNTIME_CHECK(
        "abc"s ^hana::in^ hana::make_tuple(1, '2', 3.3, "abc"s)
    );
}
