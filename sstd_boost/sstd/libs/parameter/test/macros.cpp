﻿// Copyright David Abrahams, Daniel Wallin 2003. Use, modification and
// distribution is subject to the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/parameter.hpp>
#include <sstd/boost/parameter/macros.hpp>
#include <sstd/boost/bind.hpp>
#include <sstd/boost/static_assert.hpp>
#include <sstd/boost/ref.hpp>
#include <cassert>
#include <string.h>

#include "basics.hpp"

namespace test
{

  BOOST_PARAMETER_FUN(int, f, 2, 4, f_parameters)
  {
      p[tester](
          p[name]
        , p[value || boost::bind(&value_default) ]
#if BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042))
        , p[test::index | 999 ]
#else
        , p[index | 999 ]
#endif
      );

      return 1;
  }

} // namespace test

int main()
{
    using test::f;
    using test::name;
    using test::value;
    using test::index;
    using test::tester;

    f(
       test::values(S("foo"), S("bar"), S("baz"))
     , S("foo"), S("bar"), S("baz")
   );

   int x = 56;
   f(
       test::values("foo", 666.222, 56)
     , index = boost::ref(x), name = "foo"
   );

   return boost::report_errors();
}

