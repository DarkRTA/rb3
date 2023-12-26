#include "data.hpp"
#include "string.hpp"
#include "std/string.h"
#include "common.hpp"
#include "hmx/object.hpp"

extern DataArray *fn_8035CF9C(int, int, int);

// fn_803231CC
DataNode::DataNode(const char *c) {
    value.dataArray = new (fn_8035CF9C(0x10, 0x10, 1)) DataArray(c, strlen(c) + 1);
    type = kDataString;
}

// fn_8032324C
DataNode::DataNode(const String &s) {
    value.dataArray =
        new (fn_8035CF9C(0x10, 0x10, 1)) DataArray(s.c_str(), s.length() + 1);
    type = kDataString;
}

// fn_80323318
DataNode::DataNode(DataArray *da, DataType ty) {
    value.dataArray = da;
    value.dataArray->IncRefCount();
    type = ty;
}

// fn_80322F28
int DataNode::Int(const DataArray *da) const {
    DataNode *n = Evaluate();
    return n->value.intVal;
}

// fn_80322F4C
int DataNode::LiteralInt(const DataArray *da) const {
    return value.intVal;
}

// fn_80322F54
Symbol DataNode::Sym(const DataArray *da) const {
    DataNode *n = Evaluate();
    return (Symbol&)(n->value.miscVal);
}

// fn_80322F78
Symbol DataNode::LiteralSym(const DataArray *da) const {
    return (Symbol&)(value.miscVal);
}

// fn_80322F80
Symbol DataNode::ForceSym(const DataArray *da) const {
    DataNode *n = Evaluate();
    if (n->type == kDataSymbol) {
        return (Symbol&)(n->value.miscVal);
    }
    return Symbol(n->value.symVal->m_string);
}

// fn_80322FC8
const char *DataNode::Str(const DataArray *da) const {
    DataNode *n = Evaluate();
    if (n->type == kDataSymbol)
        return n->value.strVal;
    else
        return n->value.symVal->m_string;
}

// fn_80323004
const char *DataNode::LiteralStr(const DataArray *da) const {
    if (type == kDataSymbol)
        return value.strVal;
    else
        return value.symVal->m_string;
}

// fn_80323024
float DataNode::Float(const DataArray *da) const {
    DataNode *n = Evaluate();
    if (n->type == kDataInt)
        return n->value.intVal;
    else
        return n->value.floatVal;
}

// fn_8032307C
float DataNode::LiteralFloat(const DataArray *da) const {
    if (type == kDataInt)
        return value.intVal;
    else
        return value.floatVal;
}

// fn_8032313C
DataArray *DataNode::Array(const DataArray *da) const {
    DataNode *n = Evaluate();
    return n->value.dataArray;
}

// fn_80323160
DataArray *DataNode::LiteralArray(const DataArray *da) const {
    return value.dataArray;
}

// fn_80323360
bool DataNode::operator==(const DataNode &dn) const {
    if (type == dn.type) {
        if (type == kDataString) {
            return strcmp(value.symVal->m_string, dn.value.symVal->m_string) == 0;
        } else
            return (value.intVal == dn.value.intVal);
    } else if ((type == kDataObject) || (dn.type == kDataObject)) {
        char *obj1;
        char *obj2;
        if (type == kDataObject) {
            if (value.objVal == nullptr)
                obj1 = '\0';
            else
                obj1 = (char *)value.objVal->Name();
            obj2 = (char *)dn.LiteralStr(nullptr);
        } else {
            obj1 = (char *)LiteralStr(nullptr);
            if (dn.value.objVal == nullptr)
                obj2 = '\0';
            else
                obj2 = (char *)dn.value.objVal->Name();
        }
        return strcmp(obj1, obj2) == 0;
    } else if ((type == kDataString) || (dn.type == kDataString)) {
        return strcmp(LiteralStr(nullptr), dn.LiteralStr(nullptr)) == 0;
    } else if ((type == kDataFloat) || (dn.type == kDataFloat)) {
        return (LiteralFloat(nullptr) == dn.LiteralFloat(nullptr));
    } else
        return false;
}

// fn_80323508
bool DataNode::operator!=(const DataNode &dn) const {
    return !(*this == dn);
}

#pragma dont_inline on
DataType DataNode::GetType() const {
    return type;
}
#pragma dont_inline reset

// fn_80323530
bool DataNode::NotNull() const {
    DataNode *n = Evaluate();
    DataType t = n->GetType();
    if (t == kDataSymbol) {
        return n->value.strVal[0] != 0;
    } else if (t == kDataString) {
        return (n->value.dataArray->GetNodeCount() < -1);
    } else if (t == kDataGlob) {
        return (n->value.dataArray->GetNodeCount() & -1);
    } else
        return (n->value.dataArray != 0);
}

#pragma dont_inline on
void DataNode::AssignValue(const DataNode &dn) {
    value = dn.value;
}
#pragma dont_inline reset

// fn_803235D4
DataNode *DataNode::operator=(const DataNode &dn) {
    if (type & 0x10) {
        value.dataArray->DecRefCount();
    }
    AssignValue(dn);
    type = dn.type;
    if (type & 0x10) {
        value.dataArray->IncRefCount();
    }
    return this;
}

