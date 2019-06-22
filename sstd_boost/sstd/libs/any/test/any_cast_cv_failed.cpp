﻿// Copyright 2006 Alexander Nasonov.
// Copyright Antony Polukhin, 2013-2019.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/any.hpp>

int main() {
    boost::any const a;
    boost::any_cast<int&>(a);
}
