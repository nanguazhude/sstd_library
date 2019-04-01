
//  (C) Copyright John Maddock 2000.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/type_traits/is_void.hpp>
#include <sstd/boost/type_traits/add_const.hpp>
#include <sstd/boost/mpl/list.hpp>
#include <sstd/boost/mpl/front.hpp>
#include <sstd/boost/mpl/remove_if.hpp>
#include <sstd/boost/mpl/transform.hpp>
#include <sstd/boost/static_assert.hpp>

template <class List>
struct lambda_test
{
   typedef typename boost::mpl::remove_if<List, boost::is_void<boost::mpl::_> >::type reduced_list;
   typedef typename boost::mpl::transform<reduced_list, boost::add_const<boost::mpl::_> >::type const_list;
   typedef typename boost::mpl::front<const_list>::type type;
};


int main()
{
   typedef boost::mpl::list<const void, int, float, void, double> list_type;

   lambda_test<list_type>::type i = 0;
   return i;
}

