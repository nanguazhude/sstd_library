#include <cassert>
#include <sstd_library_double_conversion/sstd_library_double_conversion.hpp>


extern void test_number_convert() {

    assert(1 == sstd::detail::toDouble("1"));
    assert(1 == sstd::detail::toDouble("1.0"));
    assert(1 == sstd::detail::toDouble(" 1.0"));
    assert(1 == sstd::detail::toDouble(" 1.0 "));
    assert((-1) == sstd::detail::toDouble("-1"));

    assert(sstd::detail::fromStringDouble(1) == "1"sv);
    assert(sstd::detail::fromStringFloat(1) == "1"sv);

}











