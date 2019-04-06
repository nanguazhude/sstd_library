
#include <sstd_library.hpp>

inline auto * data1() {
    return sstd::constexpr_array<1, 2, 3, 4>::data();
}

inline auto * data2() {
    return sstd::constexpr_array<1, 2, 3, 4>::data();
}

inline auto * data3() {
    return sstd_cstr("aabbccdd")::toStringView().data();
}

inline auto * data4() {
    return sstd_cstr("aabbccdd")::toStringView().data();
}

extern void constexpr_test() {

    assert(data1() == data2());
    assert(data3() == data4());
    static_assert (sstd::constexpr_array<1, 2, 3, 4>::size() == 4);
    std::cout << sstd_cstr("aabbccdd")::toConstexprStringView().size() << std::endl;

    assert(sstd_cstr(u8R"(今天)")::toStringView() == u8R"(今天)"sv);
    assert(sstd_cstr(u8R"(今天)")::toConstexprStringView() == u8R"(今天)"sv);
    assert(sstd_cstr(u8R"(今天)")::toConstexprStringView().data() == sstd_cstr(u8R"(今天)")::toStringView().data());

    assert(std::abs((1.0 / 3.141592654) -
        sstd::toFloat<std::ratio_divide<
        sstd::constexpr_float_one, sstd::constexpr_float_pi >>()) < 0.001);

    static_assert((sstd::toFloat< sstd::constexpr_float_pi >() - 3.141592654) < 0.001);
    static_assert((3.141592654 - sstd::toFloat< sstd::constexpr_float_pi >()) < 0.001);

}





