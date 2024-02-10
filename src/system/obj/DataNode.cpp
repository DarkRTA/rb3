#include "Data.h"
#include "Str.h"
#include "Object.h"
#include "string.h"
#include <new>
#include <map>

// std::map<Symbol, DataNode> gDataVars;
DataNode gEvalNode[8];
int gEvalIndex;

DataNode& DataNode::AddToBuffer() {
    int i;
    gEvalNode[gEvalIndex] = *this;
    i = gEvalIndex;
    gEvalIndex = gEvalIndex + 1 & 7;
    return gEvalNode[i];
}

extern Hmx::Object *gDataThis;

DataNode& DataNode::Evaluate() const {
    if (mType == kDataCommand) {
        DataNode lol = mValue.array->Execute();
        return lol.AddToBuffer();
    } else if (mType == kDataVar) {
        return *mValue.var;
    } else if (mType == kDataProperty) {
        DataNode *dn = gDataThis->Property(mValue.array, true);
        return dn->AddToBuffer();
    } else
        return (DataNode&)*this;
}

// fn_80322F28
int DataNode::Int(const DataArray *da) const {
    return Evaluate().mValue.integer;
}

// fn_80322F4C
int DataNode::LiteralInt(const DataArray *da) const {
    return mValue.integer;
}

// fn_80322F54
Symbol DataNode::Sym(const DataArray *da) const {
    return STR_TO_SYM(Evaluate().mValue.symbol);
}

// fn_80322F78
Symbol DataNode::LiteralSym(const DataArray *da) const {
    return STR_TO_SYM((char*)mValue.symbol);
}

// fn_80322F80
Symbol DataNode::ForceSym(const DataArray* da) const {
    DataNode& eval = Evaluate();
    if(eval.mType == kDataSymbol){
        return STR_TO_SYM(eval.mValue.symbol);
    }
    else return Symbol(eval.mValue.var->mValue.symbol);
}

// fn_80322FC8
const char *DataNode::Str(const DataArray *da) const {
    DataNode& eval = Evaluate();
    if(eval.mType == kDataSymbol){
        return eval.mValue.symbol;
    }
    else return eval.mValue.var->mValue.symbol;
}

// fn_80323004
const char *DataNode::LiteralStr(const DataArray *da) const {
    if(mType == kDataSymbol){
        return mValue.symbol;
    }
    else return mValue.var->mValue.symbol;
}

// fn_80323024
float DataNode::Float(const DataArray *da) const {
    DataNode& eval = Evaluate();
    if(eval.mType == kDataInt) return eval.mValue.integer;
    else return eval.mValue.real;
}

// fn_8032307C
float DataNode::LiteralFloat(const DataArray *da) const {
    if(mType == kDataInt) return mValue.integer;
    else return mValue.real;
}

DataFunc* DataNode::Func(const DataArray* da) const {
    return mValue.func;
}

Hmx::Object* DataNode::GetObj(const DataArray* da) const {

}

// fn_8032313C
DataArray *DataNode::Array(const DataArray *da) const {
    return Evaluate().mValue.array;
}

// fn_80323160
DataArray *DataNode::LiteralArray(const DataArray *da) const {
    return mValue.array;
}

DataArray* DataNode::Command(const DataArray* da) const {
    return mValue.array;
}

DataNode* DataNode::Var(const DataArray* da) const {
    return mValue.var;
}

extern void* _PoolAlloc(int, int, int);

// fn_803231CC
DataNode::DataNode(const char *c) {
    mValue.array = new (_PoolAlloc(0x10, 0x10, 1)) DataArray(c, strlen(c) + 1);
    mType = kDataString;
}

// fn_8032324C
DataNode::DataNode(const String &s) {
    mValue.array =
        new (_PoolAlloc(0x10, 0x10, 1)) DataArray(s.c_str(), s.length() + 1);
    mType = kDataString;
}

DataNode::DataNode(const DataArrayPtr &ptr) {
    DataArray* arr = ptr.mData;
    mValue.array = arr;
    arr->AddRef();
    mType = kDataArray;
}

// fn_80323318
DataNode::DataNode(DataArray *da, DataType ty) {
    mValue.array = da;
    mValue.array->AddRef();
    mType = ty;
}

// fn_80323360
bool DataNode::operator==(const DataNode& node) const {
    if(mType == node.mType){
        if(mType == kDataString){
            return strcmp(mValue.var->mValue.symbol, node.mValue.var->mValue.symbol) == 0;
        }
        else return mValue.integer == node.mValue.integer;
    }
    else if(mType == kDataObject || node.mType == kDataObject){
        const char *obj1, *obj2;
        if(mType == kDataObject){
            if(mValue.object != 0) obj1 = mValue.object->Name();
            else obj1 = '\0';
            obj2 = node.LiteralStr(0);
        }
        else {
            obj1 = LiteralStr(0);
            if(node.mValue.object != 0) obj2 = node.mValue.object->Name();
            else obj2 = '\0';
        }
        return strcmp(obj1, obj2) == 0;
    }
    else if(mType == kDataString || node.mType == kDataString){
        return strcmp(LiteralStr(0), node.LiteralStr(0)) == 0;
    }
    else if(mType == kDataFloat || node.mType == kDataFloat){
        return LiteralFloat(0) == node.LiteralFloat(0);
    }
    else return false;
}

// fn_80323508
bool DataNode::operator!=(const DataNode &dn) const {
    return !(*this == dn);
}

