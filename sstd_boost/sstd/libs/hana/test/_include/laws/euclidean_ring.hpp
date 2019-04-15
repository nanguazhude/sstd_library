// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HANA_TEST_LAWS_EUCLIDEAN_RING_HPP
#define BOOST_HANA_TEST_LAWS_EUCLIDEAN_RING_HPP

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/bool.hpp>
#include <sstd/boost/hana/concept/comparable.hpp>
#include <sstd/boost/hana/concept/constant.hpp>
#include <sstd/boost/hana/concept/euclidean_ring.hpp>
#include <sstd/boost/hana/core/when.hpp>
#include <sstd/boost/hana/div.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/for_each.hpp>
#include <sstd/boost/hana/lazy.hpp>
#include <sstd/boost/hana/mod.hpp>
#include <sstd/boost/hana/mult.hpp>
#include <sstd/boost/hana/not_equal.hpp>
#include <sstd/boost/hana/plus.hpp>
#include <sstd/boost/hana/value.hpp>
#include <sstd/boost/hana/zero.hpp>

#include <laws/base.hpp>


namespace boost { namespace hana { namespace test {
    template <typename D, typename = when<true>>
    struct TestEuclideanRing : TestEuclideanRing<D, laws> {
        using TestEuclideanRing<D, laws>::TestEuclideanRing;
    };

    template <typename D>
    struct TestEuclideanRing<D, laws> {
        template <typename Xs>
        TestEuclideanRing(Xs xs) {
            hana::for_each(xs, [](auto x) {
                static_assert(EuclideanRing<decltype(x)>{}, "");
            });

            foreach2(xs, [](auto a, auto b) {

                // commutativity
                BOOST_HANA_CHECK(hana::equal(
                    hana::mult(a, b),
                    hana::mult(b, a)
                ));

                only_when_(hana::not_equal(b, zero<D>()),
                hana::make_lazy([](auto a, auto b) {
                    BOOST_HANA_CHECK(hana::equal(
                        hana::plus(
                            hana::mult(hana::div(a, b), b),
                            hana::mod(a, b)
                        ),
                        a
                    ));

                    BOOST_HANA_CHECK(hana::equal(
                        hana::mod(zero<D>(), b),
                        zero<D>()
                    ));
                })(a, b));

            });
        }
    };

    template <typename C>
    struct TestEuclideanRing<C, when<Constant<C>::value>>
        : TestEuclideanRing<C, laws>
    {
        template <typename Xs>
        TestEuclideanRing(Xs xs) : TestEuclideanRing<C, laws>{xs} {
            foreach2(xs, [](auto x, auto y) {
                only_when_(hana::not_equal(zero<C>(), y),
                hana::make_lazy([](auto x, auto y) {
                    BOOST_HANA_CHECK(hana::equal(
                        hana::div(hana::value(x), hana::value(y)),
                        hana::value(hana::div(x, y))
                    ));

                    BOOST_HANA_CHECK(hana::equal(
                        hana::mod(hana::value(x), hana::value(y)),
                        hana::value(hana::mod(x, y))
                    ));

                })(x, y));
            });
        }
    };
}}} // end namespace boost::hana::test

#endif // !BOOST_HANA_TEST_LAWS_EUCLIDEAN_RING_HPP
