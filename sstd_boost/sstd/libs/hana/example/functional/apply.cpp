// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/functional/apply.hpp>
#include <sstd/boost/hana/plus.hpp>
namespace hana = boost::hana;


static_assert(hana::apply(hana::plus, 1, 2) == 3, "");

int main() { }

