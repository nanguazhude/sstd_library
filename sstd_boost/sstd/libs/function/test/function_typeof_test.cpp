// Boost.Function library

//  Copyright Douglas Gregor 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org
#include <sstd/boost/function/function_typeof.hpp>
#include <sstd/boost/function.hpp>
#include <sstd/boost/typeof/typeof.hpp>
#include <sstd/boost/type_traits/is_same.hpp>
#include <sstd/boost/static_assert.hpp>

void f(boost::function0<void> f, boost::function0<void> g)
{
  BOOST_STATIC_ASSERT((boost::is_same<boost::function0<void>, BOOST_TYPEOF(f = g)>::value));
}
