/*!
@file
Includes all the library components except the adapters for external
libraries.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_HPP
#define BOOST_HANA_HPP

//! @defgroup group-concepts Concepts
//! Concepts provided by the library.

//! @defgroup group-datatypes Data types
//! General purpose data types provided by the library.

//! @defgroup group-functional Functional
//! General purpose function objects.

//! @defgroup group-core Core
//! Core utilities of the library.

//! @defgroup group-experimental Experimental features
//! Experimental features that may or may not make it into the library.
//! These features should not expected to be stable.

//! @defgroup group-ext External adapters
//! Adapters for external libraries.

//! @defgroup group-config Configuration options
//! Configurable options to tweak the global behavior of the library.

//! @defgroup group-assertions Assertions
//! Macros to perform different kinds of assertions.

//! @defgroup group-details Details
//! Implementation details. Do not rely on anything here, even if it is
//! documented.

// Include config.hpp first, so that warning messages about compiler support
// appear as soon as possible.
#include <sstd/boost/hana/config.hpp>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost {
    //! Namespace containing everything in the library.
    namespace hana {
        //! Namespace containing C++14 user-defined literals provided by Hana.
        namespace literals {}
    }
}
#endif

#include <sstd/boost/hana/accessors.hpp>
#include <sstd/boost/hana/adapt_adt.hpp>
#include <sstd/boost/hana/adapt_struct.hpp>
#include <sstd/boost/hana/adjust.hpp>
#include <sstd/boost/hana/adjust_if.hpp>
#include <sstd/boost/hana/all.hpp>
#include <sstd/boost/hana/all_of.hpp>
#include <sstd/boost/hana/and.hpp>
#include <sstd/boost/hana/any.hpp>
#include <sstd/boost/hana/any_of.hpp>
#include <sstd/boost/hana/ap.hpp>
#include <sstd/boost/hana/append.hpp>
#include <sstd/boost/hana/assert.hpp>
#include <sstd/boost/hana/at.hpp>
#include <sstd/boost/hana/at_key.hpp>
#include <sstd/boost/hana/back.hpp>
#include <sstd/boost/hana/basic_tuple.hpp>
#include <sstd/boost/hana/bool.hpp>
#include <sstd/boost/hana/cartesian_product.hpp>
#include <sstd/boost/hana/chain.hpp>
#include <sstd/boost/hana/comparing.hpp>
#include <sstd/boost/hana/concat.hpp>
#include <sstd/boost/hana/concept.hpp>
#include <sstd/boost/hana/contains.hpp>
#include <sstd/boost/hana/core.hpp>
#include <sstd/boost/hana/count.hpp>
#include <sstd/boost/hana/count_if.hpp>
#include <sstd/boost/hana/cycle.hpp>
#include <sstd/boost/hana/define_struct.hpp>
#include <sstd/boost/hana/difference.hpp>
#include <sstd/boost/hana/div.hpp>
#include <sstd/boost/hana/drop_back.hpp>
#include <sstd/boost/hana/drop_front.hpp>
#include <sstd/boost/hana/drop_front_exactly.hpp>
#include <sstd/boost/hana/drop_while.hpp>
#include <sstd/boost/hana/duplicate.hpp>
#include <sstd/boost/hana/empty.hpp>
#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/erase_key.hpp>
#include <sstd/boost/hana/eval.hpp>
#include <sstd/boost/hana/eval_if.hpp>
#include <sstd/boost/hana/extend.hpp>
#include <sstd/boost/hana/extract.hpp>
#include <sstd/boost/hana/fill.hpp>
#include <sstd/boost/hana/filter.hpp>
#include <sstd/boost/hana/find.hpp>
#include <sstd/boost/hana/find_if.hpp>
#include <sstd/boost/hana/first.hpp>
#include <sstd/boost/hana/flatten.hpp>
#include <sstd/boost/hana/fold.hpp>
#include <sstd/boost/hana/fold_left.hpp>
#include <sstd/boost/hana/fold_right.hpp>
#include <sstd/boost/hana/for_each.hpp>
#include <sstd/boost/hana/front.hpp>
#include <sstd/boost/hana/functional.hpp>
#include <sstd/boost/hana/fuse.hpp>
#include <sstd/boost/hana/greater.hpp>
#include <sstd/boost/hana/greater_equal.hpp>
#include <sstd/boost/hana/group.hpp>
#include <sstd/boost/hana/index_if.hpp>
#include <sstd/boost/hana/if.hpp>
#include <sstd/boost/hana/insert.hpp>
#include <sstd/boost/hana/insert_range.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/intersection.hpp>
#include <sstd/boost/hana/intersperse.hpp>
#include <sstd/boost/hana/is_disjoint.hpp>
#include <sstd/boost/hana/is_empty.hpp>
#include <sstd/boost/hana/is_subset.hpp>
#include <sstd/boost/hana/keys.hpp>
#include <sstd/boost/hana/lazy.hpp>
#include <sstd/boost/hana/length.hpp>
#include <sstd/boost/hana/less.hpp>
#include <sstd/boost/hana/less_equal.hpp>
#include <sstd/boost/hana/lexicographical_compare.hpp>
#include <sstd/boost/hana/lift.hpp>
#include <sstd/boost/hana/map.hpp>
#include <sstd/boost/hana/max.hpp>
#include <sstd/boost/hana/maximum.hpp>
#include <sstd/boost/hana/members.hpp>
#include <sstd/boost/hana/min.hpp>
#include <sstd/boost/hana/minimum.hpp>
#include <sstd/boost/hana/minus.hpp>
#include <sstd/boost/hana/mod.hpp>
#include <sstd/boost/hana/monadic_compose.hpp>
#include <sstd/boost/hana/monadic_fold_left.hpp>
#include <sstd/boost/hana/monadic_fold_right.hpp>
#include <sstd/boost/hana/mult.hpp>
#include <sstd/boost/hana/negate.hpp>
#include <sstd/boost/hana/none.hpp>
#include <sstd/boost/hana/none_of.hpp>
#include <sstd/boost/hana/not.hpp>
#include <sstd/boost/hana/not_equal.hpp>
#include <sstd/boost/hana/one.hpp>
#include <sstd/boost/hana/optional.hpp>
#include <sstd/boost/hana/or.hpp>
#include <sstd/boost/hana/ordering.hpp>
#include <sstd/boost/hana/pair.hpp>
#include <sstd/boost/hana/partition.hpp>
#include <sstd/boost/hana/permutations.hpp>
#include <sstd/boost/hana/plus.hpp>
#include <sstd/boost/hana/power.hpp>
#include <sstd/boost/hana/prefix.hpp>
#include <sstd/boost/hana/prepend.hpp>
#include <sstd/boost/hana/product.hpp>
#include <sstd/boost/hana/range.hpp>
#include <sstd/boost/hana/remove.hpp>
#include <sstd/boost/hana/remove_at.hpp>
#include <sstd/boost/hana/remove_if.hpp>
#include <sstd/boost/hana/remove_range.hpp>
#include <sstd/boost/hana/repeat.hpp>
#include <sstd/boost/hana/replace.hpp>
#include <sstd/boost/hana/replace_if.hpp>
#include <sstd/boost/hana/replicate.hpp>
#include <sstd/boost/hana/reverse.hpp>
#include <sstd/boost/hana/reverse_fold.hpp>
#include <sstd/boost/hana/scan_left.hpp>
#include <sstd/boost/hana/scan_right.hpp>
#include <sstd/boost/hana/second.hpp>
#include <sstd/boost/hana/set.hpp>
#include <sstd/boost/hana/size.hpp>
#include <sstd/boost/hana/slice.hpp>
#include <sstd/boost/hana/sort.hpp>
#include <sstd/boost/hana/span.hpp>
#include <sstd/boost/hana/string.hpp>
#include <sstd/boost/hana/suffix.hpp>
#include <sstd/boost/hana/sum.hpp>
#include <sstd/boost/hana/symmetric_difference.hpp>
#include <sstd/boost/hana/take_back.hpp>
#include <sstd/boost/hana/take_front.hpp>
#include <sstd/boost/hana/take_while.hpp>
#include <sstd/boost/hana/tap.hpp>
#include <sstd/boost/hana/then.hpp>
#include <sstd/boost/hana/traits.hpp>
#include <sstd/boost/hana/transform.hpp>
#include <sstd/boost/hana/tuple.hpp>
#include <sstd/boost/hana/type.hpp>
#include <sstd/boost/hana/unfold_left.hpp>
#include <sstd/boost/hana/unfold_right.hpp>
#include <sstd/boost/hana/union.hpp>
#include <sstd/boost/hana/unique.hpp>
#include <sstd/boost/hana/unpack.hpp>
#include <sstd/boost/hana/value.hpp>
#include <sstd/boost/hana/version.hpp>
#include <sstd/boost/hana/while.hpp>
#include <sstd/boost/hana/zero.hpp>
#include <sstd/boost/hana/zip.hpp>
#include <sstd/boost/hana/zip_shortest.hpp>
#include <sstd/boost/hana/zip_shortest_with.hpp>
#include <sstd/boost/hana/zip_with.hpp>

#endif // !BOOST_HANA_HPP
