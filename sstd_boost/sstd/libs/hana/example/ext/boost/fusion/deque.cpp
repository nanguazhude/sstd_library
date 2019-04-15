// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/ext/boost/fusion/deque.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/transform.hpp>

#include <sstd/boost/fusion/include/deque.hpp>
#include <sstd/boost/fusion/include/make_deque.hpp>

#include <string>
namespace fusion = boost::fusion;
namespace hana = boost::hana;


struct Fish { std::string name; };
struct Cat  { std::string name; };
struct Dog  { std::string name; };

int main() {
    fusion::deque<Fish, Cat, Dog> animals{{"Nemo"}, {"Garfield"}, {"Snoopy"}};
    hana::front(animals).name = "Moby Dick";

    auto names = hana::transform(animals, [](auto a) {
      return a.name;
    });

    BOOST_HANA_RUNTIME_CHECK(hana::equal(
        names,
        fusion::make_deque("Moby Dick", "Garfield", "Snoopy")
    ));
}
