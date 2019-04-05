#pragma once

#include <variant>
#include <typeinfo>
#include <typeindex>
#include <type_traits>

namespace sstd {

    /*
        std::size_t : 静态类
        std::type_index : 虚函数类
    */
    using type_index = std::variant< std::size_t , std::type_index >;

}/*namespace sstd*/

namespace std {

    template<>
    class hash< sstd::type_index >{
    public:
        inline std::size_t operator()(const sstd::type_index & arg) const noexcept {
            if( arg.index() == 0 ){
                return std::get<0>(arg)              ;
            }else{
                return std::get<1>(arg).hash_code()  ;
            }
        }
    };

}/*namespace std*/



