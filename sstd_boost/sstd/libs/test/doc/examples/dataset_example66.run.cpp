﻿//  (C) Copyright Raffi Enficiaud 2014.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.

//[example_code
#define BOOST_TEST_MODULE dataset_example66
#include <sstd/boost/test/included/unit_test.hpp>
#include <sstd/boost/test/data/test_case.hpp>
#include <sstd/boost/test/data/monomorphic.hpp>

namespace bdata = boost::unit_test::data;

const char* arr[] = {"cat", "dog"};

BOOST_DATA_TEST_CASE(
  test1,
  bdata::xrange(2) ^ bdata::make(arr),
  xr, array_element)
{
  std::cout << "test 1: "
    << xr << ", "
    << array_element
    << std::endl;
  BOOST_TEST(array_element != "mammoth");
}
//]
