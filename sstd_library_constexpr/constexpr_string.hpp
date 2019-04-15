#pragma once

#include <string_view>

namespace sstd {

    /*只能由编译期常量 char[???] 构造*/
    class constexpr_string : public std::string_view {
        using super = std::string_view;
    public:
        inline constexpr constexpr_string() = default;
        inline constexpr constexpr_string(const constexpr_string &) = default ;
        inline constexpr constexpr_string(constexpr_string &&) = default ;
        inline constexpr constexpr_string&operator=(const constexpr_string &) = default ;
        inline constexpr constexpr_string&operator=(constexpr_string &&) = default ;
    public:
        template<typename T,std::size_t N>
        inline constexpr constexpr_string( T(&arg)[N] ) : super(arg,N-1) {
            static_assert (N>0);
        }
    };

}/*namespace sstd*/
