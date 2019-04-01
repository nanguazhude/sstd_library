// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/hash.hpp>
#include <sstd/boost/hana/string.hpp>
#include <sstd/boost/hana/type.hpp>
namespace hana = boost::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::hash(hana::string_c<>),
        hana::type_c<hana::string<>>
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::hash(hana::string_c<'a'>),
        hana::type_c<hana::string<'a'>>
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::hash(hana::string_c<'a', 'b'>),
        hana::type_c<hana::string<'a', 'b'>>
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::hash(hana::string_c<'a', 'b', 'c'>),
        hana::type_c<hana::string<'a', 'b', 'c'>>
    ));
}

