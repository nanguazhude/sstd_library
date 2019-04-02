#pragma once

#include "../global_sstd_library.hpp"

#include <limits>
#include <typeinfo>
#include <typeindex>


namespace sstd {

    constexpr auto virtual_cast_not_find_pos =
        (std::numeric_limits< std::ptrdiff_t >::max)();
    constexpr auto virtual_cast_can_not_cast =
        (std::numeric_limits< std::ptrdiff_t >::min)();
    static_assert(virtual_cast_not_find_pos != virtual_cast_can_not_cast);

    namespace detail {
        SSTD_SYMBOL_DECL void * runtimeDynamicCast(const void *,const std::type_index &,const std::type_index &);
        SSTD_SYMBOL_DECL std::ptrdiff_t findCachedVirtualPointerDistance(const std::type_index&, const std::type_index &);
        SSTD_SYMBOL_DECL void registerCachedVirtualPointerDistance(const std::type_index&, const std::type_index &, std::ptrdiff_t);
    }

}/*namespace sstd*/

template<typename To, typename From>
inline To * sstd_cached_dynamic_cast(From * arg) {

    namespace detail = sstd::detail;

    using RawFrom =
        std::remove_cv_t< std::remove_reference_t< From > >;
    using RawTo =
        std::remove_cv_t< std::remove_reference_t< To > >;

    if constexpr (std::is_same_v<RawFrom, RawTo>) {
        return const_cast<RawFrom *>(arg);
    } else {

        if (arg == nullptr) {
            return nullptr;
        }

        static_assert(std::has_virtual_destructor_v<RawFrom>);
        const std::type_index varFromIndex{ typeid(*const_cast<RawFrom *>(arg)) };
        const static std::type_index varToIndex{ typeid(RawTo) };

        if (varFromIndex == varToIndex) {
            return reinterpret_cast<RawTo*>(
                dynamic_cast<void *>(const_cast<RawFrom *>(arg)));
        }

        auto varValue = detail::findCachedVirtualPointerDistance(varFromIndex, varToIndex);
        if (varValue == sstd::virtual_cast_not_find_pos) {
            auto varAns = dynamic_cast<RawTo *>(const_cast<RawFrom *>(arg));
            if (varAns == nullptr) {
                detail::registerCachedVirtualPointerDistance(varFromIndex, varToIndex, sstd::virtual_cast_can_not_cast);
                return nullptr;
            }
            auto varDiff = reinterpret_cast<char *>(varAns) -
                reinterpret_cast<char *>(dynamic_cast<void *>(const_cast<RawFrom *>(arg)));
            detail::registerCachedVirtualPointerDistance(varFromIndex, varToIndex, varDiff);
            return varAns;
        } else if (varValue == sstd::virtual_cast_can_not_cast) {
            return nullptr;
        }

        return reinterpret_cast<RawTo *>(
            reinterpret_cast<char *>(
                dynamic_cast<void *>(const_cast<RawFrom *>(arg))) + varValue);
    }

}






