// Copyright 2015-2017 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/core/lightweight_test.hpp>
#include <sstd/boost/core/lightweight_test_trait.hpp>
#include <sstd/boost/histogram/axis/integer.hpp>
#include <sstd/boost/histogram/axis/variant.hpp>
#include <sstd/boost/histogram/detail/linearize.hpp>
#include <tuple>
#include <utility>
#include <vector>
#include "utility_meta.hpp"

using namespace boost::histogram;

int main() {
  {
    struct growing {
      auto update(int) { return std::make_pair(0, 0); }
    };
    using G = growing;
    using I = axis::integer<>;

    using A = std::tuple<I, G>;
    using B = std::vector<G>;
    using C = std::vector<axis::variant<I, G>>;
    using D = std::tuple<I>;
    using E = std::vector<I>;
    using F = std::vector<axis::variant<I>>;

    BOOST_TEST_TRAIT_TRUE((detail::has_growing_axis<A>));
    BOOST_TEST_TRAIT_TRUE((detail::has_growing_axis<B>));
    BOOST_TEST_TRAIT_TRUE((detail::has_growing_axis<C>));
    BOOST_TEST_TRAIT_FALSE((detail::has_growing_axis<D>));
    BOOST_TEST_TRAIT_FALSE((detail::has_growing_axis<E>));
    BOOST_TEST_TRAIT_FALSE((detail::has_growing_axis<F>));
  }
  return boost::report_errors();
}
