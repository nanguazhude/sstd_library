
#include <sstd_library.hpp>

auto * data1(){
    return sstd::constexpr_array<1,2,3,4>::data();
}

auto * data2(){
    return sstd::constexpr_array<1,2,3,4>::data();
}

auto * data3(){
    return sstd_cstr("aabbccdd")::toStringView().data();
}

auto * data4(){
    return sstd_cstr("aabbccdd")::toStringView().data();
}

extern void constexpr_test(){

    assert( data1() == data2() );
    assert( data3() == data4() );
    static_assert ( sstd::constexpr_array<1,2,3,4>::size() == 4 );

}





