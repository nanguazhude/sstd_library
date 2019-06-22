﻿#ifndef BOOST_SAFE_NUMERICS_TEST_MODULUS_AUTOMATIC_RESULTS_HPP
#define BOOST_SAFE_NUMERICS_TEST_MODULUS_AUTOMATIC_RESULTS_HPP

//  Copyright (c) 2019 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "test_values.hpp"

constexpr const char *test_modulus_automatic_result[
	boost::mp11::mp_size<test_values>::value
] = {
//      0       0       0       0
//      012345670123456701234567012345672
//      012345678901234567890123456789010
/* 0*/ "..............................xxx",
/* 1*/ "..............................xxx",
/* 2*/ "..............................xxx",
/* 3*/ "..............................xxx",
/* 4*/ "..............................xxx",
/* 5*/ "..............................xxx",
/* 6*/ "..............................xxx",
/* 7*/ "..............................xxx",

/* 8*/ "..............................xxx",
/* 9*/ "..............................xxx",
/*10*/ "..............................xxx",
/*11*/ "..............................xxx",
/*12*/ "..............................xxx",
/*13*/ "..............................xxx",
/*14*/ "..............................xxx",
/*15*/ "..............................xxx",

//      0       0       0       0
//      012345670123456701234567012345670
//      012345678901234567890123456789012
/*16*/ "................................x",
/*17*/ "................................x",
/*18*/ "................................x",
/*19*/ "................................x",
/*20*/ "................................x",
/*21*/ "................................x",
/*22*/ "................................x",
/*23*/ "................................x",

/*24*/ "................................x",
/*25*/ "................................x",
/*26*/ "................................x",
/*27*/ "................................x",
/*28*/ "................................x",
/*29*/ "................................x",
/*30*/ "xxxxxxxxxxxxxxxx................x",
/*31*/ "xxxxxxxxxxxxxxxx................x",
/*32*/ "..............................xxx"
};

#endif // BOOST_SAFE_NUMERICS_TEST_MODULUS_AUTOMATIC_RESULTS_HPP
