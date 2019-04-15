/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <sstd/boost/detail/lightweight_test.hpp>

#include <sstd/boost/detail/lightweight_test.hpp>
#include <sstd/boost/fusion/support/category_of.hpp>
#include <sstd/boost/fusion/view/zip_view.hpp>
#include <sstd/boost/fusion/container/vector.hpp>
#include <sstd/boost/fusion/container/list.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/size.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/at.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/front.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/back.hpp>
#include <sstd/boost/fusion/iterator/next.hpp>
#include <sstd/boost/fusion/iterator/prior.hpp>
#include <sstd/boost/fusion/iterator/deref.hpp>
#include <sstd/boost/fusion/iterator/advance.hpp>
#include <sstd/boost/fusion/sequence/comparison/equal_to.hpp>
#include <sstd/boost/fusion/container/generation/make_vector.hpp>
#include <sstd/boost/fusion/adapted/mpl.hpp>
#include <sstd/boost/mpl/assert.hpp>
#include <sstd/boost/mpl/equal_to.hpp>

#include <sstd/boost/type_traits/is_reference.hpp>
#include <sstd/boost/type_traits/is_same.hpp>
#include <sstd/boost/static_assert.hpp>

int main()
{
    {
        using namespace boost::fusion;
        typedef vector2<int,int> int_vector;
        typedef vector2<char,char> char_vector;
        typedef list<char,char> char_list;
        typedef vector<int_vector&, char_vector&, char_list&> seqs_type;
        typedef zip_view<seqs_type> view;

        BOOST_MPL_ASSERT((boost::mpl::equal_to<boost::fusion::result_of::size<view>::type, boost::fusion::result_of::size<int_vector>::type>));
        BOOST_STATIC_ASSERT((boost::fusion::result_of::size<view>::value == 2));

        int_vector iv(1,2);
        char_vector cv('a', 'b');
        char_list cl('y','z');
        seqs_type seqs(iv, cv, cl);
        view v(seqs);

        BOOST_TEST(at_c<0>(v) == make_vector(1, 'a', 'y'));
        BOOST_TEST(at_c<1>(v) == make_vector(2, 'b', 'z'));
        BOOST_TEST(front(v) == make_vector(1, 'a', 'y'));
        BOOST_TEST(*next(begin(v)) == make_vector(2, 'b', 'z'));
        BOOST_TEST(advance_c<2>(begin(v)) == end(v));
        BOOST_TEST(distance(begin(v), end(v)) == 2);
        BOOST_STATIC_ASSERT((boost::fusion::result_of::distance<boost::fusion::result_of::begin<view>::type, boost::fusion::result_of::end<view>::type>::value == 2));

        BOOST_MPL_ASSERT((boost::is_same<boost::fusion::result_of::value_at_c<view,0>::type, vector3<int,char,char> >));
        BOOST_MPL_ASSERT((boost::is_same<boost::fusion::result_of::value_of<boost::fusion::result_of::begin<view>::type>::type, vector3<int,char,char> >));
    }
    return boost::report_errors();
}
