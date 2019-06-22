﻿#ifndef BOOST_SAFE_NUMERICS_TEST_MODULUS_NATIVE_RESULTS_HPP
#define BOOST_SAFE_NUMERICS_TEST_MODULUS_NATIVE_RESULTS_HPP

//  Copyright (c) 2019 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "test_values.hpp"

constexpr const char *test_modulus_native_result[
    boost::mp11::mp_size<test_values>::value
] = {
//      0       0       0       0
//      012345670123456701234567012345672
//      012345678901234567890123456789010
/* 0*/ "................................x",
/* 1*/ "................................x",
/* 2*/ "........................xxxxxxxxx",
/* 3*/ "........................xxxxxxxxx",
/* 4*/ "................................x",
/* 5*/ "................................x",
/* 6*/ "........................xxxxxxxxx",
/* 7*/ "........................xxxxxxxxx",

/* 8*/ "................................x",
/* 9*/ "................................x",
/*10*/ "........................xxxxxxxxx",
/*11*/ "........................xxxxxxxxx",
/*12*/ "................................x",
/*13*/ "................................x",
/*14*/ "............................xxxxx",
/*15*/ "............................xxxxx",

//      0       0       0       0
//      012345670123456701234567012345672
//      012345678901234567890123456789010
/*16*/ "................................x",
/*17*/ "................................x",
/*18*/ "................................x",
/*19*/ "................................x",
/*20*/ "................................x",
/*21*/ "................................x",
/*22*/ "................................x",
/*23*/ "................................x",

/*24*/ "..xx..xx..xx....................x",
/*25*/ "..xx..xx..xx....................x",
/*26*/ "..xx..xx..xx....................x",
/*27*/ "..xx..xx..xx....................x",
/*28*/ "..xx..xx..xx..xx................x",
/*29*/ "..xx..xx..xx..xx................x",
/*30*/ "..xx..xx..xx..xx................x",
/*31*/ "..xx..xx..xx..xx................x",
/*32*/ "................................x"
};

#endif  // BOOST_SAFE_NUMERICS_TEST_MODULUS_NATIVE_RESULTS_HPP
