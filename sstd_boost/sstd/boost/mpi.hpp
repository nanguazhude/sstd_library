// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface

//  See www.boost.org/libs/mpi for documentation.

/** @file mpi.hpp
 *
 *  This file is a top-level convenience header that includes all of
 *  the Boost.MPI library headers. Users concerned about compile time
 *  may wish to include only specific headers from the Boost.MPI
 *  library.
 *
 */
#ifndef BOOST_MPI_HPP
#define BOOST_MPI_HPP

#include <sstd/boost/mpi/allocator.hpp>
#include <sstd/boost/mpi/collectives.hpp>
#include <sstd/boost/mpi/communicator.hpp>
#include <sstd/boost/mpi/datatype.hpp>
#include <sstd/boost/mpi/environment.hpp>
#include <sstd/boost/mpi/graph_communicator.hpp>
#include <sstd/boost/mpi/group.hpp>
#include <sstd/boost/mpi/intercommunicator.hpp>
#include <sstd/boost/mpi/nonblocking.hpp>
#include <sstd/boost/mpi/operations.hpp>
#include <sstd/boost/mpi/skeleton_and_content.hpp>
#include <sstd/boost/mpi/timer.hpp>

#endif // BOOST_MPI_HPP

