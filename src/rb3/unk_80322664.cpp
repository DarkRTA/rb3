#include "data.hpp"
#include "string.hpp"
#include "std/string.h"

extern DataArray* fn_8035CF9C(int, int, int);

// fn_803231CC
DataNode::DataNode(const char* c){
    DataArray* da = fn_8035CF9C(0x10, 0x10, 1);
    da = new DataArray(c, strlen(c) + 1);
    arr = da;
    type = StringDtaType;
}

// fn_8032324C
DataNode::DataNode(const String& s){
    DataArray* da = fn_8035CF9C(0x10, 0x10, 1);
    da = new DataArray(s.c_str(), s.length() + 1);
    arr = da;
    type = StringDtaType;
}