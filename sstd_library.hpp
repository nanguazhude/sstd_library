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
static_assert(true)/*__VA_ARGS__*/
#endif

namespace _theSSTDLibraryFile {
    template<typename T,typename ... Args>
    inline constexpr bool isConstructible() noexcept {
        if constexpr( std::is_constructible_v<T,Args &&... > ){
            return sizeof... (Args)>0;
        }
        return false;
    }
}/*namespace _theSSTDLibraryFile*/

template<typename T,typename ... Args>
inline T * sstd_new(Args && ... args){
    static_assert ( !std::is_reference_v<T> );
    static_assert ( !std::is_array_v<T> );
    if constexpr( _theSSTDLibraryFile::isConstructible<T,Args&&...>() ){
        return new T( std::forward<Args>(args)... );
    }else{
        return new T{ std::forward<Args>(args)... };
    }
}
