// fn_80323530
bool DataNode::NotNull() const {
    DataNode& n = Evaluate();
    DataType t = n.Type();
    if(t == kDataSymbol){
        return n.mValue.symbol[0] != 0;
    }
    else if(t == kDataString){
        return n.mValue.array->Size() < -1;
    }
    else if(t == kDataGlob){
        return n.mValue.array->Size() & -1;
    }
    else return n.mValue.array != 0;
}


// void DataNode::AssignValue(const DataNode &dn) {
//     value = dn.value;
// }


// // fn_803235D4
// DataNode& DataNode::operator=(const DataNode &dn) {
//     if (type & 0x10) {
//         value.dataArray->DecRefCount();
//     }
//     AssignValue(dn);
//     type = dn.type;
//     if (type & 0x10) {
//         value.dataArray->IncRefCount();
//     }
//     return *this;
// }

// // fn_80323178
// DataNode::DataNode(const DataNode &dn) {
//     AssignValue(dn);
//     type = dn.type;
//     if (type & 0x10)
//         value.dataArray->IncRefCount();
// }

// // fn_803239E8
// bool HasSpace(const char *str) {
//     while (*str != '\0') {
//         if (*str++ == ' ')
//             return true;
//     }
//     return false;
// }

// TextStream &operator<<(TextStream &ts, const Hmx::Object *obj) {
//     if (obj != nullptr) {
//         ts << obj->Name();
//     } else
//         ts << "<null>";
//     return ts;
// }

// extern char *DataVarName(const DataNode *);
// extern Symbol DataFuncName(DataFunc *);

// // fn_8032364C
// void DataNode::Print(TextStream &ts, bool b) const {
//     switch (type) {
//     case kDataUnhandled:
//         ts << "kDataUnhandled";
//         break;
//     case kDataInt:
//         ts << value.intVal;
//         break;
//     case kDataString:
//         if (b)
//             ts << value.symVal->m_string;
//         else {
//             ts << "\"";
//             char *tok = strtok(value.symVal->m_string, "\"");
//             while (tok != nullptr) {
//                 ts << tok;
//                 tok = strtok(nullptr, "\"");
//                 if (tok != nullptr) {
//                     ts << "\\q";
//                     tok[-1] = '\"';
//                 }
//             }
//             ts << "\"";
//         }
//         break;
//     case kDataSymbol:
//         if (!HasSpace(value.strVal))
//             ts << value.strVal;
//         else
//             ts << "'" << value.strVal << "'";
//         break;
//     case kDataGlob:
//         ts << "<glob " << -value.dataArray->GetNodeCount() << ">";
//         break;
//     case kDataFloat:
//         ts << value.floatVal;
//         break;
//     case kDataArray:
//     case kDataCommand:
//     case kDataProperty:
//         value.dataArray->Print(ts, type, b);
//         break;
//     case kDataObject:
//         ts << value.objVal;
//         break;
//     case kDataVariable:
//         ts << '$' << DataVarName(value.varVal);
//         break;
//     case kDataFunc:
//         ts << DataFuncName(value.funcVal);
//         break;
//     case kDataDefine:
//         ts << "\n#define " << value.strVal << "\n";
//         break;
//     case kDataUndef:
//         ts << "\n#undef " << value.strVal << "\n";
//         break;
//     case kDataIfdef:
//         ts << "\n#ifdef " << value.strVal << "\n";
//         break;
//     case kDataIfndef:
//         ts << "\n#ifndef " << value.strVal << "\n";
//         break;
//     case kDataAutorun:
//         ts << "\n#autorun\n";
//         break;
//     case kDataElse:
//         ts << "\n#else\n";
//         break;
//     case kDataEndif:
//         ts << "\n#endif\n";
//         break;
//     case kDataInclude:
//         ts << "\n#include " << value.strVal << "\n";
//         break;
//     case kDataMerge:
//         ts << "\n#merge " << value.strVal << "\n";
//         break;
//     }
// }

// void DataNode::Save(BinStream &bs) const {
//     int theType = type;
//     switch (theType) {
//     case kDataUnhandled:
//         theType = kDataInt;
//         break;
//     case kDataInt:
//         theType = kDataUnhandled;
//         break;
//     }
//     bs << (unsigned int)theType;
//     switch (theType) {
//     case kDataSymbol:
//     case kDataIfdef:
//     case kDataDefine:
//     case kDataInclude:
//     case kDataMerge:
//     case kDataIfndef:
//     case kDataUndef:
//         bs << value.strVal;
//         break;
//     case kDataFloat:
//         bs << value.floatVal;
//         break;
//     case kDataString:
//     case kDataGlob:
//         value.dataArray->SaveGlob(bs, (type - 0x12) == 0);
//         break;
//     case kDataArray:
//     case kDataCommand:
//     case kDataProperty:
//         value.dataArray->Save(bs);
//         break;
//     case kDataObject:
//         if (value.objVal != nullptr)
//             bs << value.objVal->Name();
//         else
//             bs << "\0";
//         break;
//     case kDataVariable:
//         bs << DataVarName(value.varVal);
//         break;
//     case kDataFunc:
//         bs << DataFuncName(value.funcVal);
//         break;
//     case kDataUnhandled:
//     case kDataInt:
//     case kDataElse:
//     case kDataEndif:
//     case kDataAutorun:
//         bs << (unsigned int)value.intVal;
//         break;
//     }
// }
