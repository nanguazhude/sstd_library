// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/look_ahead.hpp>
#include <sstd/boost/metaparse/start.hpp>
#include <sstd/boost/metaparse/get_result.hpp>
#include <sstd/boost/metaparse/digit_val.hpp>
#include <sstd/boost/metaparse/fail.hpp>
#include <sstd/boost/metaparse/is_error.hpp>
#include <sstd/boost/metaparse/get_remaining.hpp>

#include "common.hpp"

#include <sstd/boost/mpl/apply_wrap.hpp>
#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/equal.hpp>
#include <sstd/boost/mpl/assert.hpp>

#include "test_case.hpp"

BOOST_METAPARSE_TEST_CASE(look_ahead)
{

  using boost::metaparse::get_result;
  using boost::metaparse::look_ahead;
  using boost::metaparse::digit_val;
  using boost::metaparse::start;
  using boost::metaparse::is_error;
  using boost::metaparse::fail;
  using boost::metaparse::get_remaining;

  using boost::mpl::equal_to;
  using boost::mpl::apply_wrap2;
  using boost::mpl::equal;

  // test_returns_result
  BOOST_MPL_ASSERT((
    equal_to<
      int1,
      get_result<apply_wrap2<look_ahead<digit_val>, str_1983, start> >::type
    >
  ));

  // test_returns_error
  BOOST_MPL_ASSERT((
    is_error<apply_wrap2<look_ahead<fail<int13> >, str_1983, start> >
  ));

  // test_doesnt_process_input
  BOOST_MPL_ASSERT((
    equal<
      str_1983,
      get_remaining<apply_wrap2<look_ahead<digit_val>, str_1983, start> >::type
    >
  ));
}



