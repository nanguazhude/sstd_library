// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/core/make.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/optional.hpp>
namespace hana = boost::hana;


int main() {
    constexpr auto x = hana::make<hana::optional_tag>();
    BOOST_HANA_CONSTANT_CHECK(x == hana::make_optional());
    BOOST_HANA_CONSTANT_CHECK(hana::is_nothing(x));

    constexpr auto just_x = hana::make<hana::optional_tag>('x');
    static_assert(just_x == hana::make_optional('x'), "");
    BOOST_HANA_CONSTANT_CHECK(hana::is_just(just_x));
}
