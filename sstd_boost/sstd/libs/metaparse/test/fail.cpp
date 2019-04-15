// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/fail.hpp>
#include <sstd/boost/metaparse/is_error.hpp>
#include <sstd/boost/metaparse/start.hpp>

#include "common.hpp"

#include <sstd/boost/mpl/apply_wrap.hpp>
#include <sstd/boost/mpl/assert.hpp>

#include "test_case.hpp"

BOOST_METAPARSE_TEST_CASE(fail)
{
  using boost::metaparse::is_error;
  using boost::metaparse::fail;
  using boost::metaparse::start;

  using boost::mpl::apply_wrap2;

  // test_fail_for_non_empty_string
  BOOST_MPL_ASSERT((
    is_error<apply_wrap2<fail<test_failure>, str_hello, start> >
  ));
}
