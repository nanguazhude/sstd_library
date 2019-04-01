/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler
    Copyright (c) Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <sstd/boost/detail/lightweight_test.hpp>
#include <sstd/boost/fusion/container/vector/vector.hpp>
#include <sstd/boost/fusion/adapted/mpl.hpp>
#include <sstd/boost/fusion/algorithm/query/any.hpp>
#include <sstd/boost/lambda/lambda.hpp>
#include <sstd/boost/mpl/vector_c.hpp>

namespace
{
    struct search_for
    {
        explicit search_for(int in_search)
            : search(in_search)
        {}

        template<typename T>
        bool operator()(T const& v) const
        {
            return v == search;
        }

        int search;
    };
}

int
main()
{
    {
        boost::fusion::vector<int, short, double> t(1, 2, 3.3);
        BOOST_TEST(boost::fusion::any(t, boost::lambda::_1 == 2));
    }

    {
        boost::fusion::vector<int, short, double> t(1, 2, 3.3);
        BOOST_TEST(!boost::fusion::any(t, boost::lambda::_1 == 3));
    }

    {
        typedef boost::mpl::vector_c<int, 1, 2, 3> mpl_vec;
        // We cannot use lambda here as mpl vec iterators return
        // rvalues, and lambda needs lvalues.
        BOOST_TEST(boost::fusion::any(mpl_vec(), search_for(2)));
        BOOST_TEST(!boost::fusion::any(mpl_vec(), search_for(4)));
    }

    return boost::report_errors();
}


