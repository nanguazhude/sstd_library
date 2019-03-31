#include "sstd_lua_table_userdata.hpp"
#include "../../sstd_library.hpp"

class RealTableUserData : public TableUserData {
public:
    inline RealTableUserData(void *u, void(*uf)(void *),const char *un,size_t udl) : 
        TableUserData(u,uf,un,udl) {
    }
private:
    sstd_class(RealTableUserData);
};

TableUserData * TableUserData::mallocUserData(void * a, void(* b)(void *),const char *c,size_t d) {
    return sstd_new<RealTableUserData>(a,b,c,d);
}

void TableUserData::freeUserData(TableUserData *c) {
    delete reinterpret_cast<RealTableUserData *>(c);
}















