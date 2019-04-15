// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/unless_error.hpp>
#include <sstd/boost/metaparse/is_error.hpp>
#include <sstd/boost/metaparse/fail.hpp>

#include "common.hpp"

#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/apply_wrap.hpp>
#include <sstd/boost/mpl/assert.hpp>

#include "test_case.hpp"

namespace
{
  using boost::mpl::apply_wrap2;
  using boost::metaparse::fail;

  typedef apply_wrap2<fail<int1>, int11, int2> err;
}

BOOST_METAPARSE_TEST_CASE(util_unless_error)
{
  using boost::metaparse::is_error;
  using boost::metaparse::unless_error;

  using boost::mpl::equal_to;

  // test_error
  BOOST_MPL_ASSERT((is_error<unless_error<err, int13> >));

  // test_not_error
  BOOST_MPL_ASSERT((equal_to<int13, unless_error<int11, int13>::type>));
}
