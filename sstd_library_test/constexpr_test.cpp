
#include <sstd_library.hpp>

auto * data1(){
    return sstd::constexpr_array<1,2,3,4>::data();
}

auto * data2(){
    return sstd::constexpr_array<1,2,3,4>::data();
}

extern void constexpr_test(){

    assert( data1() == data2() );
    static_assert ( sstd::constexpr_array<1,2,3,4>::size() == 4 );

}





