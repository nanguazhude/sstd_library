/* Boost example/rational.cpp
 * example program of how to use interval< rational<> >
 *
 * Copyright 2002-2003 Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

// it would have been enough to only include:
//   <sstd/boost/numeric/interval.hpp>
// but it's a bit overkill to include processor intrinsics
// and transcendental functions, so we do it by ourselves

#include <sstd/boost/numeric/interval/interval.hpp>      // base class
#include <sstd/boost/numeric/interval/rounded_arith.hpp> // default arithmetic rounding policy
#include <sstd/boost/numeric/interval/checking.hpp>      // default checking policy
#include <sstd/boost/numeric/interval/arith.hpp>         // += *= -= etc
#include <sstd/boost/numeric/interval/policies.hpp>      // default policy

#include <sstd/boost/rational.hpp>
#include <iostream>

typedef boost::rational<int> Rat;
typedef boost::numeric::interval<Rat> Interval;

std::ostream& operator<<(std::ostream& os, const Interval& r) {
  os << "[" << r.lower() << "," << r.upper() << "]";
  return os;
}

int main() {
  Rat p(2, 3), q(3, 4);
  Interval z(4, 5);
  Interval a(p, q);
  a += z;
  z *= q;
  a -= p;
  a /= q;
  std::cout << z << std::endl;
  std::cout << a << std::endl;
}

