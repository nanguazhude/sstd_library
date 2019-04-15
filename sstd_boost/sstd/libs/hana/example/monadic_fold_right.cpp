// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/config.hpp>
#include <sstd/boost/hana/div.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/eval_if.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/lazy.hpp>
#include <sstd/boost/hana/monadic_fold_right.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/tuple.hpp>
namespace hana = boost::hana;


int main() {
    BOOST_HANA_CONSTEXPR_LAMBDA auto safe_div = [](auto x, auto y) {
        return hana::eval_if(y == hana::int_c<0>,
            hana::make_lazy(hana::nothing),
            [=](auto _) {
                return hana::just(_(x) / y);
            }
        );
    };

    // with an initial state
    BOOST_HANA_CONSTANT_CHECK(
        hana::monadic_fold_right<hana::optional_tag>(
            hana::tuple_c<int, 1000, 8, 4>, hana::int_c<2>, safe_div
        )
            ==
        hana::just(hana::int_c<1000> / (hana::int_c<8> / (hana::int_c<4> / hana::int_c<2>)))
    );

    BOOST_HANA_CONSTANT_CHECK(
        hana::monadic_fold_right<hana::optional_tag>(
            hana::tuple_c<int, 1000, 8, 4>, hana::int_c<0>, safe_div
        )
            ==
        hana::nothing
    );

    // without an initial state
    BOOST_HANA_CONSTANT_CHECK(
        hana::monadic_fold_right<hana::optional_tag>(
            hana::tuple_c<int, 1000, 8, 4, 2>, safe_div
        )
            ==
        hana::just(hana::int_c<1000> / (hana::int_c<8> / (hana::int_c<4> / hana::int_c<2>)))
    );

    BOOST_HANA_CONSTANT_CHECK(
        hana::monadic_fold_right<hana::optional_tag>(
            hana::tuple_c<int, 1000, 8, 4, 0>, safe_div
        )
            ==
        hana::nothing
    );
}
