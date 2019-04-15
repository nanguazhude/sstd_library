// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/string.hpp>
namespace hana = boost::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make<hana::string_tag>(),
        hana::string_c<>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make<hana::string_tag>(hana::char_c<'a'>),
        hana::string_c<'a'>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make<hana::string_tag>(hana::char_c<'a'>, hana::char_c<'b'>),
        hana::string_c<'a', 'b'>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make<hana::string_tag>(hana::char_c<'a'>, hana::char_c<'b'>, hana::char_c<'c'>),
        hana::string_c<'a', 'b', 'c'>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make<hana::string_tag>(hana::char_c<'a'>, hana::char_c<'b'>, hana::char_c<'c'>, hana::char_c<'d'>),
        hana::string_c<'a', 'b', 'c', 'd'>
    ));

    // make sure make_string == make<string_tag>
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make_string(hana::char_c<'a'>, hana::char_c<'b'>, hana::char_c<'c'>),
        hana::make<hana::string_tag>(hana::char_c<'a'>, hana::char_c<'b'>, hana::char_c<'c'>)
    ));
}
