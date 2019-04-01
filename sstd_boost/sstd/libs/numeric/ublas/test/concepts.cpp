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

#include <sstd/boost/numeric/ublas/vector.hpp>
#include <sstd/boost/numeric/ublas/vector_proxy.hpp>
#include <sstd/boost/numeric/ublas/vector_sparse.hpp>
#include <sstd/boost/numeric/ublas/matrix.hpp>
#include <sstd/boost/numeric/ublas/matrix_proxy.hpp>
#include <sstd/boost/numeric/ublas/banded.hpp>
#include <sstd/boost/numeric/ublas/triangular.hpp>
#include <sstd/boost/numeric/ublas/symmetric.hpp>
#include <sstd/boost/numeric/ublas/hermitian.hpp>
#include <sstd/boost/numeric/ublas/matrix_sparse.hpp>
#include <sstd/boost/numeric/ublas/vector_of_vector.hpp>
#include <sstd/boost/numeric/ublas/detail/concepts.hpp>
#include <sstd/boost/numeric/ublas/experimental/sparse_view.hpp>
//#include <sstd/boost/numeric/ublas/vector_view.hpp>

namespace ublas = boost::numeric::ublas;


int main () {
    void (* check) (void) = ublas::concept_checks;
    boost::ignore_unused_variable_warning (check);
}

