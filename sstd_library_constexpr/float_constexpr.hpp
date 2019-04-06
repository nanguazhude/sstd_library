
#pragma once

#include <ratio>
#include <limits>

namespace sstd {

    namespace detail{
        template<intmax_t Num_,intmax_t Den_ >
        class constexpr_float : public std::ratio<Num_,Den_> {
            using super = std::ratio<Num_,Den_>;
        public:
            template<typename T1 = double >
            static inline constexpr auto toFloat() noexcept {
                using T = std::remove_cv_t< std::remove_reference_t< T1 > >;
                if constexpr ( super::den == 1  ){
                    return static_cast< T >(super::num);
                } else if constexpr( super::den == 0 ){
                    return std::numeric_limits< T >::quiet_NaN() ;
                } else {
                    using CastType = long double;
                    return static_cast<T>( static_cast< CastType >( super::num ) /
                                           static_cast< CastType >( super::den) );
                }
            }
        };
    }

    template<intmax_t Num_,intmax_t Den_=1>
    using constexpr_float=detail::constexpr_float<std::ratio<Num_,Den_>::num,std::ratio<Num_,Den_>::den>;

    using constexpr_float_pi = constexpr_float< 31'415'926'535'897'932,
                                                10'000'000'000'000'000>;

    using constexpr_float_exp = constexpr_float< 27'182'818'284'590'452,
                                                 10'000'000'000'000'000>;

}/*namespace sstd*/



