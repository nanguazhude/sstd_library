/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_BEGIN_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_BEGIN_HPP_INCLUDED

#include <sstd/boost/fusion/support/config.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/detail/segmented_begin_impl.hpp>
#include <sstd/boost/fusion/iterator/segmented_iterator.hpp>
#include <sstd/boost/fusion/view/iterator_range.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/begin.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/end.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/empty.hpp>
#include <sstd/boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_begin( seq )
    //{
    //    return make_segmented_iterator( segmented_begin_impl( seq, nil_ ) );
    //}

    template <typename Sequence, typename Nil_ = fusion::nil_>
    struct segmented_begin
    {
        typedef
            segmented_iterator<
                typename segmented_begin_impl<Sequence, Nil_>::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq)
        {
            return type(
                segmented_begin_impl<Sequence, Nil_>::call(seq, Nil_()));
        }
    };

}}}

#endif
