// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/ext/boost/mpl/list.hpp>
#include <sstd/boost/hana/find.hpp>
#include <sstd/boost/hana/find_if.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/type.hpp>

#include <sstd/boost/mpl/list.hpp>
namespace hana = boost::hana;
namespace mpl = boost::mpl;


BOOST_HANA_CONSTANT_CHECK(
    hana::find_if(mpl::list<int, float, char const*>{}, hana::equal.to(hana::type_c<float>))
    ==
    hana::just(hana::type_c<float>)
);

BOOST_HANA_CONSTANT_CHECK(
    hana::find(mpl::list<int, float, char const*>{}, hana::type_c<void>)
    ==
    hana::nothing
);

int main() { }

