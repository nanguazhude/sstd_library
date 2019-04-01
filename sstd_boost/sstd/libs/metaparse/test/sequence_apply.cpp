// Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/sequence_apply.hpp>
#include <sstd/boost/metaparse/is_error.hpp>
#include <sstd/boost/metaparse/start.hpp>
#include <sstd/boost/metaparse/get_result.hpp>
#include <sstd/boost/metaparse/always.hpp>
#include <sstd/boost/metaparse/one_char.hpp>

#include "common.hpp"

#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/list.hpp>
#include <sstd/boost/mpl/at.hpp>
#include <sstd/boost/mpl/vector_c.hpp>
#include <sstd/boost/mpl/vector.hpp>
#include <sstd/boost/mpl/assert.hpp>
#include <sstd/boost/mpl/char.hpp>

#include <sstd/boost/type_traits/is_same.hpp>

#include <sstd/boost/preprocessor/repetition/repeat_from_to.hpp>
#include <sstd/boost/preprocessor/repetition/enum_params.hpp>
#include <sstd/boost/preprocessor/repetition/enum.hpp>
#include <sstd/boost/preprocessor/tuple/eat.hpp>
#include <sstd/boost/preprocessor/cat.hpp>

#include "test_case.hpp"

namespace
{
#ifdef BOOST_METAPARSE_C_VALUE
#  error BOOST_METAPARSE_C_VALUE already defined
#endif
#define BOOST_METAPARSE_C_VALUE(z, n, unused) BOOST_PP_CAT(C, n)::value

#ifdef BOOST_METAPARSE_TEMPLATE
#  error BOOST_METAPARSE_TEMPLATE already defined
#endif
#define BOOST_METAPARSE_TEMPLATE(z, n, unused) \
  template <BOOST_PP_ENUM(n, char BOOST_PP_TUPLE_EAT(3), ~)> \
  struct BOOST_PP_CAT(template_c, n) \
  { \
    typedef BOOST_PP_CAT(template_c, n) type; \
  }; \
  \
  template <BOOST_PP_ENUM_PARAMS(n, class C)> \
  struct BOOST_PP_CAT(template, n) \
  { \
    typedef \
      BOOST_PP_CAT(template_c, n)< \
        BOOST_PP_ENUM(n, BOOST_METAPARSE_C_VALUE, ~) \
      > \
      type; \
  };

  BOOST_PP_REPEAT_FROM_TO(1, 4, BOOST_METAPARSE_TEMPLATE, ~)

#undef BOOST_METAPARSE_TEMPLATE
#undef BOOST_METAPARSE_C_VALUE

  template <class T> struct has_no_type {};

  // "is_same<T::type::type, double_eval<T>::type>" - helper tool to avoid
  // writing type::type (which is interpreted as the constructor of ::type by
  // msvc-7.1)
  template <class T> struct double_eval : T::type {};
}

BOOST_METAPARSE_TEST_CASE(sequence_apply)
{
  using boost::metaparse::get_result;
  using boost::metaparse::sequence_apply1;
  using boost::metaparse::sequence_apply2;
  using boost::metaparse::sequence_apply3;
  using boost::metaparse::start;
  using boost::metaparse::is_error;
  using boost::metaparse::always;
  using boost::metaparse::one_char;

  using boost::mpl::list;
  using boost::mpl::equal_to;
  using boost::mpl::at_c;
  using boost::mpl::vector_c;
  using boost::mpl::vector;
  using boost::mpl::char_;

  using boost::is_same;

  typedef always<one_char, int> always_int;

  // test_one_parser
  BOOST_MPL_ASSERT((
    is_same<
      template_c1<'h'>,
      double_eval<
        get_result<
          sequence_apply1<template1, lit_h>::apply<str_hello, start>
        >
      >::type
    >
  ));

  // test_one_failing_parser
  BOOST_MPL_ASSERT((
    is_error<sequence_apply1<template1, lit_e>::apply<str_hello, start> >
  ));

  // test_two_chars
  BOOST_MPL_ASSERT((
    is_same<
      template_c2<'h', 'e'>,
      double_eval<
        get_result<
          sequence_apply2<template2, lit_h, lit_e>::apply<str_hello, start>
        >
      >::type
    >
  ));

  // test_first_fails
  BOOST_MPL_ASSERT((
    is_error<sequence_apply2<template2, lit_x, lit_e>::apply<str_hello, start> >
  ));

  // test_second_fails
  BOOST_MPL_ASSERT((
    is_error<sequence_apply2<template2, lit_h, lit_x>::apply<str_hello, start> >
  ));

  // test_empty_input
  BOOST_MPL_ASSERT((
    is_error<sequence_apply2<template2, lit_h, lit_e>::apply<str_,start> >
  ));

  // test_three_chars
  BOOST_MPL_ASSERT((
    is_same<
      template_c3<'h', 'e', 'l'>,
      double_eval<
        get_result<
          sequence_apply3<template3, lit_h, lit_e, lit_l>
            ::apply<str_hello, start>
        >
      >::type
    >
  ));

  // test_no_extra_evaluation
  BOOST_MPL_ASSERT((
    is_same<
      has_no_type<int>,
      get_result<
        sequence_apply1<has_no_type, always_int>::apply<str_ca, start>
      >::type
    >
  ));
}


