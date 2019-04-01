/*
  A variadic implementation of variadic boost::signals2::signal, used when variadic
  template support is detected in the compiler.

  Author: Frank Mori Hess <fmhess@users.sourceforge.net>
  Begin: 2009-05-26
*/
// Copyright Frank Mori Hess 2009
// Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_SIGNALS2_VARIADIC_SIGNAL_HPP
#define BOOST_SIGNALS2_VARIADIC_SIGNAL_HPP

#include <sstd/boost/preprocessor/control/expr_if.hpp>
#include <sstd/boost/signals2/detail/variadic_arg_type.hpp>
#include <sstd/boost/signals2/detail/variadic_slot_invoker.hpp>
#include <sstd/boost/type_traits/function_traits.hpp>
#include <sstd/boost/type_traits/is_void.hpp>
#include <sstd/boost/utility/enable_if.hpp>

namespace boost
{
  namespace signals2
  {
    namespace detail
    {
      template<typename Signature> class variadic_extended_signature;
      // partial template specialization
      template<typename R, typename ... Args>
        class variadic_extended_signature<R (Args...)>
      {
      public:
        typedef boost::function<R (const boost::signals2::connection &, Args...)> function_type;
      };
    } // namespace detail
  } // namespace signals2
} // namespace boost

#include <sstd/boost/signals2/detail/signal_template.hpp>

#endif // BOOST_SIGNALS2_VARIADIC_SIGNAL_HPP

