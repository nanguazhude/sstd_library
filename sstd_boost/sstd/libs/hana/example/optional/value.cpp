// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/type.hpp>

#include <string>
namespace hana = boost::hana;


int main() {
    static_assert(hana::just('x').value() == 'x', "");
    BOOST_HANA_CONSTANT_CHECK(*hana::just(hana::type_c<int>) == hana::type_c<int>);
    BOOST_HANA_RUNTIME_CHECK(hana::just(std::string{"abcd"})->size() == 4);

    // hana::nothing.value(); // compile-time error
}

