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

        template<typename T1>
        class Append {
            using T = std::remove_cv_t< std::remove_reference_t<T1> >;
        public:
            template<typename A, typename B>
            inline void append(A & argAns, const B & argData) {
                using ValueType = std::remove_cv_t< std::remove_reference_t<B> >;
                using SizeType = sstd_decltype(argAns.size());
                if constexpr (IsAppenedAbleDataSize<ValueType>::value) {
                    argAns.append(argData.data(), static_cast<SizeType>(argData.size()));
                } if constexpr (std::is_same_v<char, ValueType>) {
                    argAns.append(1, argData);
                } else {
                    auto varNumberString = sstd::toString(argData);
                    argAns.append(varNumberString.data(), static_cast<SizeType>(varNumberString.size()));
                }
            }
        };

    }/*_sstd_library_print_detail*/

    template<typename T = sstd::detail::utf8String, typename ...  Args>
    inline std::remove_cv_t< std::remove_reference_t<T> > print(Args && ... args) {
        std::remove_cv_t< std::remove_reference_t<T> > varAns;
        (_sstd_library_print_detail::Append<Args>(varAns, args), ...);
        return std::move(varAns);
    }

}/*namespace sstd*/

/*

QByteArray
data();
size();
append(const char *,int);
append(int count, char )

std::string
data();
size();
append(const char *,std::size_t);
append(std::size_t,char)

*/




















