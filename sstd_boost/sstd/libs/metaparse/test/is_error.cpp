// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/is_error.hpp>
#include <sstd/boost/metaparse/fail.hpp>

#include "common.hpp"

#include <sstd/boost/mpl/not.hpp>
#include <sstd/boost/mpl/apply_wrap.hpp>
#include <sstd/boost/mpl/assert.hpp>

#include "test_case.hpp"

BOOST_METAPARSE_TEST_CASE(is_error)
{
  using boost::metaparse::is_error;
  using boost::metaparse::fail;

  using boost::mpl::not_;
  using boost::mpl::apply_wrap2;

  // test_not_error
  BOOST_MPL_ASSERT((not_<is_error<int13> >));

  // test_error
  BOOST_MPL_ASSERT((is_error<apply_wrap2<fail<int11>, int1, int13> >));
}
