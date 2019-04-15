// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <sstd/boost/hana/ext/boost/mpl/integral_c.hpp>

#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/eval_if.hpp>
#include <sstd/boost/hana/functional/always.hpp>
#include <sstd/boost/hana/not.hpp>
#include <sstd/boost/hana/tuple.hpp>

#include <laws/base.hpp>
#include <laws/logical.hpp>

#include <sstd/boost/mpl/bool.hpp>
#include <sstd/boost/mpl/int.hpp>
#include <sstd/boost/mpl/integral_c.hpp>
namespace hana = boost::hana;
namespace mpl = boost::mpl;


int main() {
    // eval_if
    {
        auto t = hana::test::ct_eq<3>{};
        auto e = hana::test::ct_eq<4>{};

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::eval_if(mpl::true_{}, hana::always(t), hana::always(e)),
            t
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::eval_if(mpl::false_{}, hana::always(t), hana::always(e)),
            e
        ));
    }

    // not_
    {
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::not_(mpl::true_{}),
            mpl::false_{}
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::not_(mpl::false_{}),
            mpl::true_{}
        ));
    }

    // laws
    hana::test::TestLogical<hana::ext::boost::mpl::integral_c_tag<int>>{
        hana::make_tuple(
            mpl::int_<-2>{}, mpl::integral_c<int, 0>{}, mpl::integral_c<int, 3>{}
        )
    };

    hana::test::TestLogical<hana::ext::boost::mpl::integral_c_tag<bool>>{
        hana::make_tuple(
            mpl::true_{}, mpl::false_{},
            mpl::integral_c<bool, true>{}, mpl::integral_c<bool, false>{}
        )
    };
}
