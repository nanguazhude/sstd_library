#include "sstd_lua_table_userdata.hpp"
#include "../../sstd_library.hpp"

class RealTableUserData : public TableUserData {
    sstd_class(RealTableUserData);
public:
    using TableUserData::TableUserData;
};

TableUserData * TableUserData::mallocUserData(void * a, void(* b)(void *)) {
    return sstd_new<RealTableUserData>(a,b);
}

void TableUserData::freeUserData(TableUserData *c) {
    delete reinterpret_cast<RealTableUserData *>(c);
}















