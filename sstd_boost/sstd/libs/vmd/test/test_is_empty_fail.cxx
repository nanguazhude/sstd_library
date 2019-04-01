﻿
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <sstd/boost/vmd/is_empty.hpp>
#include <sstd/boost/detail/lightweight_test.hpp>

int main()
  {

#if BOOST_PP_VARIADICS

#if !BOOST_VMD_MSVC

  #define FUNC_GEN(x,y) anything

  BOOST_TEST(!BOOST_VMD_IS_EMPTY(FUNC_GEN));

#else

  typedef char BOOST_VMD_IS_EMPTY_ERROR[-1];

#endif

#endif /* BOOST_PP_VARIADICS */

  return boost::report_errors();

  }
