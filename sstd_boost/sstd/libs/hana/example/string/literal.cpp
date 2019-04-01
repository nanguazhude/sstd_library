// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/config.hpp>
#include <sstd/boost/hana/core/is_a.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/length.hpp>
#include <sstd/boost/hana/string.hpp>
namespace hana = boost::hana;
using namespace hana::literals;


// By default, this is disabled
#ifdef BOOST_HANA_CONFIG_ENABLE_STRING_UDL

    constexpr auto str = "Hello world!"_s;
    BOOST_HANA_CONSTANT_CHECK(str == hana::string_c<'H', 'e', 'l', 'l', 'o', ' ',
                                                    'w', 'o', 'r', 'l', 'd', '!'>);

    BOOST_HANA_CONSTANT_CHECK(hana::is_a<hana::string_tag>(str));
    BOOST_HANA_CONSTANT_CHECK(hana::length(str) == hana::size_c<12>);

#endif

int main() { }

