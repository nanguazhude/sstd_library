/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <sstd/boost/config.hpp>

// adapted/std_tuple.hpp only supports implementations using variadic templates
#if defined(BOOST_NO_CXX11_HDR_TUPLE) || \
    defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#   error "does not meet requirements"
#endif

#include <sstd/boost/detail/lightweight_test.hpp>
#include <sstd/boost/fusion/adapted/std_tuple.hpp>
#include <sstd/boost/fusion/sequence/convert.hpp>
#include <sstd/boost/fusion/container/vector/vector.hpp>
#include <sstd/boost/fusion/container/generation/make_vector.hpp>
#include <tuple>
#include <string>

int main()
{
    using namespace boost::fusion;
    using namespace boost;

    {
        // conversion vector to std tuple
        std::tuple<int, std::string> t = convert<std_tuple_tag>(make_vector(123, std::string("Hola!!!")));
        BOOST_TEST(std::get<0>(t) == 123);
        BOOST_TEST(std::get<1>(t) == "Hola!!!");
    }

    return boost::report_errors();
}

