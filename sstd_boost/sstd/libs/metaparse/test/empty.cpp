// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/empty.hpp>
#include <sstd/boost/metaparse/is_error.hpp>
#include <sstd/boost/metaparse/start.hpp>
#include <sstd/boost/metaparse/get_result.hpp>

#include "common.hpp"

#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/apply_wrap.hpp>
#include <sstd/boost/mpl/assert.hpp>

#include "test_case.hpp"

BOOST_METAPARSE_TEST_CASE(empty)
{
  using boost::metaparse::get_result;
  using boost::metaparse::empty;
  using boost::metaparse::start;
  using boost::metaparse::is_error;

  using boost::mpl::equal_to;
  using boost::mpl::apply_wrap2;

  typedef empty<int13> empty13;

  // test_accept_empty
  BOOST_MPL_ASSERT((
    equal_to<get_result<apply_wrap2<empty13, str_, start> >::type, int13>
  ));

  // test_reject_non_empty
  BOOST_MPL_ASSERT((is_error<apply_wrap2<empty13, str_a, start> >));
}
