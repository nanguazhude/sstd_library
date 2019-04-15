/*!
@file
Defines `boost::hana::Struct`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_STRUCT_HPP
#define BOOST_HANA_CONCEPT_STRUCT_HPP

#include <sstd/boost/hana/fwd/concept/struct.hpp>

#include <sstd/boost/hana/accessors.hpp>
#include <sstd/boost/hana/config.hpp>
#include <sstd/boost/hana/core/default.hpp>
#include <sstd/boost/hana/core/tag_of.hpp>
#include <sstd/boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Struct
        : hana::integral_constant<bool,
            !is_default<accessors_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_STRUCT_HPP
