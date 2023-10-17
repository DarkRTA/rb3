#include "data.hpp"
#include "string.hpp"
#include "std/string.h"

extern DataArray* fn_8035CF9C(int, int, int);

// fn_803231CC
DataNode::DataNode(const char* c){
    DataArray* da = fn_8035CF9C(0x10, 0x10, 1);
    da = new DataArray(c, strlen(c) + 1);
    value.dataArray = da;
    type = STRING_VALUE;
}

// fn_8032324C
DataNode::DataNode(const String& s){
    DataArray* da = fn_8035CF9C(0x10, 0x10, 1);
    da = new DataArray(s.c_str(), s.length() + 1);
    value.dataArray = da;
    type = STRING_VALUE;
}

// fn_80322F28
int DataNode::Int(const DataArray* da) const {
    DataNode* n = Evaluate();
    return n->value.intVal;
}

// fn_80322F4C
int DataNode::LiteralInt(const DataArray* da) const {
    return value.intVal;
}

// fn_80322F54
Symbol* DataNode::Sym(const DataArray* da) const {
    DataNode* n = Evaluate();
    return n->value.symVal;
}

// fn_80322F78
Symbol* DataNode::LiteralSym(const DataArray* da) const {
    return value.symVal;
}

// fn_80322F80
Symbol* DataNode::ForceSym(const DataArray* da) const {
    DataNode* n = Evaluate();
    if(n->type == SYMBOL){
        return n->value.symVal;
    }
    Symbol s;
}

// fn_80322FC8
const char* DataNode::Str(const DataArray* da) const {
    DataNode* n = Evaluate();
    if(n->type == SYMBOL) return n->value.strVal;
    else return n->value.dataArray->mNodes->value.strVal;
}

// fn_80323004
const char* DataNode::LiteralStr(const DataArray* da) const {
    if(type == SYMBOL) return value.strVal;
    else return value.dataArray->mNodes->value.strVal;
}

// fn_80323024
float DataNode::Float(const DataArray* da) const {
    DataNode* n = Evaluate();
    if(n->type == EMPTY) return n->value.intVal;
    else return n->value.floatVal;
}

// fn_8032307C
float DataNode::LiteralFloat(const DataArray* da) const {
    if(type == EMPTY) return value.intVal;
    else return value.floatVal;
}

// fn_8032313C
DataArray* DataNode::Array(const DataArray* da) const {
    DataNode* n = Evaluate();
    return n->value.dataArray;
}

// fn_80323160
DataArray* DataNode::LiteralArray(const DataArray* da) const {
    return value.dataArray;
}

// fn_80323360
bool DataNode::operator==(const DataNode& dn) const {
    if(type == dn.type){
        if(type == 0x12){
            // return strcmp()
        }
    }
}