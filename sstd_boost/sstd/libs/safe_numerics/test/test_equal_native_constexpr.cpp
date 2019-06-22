﻿//  Copyright (c) 2019 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/safe_numerics/safe_integer.hpp>
#include <sstd/boost/safe_numerics/native.hpp>
#include "test_compare_native.hpp"

template <class T>
using safe_t = boost::safe_numerics::safe<
    T,
    boost::safe_numerics::native
>;

#include "test_equal_constexpr.hpp"

using namespace boost::mp11;

template<typename First, typename Second>
struct test_pair {
    static const std::size_t i = First();
    static const std::size_t j = Second();
    constexpr static const bool value = test_equal_constexpr(
        mp_at_c<test_values, i>()(),
        mp_at_c<test_values, j>()(),
        test_compare_native_result[i][j]
    );
};

#include <sstd/boost/mp11/list.hpp>
#include <sstd/boost/mp11/algorithm.hpp>

int main(){
    using namespace boost::mp11;

    using value_indices = mp_iota_c<mp_size<test_values>::value>;

    static_assert(
        mp_all_of<
            mp_product<
                test_pair,
                value_indices,
                value_indices
            >,
            mp_to_bool
        >(),
        "all values for all integer types correctly compared for equality"
    );
    return 0;
}
