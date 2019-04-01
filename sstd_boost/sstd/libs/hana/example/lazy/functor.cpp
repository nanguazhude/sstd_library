// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/eval.hpp>
#include <sstd/boost/hana/functional/placeholder.hpp>
#include <sstd/boost/hana/lazy.hpp>
#include <sstd/boost/hana/transform.hpp>
namespace hana = boost::hana;
using hana::_;


int main() {
    static_assert(hana::eval(hana::transform(hana::make_lazy(4 / _)(1), _ * 3)) == (4 / 1) * 3, "");

    hana::transform(hana::make_lazy(4 / _)(0), _ * 3); // never evaluated
}

