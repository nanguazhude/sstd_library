#include "lua_full_test.hpp"

#include <sstd_library.hpp>
#include <iostream>

class Node {
public:
    virtual ~Node() = default;
    Node() = default;
public:
    static void * luaMetaTable();
private:
    sstd_delete_copy_create(Node);
private:
    sstd_class(Node);
};

void * Node::luaMetaTable() {
    static int varAns{ 123 };
    return &varAns;
}

int deleteNode(lua_State * L) {

    class DeleteNode {
    public:
        Node * data;
    };

    auto varNode =
        reinterpret_cast<DeleteNode *>(::lua_touserdata(L, 1));
    std::destroy_at(varNode->data);

    return 0;
}

inline void setMetaTable(lua_State *L, int varUserDataIndex) {

    ::lua_rawgetp(L, LUA_REGISTRYINDEX, Node::luaMetaTable());
    auto varRegistryTableIndex = ::lua_gettop(L);

    if (::lua_type(L, varRegistryTableIndex) != LUA_TTABLE) {

        ::lua_pop(L, 1);
        ::lua_createtable(L, 0, 8);
        ::lua_pushvalue(L, varRegistryTableIndex);
        ::lua_rawsetp(L, LUA_REGISTRYINDEX, Node::luaMetaTable());

        ::lua_pushlstring(L, "__gc", 4);
        ::lua_pushcclosure(L, &deleteNode, 0);
        ::lua_settable(L, varRegistryTableIndex);

        ::lua_pushlstring(L, "__name", 6);
        ::lua_pushlstring(L, "Node", 4);
        ::lua_settable(L, varRegistryTableIndex);

    }

    ::lua_setmetatable(L, varUserDataIndex);

}

template<typename T1, typename ... Args>
inline sstd::LuaObjectCplusplusRef createNode(lua_State *L, Args && ... args) {

    auto varLock = ::lua_gettop(L);

    using T = std::remove_cv_t< std::remove_reference_t< T1 > >;

    class Wrap {
    public:
        Node * node;
        std::array<char, sizeof(T) + alignof(T) > data;
    };

    auto varRawUserData = reinterpret_cast<Wrap *>(
        ::lua_newuserdata(L, sizeof(Wrap)));

    auto varUserDataIndex = ::lua_gettop(L);

    void * varData = varRawUserData->data.data();
    std::size_t varSize = varRawUserData->data.size();

    varRawUserData->node =
        ::new (std::align(alignof (T), sizeof(T), varData, varSize))
        T(std::forward<Args>(args)...);

    setMetaTable(L, varUserDataIndex);

    class Lock {
        lua_State * L;
        int top;
    public:
        inline Lock(lua_State *arg, int v) :
            L(arg),
            top(v) {
        }
        inline ~Lock() {
            ::lua_settop(L, top);
        }
    } varLockThere{ L, varLock };

    return { L , varUserDataIndex };

}

class Test1Node : public Node {
public:
    inline ~Test1Node() {
        std::cout << __func__ << std::endl;
    }
};

extern void luaFullTest() {
    auto L = ::luaL_newstate();

    {
        auto varWrap =
            createNode<Test1Node>(L);
        ::lua_gc(L, LUA_GCCOLLECT, 0);
    }

    {
        auto varWrap =
            createNode<Test1Node>(L);
        ::lua_gc(L, LUA_GCCOLLECT, 0);
    }

    ::lua_gc(L, LUA_GCCOLLECT,0);

    ::lua_close(L);
}



















