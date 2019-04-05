#include <sstd_library.hpp>

class MTest {
};

extern void static_type_test(){

    auto varIndex =
        sstd::registerStaticClass< MTest, sstd_cstr("MTest") >();

    assert(varIndex);

    double a = 12;

    auto var =
         sstd::RegisterStaticClass<double>::convertFunction<int>();

    assert(var);

    auto intVar = var(&a );
    
    assert(intVar.first);
    assert(intVar.second);

    int * varValue = reinterpret_cast<int *>(intVar.first);

    assert( 12==*varValue );

    intVar.second(intVar.first);

}





