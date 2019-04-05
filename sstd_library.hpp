#pragma once

namespace _theSSTDLibraryFile {
}/*namespace _theSSTDLibraryFile*/

#include <cmath>
#include <array>
#include <limits>
#include <memory>
#include <cassert>
#include <utility>
#include <cstddef>
#include <cstdlib>
#include <variant>
#include <optional>
#include <type_traits>

#include "global_sstd_library.hpp"
#include "sstd_library_memory/sstd_library_memory.hpp"
#include "sstd_library_exception/sstd_library_exception.hpp"
#include "sstd_library_filesystem/sstd_library_filesystem.hpp"
#include "sstd_library_constexpr/array_constexpr.hpp"
#include "sstd_library_tuple/sstd_library_tuple.hpp"

#include <sstd/boost/intrusive_ptr.hpp>

#include <string_view>
using namespace std::string_view_literals;

#include <chrono>
using namespace std::chrono_literals;

#include <fstream>
#include <sstream>
#include <iostream>

#include <mutex>
#include <thread>
#include <atomic>
#include <shared_mutex>

template<typename>
class sstd_friend_class;

namespace sstd {

    template<typename ...> using void_t = void;

}/*namespace sstd*/

#ifndef sstd_decltype
#define sstd_decltype(...) std::remove_cv_t< std::remove_reference_t< decltype( __VA_ARGS__ ) > > 
#endif

#ifndef sstd_friend
#define sstd_friend(...) template<typename> friend class ::sstd_friend_class; \
static_assert(true)/*__VA_ARGS__*/
#endif

#ifndef sstd_class
#define sstd_class(...) private:\
inline void _1_check_this_1_(){ \
    static_assert( std::is_same_v< sstd_decltype(*this) ,  __VA_ARGS__ > , \
    "the type is not *this type" );\
} \
sstd_friend(__VA_ARGS__) ; \
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
inline std::unique_ptr<T> sstd_make_unique(Args && ... args) {
    using T1 = std::remove_cv_t< std::remove_reference_t<T> >;
    static_assert(!std::is_array_v<T1>);
    T1 * varPointer = sstd_new<T1>(std::forward<Args>(args)...);
    return std::unique_ptr<T>{varPointer};
}

namespace _theSSTDLibraryFile {
    template<typename T>
    class sstd_virtual_not_final : public T {
        sstd_delete_copy_create(sstd_virtual_not_final);
    public:
        inline sstd_virtual_not_final() = default;
        inline virtual ~sstd_virtual_not_final() = default;
    public:
        template<typename A0, typename ... Args,
            typename = std::enable_if_t< isConstructible<T, A0&&, Args&&...>() >
        >inline sstd_virtual_not_final(A0&&a0, Args && ... args) :
            T(std::forward<A0>(a0), std::forward<Args>(args)...) {
        }
        template<typename A0, typename ... Args,
            typename = void ****,
            typename = std::enable_if_t< !isConstructible<T, A0&&, Args&&...>() >
        >inline sstd_virtual_not_final(A0&&a0, Args && ... args) :
            T{ std::forward<A0>(a0), std::forward<Args>(args)... } {
        }
    private:
        sstd_class(sstd_virtual_not_final);
    };
}/*namespace _theSSTDLibraryFile*/

template<typename T, typename ... Args>
inline T * sstd_virtual_new(Args && ... args) {
    static_assert(std::has_virtual_destructor_v<T>);
    static_assert(!std::is_final_v<T>);
    using T1 = std::remove_cv_t< std::remove_reference_t<T> >;
    return sstd_new< _theSSTDLibraryFile::sstd_virtual_not_final<T1> >(
        std::forward<Args>(args)...);
}

template<typename T, typename ... Args>
inline std::unique_ptr<T> sstd_make_virtual_unique(Args && ... args) {
    static_assert(std::has_virtual_destructor_v<T>);
    static_assert(!std::is_final_v<T>);
    using T1 = std::remove_cv_t< std::remove_reference_t<T> >;
    return sstd_make_unique< _theSSTDLibraryFile::sstd_virtual_not_final<T1> >(
        std::forward<Args>(args)...);
}

namespace _theSSTDLibraryFile {
    template<typename T>
    class sstd_shared_data {
        sstd_delete_copy_create(sstd_shared_data);
        T theData;
    public:
        inline T * getTheData() {
            assert(static_cast<const void *>(this) == static_cast<const void *>(&theData));
            return &theData;
        }
    public:
        inline sstd_shared_data() : theData{} {
        }
        inline ~sstd_shared_data() = default;
    public:
        template<typename A0, typename ... Args,
            typename = std::enable_if_t< isConstructible<T, A0&&, Args&&...>() >
        >inline sstd_shared_data(A0&&a0, Args && ... args) :
            theData(std::forward<A0>(a0), std::forward<Args>(args)...) {
        }
        template<typename A0, typename ... Args,
            typename = void ****,
            typename = std::enable_if_t< !isConstructible<T, A0&&, Args&&...>() >
        >inline sstd_shared_data(A0&&a0, Args && ... args) :
            theData{ std::forward<A0>(a0), std::forward<Args>(args)... } {
        }
    private:
        sstd_class(sstd_shared_data);
    };
}/*namespace _theSSTDLibraryFile*/

template<typename T, typename ... Args>
inline std::shared_ptr<T> sstd_make_shared(Args && ... args) {
    using T1 = std::remove_cv_t< std::remove_reference_t<T> >;
    static_assert(!std::is_array_v<T1>);
    sstd_allocator<T1> varAllocator;
    using T2 = _theSSTDLibraryFile::sstd_shared_data<T1>;
    T2 * varPointer = sstd_new<T2>(std::forward<Args>(args)...);
    return std::shared_ptr<T1>(
        varPointer->getTheData(),
        [](T1 * arg) { delete reinterpret_cast<T2*>(arg); },
        std::move(varAllocator));
}

#include "sstd_library_local_utf8/sstd_library_local_utf8.hpp"
#include "sstd_library_function/sstd_library_function.hpp"
#include "sstd_runtime_memory/sstd_runtime_memory.hpp"
#include "sstd_lua/sstd_lua.hpp"
#include "sstd_library_cached_dynamic_cast/sstd_library_cached_dynamic_cast.hpp"

