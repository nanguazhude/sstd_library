#include "sstd_lua.hpp"

namespace _theSSTDLuaFile {

    const static auto varIndex{ 1 };

    namespace detail {

        inline int pushRegistryTable(lua_State* L) {
            ::lua_rawgetp(L, LUA_REGISTRYINDEX, &varIndex);
            auto varRegistryTableIndex = ::lua_gettop(L);
            if (::lua_type(L, varRegistryTableIndex) != LUA_TTABLE) {
                ::lua_pop(L, 1);
                ::lua_createtable(L, 0, 64);
                ::lua_pushvalue(L, varRegistryTableIndex);
                ::lua_rawsetp(L, LUA_REGISTRYINDEX, &varIndex);
                assert(::lua_type(L, varRegistryTableIndex) == LUA_TTABLE);
            }
            return varRegistryTableIndex;
        }

        inline int pushValue(lua_State* L) {
            auto varTable = pushRegistryTable(L);
            auto varPoiner = ::lua_touserdata(L, 1);
            ::lua_rawgetp(L, varTable, varPoiner);
            return 1;
        }

        inline int setValue(lua_State* L) {
            auto varTable = pushRegistryTable(L);
            auto varPoiner = ::lua_touserdata(L, 1);
            ::lua_pushvalue(L, 2);
            ::lua_rawsetp(L, varTable, varPoiner);
            return 0;
        }

        inline int clearValue(lua_State *L) {
            auto varTable = pushRegistryTable(L);
            auto varPoiner = ::lua_touserdata(L, 1);
            ::lua_pushnil(L);
            ::lua_rawsetp(L, varTable, varPoiner);
            return 0;
        }

        inline int copy(lua_State *L) {
            auto varFromPoiner = ::lua_touserdata(L, 1);
            auto varToPoiner = ::lua_touserdata(L, 2);
            auto varTable = pushRegistryTable(L);
            ::lua_rawgetp(L, varTable, varFromPoiner);
            ::lua_rawsetp(L, varTable, varToPoiner);
            return 0;
        }

    }/*detail*/

    inline void setValue(sstd::LuaObjectCplusplusRef * p, lua_State* L, int index) {
        auto varValueIndex = ::lua_absindex(L, index);
        ::lua_pushcclosure(L, &_theSSTDLuaFile::detail::setValue, 0);
        ::lua_pushlightuserdata(L, p);
        ::lua_pushvalue(L, varValueIndex);
        ::lua_pcall(L, 2, 0, 0);
    }

    inline void clearValue(sstd::LuaObjectCplusplusRef * p, lua_State* L) {
        ::lua_pushcclosure(L, &_theSSTDLuaFile::detail::clearValue, 0);
        ::lua_pushlightuserdata(L, p);
        ::lua_pcall(L, 1, 0, 0);
    }

    inline void copy(sstd::LuaObjectCplusplusRef * f, sstd::LuaObjectCplusplusRef * t, lua_State* L) {
        ::lua_pushcclosure(L, &_theSSTDLuaFile::detail::copy, 0);
        ::lua_pushlightuserdata(L, f);
        ::lua_pushlightuserdata(L, t);
        ::lua_pcall(L, 2, 0, 0);
    }

    inline void pushValue(sstd::LuaObjectCplusplusRef * p, lua_State* L) {
        ::lua_pushcclosure(L, &_theSSTDLuaFile::detail::pushValue, 0);
        ::lua_pushlightuserdata(L, p);
        ::lua_pcall(L, 1, 1, 0);
    }

}/*namespace _theSSTDLuaFile*/

namespace sstd {

    LuaObjectCplusplusRef::LuaObjectCplusplusRef() : thisData{nullptr} {
    }

    LuaObjectCplusplusRef::LuaObjectCplusplusRef(lua_State* L, int index) : thisData(L) {
        if (!thisData) {
            return;
        }
        _theSSTDLuaFile::setValue(this, L, index);
    }

    LuaObjectCplusplusRef::LuaObjectCplusplusRef(LuaObjectCplusplusRef && arg) :
        thisData(arg.thisData) {
        if (!thisData) {
            return;
        }
        assert(this != &arg);
        _theSSTDLuaFile::copy(&arg, this, arg.thisData);
        {
            _theSSTDLuaFile::clearValue(&arg, thisData);
            arg.thisData = nullptr;
        }
    }

    LuaObjectCplusplusRef::LuaObjectCplusplusRef(const LuaObjectCplusplusRef & arg) :
        thisData(arg.thisData) {
        if (!thisData) {
            return;
        }
        _theSSTDLuaFile::copy(const_cast<LuaObjectCplusplusRef *>(&arg), this, arg.thisData);
    }

    LuaObjectCplusplusRef&LuaObjectCplusplusRef::operator=(const LuaObjectCplusplusRef & arg) {
        if (this == &arg) {
            return *this;
        }
        if (thisData) {
            _theSSTDLuaFile::clearValue(this, thisData);
        }
        thisData = arg.thisData;
        if (arg.thisData) {
            _theSSTDLuaFile::copy(const_cast<LuaObjectCplusplusRef *>(&arg), this, arg.thisData);
        }
        return *this;
    }

    LuaObjectCplusplusRef&LuaObjectCplusplusRef::operator=(LuaObjectCplusplusRef && arg) {
        if (this == &arg) {
            return *this;
        }
        if (thisData) {
            _theSSTDLuaFile::clearValue(this, thisData);
        }
        thisData = arg.thisData;
        if (arg.thisData) {
            _theSSTDLuaFile::copy(&arg, this, arg.thisData);
            _theSSTDLuaFile::clearValue(&arg, arg.thisData);
            arg.thisData = nullptr;
        }
        return *this;
    }

    LuaObjectCplusplusRef::~LuaObjectCplusplusRef() {
        if (!thisData) {
            return;
        }
        _theSSTDLuaFile::clearValue(this, thisData);
    }

    lua_State* LuaObjectCplusplusRef::push() const {
        if (thisData) {
            _theSSTDLuaFile::pushValue(const_cast<LuaObjectCplusplusRef *>(this), thisData);
            return thisData;
        }
        return nullptr;
    }

}/*namespace sstd*/
