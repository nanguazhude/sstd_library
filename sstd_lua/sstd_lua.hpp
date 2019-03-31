#pragma once

#include "sstd_lua_exception.hpp"
#include "source/lua.hpp"
#include "../sstd_library.hpp"

namespace _theSSTDLuaFile {
}/*namespace _theSSTDLuaFile*/

namespace sstd {

    class SSTD_SYMBOL_DECL LuaObjectCplusplusRef final {
        lua_State* thisData;
    public:
        LuaObjectCplusplusRef(LuaObjectCplusplusRef &&);
        LuaObjectCplusplusRef(const LuaObjectCplusplusRef &);
        LuaObjectCplusplusRef&operator=(const LuaObjectCplusplusRef &);
        LuaObjectCplusplusRef&operator=(LuaObjectCplusplusRef &&);
    public:
        ~LuaObjectCplusplusRef();
    public:
        LuaObjectCplusplusRef(lua_State*, int);
        LuaObjectCplusplusRef();
    public:
        lua_State* push() const;
    public:
        template<typename T>
        inline T * getFirstUserDataPointer() const;
    public:
        inline lua_State* get() const;
    public:
        inline operator bool() const;
    public:
        sstd_class(LuaObjectCplusplusRef);
    };

    inline lua_State* LuaObjectCplusplusRef::get() const {
        return thisData;
    }

    inline LuaObjectCplusplusRef::operator bool() const {
        return thisData;
    }

    template<typename T1>
    inline T1 * LuaObjectCplusplusRef::getFirstUserDataPointer() const {

        using T = std::remove_cv_t< std::remove_reference_t< T1 > >;

        class FirstData {
        public:
            T * ans;
        };

        if (!thisData) {
            return nullptr;
        }

        auto varTop = ::lua_gettop(thisData);
        this->push();
        auto varPos = ::lua_gettop(thisData);
        assert(::lua_type(thisData, varPos) == LUA_TUSERDATA);
        auto varAns = reinterpret_cast<FirstData *>(
            ::lua_touserdata(thisData, varPos))->ans;

        class ReturnLock {
            lua_State* L;
            int top;
        public:
            inline ReturnLock(lua_State* a, int b) :
                L(a), top(b) {
            }
            inline ~ReturnLock() {
                ::lua_settop(L, top);
            }
        }varLock{ thisData ,varTop };

        return varAns;
    }

    template<typename T>
    inline T * luaCheckTableUserData(lua_State * L, int t, std::string_view n) {
        const auto varTop = ::lua_gettop(L);
        const auto varTable = ::lua_absindex(L, t);

        auto varAns =
            reinterpret_cast<T *>(::lua_gettable_userdata(L, varTable));
        if (varAns == nullptr) {
            ::lua_pushlstring(L, "empty user data", 15);
            ::lua_error(L);
        }
        ::lua_pushlstring(L, "__name", 6);
        ::lua_gettable(L, varTable);
        if (::lua_isstring(L, -1)) {
            std::size_t varStringSize{ 1 };
            auto varAns =
                ::lua_tolstring(L, -1, &varStringSize);
            if (std::string_view(varAns, varStringSize) != n) {
                ::lua_pushlstring(L, "table name error", 16);
                ::lua_error(L);
            }
        } else {
            ::lua_pushlstring(L, "can not find table name", 23);
            ::lua_error(L);
        }
        ::lua_settop(L, varTop);
        return varAns;

    }

}/*namespace sstd*/



















