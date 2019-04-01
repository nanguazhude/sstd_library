//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Basic sanity check that header <sstd/boost/math/special_functions/legendre.hpp>
// #includes all the files that it needs to.
//

#include <sstd/boost/math/concepts/std_real_concept.hpp>
#include <sstd/boost/math/special_functions/legendre_stieltjes.hpp>

template class boost::math::legendre_stieltjes<boost::math::concepts::std_real_concept>;

