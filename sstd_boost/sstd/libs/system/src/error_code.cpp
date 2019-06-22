//  error_code stub implementation, for compatibility only

//  Copyright Beman Dawes 2002, 2006
//  Copyright Peter Dimov 2018

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/system

//----------------------------------------------------------------------------//

// define BOOST_SYSTEM_SOURCE so that <sstd/boost/system/config.hpp> knows
// the library is being built (possibly exporting rather than importing code)
#ifndef BOOST_SYSTEM_SOURCE
#define BOOST_SYSTEM_SOURCE
#endif

#include <sstd/boost/system/config.hpp>

namespace boost
{

namespace system
{

BOOST_SYSTEM_DECL void dummy_exported_function()
{
}

} // namespace system

} // namespace boost
