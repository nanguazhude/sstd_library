
// Copyright 2018 Peter Dimov.
// Distributed under the Boost Software License, Version 1.0.

#include <sstd/boost/config.hpp>

#if defined(SINGLE_INSTANCE_DYN_LINK)
# define EXPORT BOOST_SYMBOL_EXPORT
#else
# define EXPORT
#endif

#include <sstd/boost/system/error_code.hpp>
using namespace boost::system;

namespace lib1
{

EXPORT error_code get_system_code()
{
    return error_code( 0, system_category() );
}

EXPORT error_code get_generic_code()
{
    return error_code( 0, generic_category() );
}

} // namespace lib1
