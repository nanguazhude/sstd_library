
#pragma once

#include <ratio>
#include <limits>

namespace sstd {

    template<intmax_t Num_,intmax_t Den_ = 1 >
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
                                       static_cast< CastType >(super::den) );
            }
        }
    };

    using constexpr_float_pi = constexpr_float< 31'415'926'535'897'932,10'000'000'000'000'000>;

}/*namespace sstd*/



