// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/ext/std/integral_constant.hpp>

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/eval_if.hpp>
#include <sstd/boost/hana/functional/always.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/not.hpp>
#include <sstd/boost/hana/tuple.hpp>

#include <laws/base.hpp>
#include <laws/logical.hpp>

#include <type_traits>
namespace hana = boost::hana;


int main() {
    // eval_if
    {
        auto t = hana::test::ct_eq<3>{};
        auto e = hana::test::ct_eq<4>{};

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::eval_if(std::true_type{}, hana::always(t), hana::always(e)),
            t
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::eval_if(std::false_type{}, hana::always(t), hana::always(e)),
            e
        ));
    }

    // not_
    {
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::not_(std::true_type{}),
            std::false_type{}
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::not_(std::false_type{}),
            std::true_type{}
        ));
    }

    auto ints = hana::make_tuple(
        std::integral_constant<int, -2>{},
        std::integral_constant<int, 0>{},
        std::integral_constant<int, 1>{},
        std::integral_constant<int, 3>{}
    );

    auto bools = hana::make_tuple(std::true_type{}, std::false_type{});

    // laws
    hana::test::TestLogical<hana::ext::std::integral_constant_tag<int>>{ints};
    hana::test::TestLogical<hana::ext::std::integral_constant_tag<bool>>{bools};
}
