// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

//
// concept_checks.cpp -
//   make sure the types meet concept requirements
//

#include <sstd/boost/concept_check.hpp>
#include <sstd/boost/multi_array/concept_checks.hpp>
#include <sstd/boost/multi_array.hpp>

#include <sstd/boost/cstdlib.hpp>

#include <sstd/boost/core/lightweight_test.hpp>

#include <sstd/boost/array.hpp>

int
main()
{
  const int ndims=3;
  typedef boost::multi_array<int,ndims> array;
  typedef boost::multi_array_ref<int,ndims> array_ref;
  typedef boost::const_multi_array_ref<int,ndims> const_array_ref;
  typedef array::array_view<ndims>::type array_view;
  typedef array::const_array_view<ndims>::type const_array_view;
  typedef array::subarray<ndims>::type subarray;
  typedef array::const_subarray<ndims>::type const_subarray;

boost::function_requires<
  boost::multi_array_concepts::ConstMultiArrayConcept<array,ndims> >();
boost::function_requires<
  boost::multi_array_concepts::ConstMultiArrayConcept<array_ref,ndims> >();
boost::function_requires<
  boost::multi_array_concepts::ConstMultiArrayConcept<const_array_ref,ndims> >();
boost::function_requires<
  boost::multi_array_concepts::ConstMultiArrayConcept<array_view,ndims> >();
boost::function_requires<
  boost::multi_array_concepts::ConstMultiArrayConcept<const_array_view,ndims> >();
boost::function_requires<
  boost::multi_array_concepts::ConstMultiArrayConcept<subarray,ndims> >();
boost::function_requires<
  boost::multi_array_concepts::ConstMultiArrayConcept<const_subarray,ndims> >();

boost::function_requires<
  boost::multi_array_concepts::MutableMultiArrayConcept<array,ndims> >();
boost::function_requires<
  boost::multi_array_concepts::MutableMultiArrayConcept<array_ref,ndims> >();
boost::function_requires<
  boost::multi_array_concepts::MutableMultiArrayConcept<array_view,ndims> >();
boost::function_requires<
  boost::multi_array_concepts::MutableMultiArrayConcept<subarray,ndims> >();

  return 0;
}
