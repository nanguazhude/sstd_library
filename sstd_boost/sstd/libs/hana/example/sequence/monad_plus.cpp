// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/append.hpp>
#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/concat.hpp>
#include <sstd/boost/hana/empty.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/tuple.hpp>

#include <string>
namespace hana = boost::hana;
using namespace std::string_literals;


BOOST_HANA_CONSTANT_CHECK(hana::empty<hana::tuple_tag>() == hana::make_tuple());

static_assert(hana::append(hana::make_tuple(1, '2', 3.3), nullptr)
                        == hana::make_tuple(1, '2', 3.3, nullptr), "");

int main() {
    BOOST_HANA_RUNTIME_CHECK(
        hana::concat(hana::make_tuple(1, '2', 3.3), hana::make_tuple("abcdef"s)) ==
        hana::make_tuple(1, '2', 3.3, "abcdef"s)
    );
}

