// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/config.hpp>
#include <sstd/boost/hana/core/to.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/find.hpp>
#include <sstd/boost/hana/functional/id.hpp>
#include <sstd/boost/hana/fwd/accessors.hpp>
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
    Person(std::string const& name, int age) : name_(name), age_(age) { }

    std::string const& get_name() const { return name_; }
    int get_age() const { return age_; }

private:
    std::string name_;
    int age_;
};

namespace boost { namespace hana {
    template <>
    struct accessors_impl<Person> {
        static BOOST_HANA_CONSTEXPR_LAMBDA auto apply() {
            return make_tuple(
                make_pair(BOOST_HANA_STRING("name"), [](auto&& p) -> std::string const& {
                    return p.get_name();
                }),
                make_pair(BOOST_HANA_STRING("age"), [](auto&& p) {
                    return p.get_age();
                })
            );
        }
    };
}}
//! [main]

int main() {
    auto name = BOOST_HANA_STRING("name");
    auto age = BOOST_HANA_STRING("age");

    Person john{"John", 30}, bob{"Bob", 40};
    BOOST_HANA_RUNTIME_CHECK(hana::equal(john, john));
    BOOST_HANA_RUNTIME_CHECK(hana::not_equal(john, bob));

    BOOST_HANA_RUNTIME_CHECK(hana::find(john, name) == hana::just("John"));
    BOOST_HANA_RUNTIME_CHECK(hana::find(john, age) == hana::just(30));
    BOOST_HANA_CONSTANT_CHECK(hana::find(john, BOOST_HANA_STRING("foo")) == hana::nothing);

    BOOST_HANA_RUNTIME_CHECK(hana::to_tuple(john) == hana::make_tuple(
        hana::make_pair(name, "John"),
        hana::make_pair(age, 30)
    ));
}
