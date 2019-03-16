#pragma once

namespace _theSSTDLibraryFile {
}/*namespace _theSSTDLibraryFile*/

#include <cmath>
#include <limits>
#include <memory>
#include <utility>
#include <cstddef>
#include <cstdlib>
#include <variant>
#include <optional>
#include <type_traits>

#include "global_sstd_library.hpp"
#include "sstd_library_memory/sstd_library_memory.hpp"
#include "sstd_library_exception/sstd_library_exception.hpp"

#include <sstd/boost/intrusive_ptr.hpp>

#include <string_view>
using namespace std::string_view_literals;

#include <chrono>
using namespace std::chrono_literals;

template<typename>
class sstd_friend;

namespace sstd {

    template<typename ...> using void_t = void;

}/*namespace sstd*/

#ifndef sstd_friend
#define sstd_friend(...) template<typename> friend class ::sstd_friend_class; \
static_assert(true)/*__VA_ARGS__*/
#endif

#ifndef sstd_class
#define sstd_class(...) sstd_friend(__VA_ARGS__) ; \
_1_SSTD_MEMORY_1_DEFINE_1_ \
static_assert(true)/*__VA_ARGS__*/
#endif

namespace _theSSTDLibraryFile {
    template<typename T, typename ... Args>
    inline constexpr bool isConstructible() noexcept {
        if constexpr (std::is_constructible_v<T, Args &&... >) {
            return sizeof... (Args) > 0;
        }
        return false;
    }
}/*namespace _theSSTDLibraryFile*/

template<typename T, typename ... Args>
inline T * sstd_new(Args && ... args) {
    static_assert (!std::is_reference_v<T>);
    static_assert (!std::is_array_v<T>);
    if constexpr (_theSSTDLibraryFile::isConstructible<T, Args&&...>()) {
        return new T(std::forward<Args>(args)...);
    } else {
        return new T{ std::forward<Args>(args)... };
    }
}

template<typename T, typename ... Args>
inline std::shared_ptr<T> sstd_make_shared(Args && ... args) {
    using T1 = std::remove_cv_t< std::remove_reference_t<T> >;
    static_assert(!std::is_array_v<T1>);
    sstd_allocator<T1> varAllocator;
    T1 * varPointer = sstd_new<T1>(std::forward<Args>(args)...);
    return std::shared_ptr<T>(
        varPointer,
        std::default_delete<T1>{},
        std::move(varAllocator));
}

template<typename T, typename ... Args>
inline std::unique_ptr<T> sstd_make_unique(Args && ... args) {
    using T1 = std::remove_cv_t< std::remove_reference_t<T> >;
    static_assert(!std::is_array_v<T1>);
    T1 * varPointer = sstd_new<T1>(std::forward<Args>(args)...);
    return std::unique_ptr<T>{varPointer};
}











