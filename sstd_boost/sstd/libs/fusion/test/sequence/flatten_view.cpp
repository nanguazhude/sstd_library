/*==============================================================================
    Copyright (c) 2013 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <sstd/boost/detail/lightweight_test.hpp>
#include <sstd/boost/fusion/container/vector/vector.hpp>
#include <sstd/boost/fusion/view/flatten_view/flatten_view.hpp>
#include <sstd/boost/fusion/sequence/io/out.hpp>
#include <sstd/boost/fusion/sequence/comparison/equal_to.hpp>
#include <sstd/boost/fusion/container/generation/make_vector.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/begin.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/end.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/at.hpp>
#include <sstd/boost/fusion/sequence/intrinsic/size.hpp>
#include <sstd/boost/fusion/iterator/advance.hpp>
#include <sstd/boost/fusion/iterator/deref.hpp>
#include <sstd/boost/fusion/iterator/distance.hpp>
#include <sstd/boost/fusion/algorithm/auxiliary/copy.hpp>


int main()
{
    using namespace boost::fusion;

    {
        typedef vector<int, int, vector<int, int>, int> sequence_type;
        sequence_type seq(1, 2, make_vector(3, 4), 5);
        flatten_view<sequence_type> flattened(seq);

        BOOST_TEST((boost::fusion::size(flattened) == 5));
        BOOST_TEST((boost::fusion::distance(boost::fusion::begin(flattened), boost::fusion::end(flattened)) == 5));
    }

    {
        typedef vector<int, int, vector<int, int>, int> sequence_type;
        sequence_type seq(1, 2, make_vector(3, 4), 5);
        flatten_view<sequence_type> flattened(seq);
        std::cout << flattened << std::endl;
        BOOST_TEST((flattened == make_vector(1, 2, 3, 4, 5)));
        BOOST_TEST((*advance_c<2>(boost::fusion::begin(flattened)) == 3));
    }

    {
        typedef vector<int, int, vector<int, int>, int> sequence_type;
        sequence_type seq;
        flatten_view<sequence_type> flattened(seq);
        copy(make_vector(1, 2, 3, 4, 5), flattened);
        std::cout << seq << std::endl;
        BOOST_TEST((seq == make_vector(1, 2, make_vector(3, 4), 5)));
    }

    return boost::report_errors();
}
