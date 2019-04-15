// Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/transform_error_message.hpp>
#include <sstd/boost/metaparse/start.hpp>
#include <sstd/boost/metaparse/string.hpp>
#include <sstd/boost/metaparse/reject.hpp>
#include <sstd/boost/metaparse/lit_c.hpp>
#include <sstd/boost/metaparse/get_position.hpp>
#include <sstd/boost/metaparse/error/literal_expected.hpp>

#include <sstd/boost/mpl/assert.hpp>

#include <sstd/boost/type_traits.hpp>

#include "test_case.hpp"

using boost::metaparse::reject;
using boost::metaparse::get_position;

namespace
{
  template <class OldMsg>
  struct new_message
  {
    typedef new_message type;
  };

  struct change_message
  {
    typedef change_message type;

    template <class Msg>
    struct apply : new_message<Msg> {};
  };
}

BOOST_METAPARSE_TEST_CASE(transform_error_message)
{
  using boost::metaparse::transform_error_message;
  using boost::metaparse::start;
  using boost::metaparse::string;
  using boost::metaparse::lit_c;
  using boost::metaparse::error::literal_expected;

  using boost::is_same;

  typedef string<'H','e','l','l','o'> s;

  // test_transform_error_message_does_not_change_accept
  BOOST_MPL_ASSERT((
    is_same<
      lit_c<'H'>::apply<s, start>::type,
      transform_error_message<lit_c<'H'>, change_message>::apply<s, start>::type
    >
  ));

  // test_transform_is_called
  BOOST_MPL_ASSERT((
    is_same<
      reject<new_message<literal_expected<'x'> >, start>,
      transform_error_message<lit_c<'x'>, change_message>::apply<s, start>::type
    >
  ));
}
