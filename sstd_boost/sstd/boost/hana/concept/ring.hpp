/*!
@file
Defines `boost::hana::Ring`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_RING_HPP
#define BOOST_HANA_CONCEPT_RING_HPP

#include <sstd/boost/hana/fwd/concept/ring.hpp>

#include <sstd/boost/hana/config.hpp>
#include <sstd/boost/hana/core/default.hpp>
#include <sstd/boost/hana/core/tag_of.hpp>
#include <sstd/boost/hana/detail/integral_constant.hpp>
#include <sstd/boost/hana/mult.hpp>
#include <sstd/boost/hana/one.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename R>
    struct Ring
        : hana::integral_constant<bool,
            !is_default<one_impl<typename tag_of<R>::type>>::value &&
            !is_default<mult_impl<typename tag_of<R>::type,
                                  typename tag_of<R>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_RING_HPP
