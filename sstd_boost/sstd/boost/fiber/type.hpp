
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_TYPE_H
#define BOOST_FIBERS_TYPE_H

#include <atomic>
#include <chrono>
#include <exception>
#include <functional>
#include <map>
#include <memory>
#include <type_traits>

#include <sstd/boost/assert.hpp>
#include <sstd/boost/config.hpp>
#include <sstd/boost/context/detail/apply.hpp>
#include <sstd/boost/context/stack_context.hpp>
#include <sstd/boost/intrusive/list.hpp>
#include <sstd/boost/intrusive/parent_from_member.hpp>
#include <sstd/boost/intrusive_ptr.hpp>
#include <sstd/boost/intrusive/set.hpp>

#include <sstd/boost/fiber/detail/config.hpp>
#include <sstd/boost/fiber/detail/data.hpp>
#include <sstd/boost/fiber/detail/decay_copy.hpp>
#include <sstd/boost/fiber/detail/fss.hpp>
#include <sstd/boost/fiber/detail/spinlock.hpp>
#include <sstd/boost/fiber/exceptions.hpp>
#include <sstd/boost/fiber/fixedsize_stack.hpp>
#include <sstd/boost/fiber/properties.hpp>
#include <sstd/boost/fiber/segmented_stack.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

enum class type {
    none               = 0,
    main_context       = 1 << 1,
    dispatcher_context = 1 << 2,
    worker_context     = 1 << 3,
    pinned_context     = main_context | dispatcher_context
};

inline
constexpr type
operator&( type l, type r) {
    return static_cast< type >(
            static_cast< unsigned int >( l) & static_cast< unsigned int >( r) );
}

inline
constexpr type
operator|( type l, type r) {
    return static_cast< type >(
            static_cast< unsigned int >( l) | static_cast< unsigned int >( r) );
}

inline
constexpr type
operator^( type l, type r) {
    return static_cast< type >(
            static_cast< unsigned int >( l) ^ static_cast< unsigned int >( r) );
}

inline
constexpr type
operator~( type l) {
    return static_cast< type >( ~static_cast< unsigned int >( l) );
}

inline
type &
operator&=( type & l, type r) {
    l = l & r;
    return l;
}

inline
type &
operator|=( type & l, type r) {
    l = l | r;
    return l;
}

inline
type &
operator^=( type & l, type r) {
    l = l ^ r;
    return l;
}

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_TYPE_H

