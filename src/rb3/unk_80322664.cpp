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

// fn_80322F80
DataNode* DataNode::ForceSym(const DataArray* da) const {
    DataNode* n = Evaluate();
    if(n->type == SymbolDtaType){
        return n;
    }
    Symbol s;
}

// fn_80323004
DataNode* DataNode::LiteralStr(const DataArray* da) const {
    if(type == SymbolDtaType){
        return (DataNode*)this;
    }
    else return this->arr->node;
}

// fn_80323024
double DataNode::Float(const DataArray* da) const {
    DataNode* n = Evaluate();
    if(n->type == 6){
        return 0.0;
    }
}

// fn_80323360
bool DataNode::operator==(const DataNode& dn) const {
    if(type == dn.type){
        if(type == 0x12){
            // return strcmp()
        }
    }
}