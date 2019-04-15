/* boost random.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/random for documentation.
 *
 * $Id$
 *
 * Revision history
 *  2000-02-18  portability fixes (thanks to Beman Dawes)
 *  2000-02-21  shuffle_output, inversive_congruential_schrage,
 *              generator_iterator, uniform_smallint
 *  2000-02-23  generic modulus arithmetic helper, removed *_schrage classes,
 *              implemented Streamable and EqualityComparable concepts for
 *              generators, added Bernoulli distribution and Box-Muller
 *              transform
 *  2000-03-01  cauchy, lognormal, triangle distributions; fixed
 *              uniform_smallint; renamed gaussian to normal distribution
 *  2000-03-05  implemented iterator syntax for distribution functions
 *  2000-04-21  removed some optimizations for better BCC/MSVC compatibility
 *  2000-05-10  adapted to BCC and MSVC
 *  2000-06-13  incorporated review results
 *  2000-07-06  moved basic templates from namespace detail to random
 *  2000-09-23  warning removals and int64 fixes (Ed Brey)
 *  2000-09-24  added lagged_fibonacci generator (Matthias Troyer)
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_HPP
#define BOOST_RANDOM_HPP

// generators
#include <sstd/boost/random/additive_combine.hpp>
#include <sstd/boost/random/discard_block.hpp>
#include <sstd/boost/random/independent_bits.hpp>
#include <sstd/boost/random/inversive_congruential.hpp>
#include <sstd/boost/random/lagged_fibonacci.hpp>
#include <sstd/boost/random/linear_congruential.hpp>
#include <sstd/boost/random/linear_feedback_shift.hpp>
#include <sstd/boost/random/mersenne_twister.hpp>
#include <sstd/boost/random/ranlux.hpp>
#include <sstd/boost/random/shuffle_order.hpp>
#include <sstd/boost/random/shuffle_output.hpp>
#include <sstd/boost/random/subtract_with_carry.hpp>
#include <sstd/boost/random/taus88.hpp>
#include <sstd/boost/random/xor_combine.hpp>

// misc
#include <sstd/boost/random/generate_canonical.hpp>
#include <sstd/boost/random/seed_seq.hpp>
#include <sstd/boost/random/random_number_generator.hpp>
#include <sstd/boost/random/variate_generator.hpp>

// distributions
#include <sstd/boost/random/bernoulli_distribution.hpp>
#include <sstd/boost/random/beta_distribution.hpp>
#include <sstd/boost/random/binomial_distribution.hpp>
#include <sstd/boost/random/cauchy_distribution.hpp>
#include <sstd/boost/random/chi_squared_distribution.hpp>
#include <sstd/boost/random/discrete_distribution.hpp>
#include <sstd/boost/random/exponential_distribution.hpp>
#include <sstd/boost/random/extreme_value_distribution.hpp>
#include <sstd/boost/random/fisher_f_distribution.hpp>
#include <sstd/boost/random/gamma_distribution.hpp>
#include <sstd/boost/random/geometric_distribution.hpp>
#include <sstd/boost/random/hyperexponential_distribution.hpp>
#include <sstd/boost/random/laplace_distribution.hpp>
#include <sstd/boost/random/lognormal_distribution.hpp>
#include <sstd/boost/random/negative_binomial_distribution.hpp>
#include <sstd/boost/random/non_central_chi_squared_distribution.hpp>
#include <sstd/boost/random/normal_distribution.hpp>
#include <sstd/boost/random/piecewise_constant_distribution.hpp>
#include <sstd/boost/random/piecewise_linear_distribution.hpp>
#include <sstd/boost/random/poisson_distribution.hpp>
#include <sstd/boost/random/student_t_distribution.hpp>
#include <sstd/boost/random/triangle_distribution.hpp>
#include <sstd/boost/random/uniform_01.hpp>
#include <sstd/boost/random/uniform_int.hpp>
#include <sstd/boost/random/uniform_int_distribution.hpp>
#include <sstd/boost/random/uniform_on_sphere.hpp>
#include <sstd/boost/random/uniform_real.hpp>
#include <sstd/boost/random/uniform_real_distribution.hpp>
#include <sstd/boost/random/uniform_smallint.hpp>
#include <sstd/boost/random/weibull_distribution.hpp>

#include <sstd/boost/random/generate_canonical.hpp>

#endif // BOOST_RANDOM_HPP
