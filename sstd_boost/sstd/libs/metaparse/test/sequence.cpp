// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/sequence.hpp>
#include <sstd/boost/metaparse/is_error.hpp>
#include <sstd/boost/metaparse/start.hpp>
#include <sstd/boost/metaparse/get_result.hpp>
#include <sstd/boost/metaparse/always.hpp>
#include <sstd/boost/metaparse/one_char.hpp>

#include "common.hpp"

#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/apply_wrap.hpp>
#include <sstd/boost/mpl/list.hpp>
#include <sstd/boost/mpl/at.hpp>
#include <sstd/boost/mpl/equal.hpp>
#include <sstd/boost/mpl/vector_c.hpp>
#include <sstd/boost/mpl/vector.hpp>
#include <sstd/boost/mpl/assert.hpp>

#include "test_case.hpp"

BOOST_METAPARSE_TEST_CASE(sequence)
{
  using boost::metaparse::get_result;
  using boost::metaparse::sequence;
  using boost::metaparse::start;
  using boost::metaparse::is_error;
  using boost::metaparse::always;
  using boost::metaparse::one_char;

  using boost::mpl::equal;
  using boost::mpl::apply_wrap2;
  using boost::mpl::list;
  using boost::mpl::equal_to;
  using boost::mpl::at_c;
  using boost::mpl::vector_c;
  using boost::mpl::vector;

  typedef always<one_char, int> always_int;

  // test_no_parser
  BOOST_MPL_ASSERT((
    equal<get_result<apply_wrap2<sequence<>, str_hello, start> >::type, list<> >
  ));

  // test_one_parser
  BOOST_MPL_ASSERT((
    equal<
      get_result<apply_wrap2<sequence<lit_h>, str_hello, start> >::type,
      vector_c<char, 'h'>
    >
  ));

  // test_one_failing_parser
  BOOST_MPL_ASSERT((is_error<apply_wrap2<sequence<lit_e>, str_hello, start> >));

  // test_two_chars
  BOOST_MPL_ASSERT((
    equal<
      get_result<apply_wrap2<sequence<lit_h, lit_e>, str_hello, start> >::type,
      vector_c<char, 'h', 'e'>
    >
  ));

  // test_first_fails
  BOOST_MPL_ASSERT((
    is_error<apply_wrap2<sequence<lit_x, lit_e>, str_hello, start> >
  ));

  // test_second_fails
  BOOST_MPL_ASSERT((
    is_error<apply_wrap2<sequence<lit_h, lit_x>, str_hello, start> >
  ));

  // test_empty_input
  BOOST_MPL_ASSERT((is_error<apply_wrap2<sequence<lit_h,lit_e>, str_,start> >));

  // test_three_chars
  BOOST_MPL_ASSERT((
    equal<
      get_result<
        apply_wrap2<sequence<lit_h, lit_e, lit_l>, str_hello, start>
      >::type,
      vector_c<char, 'h', 'e', 'l'>
    >
  ));

  // test_indexing_in_result
  BOOST_MPL_ASSERT((
    equal_to<
      at_c<
        get_result<
          apply_wrap2<sequence<lit_h, lit_e, lit_l>, str_hello, start>
        >::type,
        1
      >::type,
      char_e
    >
  ));

  // test_no_extra_evaluation
  BOOST_MPL_ASSERT((
    equal<
      get_result<
        apply_wrap2<sequence<always_int, always_int>, str_ca, start>
      >::type,
      vector<int, int>
    >
  ));
}
