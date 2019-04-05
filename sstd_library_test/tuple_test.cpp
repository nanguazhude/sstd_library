
#include <sstd_library.hpp>
#include <iostream>
#include <string_view>

extern void tuple_test(){

    std::apply([]( const auto & ... args ){

        auto fun = [](const auto & arg){
            if constexpr( sstd_decltype(arg)::index() & 1 ){
                std::cout << arg.index() << " , "sv << arg.value() << std::endl;
            }else{
                std::cout << arg.index() << " , "sv << -arg.value()  << std::endl;
            }
        };

        ( fun(args), ... );
    },
    sstd::forward_as_indexed_tuple(1,2,3,4));

}




