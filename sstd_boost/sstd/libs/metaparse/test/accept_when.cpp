// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/accept_when.hpp>
#include <sstd/boost/metaparse/get_result.hpp>
#include <sstd/boost/metaparse/util/is_digit.hpp>
#include <sstd/boost/metaparse/is_error.hpp>
#include <sstd/boost/metaparse/start.hpp>
#include <sstd/boost/metaparse/one_char.hpp>

#include "common.hpp"

#include <sstd/boost/metaparse/util/is_digit.hpp>

#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/apply_wrap.hpp>
#include <sstd/boost/mpl/assert.hpp>

#include "test_case.hpp"

BOOST_METAPARSE_TEST_CASE(accept_when)
{
  using boost::metaparse::is_error;
  using boost::metaparse::accept_when;
  using boost::metaparse::one_char;
  using boost::metaparse::start;
  using boost::metaparse::get_result;

  using boost::metaparse::util::is_digit;

  using boost::mpl::apply;
  using boost::mpl::equal_to;
  using boost::mpl::apply_wrap2;

  // test_with_text
  BOOST_MPL_ASSERT((
    is_error<
      apply_wrap2<
        accept_when<one_char, is_digit<>, test_failure>,
        str_hello,
        start
      >
    >
  ));

  // test_with_number
  BOOST_MPL_ASSERT((
    equal_to<
      get_result<
        apply_wrap2<
          accept_when<one_char, is_digit<>, test_failure>,
          str_1983,
          start
        >
      >::type,
      char_1
    >
  ));

  // test_with_empty_string
  BOOST_MPL_ASSERT((
    is_error<
      apply_wrap2<accept_when<one_char, is_digit<>, test_failure>, str_, start>
    >
  ));
}
