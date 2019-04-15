// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/suffix.hpp>
#include <sstd/boost/hana/tuple.hpp>
namespace hana = boost::hana;


static_assert(
    hana::suffix(hana::make_tuple(1, 2, 3, 4), 0) == hana::make_tuple(1, 0, 2, 0, 3, 0, 4, 0)
, "");

int main() { }
