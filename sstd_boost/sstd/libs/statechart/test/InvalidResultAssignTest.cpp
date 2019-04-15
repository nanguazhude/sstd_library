//////////////////////////////////////////////////////////////////////////////
// Copyright 2005-2006 Andreas Huber Doenni
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <sstd/boost/statechart/state_machine.hpp>
#include <sstd/boost/statechart/event.hpp>
#include <sstd/boost/statechart/simple_state.hpp>
#include <sstd/boost/statechart/custom_reaction.hpp>
#include <sstd/boost/statechart/result.hpp>

#include <sstd/boost/static_assert.hpp>



namespace sc = boost::statechart;



struct E : sc::event< E > {};

struct A;
struct InvalidResultAssignTest :
  sc::state_machine< InvalidResultAssignTest, A > {};

struct A : sc::simple_state< A, InvalidResultAssignTest >
{
  typedef sc::custom_reaction< E > reactions;

  sc::result react( const E & )
  {
    sc::result r( discard_event() );
    // sc::result must not be assignmable
    r = discard_event();
    return r;
  }
};



int main()
{
  InvalidResultAssignTest machine;
  machine.initiate();

  #ifdef NDEBUG
    // Test only fails in DEBUG mode. Forcing failure...
    BOOST_STATIC_ASSERT( false );
  #endif

  return 0;
}
