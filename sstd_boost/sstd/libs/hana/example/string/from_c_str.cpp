// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/core/to.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/string.hpp>
namespace hana = boost::hana;


constexpr char const hello[] = "hello";
auto hello_constant = hana::integral_constant<char const*, hello>{};

BOOST_HANA_CONSTANT_CHECK(
    hana::to_string(hello_constant) == hana::string_c<'h', 'e', 'l', 'l', 'o'>
);

int main() { }

