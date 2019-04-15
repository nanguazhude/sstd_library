// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/type.hpp>
namespace hana = boost::hana;


struct X { };
static_assert(hana::alignof_(hana::type_c<X>) == alignof(X), "");

static_assert(hana::alignof_(1) == alignof(decltype(1)), "");
static_assert(hana::alignof_(hana::type_c<int>) == alignof(int), "");

int main() { }
