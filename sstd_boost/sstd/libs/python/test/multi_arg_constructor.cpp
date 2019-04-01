// Copyright David Abrahams 2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <sstd/boost/python/module.hpp>
#include <sstd/boost/python/def.hpp>
#include <sstd/boost/python/class.hpp>

struct A
{
    A(const double, const double, const double, const double, const double
      , const double, const double
      , const double, const double
        ) {}
};

BOOST_PYTHON_MODULE(multi_arg_constructor_ext)
{
  using namespace boost::python;

  class_<A>(
      "A"
      , init<double, double, double, double, double, double, double, double, double>()
      )
      ;

}


