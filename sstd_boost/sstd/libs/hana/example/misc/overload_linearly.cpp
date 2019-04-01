// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/find_if.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/transform.hpp>
#include <sstd/boost/hana/tuple.hpp>
#include <sstd/boost/hana/type.hpp>

#include <string>
namespace hana = boost::hana;


// We have an utility in the Functional module that does pretty much the
// same, but is more compile-time efficient. It is still interesting to
// see this implemented with sequences and the SFINAE combinator.

auto overload_linearly = [](auto ...candidates) {
    return [=](auto ...args) {
        auto maybe_function = hana::find_if(hana::make_tuple(candidates...), [=](auto f) {
            return hana::is_valid(f)(args...);
        });
        auto result = hana::transform(maybe_function, [=](auto f) {
            return f(args...);
        });
        return result;
    };
};

int main() {
    auto f = ::overload_linearly(
        [](std::string s) { return s + "abcd"; },
        [](int i) { return i + 1; },
        [](double f) { return f + 2; }
    );

    BOOST_HANA_RUNTIME_CHECK(f(1) == hana::just(1 + 1));
    BOOST_HANA_RUNTIME_CHECK(f(2.3) == hana::just(static_cast<int>(2.3) + 1));
}

