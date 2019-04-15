// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/concept/struct.hpp>
#include <sstd/boost/hana/config.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/find.hpp>
#include <sstd/boost/hana/functional/id.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/not_equal.hpp>
#include <sstd/boost/hana/pair.hpp>
#include <sstd/boost/hana/string.hpp>
#include <sstd/boost/hana/tuple.hpp>

#include <string>
#include <utility>
namespace hana = boost::hana;


//! [main]
struct Person {
    std::string name;
    int age;

    struct hana_accessors_impl {
        static BOOST_HANA_CONSTEXPR_LAMBDA auto apply() {
            return boost::hana::make_tuple(
                boost::hana::make_pair(BOOST_HANA_STRING("name"),
                [](auto&& p) -> decltype(auto) {
                    return boost::hana::id(std::forward<decltype(p)>(p).name);
                }),
                boost::hana::make_pair(BOOST_HANA_STRING("age"),
                [](auto&& p) -> decltype(auto) {
                    return boost::hana::id(std::forward<decltype(p)>(p).age);
                })
            );
        }
    };
};
//! [main]

int main() {
    Person john{"John", 30}, bob{"Bob", 40};
    BOOST_HANA_RUNTIME_CHECK(hana::equal(john, john));
    BOOST_HANA_RUNTIME_CHECK(hana::not_equal(john, bob));

    BOOST_HANA_RUNTIME_CHECK(hana::find(john, BOOST_HANA_STRING("name")) == hana::just("John"));
    BOOST_HANA_RUNTIME_CHECK(hana::find(john, BOOST_HANA_STRING("age")) == hana::just(30));
    BOOST_HANA_CONSTANT_CHECK(hana::find(john, BOOST_HANA_STRING("foo")) == hana::nothing);

    BOOST_HANA_RUNTIME_CHECK(hana::to_tuple(john) == hana::make_tuple(
        hana::make_pair(BOOST_HANA_STRING("name"), "John"),
        hana::make_pair(BOOST_HANA_STRING("age"), 30)
    ));
}
