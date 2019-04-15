
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_VMD_DETAIL_IS_LIST_HPP)
#define BOOST_VMD_DETAIL_IS_LIST_HPP

#include <sstd/boost/preprocessor/cat.hpp>
#include <sstd/boost/preprocessor/comparison/equal.hpp>
#include <sstd/boost/preprocessor/control/iif.hpp>
#include <sstd/boost/preprocessor/control/while.hpp>
#include <sstd/boost/preprocessor/debug/assert.hpp>
#include <sstd/boost/preprocessor/facilities/empty.hpp>
#include <sstd/boost/preprocessor/logical/bitor.hpp>
#include <sstd/boost/preprocessor/logical/compl.hpp>
#include <sstd/boost/preprocessor/punctuation/is_begin_parens.hpp>
#include <sstd/boost/preprocessor/tuple/elem.hpp>
#include <sstd/boost/preprocessor/tuple/size.hpp>
#include <sstd/boost/preprocessor/variadic/elem.hpp>
#include <sstd/boost/preprocessor/variadic/size.hpp>
#include <sstd/boost/vmd/identity.hpp>
#include <sstd/boost/vmd/is_empty.hpp>
#include <sstd/boost/vmd/is_identifier.hpp>
#include <sstd/boost/vmd/is_tuple.hpp>
#include <sstd/boost/vmd/detail/nil_registration.hpp>

#define BOOST_VMD_DETAIL_IS_LIST_PROCESS_TUPLE(d,x) \
    BOOST_PP_IIF \
      ( \
      BOOST_VMD_IS_TUPLE(x), \
      BOOST_VMD_DETAIL_IS_LIST_PROCESS_TUPLE_SIZE, \
      BOOST_VMD_DETAIL_IS_LIST_ASSERT \
      ) \
    (d,x) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_PROCESS_TUPLE_SIZE(d,x) \
    BOOST_PP_IIF \
      ( \
      BOOST_PP_EQUAL_D(d,2,BOOST_PP_TUPLE_SIZE(x)), \
      BOOST_VMD_DETAIL_IS_LIST_RETURN_SECOND, \
      BOOST_VMD_DETAIL_IS_LIST_ASSERT \
      ) \
    (x) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_PRED(d,state) \
    BOOST_VMD_IDENTITY_RESULT \
        ( \
        BOOST_PP_IIF \
          ( \
          BOOST_PP_IS_BEGIN_PARENS(state), \
          BOOST_VMD_IDENTITY(1), \
          BOOST_VMD_DETAIL_IS_LIST_NOT_BOOST_PP_NIL \
          ) \
        (state) \
        ) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_OP(d,state) \
    BOOST_PP_IIF \
      ( \
      BOOST_PP_IS_BEGIN_PARENS(state), \
      BOOST_VMD_DETAIL_IS_LIST_PROCESS_TUPLE, \
      BOOST_VMD_DETAIL_IS_LIST_PROCESS_IF_BOOST_PP_NIL \
      ) \
    (d,state) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_PROCESS_IF_BOOST_PP_NIL(d,x) \
    BOOST_PP_IIF \
      ( \
      BOOST_VMD_DETAIL_IS_LIST_BOOST_PP_NIL(x), \
      BOOST_PP_NIL, \
      BOOST_VMD_IS_LIST_FAILURE \
      ) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_ASSERT(...) \
    BOOST_VMD_IS_LIST_FAILURE \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_NOT_BOOST_PP_NIL(x) \
    BOOST_PP_COMPL \
      ( \
      BOOST_PP_BITOR \
        ( \
        BOOST_VMD_DETAIL_IS_LIST_BOOST_PP_NIL(x), \
        BOOST_VMD_DETAIL_IS_LIST_IS_FAILURE(x) \
        ) \
      ) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_BOOST_PP_NIL(x) \
    BOOST_VMD_IS_EMPTY \
      ( \
      BOOST_PP_CAT \
        ( \
        BOOST_VMD_DETAIL_IS_LIST_NIL_HELPER_, \
        x \
        ) BOOST_PP_EMPTY() \
      ) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_NIL_HELPER_BOOST_PP_NIL

#define BOOST_VMD_DETAIL_IS_LIST_IS_FAILURE(x) \
    BOOST_VMD_IS_EMPTY \
      ( \
      BOOST_PP_CAT(BOOST_VMD_DETAIL_IS_LIST_FHELPER_,x) BOOST_PP_EMPTY() \
      ) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_FHELPER_BOOST_VMD_IS_LIST_FAILURE

#define BOOST_VMD_DETAIL_IS_LIST_RETURN_SECOND(x) \
    BOOST_PP_TUPLE_ELEM(1,x) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_RESULT(x) \
    BOOST_PP_COMPL \
        ( \
        BOOST_VMD_DETAIL_IS_LIST_IS_FAILURE(x) \
        ) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_WLOOP(list) \
    BOOST_VMD_DETAIL_IS_LIST_RESULT \
      ( \
      BOOST_PP_WHILE \
        ( \
        BOOST_VMD_DETAIL_IS_LIST_PRED, \
        BOOST_VMD_DETAIL_IS_LIST_OP, \
        list \
        ) \
      ) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_WLOOP_D(d,list) \
    BOOST_VMD_DETAIL_IS_LIST_RESULT \
      ( \
      BOOST_PP_WHILE_ ## d \
        ( \
        BOOST_VMD_DETAIL_IS_LIST_PRED, \
        BOOST_VMD_DETAIL_IS_LIST_OP, \
        list \
        ) \
      ) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_IS_EMPTY_LIST_PROCESS(list) \
    BOOST_VMD_IS_IDENTIFIER(list,BOOST_PP_NIL) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_IS_EMPTY_LIST_PROCESS_D(d,list) \
    BOOST_VMD_IS_IDENTIFIER_D(d,list,BOOST_PP_NIL) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_PROCESS(param) \
    BOOST_PP_IIF \
      ( \
      BOOST_PP_IS_BEGIN_PARENS(param), \
      BOOST_VMD_DETAIL_IS_LIST_WLOOP, \
      BOOST_VMD_DETAIL_IS_LIST_IS_EMPTY_LIST_PROCESS \
      ) \
    (param) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST(param) \
    BOOST_VMD_IDENTITY_RESULT \
        ( \
        BOOST_PP_IIF \
          ( \
          BOOST_VMD_IS_EMPTY(param), \
          BOOST_VMD_IDENTITY(0), \
          BOOST_VMD_DETAIL_IS_LIST_PROCESS \
          ) \
        (param) \
        ) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_PROCESS_D(d,param) \
    BOOST_PP_IIF \
      ( \
      BOOST_PP_IS_BEGIN_PARENS(param), \
      BOOST_VMD_DETAIL_IS_LIST_WLOOP_D, \
      BOOST_VMD_DETAIL_IS_LIST_IS_EMPTY_LIST_PROCESS_D \
      ) \
    (d,param) \
/**/

#define BOOST_VMD_DETAIL_IS_LIST_D(d,param) \
    BOOST_VMD_IDENTITY_RESULT \
        ( \
        BOOST_PP_IIF \
          ( \
          BOOST_VMD_IS_EMPTY(param), \
          BOOST_VMD_IDENTITY(0), \
          BOOST_VMD_DETAIL_IS_LIST_PROCESS_D \
          ) \
        (d,param) \
        ) \
/**/

#endif /* BOOST_VMD_DETAIL_IS_LIST_HPP */