// fn_80323178
DataNode::DataNode(const DataNode &dn) {
    AssignValue(dn);
    type = dn.type;
    if (type & 0x10)
        value.dataArray->IncRefCount();
}

DataNode::DataNode(const DataArrayPtr &ptr) {
    DataArray *arr = ptr.arr;
    value.dataArray = arr;
    arr->IncRefCount();
    type = kDataArray;
}

// fn_80323170
DataNode *DataNode::Var(const DataArray *) const {
    return value.varVal;
}

// fn_803230C0
DataFunc *DataNode::Func(const DataArray *) const {
    return value.funcVal;
}

// fn_803239E8
bool HasSpace(const char *str) {
    while (*str != '\0') {
        if (*str++ == ' ')
            return true;
    }
    return false;
}

TextStream &operator<<(TextStream &ts, const Hmx::Object *obj) {
    if (obj != nullptr) {
        ts << obj->Name();
    } else
        ts << "<null>";
    return ts;
}

extern char *DataVarName(const DataNode *);
extern Symbol DataFuncName(DataFunc *);

// fn_8032364C
void DataNode::Print(TextStream &ts, bool b) const {
    switch (type) {
    case kDataUnhandled:
        ts << "kDataUnhandled";
        break;
    case kDataInt:
        ts << value.intVal;
        break;
    case kDataString:
        if (b)
            ts << value.symVal->m_string;
        else {
            ts << "\"";
            char *tok = strtok(value.symVal->m_string, "\"");
            while (tok != nullptr) {
                ts << tok;
                tok = strtok(nullptr, "\"");
                if (tok != nullptr) {
                    ts << "\\q";
                    tok[-1] = '\"';
                }
            }
            ts << "\"";
        }
        break;
    case kDataSymbol:
        if (!HasSpace(value.strVal))
            ts << value.strVal;
        else
            ts << "'" << value.strVal << "'";
        break;
    case kDataGlob:
        ts << "<glob " << -value.dataArray->GetNodeCount() << ">";
        break;
    case kDataFloat:
        ts << value.floatVal;
        break;
    case kDataArray:
    case kDataCommand:
    case kDataProperty:
        value.dataArray->Print(ts, type, b);
        break;
    case kDataObject:
        ts << value.objVal;
        break;
    case kDataVariable:
        ts << '$' << DataVarName(value.varVal);
        break;
    case kDataFunc:
        ts << DataFuncName(value.funcVal);
        break;
    case kDataDefine:
        ts << "\n#define " << value.strVal << "\n";
        break;
    case kDataUndef:
        ts << "\n#undef " << value.strVal << "\n";
        break;
    case kDataIfdef:
        ts << "\n#ifdef " << value.strVal << "\n";
        break;
    case kDataIfndef:
        ts << "\n#ifndef " << value.strVal << "\n";
        break;
    case kDataAutorun:
        ts << "\n#autorun\n";
        break;
    case kDataElse:
        ts << "\n#else\n";
        break;
    case kDataEndif:
        ts << "\n#endif\n";
        break;
    case kDataInclude:
        ts << "\n#include " << value.strVal << "\n";
        break;
    case kDataMerge:
        ts << "\n#merge " << value.strVal << "\n";
        break;
    }
}

void DataNode::Save(BinStream &bs) const {
    int theType = type;
    switch (theType) {
    case kDataUnhandled:
        theType = kDataInt;
        break;
    case kDataInt:
        theType = kDataUnhandled;
        break;
    }
    bs << (unsigned int)theType;
    switch (theType) {
    case kDataSymbol:
    case kDataIfdef:
    case kDataDefine:
    case kDataInclude:
    case kDataMerge:
    case kDataIfndef:
    case kDataUndef:
        bs << value.strVal;
        break;
    case kDataFloat:
        bs << value.floatVal;
        break;
    case kDataString:
    case kDataGlob:
        value.dataArray->SaveGlob(bs, (type - 0x12) == 0);
        break;
    case kDataArray:
    case kDataCommand:
    case kDataProperty:
        value.dataArray->Save(bs);
        break;
    case kDataObject:
        if (value.objVal != nullptr)
            bs << value.objVal->Name();
        else
            bs << "\0";
        break;
    case kDataVariable:
        bs << DataVarName(value.varVal);
        break;
    case kDataFunc:
        bs << DataFuncName(value.funcVal);
        break;
    case kDataUnhandled:
    case kDataInt:
    case kDataElse:
    case kDataEndif:
    case kDataAutorun:
        bs << (unsigned int)value.intVal;
        break;
    }
}

extern int gEvalIndex;
extern DataNode gEvalNode[];

DataNode *DataNode::AddToBuffer() {
    int i;
    gEvalNode[gEvalIndex] = *this;
    i = gEvalIndex;
    gEvalIndex = gEvalIndex + 1 & 7;
    return &gEvalNode[i];
}

extern Hmx::Object *gDataThis;

DataNode *DataNode::Evaluate() const {
    if (type == kDataCommand) {
        DataNode lol = value.dataArray->Execute();
        return lol.AddToBuffer();
    } else if (type == kDataVariable) {
        return value.varVal;
    } else if (type == kDataProperty) {
        DataNode *dn = gDataThis->Property(value.dataArray, true);
        return dn->AddToBuffer();
    } else
        return (DataNode *)this;
}