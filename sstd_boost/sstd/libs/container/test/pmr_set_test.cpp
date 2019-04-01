﻿//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <sstd/boost/container/pmr/set.hpp>
#include <sstd/boost/static_assert.hpp>
#include <sstd/boost/container/detail/type_traits.hpp>

int main()
{
   using namespace boost::container;
   using boost::container::dtl::is_same;

   typedef set<int, std::less<int>, pmr::polymorphic_allocator<int> > intcontainer_t;
   BOOST_STATIC_ASSERT(( is_same<intcontainer_t, pmr::set_of<int>::type >::value ));
   #if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
      BOOST_STATIC_ASSERT(( is_same<intcontainer_t, pmr::set<int> >::value ));
   #endif
   return 0;
}
