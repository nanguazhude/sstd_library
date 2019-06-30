// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_HPP
#define BOOST_HISTOGRAM_HPP

/**
  \file sstd/boost/histogram.hpp
  Includes all standard headers of the Boost.histogram library.

  Extra headers not automatically included are:
    - sstd/boost/histogram/accumulators/ostream.hpp
    - sstd/boost/histogram/axis/ostream.hpp
    - sstd/boost/histogram/ostream.hpp
    - sstd/boost/histogram/serialization.hpp
*/

#include <sstd/boost/histogram/accumulators/mean.hpp>
#include <sstd/boost/histogram/accumulators/sum.hpp>
#include <sstd/boost/histogram/accumulators/weighted_mean.hpp>
#include <sstd/boost/histogram/accumulators/weighted_sum.hpp>
#include <sstd/boost/histogram/algorithm/project.hpp>
#include <sstd/boost/histogram/algorithm/reduce.hpp>
#include <sstd/boost/histogram/algorithm/sum.hpp>
#include <sstd/boost/histogram/axis.hpp>
#include <sstd/boost/histogram/histogram.hpp>
#include <sstd/boost/histogram/indexed.hpp>
#include <sstd/boost/histogram/literals.hpp>
#include <sstd/boost/histogram/make_histogram.hpp>
#include <sstd/boost/histogram/make_profile.hpp>
#include <sstd/boost/histogram/storage_adaptor.hpp>
#include <sstd/boost/histogram/unlimited_storage.hpp>

#endif
