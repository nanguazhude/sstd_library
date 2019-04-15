// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/config.hpp>
#include <sstd/boost/hana/tuple.hpp>
#include <sstd/boost/hana/unpack.hpp>
namespace hana = boost::hana;


int main() {
    BOOST_HANA_CONSTEXPR_LAMBDA auto add = [](auto x, auto y, auto z) {
        return x + y + z;
    };

    BOOST_HANA_CONSTEXPR_CHECK(hana::unpack(hana::make_tuple(1, 2, 3), add) == 6);
}
