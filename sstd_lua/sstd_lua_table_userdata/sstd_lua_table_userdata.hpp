#pragma once

class TableUserData {
public:
    void *userData;
    void(*userDataFunction)(void *);
protected:
    inline TableUserData(void *u, void(*uf)(void *)) :
        userData(u),
        userDataFunction(uf) {
    }
public:
    inline ~TableUserData() {
        if (userDataFunction) {
            userDataFunction(userData);
        }
    }
public:
    TableUserData(const TableUserData &)=delete;
    TableUserData(TableUserData &&)=delete;
    TableUserData&operator=(const TableUserData &) = delete;
    TableUserData&operator=(TableUserData &&) = delete;
public:
    static TableUserData * mallocUserData(void *,void(*)(void *));
    static void freeUserData(TableUserData *);
};














