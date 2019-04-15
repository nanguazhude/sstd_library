#pragma once

#include <cstddef>
#include <cinttypes>

class TableUserData {
public:
    void *userData;
    void(*userDataFunction)(void *);
    const char * userDataType;
    size_t userDataTypeLength;
protected:
    inline TableUserData(void *u, void(*uf)(void *), const char *un, size_t unl) :
        userData(u),
        userDataFunction(uf),
        userDataType(un),
        userDataTypeLength(unl) {
    }
public:
    inline ~TableUserData() {
        if (userDataFunction) {
            userDataFunction(userData);
        }
    }
public:
    TableUserData(const TableUserData &) = delete;
    TableUserData(TableUserData &&) = delete;
    TableUserData&operator=(const TableUserData &) = delete;
    TableUserData&operator=(TableUserData &&) = delete;
public:
    static TableUserData * mallocUserData(void *, void(*)(void *),const char*,size_t);
    static void freeUserData(TableUserData *);
};
