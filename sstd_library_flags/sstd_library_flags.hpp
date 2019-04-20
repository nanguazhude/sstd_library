#pragma once

#include <array>
#include <limits>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>
#include "../sstd_library.hpp"

namespace sstd {

    namespace _detail_sstd_quick_flags {

        template<std::size_t N>
        class Integer;

        template<>
        class Integer<8> {
        public:
            using type = std::uint8_t;
        };

        template<>
        class Integer<16> {
        public:
            using type = std::uint16_t;
        };

        template<>
        class Integer<32> {
        public:
            using type = std::uint32_t;
        };

        template<>
        class Integer<64> {
        public:
            using type = std::uint64_t;
        };

        template<std::size_t N>
        class Integer {
            static_assert(N <= 64);
        public:
            using type = std::conditional_t< N <= 8,
                typename Integer<8>::type,
                std::conditional_t<  N <= 16,
                typename Integer<16>::type,
                std::conditional_t< N <= 32,
                typename Integer<32>::type,
                std::conditional_t< N <= 64,
                typename Integer<64>::type,
                void>>>>;
        };

        template<std::size_t N, typename T, typename U>
        class _Array;

        template<std::size_t N,
            typename Integer<N>::type ... V>
            class _Array< N,
            typename Integer<N>::type,
            std::integer_sequence<typename Integer<N>::type, V...> > {
            public:
                constexpr const static std::array<typename Integer<N>::type, sizeof...(V)> valueArray1{
                    (((typename Integer<N>::type)1) << V)...,
                };
                constexpr const static std::array<typename Integer<N>::type, sizeof...(V)> valueArray2{
                    (typename Integer<N>::type)(~(((typename Integer<N>::type)1) << V))...,
                };
        };

        template<std::size_t N>
        using Array = _Array< sizeof(typename Integer<N>::type) * 8,
            typename Integer<N>::type,
            std::make_integer_sequence<typename Integer<N>::type,
            sizeof(typename Integer<N>::type) * 8> >;

        template< std::size_t N >
        class _QuickFlags {
            using _value_t = typename Integer<N>::type;
            _value_t thisData{ 0 };
            inline constexpr static _value_t _getMax() {
                return std::numeric_limits<_value_t>::max();
            }
        public:
            inline constexpr _QuickFlags() {
            }
            inline constexpr void clearAll() {
                thisData = 0;
            }
            inline constexpr void setAll() {
                thisData = _getMax();
            }
            template<auto I>
            inline constexpr void set() {
                static_assert(static_cast<std::size_t>(I) < N);
                thisData |= (1 << static_cast<_value_t>(I));
            }
            template<auto I>
            inline constexpr void clear() {
                static_assert(static_cast<std::size_t>(I) < N);
                thisData &= (~(1 << static_cast<_value_t>(I)));
            }
            template<auto I>
            inline constexpr bool test() const {
                static_assert(static_cast<std::size_t>(I) < N);
                return thisData & (1 << static_cast<_value_t>(I));
            }
            template<typename I>
            inline constexpr void set(const I & argIndex) {
                assert(static_cast<std::size_t>(argIndex) < N);
                thisData |= _values1()[static_cast<std::size_t>(argIndex)];
            }
            template<typename I>
            inline constexpr void clear(const I & argIndex) {
                assert(static_cast<std::size_t>(argIndex) < N);
                thisData &= _values2()[static_cast<std::size_t>(argIndex)];
            }
            template<typename I>
            inline constexpr bool test(const I & argIndex) const {
                assert(static_cast<std::size_t>(argIndex) < N);
                return thisData & _values1()[static_cast<std::size_t>(argIndex)];
            }
        private:
            inline static constexpr const auto & _values1() {
                return Array<N>::valueArray1;
            }
            inline static constexpr const auto & _values2() {
                return Array<N>::valueArray2;
            }
        private:
            sstd_class(_QuickFlags);
        };

    }/*namespace _detail_sstd_quick_flags*/

    template< auto N >
    using QuickFlags = _detail_sstd_quick_flags::_QuickFlags< static_cast<std::size_t>(N) >;

}/*namespace sstd*/
