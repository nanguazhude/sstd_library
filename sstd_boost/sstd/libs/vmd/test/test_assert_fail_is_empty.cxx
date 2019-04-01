
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <sstd/boost/vmd/assert.hpp>
#include <sstd/boost/vmd/is_empty.hpp>
#include <sstd/boost/detail/lightweight_test.hpp>
#include <sstd/boost/preprocessor/facilities/empty.hpp>

int main()
  {

#if BOOST_PP_VARIADICS

  #define DATA x

  BOOST_VMD_ASSERT(BOOST_VMD_IS_EMPTY(DATA BOOST_PP_EMPTY()),BOOST_VMD_TEST_FAIL_IS_EMPTY)

#endif

  return boost::report_errors();

  }

