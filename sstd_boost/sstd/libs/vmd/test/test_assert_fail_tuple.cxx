
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <sstd/boost/vmd/assert.hpp>
#include <sstd/boost/vmd/is_empty.hpp>
#include <sstd/boost/vmd/elem.hpp>
#include <sstd/boost/detail/lightweight_test.hpp>
#include <sstd/boost/preprocessor/tuple/elem.hpp>

int main()
  {

#if BOOST_PP_VARIADICS

  #define KDATA (a,b) name

  BOOST_VMD_ASSERT(BOOST_VMD_IS_EMPTY(BOOST_PP_TUPLE_ELEM(1,BOOST_VMD_ELEM(0,KDATA,BOOST_VMD_RETURN_AFTER,BOOST_VMD_TYPE_TUPLE))),BOOST_VMD_TEST_FAIL_TUPLE)

#endif

  return boost::report_errors();

  }

