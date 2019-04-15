// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/front.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/type.hpp>

#include <sstd/boost/mpl/size.hpp>
#include <sstd/boost/mpl/vector.hpp>
namespace hana = boost::hana;
namespace mpl = boost::mpl;


//! [front]
#include <sstd/boost/hana/ext/boost/mpl/vector.hpp> // bridge header

using Vector = mpl::vector<int, char, float>;
static_assert(hana::front(Vector{}) == hana::type_c<int>, "");
//! [front]


namespace _ns0 {
//! [size]
using Size = mpl::size<Vector>::type;
static_assert(hana::equal(Size{}, hana::int_c<3>), ""); // breaks!
//! [size]
}


//! [size-fixed]
#include <sstd/boost/hana/ext/boost/mpl/integral_c.hpp>

using Size = mpl::size<Vector>::type;
static_assert(hana::equal(Size{}, hana::int_c<3>), "");
//! [size-fixed]


int main() { }
