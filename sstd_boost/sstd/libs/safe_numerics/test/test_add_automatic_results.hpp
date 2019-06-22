﻿#ifndef BOOST_SAFE_NUMERICS_TEST_ADD_AUTOMATIC_RESULTS_HPP
#define BOOST_SAFE_NUMERICS_TEST_ADD_AUTOMATIC_RESULTS_HPP

//  Copyright (c) 2019 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "test_values.hpp"

constexpr const char *test_addition_automatic_result[
    boost::mp11::mp_size<test_values>::value
] = {
//      0       0       0       0
//      012345670123456701234567012345670
//      012345678901234567890123456789012
/* 0*/ ".............x...............xxx.",
/* 1*/ ".............x...............xxx.",
/* 2*/ "..............x...............xx.",
/* 3*/ "..............x...............xx.",
/* 4*/ ".............x...............xxx.",
/* 5*/ ".............x...............xxx.",
/* 6*/ "..............x...............xx.",
/* 7*/ "..............x...............xx.",

/* 8*/ ".............x...............xxx.",
/* 9*/ ".............x...............xxx.",
/*10*/ "..............x...............xx.",
/*11*/ "..............x...............xx.",
/*12*/ ".............x...............xxx.",
/*13*/ "xx..xx..xx..xx..xxxxxxxxxxxxxxxx.",
/*14*/ "..xx..xx..xx..xx..............xx.",
/*15*/ "..............x...............xx.",

//      0       0       0       0
//      012345670123456701234567012345670
//      012345678901234567890123456789012
/*16*/ ".............x.................x.",
/*17*/ ".............x.................x.",
/*18*/ ".............x.................x.",
/*19*/ ".............x.................x.",
/*20*/ ".............x.................x.",
/*21*/ ".............x.................x.",
/*22*/ ".............x.................x.",
/*23*/ ".............x.................x.",

/*24*/ ".............x.................x.",
/*25*/ ".............x.................x.",
/*26*/ ".............x.................x.",
/*27*/ ".............x.................x.",
/*28*/ ".............x.................x.",
/*29*/ "xx..xx..xx..xx.................x.",
/*30*/ "xxxxxxxxxxxxxxxx..............xxx",
/*31*/ "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
/*32*/ "..............................xx."
};

#endif
