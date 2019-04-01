// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/functional/fix.hpp>

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/config.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/eval_if.hpp>
#include <sstd/boost/hana/functional/always.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/minus.hpp>
#include <sstd/boost/hana/mult.hpp>
namespace hana = boost::hana;


BOOST_HANA_CONSTEXPR_LAMBDA auto fact = hana::fix([](auto fact, auto n) {
    return hana::eval_if(hana::equal(n, hana::ullong_c<0>),
        hana::always(hana::ullong_c<1>),
        [=](auto _) { return hana::mult(n, fact(_(n) - hana::ullong_c<1>)); }
    );
});

constexpr unsigned long long reference(unsigned long long n)
{ return n == 0 ? 1 : n * reference(n - 1); }

template <int n>
void test() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        fact(hana::ullong_c<n>),
        hana::ullong_c<reference(n)>
    ));
    test<n - 1>();
}

template <> void test<-1>() { }

int main() {
    test<15>();
}

