// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/hash.hpp>
#include <sstd/boost/hana/not_equal.hpp>
#include <sstd/boost/hana/string.hpp>
namespace hana = boost::hana;


// `hana::hash` returns a type uniquely representing the string. The hash is
// perfect, meaning no two different strings have the same hash value.
BOOST_HANA_CONSTANT_CHECK(hana::not_equal(
    hana::hash(BOOST_HANA_STRING("abcdef")),
    hana::hash(BOOST_HANA_STRING("abcdefg"))
));

int main() { }

