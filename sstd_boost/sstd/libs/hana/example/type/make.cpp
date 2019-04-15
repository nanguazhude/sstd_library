// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/core/make.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/type.hpp>
namespace hana = boost::hana;


struct X { };
BOOST_HANA_CONSTANT_CHECK(hana::make<hana::type_tag>(X{}) == hana::type_c<X>);
BOOST_HANA_CONSTANT_CHECK(hana::make<hana::type_tag>(hana::type_c<X>) == hana::type_c<X>);

BOOST_HANA_CONSTANT_CHECK(hana::make_type(X{}) == hana::type_c<X>);
BOOST_HANA_CONSTANT_CHECK(hana::make_type(hana::type_c<X>) == hana::type_c<X>);

int main() { }
