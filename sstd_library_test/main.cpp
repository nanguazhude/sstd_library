
#include <sstd_library.hpp>

#include <iostream>
#include <sstd/boost/context/fiber.hpp>
#include <sstd_botan.hpp>

#include <cassert>

#include <string>
using namespace std::string_literals;

class AClass {
private:
    sstd_class(AClass);
public:
    virtual ~AClass() = default;
    AClass() = default;
public:
    sstd_delete_copy_create(AClass);
};

class BClass : public AClass {
    sstd_class(BClass);
};

inline void testException(std::exception_ptr,
    std::string_view/*func*/,
    std::string_view/*file*/,
    int/*line*/) noexcept {
    std::cout << "exception ok" << std::endl;
}

inline void botan_test() {
    {
        /*  https://botan.randombit.net/manual/hash.html  */
        constexpr auto varTestAlg = "MD5"sv;
        constexpr auto varTestData = "aabbcc"sv;
        auto varHashFunction =
            Botan::HashFunction::create({ varTestAlg.data(),varTestAlg.size() });
        varHashFunction->update((const uint8_t*)varTestData.data(), varTestData.size());
        std::cout
            << varTestAlg
            << "::"sv
            << Botan::hex_encode(varHashFunction->final())
            << std::endl;
    }
}

void lua_test() {
    auto L = ::luaL_newstate();

    ::lua_pushstring(L, "AABBC");
    auto varSize = ::lua_gettop(L);

    {/*测试构造析构函数*/
        sstd::LuaObjectCplusplusRef varRef{ L,-1 };
    }
    assert(::lua_gettop(L) == varSize);

    {/*测试构造析构函数*/
        sstd::LuaObjectCplusplusRef varRef{ L,-1 };
    }
    assert(::lua_gettop(L) == varSize);

    {/*测试获得值*/
        sstd::LuaObjectCplusplusRef varRef{ L,-1 };
        varRef.push();
        assert(::lua_gettop(L) == (varSize + 1));
        assert(::lua_tostring(L, -1) == "AABBC"sv);
        ::lua_pop(L, 1);
    }
    assert(::lua_gettop(L) == varSize);

    {/*测试拷贝*/
        sstd::LuaObjectCplusplusRef varRef1{ L,-1 };
        sstd::LuaObjectCplusplusRef varRef2{ L,-1 };
        varRef2 = std::move(varRef1);
        assert(::lua_gettop(L) == varSize);
        varRef2.push();
        assert(::lua_gettop(L) == (varSize + 1));
        assert(::lua_tostring(L, -1) == "AABBC"sv);
        ::lua_pop(L, 1);
    }
    assert(::lua_gettop(L) == varSize);

    {/*测试默认构造*/
        sstd::LuaObjectCplusplusRef varRef1;
        varRef1 = sstd::LuaObjectCplusplusRef{ L,-1 };
        assert(::lua_gettop(L) == varSize);
        varRef1.push();
        assert(::lua_gettop(L) == (varSize + 1));
        assert(::lua_tostring(L, -1) == "AABBC"sv);
        ::lua_pop(L, 1);
    }
    assert(::lua_gettop(L) == varSize);

    ::lua_close(L);
}

#include "lua_full_test.hpp"

int main(int, char **) {

    {
        class A {
        public:
            virtual ~A() {
            }
        };

        class B {
        public:
            virtual ~B() {
            }
        };

        class C {
        public:
            virtual ~C() {
            }
        };

        class D : public virtual B, public C, public A {
        };

        D * d = new D;
        A * a = d;
        B * b = d;
        C * c = d;

        assert(reinterpret_cast<void *>(a) != reinterpret_cast<void *>(d));

        assert(d == sstd_cached_dynamic_cast<D>(a));
        assert(a == sstd_cached_dynamic_cast<A>(a));
        assert(b == sstd_cached_dynamic_cast<B>(a));
        assert(c == sstd_cached_dynamic_cast<C>(a));

        assert(d == sstd_cached_dynamic_cast<D>(a));
        assert(a == sstd_cached_dynamic_cast<A>(a));
        assert(b == sstd_cached_dynamic_cast<B>(a));
        assert(c == sstd_cached_dynamic_cast<C>(a));

    }

    {
        lua_test();
        luaFullTest();
    }return 0;

    {
        using fiber = boost::context::fiber;
        fiber var([](fiber &&f) {
            std::cout << "Hellow World!" << std::endl;
            {
                auto varUniqueTest = sstd_make_unique<BClass>();
            }
            {
                auto varSharedTest = sstd_make_shared<BClass>();
            }
            return std::move(f);
        });
        var = std::move(var).resume();
    }

    {
        sstd_try{
            sstd_throw(123);
        } sstd_catch(...) {
            sstd_on_exception();
        }
    }

    {
        auto varOldException = sstd::getExceptionFunction();
        auto varOldNew = sstd::setExceptionFunction(&testException);
        assert(varOldException == varOldNew);
        assert(sstd::getExceptionFunction() == &testException);
        (void)varOldException;
        (void)varOldNew;
    }

    {
        sstd_try{
            sstd_throw(123);
        } sstd_catch(...) {
            sstd_on_exception();
        }
    }

    {
        std::vector< int, sstd_allocator<int> > test;
        test.push_back(1);
        test.push_back(3);
    }

    {
        auto var = sstd_make_virtual_unique<const BClass>();
    }

    {
        auto var = sstd_make_shared< const std::array<int, 3> >(1, 2, 3);
    }

    {
        botan_test();
    }

    return 0;

}




