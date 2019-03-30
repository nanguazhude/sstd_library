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

#include <string>
using namespace std::string_literals;

#include <list>

class Test1Node : public Node {
public:
    inline ~Test1Node() {
        std::cout << __func__ << std::endl;
    }
    std::string testData{ "aabbccddeeffgg"s };



};

#include <string_view>

#include <vector>

std::vector< char, sstd::allocator<char> > luaBuildString(lua_State *L,
    std::string_view argProgram,
    const char * argDebugFunctionName = nullptr) {

        {
            class ReaderData {
            public:
                bool isReadFinished;
                std::string_view program;
            } varReadData{ false ,argProgram };

            /* http://www.lua.org/manual/5.3/manual.html#lua_load */
            /* lua_Reader : typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz); */
            auto varLoadState = ::lua_load(L,
                [](lua_State *, void *ud, size_t *sz)->const char * {
                auto varText = reinterpret_cast<ReaderData *>(ud);
                if (varText->isReadFinished) {
                    *sz = 0;
                    return nullptr;
                }
                varText->isReadFinished = true;
                *sz = varText->program.size();
                return varText->program.data(); },
                &varReadData,
                    argDebugFunctionName ? argDebugFunctionName : __func__,
                    nullptr);

            if (varLoadState != LUA_OK) {
                std::cout << ::lua_tostring(L, -1) << std::endl;
                ::lua_pop(L, 1);
                return {};
            }
        }

        {
            using AnsType = std::vector< char, sstd::allocator<char> >;
            AnsType  varAns;
            /* http://www.lua.org/manual/5.3/manual.html#lua_dump */
            /* int lua_dump (lua_State *L,  lua_Writer writer,  void *data, int strip); */
            ::lua_dump(L, [](lua_State *, const void* p, size_t sz, void* ud) ->int {
                auto varAns = reinterpret_cast<AnsType *>(ud);
                varAns->insert(varAns->end(),
                    reinterpret_cast<const char *>(p),
                    reinterpret_cast<const char *>(p) + sz);
                return 0;
            }, &varAns, true);

            return std::move(varAns);
        }

}

template<typename T>
inline int luaCallString(lua_State *L,
    const T & argProgram,
    const char * argDebugFunctionName = nullptr) {

    luaL_loadbufferx(L,
        argProgram.data(),
        argProgram.size(),
        argDebugFunctionName ? argDebugFunctionName : nullptr,
        nullptr);
    return lua_pcall(L, 0, LUA_MULTRET, 0);

}


extern void luaFullTest() {

    auto L = ::luaL_newstate();
    ::luaL_openlibs(L);

    if constexpr (true) {

        class Test112 {
        public:
            inline ~Test112() {
                std::cout << __func__ << std::endl;
            }
            std::string test{ "aaxxbbc"s };
            void foo() {
                std::cout << test << std::endl;
            }
        };

       
        ::lua_createtable(L,3,3);
        auto varTable = ::lua_gettop(L);

        ::lua_settable_userdata(L,varTable,
            new Test112, [](void *arg)->void {  
            delete reinterpret_cast< Test112 * >(arg);  });

        reinterpret_cast<Test112 *>(
            ::lua_gettable_userdata(L,varTable))->foo();

        ::lua_settop(L,0);

        ::lua_gc(L, LUA_GCCOLLECT, 0);

    }

    {
        //lua_load 编译;
        //lua_dump 保存；

        auto var = luaBuildString(L, u8R"1(print("hellow world"))1"sv);
        luaCallString(L, var);

    }

    {
        auto var = luaBuildString(L,
            u8R"1( return function(  a , b )  
                            return a + b;  
                          end    )1"sv);
        luaCallString(L, var);

        std::cout << lua_isfunction(L, -1) << std::endl;

        lua_pushinteger(L, 1);
        lua_pushinteger(L, 99);

        lua_pcall(L, 2, 1, 0);

        std::cout << lua_tointeger(L, -1) << std::endl;

    }

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

    {

        auto varWrap =
            createNode<Test1Node>(L);
        auto varNode =
            varWrap.getFirstUserDataPointer<Node>();
        std::cout <<
            static_cast<Test1Node *>(varNode)->testData << std::endl;

    }

    ::lua_gc(L, LUA_GCCOLLECT, 0);

    ::lua_close(L);
}

