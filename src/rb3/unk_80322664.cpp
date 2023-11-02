#include "data.hpp"
#include "string.hpp"
#include "std/string.h"
#include "common.hpp"

extern DataArray* fn_8035CF9C(int, int, int);

// fn_803231CC
DataNode::DataNode(const char* c){
    value.dataArray = new (DataArray::fn_8035CF9C(0x10, 0x10, 1)) DataArray(c, strlen(c) + 1);
    type = STRING_VALUE;
}

// fn_8032324C
DataNode::DataNode(const String& s){
    value.dataArray = new (DataArray::fn_8035CF9C(0x10, 0x10, 1)) DataArray(s.c_str(), s.length() + 1);
    type = STRING_VALUE;
}

// fn_80323318
DataNode::DataNode(DataArray* da, DataType ty){
    value.dataArray = da;
    value.dataArray->IncRefCount();
    type = ty;
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
    Symbol s(n->value.symVal->m_string);
    return &s;
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
        if(type == STRING_VALUE){
            return strcmp(value.strVal, dn.value.strVal) == 0;
        }
        else return (value.intVal == dn.value.intVal);
    }
    else if((type == OBJECT) || (dn.type == OBJECT)){

    }
    else if((type == STRING_VALUE) || (dn.type == STRING_VALUE)){
        return strcmp(LiteralStr(nullptr), dn.LiteralStr(nullptr)) == 0;
    }
    else if((type == FLOAT_VALUE) || (dn.type == FLOAT_VALUE)){
        return (LiteralFloat(nullptr) == dn.LiteralFloat(nullptr));
    }
    else return false;
}

// fn_80323508
bool DataNode::operator!=(const DataNode& dn) const {
    return !(*this == dn);
}

#pragma dont_inline on
DataType DataNode::GetType(){ return type; }
#pragma dont_inline reset

// fn_80323530
bool DataNode::NotNull() const {
    DataNode* n = Evaluate();
    DataType t = n->GetType();
    if(t == SYMBOL){
        return n->value.strVal[0] != 0;
    }
    else if(t == STRING_VALUE){
        return (n->value.dataArray->GetNodeCount() < -1);
    }
    else if(t == GLOB){
        return (n->value.dataArray->GetNodeCount() & -1);
    }
    else return (n->value.dataArray != 0);
}

#pragma dont_inline on
void DataNode::AssignValue(const DataNode& dn){ value = dn.value; }
#pragma dont_inline reset

// fn_803235D4
DataNode* DataNode::operator=(const DataNode& dn) {
    if(type & 0x10){
        value.dataArray->DecRefCount();
    }
    AssignValue(dn);
    type = dn.type;
    if(type & 0x10){
        value.dataArray->IncRefCount();
    }
    return this;
}

// fn_80323178
DataNode::DataNode(const DataNode& dn){
    AssignValue(dn);
    type = dn.type;
    if(type & 0x10) value.dataArray->IncRefCount();
}

// fn_8032364C
void DataNode::Print(TextStream& ts, bool b) const {
    switch(type){
        case INT_VALUE: ts << value.intVal; break;
        case FLOAT_VALUE: ts << value.floatVal; break;
        case VAR:
            // DataVarName__FPC8DataNode gets called here
            ts << "$";
            break;
        case FUNC:
            // DataFuncName__FPFP9DataArray_8DataNode gets called here
            // ts << (Symbol)0xE8;
            break;
        case OBJECT:
            if(value.dataArray == nullptr){
                ts << "<null>";
            }
            break;
        case SYMBOL:
            if(!b){
                ts << "'";
                ts << value.strVal;
                ts << "'";
            }
            else ts << value.strVal;
            break;
        case EMPTY: ts << "invalid"; break;
        case IFDEF:
            ts << "\n#ifdef ";
            ts << value.strVal;
            ts << "\n";
            break;
        case ELSE: ts << "\n#else\n"; break;
        case ENDIF: ts << "\n#endif\n"; break;
        case ARRAY:
        case COMMAND:
        case OBJECT_PROP_REF:
            break;
        case STRING_VALUE:
            break;
        case GLOB:
            break;
        case DEFINE:
            ts << "\n#define ";
            ts << value.strVal;
            ts << "\n";
            break;
        case INCLUDE:
            ts << "\n#include ";
            ts << value.strVal;
            ts << "\n";
            break;
        case MERGE:
            ts << "\n#merge ";
            ts << value.strVal;
            ts << "\n";
            break;
        case IFNDEF:
            ts << "\n#ifndef ";
            ts << value.strVal;
            ts << "\n";
            break;
        case AUTORUN:
            ts << "\n#autorun\n";
            break;
        case UNDEF:
            ts << "\n#undef ";
            ts << value.strVal;
            ts << "\n";
            break;
    }
}