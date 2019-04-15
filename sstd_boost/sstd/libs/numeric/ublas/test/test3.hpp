//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef TEST3_H
#define TEST3_H

#include <iostream>

#include <sstd/boost/numeric/ublas/vector.hpp>
#include <sstd/boost/numeric/ublas/vector_proxy.hpp>
#include <sstd/boost/numeric/ublas/vector_sparse.hpp>
#include <sstd/boost/numeric/ublas/matrix.hpp>
#include <sstd/boost/numeric/ublas/matrix_proxy.hpp>
#include <sstd/boost/numeric/ublas/matrix_sparse.hpp>
#include <sstd/boost/numeric/ublas/vector_sparse.hpp>
#ifdef USE_GENERALIZED_VECTOR_OF_VECTOR
#include <sstd/boost/numeric/ublas/vector_of_vector.hpp>
#endif
#include <sstd/boost/numeric/ublas/io.hpp>

namespace ublas = boost::numeric::ublas;

#include "common/init.hpp"

void test_vector ();
void test_matrix_vector ();
void test_matrix ();

#endif
