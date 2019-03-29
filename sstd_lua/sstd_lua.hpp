#pragma once

#include "sstd_lua_exception.hpp"
#include "source/lua.hpp"
#include "../sstd_library.hpp"

namespace _theSSTDLuaFile {
}/*namespace _theSSTDLuaFile*/

namespace sstd {

    class SSTD_SYMBOL_DECL LuaObjectCplusplusRef final {
        lua_State* thisData{ nullptr };
    public:
        LuaObjectCplusplusRef(LuaObjectCplusplusRef &&);
        LuaObjectCplusplusRef(const LuaObjectCplusplusRef &);
        LuaObjectCplusplusRef&operator=(const LuaObjectCplusplusRef &);
        LuaObjectCplusplusRef&operator=(LuaObjectCplusplusRef &&);
    public:
        ~LuaObjectCplusplusRef();
    public:
        LuaObjectCplusplusRef(lua_State*,int);
    public:
        bool push() const;
    public:
        operator bool() const;
    public:
        sstd_class(LuaObjectCplusplusRef);
    };

}/*namespace sstd*/



















