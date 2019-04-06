#pragma once

namespace sstd {

    template< auto ...  >
    class constexpr_array;

    template< auto A0, auto ... Args >
    class constexpr_array<A0, Args...> {
        inline constexpr const static decltype(A0) thisData[]{
            A0,
            Args ...
        };
    public:
        inline constexpr static const auto * data() noexcept {
            return thisData;
        }
        inline constexpr static std::size_t size() noexcept {
            return sizeof...(Args) + 1;
        }
    };

    template<>
    class constexpr_array< > {
    public:
        inline constexpr static std::size_t size() noexcept {
            return 0;
        }
        inline constexpr static void * data() noexcept {
            return nullptr;
        }
    };

    template<typename T1>
    inline constexpr auto arrayData() noexcept {
        using T = std::remove_cv_t< std::remove_reference_t< T1 > >;
        return T::data();
    }

    template<typename T1>
    inline constexpr auto arraySize() noexcept {
        using T = std::remove_cv_t< std::remove_reference_t< T1 > >;
        return T::size();
    }

}/*namespace sstd*/



