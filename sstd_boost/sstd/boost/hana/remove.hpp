/*!
@file
Defines `boost::hana::remove`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_HPP
#define BOOST_HANA_REMOVE_HPP

#include <sstd/boost/hana/fwd/remove.hpp>

#include <sstd/boost/hana/concept/monad_plus.hpp>
#include <sstd/boost/hana/config.hpp>
#include <sstd/boost/hana/core/dispatch.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/filter.hpp>
#include <sstd/boost/hana/functional/compose.hpp>
#include <sstd/boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto remove_t::operator()(Xs&& xs, Value&& value) const {
        using M = typename hana::tag_of<Xs>::type;
        using Remove = BOOST_HANA_DISPATCH_IF(remove_impl<M>,
            hana::MonadPlus<M>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::MonadPlus<M>::value,
            "hana::remove(xs, value) requires 'xs' to be a MonadPlus");
        #endif

        return Remove::apply(static_cast<Xs&&>(xs),
                             static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename M, bool condition>
    struct remove_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& value) {
            return hana::filter(static_cast<Xs&&>(xs),
                    hana::compose(hana::not_,
                                  hana::equal.to(static_cast<Value&&>(value))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_HPP
