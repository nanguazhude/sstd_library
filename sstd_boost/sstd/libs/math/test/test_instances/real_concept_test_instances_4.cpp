// Copyright John Maddock 2011.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "pch.hpp"

#ifndef BOOST_BUILD_PCH_ENABLED
#define BOOST_MATH_OVERFLOW_ERROR_POLICY ignore_error
#include <sstd/boost/math/special_functions/ellint_rf.hpp>
#include <sstd/boost/math/special_functions/ellint_1.hpp>
#include <sstd/boost/math/special_functions/ellint_2.hpp>
#include <sstd/boost/math/special_functions/ellint_3.hpp>
#include <sstd/boost/math/special_functions/ellint_d.hpp>
#include <sstd/boost/math/special_functions/jacobi_zeta.hpp>
#include <sstd/boost/math/special_functions/heuman_lambda.hpp>
#include <sstd/boost/math/special_functions/ellint_rc.hpp>
#include <sstd/boost/math/special_functions/ellint_rf.hpp>
#include <sstd/boost/math/special_functions/ellint_rj.hpp>
#include <sstd/boost/math/special_functions/ellint_rd.hpp>
#include <sstd/boost/math/special_functions/ellint_rg.hpp>
#endif

#include <sstd/boost/math/tools/config.hpp>
#include <sstd/boost/math/concepts/real_concept.hpp>

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS

#define BOOST_MATH_TEST_TYPE boost::math::concepts::real_concept
#define TEST_GROUP_4
#include "test_instances.hpp"

#endif
