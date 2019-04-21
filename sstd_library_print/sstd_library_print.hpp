#pragma once

#include "../sstd_library.hpp"

namespace sstd {

    namespace _sstd_library_print_detail {

        template<typename T, typename = void, typename = void>
        class IsAppenedAbleDataSize : public std::false_type {
        };

        template<typename T >
        class IsAppenedAbleDataSize< T,
            std::void_t< decltype(std::declval<T>().data()) >,
            std::void_t< decltype(std::declval<T>().size()) > > : public std::true_type {
        };

        template<typename T, typename = void>
        class IsToStringAble : public std::false_type {
        };

        template<typename T>
        class IsToStringAble<T, std::void_t<decltype(
            sstd::toString(std::declval<const T &>()))>> : public std::true_type {
        };

        template<typename T, typename U, typename = void>
        class IsAppenedAble : public std::false_type {
        };

        template<typename T, typename U>
        class IsAppenedAble < T, U, std::void_t < decltype(
            std::declval<T>().append(std::declval<const U &>())) >> : public std::true_type{
        };

        template<typename, typename >
        class IsCharArray : public std::false_type {
        };

        template<typename C, typename T, std::size_t N>
        class IsCharArray <C, T[N] > : public std::true_type {
        public:
            static constexpr const std::size_t array_value = (N > 0) ? (N - 1) : 0;
            static constexpr const bool value = std::is_same_v<std::remove_cv_t<T>, C>;
        };

        template<typename T1>
        class Append {
        public:
            template<typename A, typename B>
            static inline void append(A & argAns, const B & argData) {
                using ValueType = std::remove_cv_t< std::remove_reference_t<B> >;
                using SizeType = sstd_decltype(argAns.size());
                using ElementType = sstd_decltype(*argAns.data());
                if constexpr (IsAppenedAbleDataSize<const ValueType &>::value) {
                    argAns.append(argData.data(), static_cast<SizeType>(argData.size()));
                } else if constexpr (std::is_same_v<ElementType, ValueType>) {
                    argAns.append(1, argData);
                } else if constexpr ((false == IsAppenedAble<A &, ValueType>::value) &&
                    IsToStringAble<ValueType>::value) {
                    auto varNumberString = sstd::toString(argData);
                    argAns.append(varNumberString.data(), static_cast<SizeType>(varNumberString.size()));
                } else {
                    using char_array_type = IsCharArray<ElementType, ValueType>;
                    if constexpr (char_array_type::value) {
                        argAns.append(argData, static_cast<SizeType>(char_array_type::array_value));
                    } else {
                        argAns.append(argData);
                    }
                }
            }
        };

        template<typename A, typename B>
        static inline auto getSize(const B & argData) {
            using ValueType = std::remove_cv_t< std::remove_reference_t<B> >;
            using SizeType = sstd_decltype(std::declval<A>().size());
            using ElementType = sstd_decltype(*(std::declval<A>().data()));
            if constexpr (IsAppenedAbleDataSize<ValueType>::value) {
                return static_cast<SizeType>(argData.size());
            } else if constexpr (std::is_same_v<ValueType, ElementType>) {
                return static_cast<SizeType>(1);
            } else {
                return static_cast<SizeType>(6);
            }
        }

    }/*_sstd_library_print_detail*/

    template<typename T = std::basic_string< char ,std::char_traits<char>,sstd::allocator<char> >, typename ...  Args>
    inline std::remove_reference_t<T> print(Args && ... args) {
        using AnsType = std::remove_cv_t< std::remove_reference_t<T> >;
        AnsType varAns;
        if constexpr (0 != sizeof...(args)) {
            {
                using SizeType = sstd_decltype(varAns.size());
                static_assert(std::is_integral_v<SizeType>);
                SizeType varSize{ 0 };
                (varSize += ... += _sstd_library_print_detail::getSize<AnsType>(args));
                varAns.reserve(varSize);
            }
            (_sstd_library_print_detail::Append<Args>::append(varAns, args), ...);
        }
        return std::move(varAns);

    }

}/*namespace sstd*/

/*

QByteArray
data();
size();
append(const char *,int);
append(int count, char )
reserve(int)

std::string
data();
size();
append(const char *,std::size_t);
append(std::size_t,char)
reserve(std::size_t)

*/




















