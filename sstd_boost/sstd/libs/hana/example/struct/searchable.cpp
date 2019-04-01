// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/accessors.hpp>
#include <sstd/boost/hana/all_of.hpp>
#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/define_struct.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/find.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/second.hpp>
#include <sstd/boost/hana/string.hpp>

#include <string>
namespace hana = boost::hana;


struct Person {
    BOOST_HANA_DEFINE_STRUCT(Person,
        (std::string, name),
        (unsigned short, age)
    );
};

int main() {
    Person john{"John", 30};

    BOOST_HANA_RUNTIME_CHECK(
        hana::find(john, BOOST_HANA_STRING("name")) == hana::just("John")
    );

    BOOST_HANA_CONSTANT_CHECK(
        hana::find(john, BOOST_HANA_STRING("foobar")) == hana::nothing
    );


    BOOST_HANA_RUNTIME_CHECK(
        hana::all_of(hana::accessors<Person>(), [&](auto a) {
            return hana::second(a)(john) == hana::second(a)(john);
        })
    );

    // the above is equivalent to:
    BOOST_HANA_RUNTIME_CHECK(hana::equal(john, john));
}

