//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <sstd/boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED("<sstd/boost/config/workaround.hpp>")

#define ALTERNATIVE "the suitable component header"
BOOST_HEADER_DEPRECATED(ALTERNATIVE)

#include <sstd/boost/config.hpp> // BOOST_STRINGIZE

#define HEADER <sstd/boost/config/workaround.hpp>
BOOST_HEADER_DEPRECATED(BOOST_STRINGIZE(HEADER))

