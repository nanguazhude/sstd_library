﻿/* Unit testing for outcomes
(C) 2013-2019 Niall Douglas <http://www.nedproductions.biz/> (149 commits)


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "../../include/boost/outcome/outcome.hpp"
#include <sstd/boost/test/unit_test.hpp>
#include <sstd/boost/test/unit_test_monitor.hpp>

#ifdef _MSC_VER
#pragma warning(disable : 4127)  // conditional expression is constant
#endif

#ifndef BOOST_NO_EXCEPTIONS
// std nothrow traits seem to return random values if exceptions are disabled on MSVC
BOOST_OUTCOME_AUTO_TEST_CASE(works_outcome_noexcept, "Tests that the outcome correctly inherits noexcept from its type R")
{
  using namespace BOOST_OUTCOME_V2_NAMESPACE;
  {
    using type = outcome<int>;
    BOOST_CHECK(std::is_nothrow_copy_constructible<type>::value);
    BOOST_CHECK(std::is_nothrow_move_constructible<type>::value);
    BOOST_CHECK(std::is_nothrow_copy_assignable<type>::value);
    BOOST_CHECK(std::is_nothrow_move_assignable<type>::value);
    BOOST_CHECK(std::is_nothrow_destructible<type>::value);
  }
  {
    using type = outcome<std::string>;
    BOOST_CHECK(std::is_nothrow_copy_constructible<type>::value == std::is_nothrow_copy_constructible<std::string>::value);
    BOOST_CHECK(std::is_nothrow_move_constructible<type>::value == std::is_nothrow_move_constructible<std::string>::value);
    BOOST_CHECK(std::is_nothrow_copy_assignable<type>::value == std::is_nothrow_copy_assignable<std::string>::value);
    BOOST_CHECK(std::is_nothrow_move_assignable<type>::value == std::is_nothrow_move_assignable<std::string>::value);
    BOOST_CHECK(std::is_nothrow_destructible<type>::value == std::is_nothrow_destructible<std::string>::value);
  }
  {
    struct Except
    {
      int n;
      Except() = delete;
      Except(const Except & /*unused*/) noexcept(false)
          : n(0)
      {
      }
      Except(Except && /*unused*/) noexcept(false)
          : n(0)
      {
      }
      Except &operator=(const Except & /*unused*/) noexcept(false) { return *this; }
      Except &operator=(Except && /*unused*/) noexcept(false) { return *this; }
      ~Except() noexcept(false) { n = 0; }
    };
    using type = outcome<Except>;
    BOOST_CHECK(!std::is_nothrow_copy_constructible<type>::value);
    BOOST_CHECK(!std::is_nothrow_move_constructible<type>::value);
    BOOST_CHECK(!std::is_nothrow_copy_assignable<type>::value);
    BOOST_CHECK(!std::is_nothrow_move_assignable<type>::value);
    BOOST_CHECK(!std::is_nothrow_destructible<type>::value);
  }
}
#endif
