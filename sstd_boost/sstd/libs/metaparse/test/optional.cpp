// Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/optional.hpp>
#include <sstd/boost/metaparse/string.hpp>
#include <sstd/boost/metaparse/lit_c.hpp>
#include <sstd/boost/metaparse/get_result.hpp>
#include <sstd/boost/metaparse/start.hpp>

#include <sstd/boost/mpl/assert.hpp>
#include <sstd/boost/mpl/equal_to.hpp>
#include <sstd/boost/mpl/char.hpp>

#include <sstd/boost/type_traits/is_same.hpp>

#include "test_case.hpp"

BOOST_METAPARSE_TEST_CASE(optional)
{
  using boost::metaparse::optional;
  using boost::metaparse::lit_c;
  using boost::metaparse::string;
  using boost::metaparse::get_result;
  using boost::metaparse::start;

  using boost::mpl::equal_to;

  using boost::is_same;

  typedef optional<lit_c<'x'>, double> optional_x;

  // test_optional_parser_succeeds
  BOOST_MPL_ASSERT((
    equal_to<
      boost::mpl::char_<'x'>,
      get_result<optional_x::apply<string<'x'>, start> >::type
    >
  ));

  // test_optional_parser_fails
  BOOST_MPL_ASSERT((
    is_same<double, get_result<optional_x::apply<string<'y'>, start> >::type>
  ));

  // test_optional_parser_default_value
  BOOST_MPL_ASSERT((
    is_same<
      void,
      get_result<optional<lit_c<'x'> >::apply<string<'y'>, start> >::type
    >
  ));
}


