/*=============================================================================
    Copyright (c) 2014 Louis Dionne

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <sstd/boost/detail/lightweight_test.hpp>
#include <sstd/boost/fusion/algorithm/transformation/push_back.hpp>
#include <sstd/boost/fusion/algorithm/transformation/push_front.hpp>
#include <sstd/boost/fusion/container/deque/convert.hpp>
#include <sstd/boost/fusion/container/deque/deque.hpp>
#include <sstd/boost/fusion/container/generation/make_deque.hpp>
#include <sstd/boost/fusion/container/generation/make_list.hpp>
#include <sstd/boost/fusion/container/generation/make_vector.hpp>
#include <sstd/boost/fusion/sequence/comparison/equal_to.hpp>

#include <string>


int main() {
    using namespace boost::fusion;
    using namespace boost;

    BOOST_TEST(as_deque(make_vector()) == make_deque());
    BOOST_TEST(as_deque(make_vector(1)) == make_deque(1));
    BOOST_TEST(as_deque(make_vector(1, '2')) == make_deque(1, '2'));
    BOOST_TEST(as_deque(make_vector(1, '2', 3.3f)) == make_deque(1, '2', 3.3f));

    BOOST_TEST(as_deque(make_list()) == make_deque());
    BOOST_TEST(as_deque(make_list(1)) == make_deque(1));
    BOOST_TEST(as_deque(make_list(1, '2')) == make_deque(1, '2'));
    BOOST_TEST(as_deque(make_list(1, '2', 3.3f)) == make_deque(1, '2', 3.3f));

    {
        deque<> xs;
        BOOST_TEST(as_deque(push_back(xs, 1)) == make_deque(1));
    }

    {
        deque<int> xs(1);
        BOOST_TEST(as_deque(push_back(xs, '2')) == make_deque(1, '2'));
    }

    {
        deque<int, char> xs(1, '2');
        BOOST_TEST(as_deque(push_back(xs, 3.3f)) == make_deque(1, '2', 3.3f));
    }

    {
        deque<> xs;
        BOOST_TEST(
            as_deque(push_front(xs, make_deque(1, '2', 3.3f))) ==
            make_deque(make_deque(1, '2', 3.3f))
        );

        BOOST_TEST(as_deque(make_deque(make_deque(1))) == make_deque(make_deque(1)));
    }

/* Disabling test for now, see https://github.com/boostorg/fusion/pull/38 ($$$ FIXME $$$)

    {
        deque<> xs;
        BOOST_TEST(
            as_deque(push_front(xs, make_vector(1, '2', 3.3f))) ==
            make_deque(make_vector(1, '2', 3.3f))
        );
    }
*/
    return boost::report_errors();
}
