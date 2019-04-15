// Copyright David Abrahams 2002.
// Copyright Stefan Seefeld 2016.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/python/module.hpp>
#include <sstd/boost/python/class.hpp>
#include <sstd/boost/python/call_method.hpp>
#include <sstd/boost/python/extract.hpp>
#include <sstd/boost/python/def.hpp>
#include <sstd/boost/shared_ptr.hpp>
#include <memory>

using boost::shared_ptr;
#define MODULE boost_shared_ptr_ext

#include "shared_ptr.hpp"
#include "module_tail.cpp"
