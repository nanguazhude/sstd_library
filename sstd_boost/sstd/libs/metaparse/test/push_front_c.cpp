// Copyright Abel Sinkovics (abel@sinkovics.hu) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/config.hpp>
#if BOOST_METAPARSE_STD >= 2011
#  include <sstd/boost/metaparse/v1/cpp11/impl/push_front_c.hpp>
#else
#  include <sstd/boost/metaparse/v1/cpp98/impl/push_front_c.hpp>
#endif

#include <sstd/boost/metaparse/string.hpp>

#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/char.hpp>
#include <sstd/boost/mpl/assert.hpp>

#include "test_case.hpp"

BOOST_METAPARSE_TEST_CASE(push_front_c)
{
  using boost::metaparse::v1::impl::push_front_c;
  using boost::metaparse::string;

  using boost::mpl::equal_to;
  using boost::mpl::char_;

  typedef string<'h','e','l','l','o'> hello;

  // test_push_front
  BOOST_MPL_ASSERT((
    equal_to<hello, push_front_c<string<'e','l','l','o'>, 'h'>::type>
  ));

  // test_push_front_to_empty
  BOOST_MPL_ASSERT((equal_to<string<'x'>, push_front_c<string<>, 'x'>::type>));
}
