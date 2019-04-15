// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/accessors.hpp>
#include <sstd/boost/hana/adapt_struct.hpp>
#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/core/to.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/find.hpp>
#include <sstd/boost/hana/first.hpp>
#include <sstd/boost/hana/map.hpp>
#include <sstd/boost/hana/not_equal.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/pair.hpp>
#include <sstd/boost/hana/string.hpp>
#include <sstd/boost/hana/transform.hpp>
#include <sstd/boost/hana/tuple.hpp>

#include <string>
namespace hana = boost::hana;


namespace ns {
    struct Person {
        std::string name;
        int age;
    };
}

BOOST_HANA_ADAPT_STRUCT(ns::Person,
    name,
    age
);

// The member names are hana::strings:
auto names = hana::transform(hana::accessors<ns::Person>(), hana::first);
BOOST_HANA_CONSTANT_CHECK(
    names == hana::make_tuple(BOOST_HANA_STRING("name"), BOOST_HANA_STRING("age"))
);

int main() {
    ns::Person john{"John", 30}, bob{"Bob", 40};
    BOOST_HANA_RUNTIME_CHECK(hana::equal(john, john));
    BOOST_HANA_RUNTIME_CHECK(hana::not_equal(john, bob));

    BOOST_HANA_RUNTIME_CHECK(hana::find(john, BOOST_HANA_STRING("name")) == hana::just("John"));
    BOOST_HANA_RUNTIME_CHECK(hana::find(john, BOOST_HANA_STRING("age")) == hana::just(30));
    BOOST_HANA_CONSTANT_CHECK(hana::find(john, BOOST_HANA_STRING("foo")) == hana::nothing);

    BOOST_HANA_RUNTIME_CHECK(hana::to_tuple(john) == hana::make_tuple(
        hana::make_pair(BOOST_HANA_STRING("name"), "John"),
        hana::make_pair(BOOST_HANA_STRING("age"), 30)
    ));

    BOOST_HANA_RUNTIME_CHECK(hana::to_map(john) == hana::make_map(
        hana::make_pair(BOOST_HANA_STRING("name"), "John"),
        hana::make_pair(BOOST_HANA_STRING("age"), 30)
    ));
}
