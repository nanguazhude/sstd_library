#include "sstd_lua_table_userdata.hpp"
#include "../../sstd_library.hpp"

class RealTableUserData : public TableUserData {
public:
    inline RealTableUserData(void *u, void(*uf)(void *)) : 
        TableUserData(u,uf) {
    }
private:
    sstd_class(RealTableUserData);
};

TableUserData * TableUserData::mallocUserData(void * a, void(* b)(void *)) {
    return sstd_new<RealTableUserData>(a,b);
}

void TableUserData::freeUserData(TableUserData *c) {
    delete reinterpret_cast<RealTableUserData *>(c);
}















