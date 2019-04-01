///////////////////////////////////////////////////////////////////////////////
/// \file algorithm.hpp
///   Includes the range-based versions of the algorithms in the
///   C++ standard header file <algorithm>
//
/////////////////////////////////////////////////////////////////////////////

// Copyright 2009 Neil Groves.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Acknowledgements:
// This code uses combinations of ideas, techniques and code snippets
// from: Thorsten Ottosen, Eric Niebler, Jeremy Siek,
// and Vladimir Prus'
//
// The original mutating algorithms that served as the first version
// were originally written by Vladimir Prus'
// <ghost@cs.msu.su> code from Boost Wiki

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_RANGE_ALGORITHM_HPP_INCLUDED_01012009
#define BOOST_RANGE_ALGORITHM_HPP_INCLUDED_01012009

#include <sstd/boost/range/concepts.hpp>
#include <sstd/boost/range/iterator_range.hpp>
#include <sstd/boost/range/difference_type.hpp>
#include <sstd/boost/range/detail/range_return.hpp>
#include <sstd/boost/iterator/iterator_traits.hpp>
#include <sstd/boost/next_prior.hpp>
#include <algorithm>

// Non-mutating algorithms
#include <sstd/boost/range/algorithm/adjacent_find.hpp>
#include <sstd/boost/range/algorithm/count.hpp>
#include <sstd/boost/range/algorithm/count_if.hpp>
#include <sstd/boost/range/algorithm/equal.hpp>
#include <sstd/boost/range/algorithm/for_each.hpp>
#include <sstd/boost/range/algorithm/find.hpp>
#include <sstd/boost/range/algorithm/find_end.hpp>
#include <sstd/boost/range/algorithm/find_first_of.hpp>
#include <sstd/boost/range/algorithm/find_if.hpp>
#include <sstd/boost/range/algorithm/lexicographical_compare.hpp>
#include <sstd/boost/range/algorithm/mismatch.hpp>
#include <sstd/boost/range/algorithm/search.hpp>
#include <sstd/boost/range/algorithm/search_n.hpp>

// Mutating algorithms
#include <sstd/boost/range/algorithm/copy.hpp>
#include <sstd/boost/range/algorithm/copy_backward.hpp>
#include <sstd/boost/range/algorithm/fill.hpp>
#include <sstd/boost/range/algorithm/fill_n.hpp>
#include <sstd/boost/range/algorithm/generate.hpp>
#include <sstd/boost/range/algorithm/inplace_merge.hpp>
#include <sstd/boost/range/algorithm/merge.hpp>
#include <sstd/boost/range/algorithm/nth_element.hpp>
#include <sstd/boost/range/algorithm/partial_sort.hpp>
#include <sstd/boost/range/algorithm/partial_sort_copy.hpp>
#include <sstd/boost/range/algorithm/partition.hpp>
#include <sstd/boost/range/algorithm/random_shuffle.hpp>
#include <sstd/boost/range/algorithm/remove.hpp>
#include <sstd/boost/range/algorithm/remove_copy.hpp>
#include <sstd/boost/range/algorithm/remove_copy_if.hpp>
#include <sstd/boost/range/algorithm/remove_if.hpp>
#include <sstd/boost/range/algorithm/replace.hpp>
#include <sstd/boost/range/algorithm/replace_copy.hpp>
#include <sstd/boost/range/algorithm/replace_copy_if.hpp>
#include <sstd/boost/range/algorithm/replace_if.hpp>
#include <sstd/boost/range/algorithm/reverse.hpp>
#include <sstd/boost/range/algorithm/reverse_copy.hpp>
#include <sstd/boost/range/algorithm/rotate.hpp>
#include <sstd/boost/range/algorithm/rotate_copy.hpp>
#include <sstd/boost/range/algorithm/sort.hpp>
#include <sstd/boost/range/algorithm/stable_partition.hpp>
#include <sstd/boost/range/algorithm/stable_sort.hpp>
#include <sstd/boost/range/algorithm/transform.hpp>
#include <sstd/boost/range/algorithm/unique.hpp>
#include <sstd/boost/range/algorithm/unique_copy.hpp>

// Binary search
#include <sstd/boost/range/algorithm/binary_search.hpp>
#include <sstd/boost/range/algorithm/equal_range.hpp>
#include <sstd/boost/range/algorithm/lower_bound.hpp>
#include <sstd/boost/range/algorithm/upper_bound.hpp>

// Set operations of sorted ranges
#include <sstd/boost/range/algorithm/set_algorithm.hpp>

// Heap operations
#include <sstd/boost/range/algorithm/heap_algorithm.hpp>

// Minimum and Maximum
#include <sstd/boost/range/algorithm/max_element.hpp>
#include <sstd/boost/range/algorithm/min_element.hpp>

// Permutations
#include <sstd/boost/range/algorithm/permutation.hpp>

#endif // include guard


