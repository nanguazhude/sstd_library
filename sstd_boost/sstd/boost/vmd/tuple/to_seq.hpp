
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_VMD_TUPLE_TO_SEQ_HPP)
#define BOOST_VMD_TUPLE_TO_SEQ_HPP

#include <sstd/boost/vmd/detail/setup.hpp>

#if BOOST_PP_VARIADICS

#include <sstd/boost/preprocessor/control/iif.hpp>
#include <sstd/boost/preprocessor/tuple/to_seq.hpp>
#include <sstd/boost/vmd/empty.hpp>
#include <sstd/boost/vmd/is_empty.hpp>

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def BOOST_VMD_TUPLE_TO_SEQ(tuple)

    \brief converts a tuple to a seq.

    tuple = tuple to be converted.

    If the tuple is an empty tuple it is converted to an empty seq.
    Otherwise the tuple is converted to a seq with the same number of elements as the tuple.
*/

#define BOOST_VMD_TUPLE_TO_SEQ(tuple) \
    BOOST_PP_IIF \
        ( \
        BOOST_VMD_IS_EMPTY(tuple), \
        BOOST_VMD_EMPTY, \
        BOOST_PP_TUPLE_TO_SEQ \
        ) \
    (tuple) \
/**/

#endif /* BOOST_PP_VARIADICS */
#endif /* BOOST_VMD_TUPLE_TO_SEQ_HPP */

