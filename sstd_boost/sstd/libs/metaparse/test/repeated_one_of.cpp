// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/repeated_one_of.hpp>
#include <sstd/boost/metaparse/one_char.hpp>
#include <sstd/boost/metaparse/fail.hpp>
#include <sstd/boost/metaparse/keyword.hpp>
#include <sstd/boost/metaparse/start.hpp>
#include <sstd/boost/metaparse/get_result.hpp>

#include "common.hpp"

#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/apply_wrap.hpp>
#include <sstd/boost/mpl/list.hpp>
#include <sstd/boost/mpl/equal.hpp>
#include <sstd/boost/mpl/vector_c.hpp>
#include <sstd/boost/mpl/assert.hpp>

#include "test_case.hpp"

BOOST_METAPARSE_TEST_CASE(repeated_one_of)
{
  using boost::metaparse::fail;
  using boost::metaparse::get_result;
  using boost::metaparse::repeated_one_of;
  using boost::metaparse::start;
  using boost::metaparse::one_char;
  using boost::metaparse::keyword;

  using boost::mpl::equal;
  using boost::mpl::apply_wrap2;
  using boost::mpl::list;
  using boost::mpl::vector_c;

  typedef fail<test_failure> test_fail;

  // test0
  BOOST_MPL_ASSERT((
    equal<
      get_result<apply_wrap2<repeated_one_of< >, str_hello, start> >::type,
      list<>
    >
  ));

  // test_good_sequence
  BOOST_MPL_ASSERT((
    equal<
      get_result<
        apply_wrap2<repeated_one_of<one_char>, str_hello, start>
      >::type,
      vector_c<char, 'h', 'e', 'l', 'l', 'o'>
    >
  ));

  // test_1_with_bad
  BOOST_MPL_ASSERT((
    equal<
      get_result<
        apply_wrap2<repeated_one_of<test_fail>, str_hello, start>
      >::type,
      list< >
    >
  ));

  // test_2_with_first_good
  BOOST_MPL_ASSERT((
    equal<
      get_result<
        apply_wrap2<repeated_one_of<one_char, test_fail>, str_hello, start>
      >::type,
      vector_c<char, 'h', 'e', 'l', 'l', 'o'>
    >
  ));

  // test_2_with_second_good
  BOOST_MPL_ASSERT((
    equal<
      get_result<
        apply_wrap2<repeated_one_of<test_fail, one_char>, str_hello, start>
      >::type,
      vector_c<char, 'h', 'e', 'l', 'l', 'o'>
    >
  ));

  typedef keyword<str_h, char_h> keyword_h;
  typedef keyword<str_e, char_e> keyword_e;
  typedef keyword<str_l, char_l> keyword_l;

  // test_accept_any_argument
  BOOST_MPL_ASSERT((
    equal<
      get_result<
        apply_wrap2<
          repeated_one_of<keyword_h, keyword_e, keyword_l>,
          str_hello,
          start
        >
      >::type,
      list<char_h, char_e, char_l, char_l>
    >
  ));
}
