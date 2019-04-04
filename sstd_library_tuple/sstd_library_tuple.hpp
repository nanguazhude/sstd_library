#pragma once

#include <tuple>
#include <type_traits>

namespace sstd {

    template< std::size_t Index, typename T >
    class ArgReference {
        static_assert(std::is_reference_v<T>);
        T && thisData;
        inline T && getValueHelper() noexcept {
            return std::forward<T>(thisData);
        }
    public:
        inline constexpr static std::size_t getIndex() noexcept {
            return Index;
        }
        inline T && getValue() const noexcept {
            return const_cast<ArgReference *>(this)->getValueHelper();
        }
        ArgReference() = delete;
        inline ArgReference(const ArgReference&) = default;
        inline ArgReference(ArgReference&&) = default;
        inline ArgReference(T && arg) :thisData(std::forward<T>(arg)) {
        }
    };

}/*namespace sstd*/

namespace sstd::_detail_sstd_index_maker {

    template< typename Index, typename ... T  >
    class ArgReferenceMaker;

    template< std::size_t ... I, typename ... T  >
    class ArgReferenceMaker< std::integer_sequence<std::size_t, I...>, T ... > {
    public:
        using AnsType = std::tuple< ArgReference<I, T && > ... >;
        inline constexpr static AnsType forward_as_indexed_tuple(T && ... arg) noexcept {
            return { ArgReference<I,T&&>(std::forward<T>(arg)) ... };
        }
    };

}/*namespace namespace sstd::_detail_sstd_index_maker*/

namespace sstd {

    template< typename T0, typename ... T >
    inline constexpr auto forward_as_indexed_tuple(T0 && a0,T && ... arg) noexcept {
        return _detail_sstd_index_maker::ArgReferenceMaker<
            std::make_index_sequence<sizeof...(T)+1>, T0 &&, T && ... >
            ::forward_as_indexed_tuple(
                std::forward<T0>(a0),
                std::forward<T>(arg) ...);
    }

    inline constexpr std::tuple<> forward_as_indexed_tuple() noexcept {
        return{};
    }

}/*namespace sstd*/

