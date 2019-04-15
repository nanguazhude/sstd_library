// Copyright Abel Sinkovics (abel@sinkovics.hu) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/config.hpp>
#if BOOST_METAPARSE_STD >= 2011

#include <sstd/boost/metaparse/v1/cpp11/impl/remove_trailing_no_chars.hpp>
#include <sstd/boost/metaparse/string.hpp>

#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/char.hpp>
#include <sstd/boost/mpl/assert.hpp>

#include "test_case.hpp"

BOOST_METAPARSE_TEST_CASE(remove_trailing_no_chars)
{
  using boost::metaparse::v1::impl::remove_trailing_no_chars;
  using boost::metaparse::string;

  using boost::mpl::equal_to;
  using boost::mpl::char_;

  typedef string<'h','e','l','l','o'> hello;

  // test_hello
  BOOST_MPL_ASSERT((equal_to<hello, remove_trailing_no_chars<hello>::type>));

  // test_twice
  BOOST_MPL_ASSERT((
    equal_to<
      hello,
      remove_trailing_no_chars<remove_trailing_no_chars<hello>::type>::type
    >
  ));

  // test_hello_with_no_chars
  BOOST_MPL_ASSERT((
    equal_to<
      hello,
      remove_trailing_no_chars<
        string<'h','e','l','l','o', BOOST_NO_CHAR, BOOST_NO_CHAR>
      >::type
    >
  ));

  // test_empty
  BOOST_MPL_ASSERT((
    equal_to<string<>, remove_trailing_no_chars<string<> >::type>
  ));

  // test_empty_with_no_chars
  BOOST_MPL_ASSERT((
    equal_to<
      string<>,
      remove_trailing_no_chars<string<BOOST_NO_CHAR, BOOST_NO_CHAR> >::type
    >
  ));
}

#endif
