// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HANA_EXAMPLE_CPPCON_2014_MATRIX_DET_HPP
#define BOOST_HANA_EXAMPLE_CPPCON_2014_MATRIX_DET_HPP

#include <sstd/boost/hana/equal.hpp>
#include <sstd/boost/hana/eval_if.hpp>
#include <sstd/boost/hana/front.hpp>
#include <sstd/boost/hana/functional/always.hpp>
#include <sstd/boost/hana/functional/fix.hpp>
#include <sstd/boost/hana/functional/flip.hpp>
#include <sstd/boost/hana/functional/on.hpp>
#include <sstd/boost/hana/functional/partial.hpp>
#include <sstd/boost/hana/integral_constant.hpp>
#include <sstd/boost/hana/plus.hpp>
#include <sstd/boost/hana/power.hpp>
#include <sstd/boost/hana/range.hpp>
#include <sstd/boost/hana/remove_at.hpp>
#include <sstd/boost/hana/transform.hpp>
#include <sstd/boost/hana/tuple.hpp>
#include <sstd/boost/hana/unpack.hpp>

#include <utility>

#include "matrix.hpp"


namespace cppcon {
    namespace hana = boost::hana;
    auto det = hana::fix([](auto det, auto&& m) -> decltype(auto) {
        auto matrix_minor = [=](auto&& m, auto i, auto j) -> decltype(auto) {
            return det(hana::unpack(
                hana::transform(
                    hana::remove_at(rows(std::forward<decltype(m)>(m)), i),
                    hana::partial(hana::flip(hana::remove_at), j)
                ),
                matrix
            ));
        };

        auto cofactor = [=](auto&& m, auto i, auto j) {
            return hana::power(hana::int_c<-1>, hana::plus(i, j)) *
                    matrix_minor(std::forward<decltype(m)>(m), i, j);
        };

        return hana::eval_if(m.size() == hana::size_c<1>,
            hana::always(m.at(hana::size_c<0>, hana::size_c<0>)),
            [=](auto _) {
                auto cofactors_1st_row = hana::unpack(_(hana::make_range)(hana::size_c<0>, m.ncolumns()),
                    hana::on(hana::make_tuple, hana::partial(cofactor, m, hana::size_c<0>))
                );
                return detail::tuple_scalar_product(hana::front(rows(m)), cofactors_1st_row);
            }
        );
    });
} // end namespace cppcon

#endif // !BOOST_HANA_EXAMPLE_CPPCON_2014_MATRIX_DET_HPP
