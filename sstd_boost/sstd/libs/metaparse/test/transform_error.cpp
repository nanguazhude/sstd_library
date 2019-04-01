// Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/metaparse/transform_error.hpp>
#include <sstd/boost/metaparse/start.hpp>
#include <sstd/boost/metaparse/string.hpp>
#include <sstd/boost/metaparse/reject.hpp>
#include <sstd/boost/metaparse/lit_c.hpp>
#include <sstd/boost/metaparse/get_position.hpp>

#include <sstd/boost/mpl/assert.hpp>

#include <sstd/boost/type_traits.hpp>

#include "test_case.hpp"

using boost::metaparse::reject;
using boost::metaparse::get_position;

namespace
{
  struct new_message
  {
    typedef new_message type;
  };

  struct change_message
  {
    typedef change_message type;

    template <class E>
    struct apply : reject<new_message, get_position<E> > {};
  };
}

BOOST_METAPARSE_TEST_CASE(transform_error)
{
  using boost::metaparse::transform_error;
  using boost::metaparse::start;
  using boost::metaparse::string;
  using boost::metaparse::lit_c;

  using boost::is_same;

  typedef string<'H','e','l','l','o'> s;

  // test_transform_error_does_not_change_accept
  BOOST_MPL_ASSERT((
    is_same<
      lit_c<'H'>::apply<s, start>::type,
      transform_error<lit_c<'H'>, change_message>::apply<s, start>::type
    >
  ));

  // test_transform_is_called
  BOOST_MPL_ASSERT((
    is_same<
      reject<new_message, start>,
      transform_error<lit_c<'x'>, change_message>::apply<s, start>::type
    >
  ));
}


