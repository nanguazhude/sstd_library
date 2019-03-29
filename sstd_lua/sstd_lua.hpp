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
        assert( ::lua_type( thisData ,varPos ) == LUA_TUSERDATA );
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

}/*namespace sstd*/



















