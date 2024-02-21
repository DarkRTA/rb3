#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Str.h"
#include "utl/MakeString.h"
// #include <string.h>
// #include <new>
// #include <map>
// #include "obj/Object.h"

// // std::map<Symbol, DataNode> gDataVars;
DataNode gEvalNode[8];
int gEvalIndex;

extern Hmx::Object *gDataThis;

bool DataNode::CompatibleType(DataType ty) const {
    DataType thisType = mType;
    if(thisType == ty) return true;
    else if(thisType == kDataInt){
        return ty == kDataFloat;
    }
    else if(thisType != kDataSymbol){
        if(thisType != kDataString){
            return false;
        }
        return ty == kDataObject;
    }
    else if((ty != kDataString) && (ty != kDataObject)) return false;
    else return true;
}

DataNode& UseQueue(const DataNode& node){
    int i;
    gEvalNode[gEvalIndex] = node;
    i = gEvalIndex;
    gEvalIndex = gEvalIndex + 1 & 7;
    return gEvalNode[i];
}

// TODO: edit the Data.h header such that the weak DataNode dtor can be implemented without errors of an incomplete DataArray class
DataNode& DataNode::Evaluate() const {
    if(mType == kDataCommand){
        DataNode lol = mValue.array->Execute();
        return UseQueue(lol);
    }
    else if(mType == kDataVar){
        return *mValue.var;
    }
    else if(mType == kDataProperty){
        MILO_ASSERT(gDataThis, 0x78);
        DataNode* n = gDataThis->Property(mValue.array, true);
        return UseQueue(*n);
    }
    else return (DataNode&)*this;
}

int DataNode::Int(const DataArray* a) const {
    DataNode& n = Evaluate();
    if(n.mType != kDataInt){
        String s;
        n.Print(s, true);
        if(a) MILO_FAIL("Data %s is not Int (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
        else MILO_FAIL("Data %s is not Int", String(s));
    }
    return n.mValue.integer;
}

int DataNode::LiteralInt(const DataArray* a) const {
    if(mType != kDataInt){
        String s;
        Print(s, true);
        if(a) MILO_FAIL("Data %s is not Int (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
        else MILO_FAIL("Data %s is not Int", String(s));
    }
    return mValue.integer;
}

Symbol DataNode::Sym(const DataArray* a) const {
    DataNode& n = Evaluate();
    if(n.mType != kDataSymbol){
        String s;
        n.Print(s, true);
        if(a) MILO_FAIL("Data %s is not Symbol (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
        else MILO_FAIL("Data %s is not Symbol", String(s));
    }
    return STR_TO_SYM(n.mValue.symbol);
}

Symbol DataNode::LiteralSym(const DataArray* a) const {
    if(mType != kDataSymbol){
        String s;
        Print(s, true);
        if(a) MILO_FAIL("Data %s is not Symbol (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
        else MILO_FAIL("Data %s is not Symbol", String(s));
    }
    return STR_TO_SYM((char*)mValue.symbol);
}

Symbol DataNode::ForceSym(const DataArray* a) const {
    DataNode& n = Evaluate();
    if(n.mType == kDataSymbol){
        return STR_TO_SYM(n.mValue.symbol);
    }
    else {
        if(n.mType != kDataString){
            String s;
            n.Print(s, true);
            if(a) MILO_FAIL("Data %s is not String (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
            else MILO_FAIL("Data %s is not String", String(s));
        }
        return Symbol(n.mValue.var->mValue.symbol);
    }
}

const char* DataNode::Str(const DataArray* a) const {
    DataNode& n = Evaluate();
    if(n.mType == kDataSymbol){
        return n.mValue.symbol;
    }
    else {
        if(n.mType != kDataString){
            String s;
            n.Print(s, true);
            if(a) MILO_FAIL("Data %s is not String (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
            else MILO_FAIL("Data %s is not String", String(s));
        }
        return n.mValue.var->mValue.symbol;
    }
}

const char* DataNode::LiteralStr(const DataArray* a) const {
    if(mType == kDataSymbol){
        return mValue.symbol;
    }
    else {
        if(mType != kDataString){
            String s;
            Print(s, true);
            if(a) MILO_FAIL("Data %s is not String (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
            else MILO_FAIL("Data %s is not String", String(s));
        }
        return mValue.var->mValue.symbol;
    }
}

float DataNode::Float(const DataArray* a) const {
    DataNode& n = Evaluate();
    if(n.mType == kDataInt){
        return n.mValue.integer;
    }
    else {
        if(n.mType != kDataFloat){
            String s;
            n.Print(s, true);
            if(a) MILO_FAIL("Data %s is not Float (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
            else MILO_FAIL("Data %s is not Float", String(s));
        }
        return n.mValue.real;
    }
}

float DataNode::LiteralFloat(const DataArray* a) const {
    if(mType == kDataInt){
        return mValue.integer;
    }
    else {
        if(mType != kDataFloat){
            String s;
            Print(s, true);
            if(a) MILO_FAIL("Data %s is not Float (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
            else MILO_FAIL("Data %s is not Float", String(s));
        }
        return mValue.real;
    }
}

DataFunc* DataNode::Func(const DataArray* a) const {
    if(mType != kDataFunc){
        String s;
        Print(s, true);
        if(a) MILO_FAIL("Data %s is not Func (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
        else MILO_FAIL("Data %s is not Func", String(s));
    }
    return mValue.func;
}

// Hmx::Object* DataNode::GetObj(const DataArray* da) const {

// }

DataArray* DataNode::Array(const DataArray* a) const {
    DataNode& n = Evaluate();
    if(n.mType != kDataArray){
        String s;
        n.Print(s, true);
        if(a) MILO_FAIL("Data %s is not Array (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
        else MILO_FAIL("Data %s is not Array", String(s));
    }
    return n.mValue.array;
}

DataArray* DataNode::LiteralArray(const DataArray* a) const {
    if(mType != kDataArray){
        String s;
        Print(s, true);
        if(a) MILO_FAIL("Data %s is not Array (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
        else MILO_FAIL("Data %s is not Array", String(s));
    }
    return mValue.array;
}

DataArray* DataNode::Command(const DataArray* a) const {
    if(mType != kDataCommand){
        String s;
        Print(s, true);
        if(a) MILO_FAIL("Data %s is not Command (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
        else MILO_FAIL("Data %s is not Command", String(s));
    }
    return mValue.array;
}

DataNode* DataNode::Var(const DataArray* a) const {
    if(mType != kDataVar){
        String s;
        Print(s, true);
        if(a) MILO_FAIL("Data %s is not Var (file %s, line %d)", s.c_str(), a->mFile.mStr, (int)a->mLine);
        else MILO_FAIL("Data %s is not Var", String(s));
    }
    return mValue.var;
}

DataNode::DataNode(const DataNode& node){
    mValue = node.mValue;
    mType = node.mType;
    if(mType & kDataArray) mValue.array->AddRef();
}

// extern void* _PoolAlloc(int, int, int);

// // fn_803231CC
// DataNode::DataNode(const char *c) {
//     mValue.array = new (_PoolAlloc(0x10, 0x10, 1)) DataArray(c, strlen(c) + 1);
//     mType = kDataString;
// }

// // fn_8032324C
// DataNode::DataNode(const String &s) {
//     mValue.array =
//         new (_PoolAlloc(0x10, 0x10, 1)) DataArray(s.c_str(), s.length() + 1);
//     mType = kDataString;
// }

DataNode::DataNode(const DataArrayPtr& ptr){
    DataArray* arr = ptr.mData;
    mValue.array = arr;
    arr->AddRef();
    mType = kDataArray;
}

DataNode::DataNode(DataArray *array, DataType type) {
    MILO_ASSERT(array, 0x155);
    mValue.array = array;
    mValue.array->AddRef();
    MILO_ASSERT(type & kDataArray, 0x158);
    mType = type;
}

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
            else obj1 = "";
            obj2 = node.LiteralStr(0);
        }
        else {
            obj1 = LiteralStr(0);
            if(node.mValue.object != 0) obj2 = node.mValue.object->Name();
            else obj2 = "";
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

bool DataNode::operator!=(const DataNode &dn) const {
    return !(*this == dn);
}

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

DataNode& DataNode::operator=(const DataNode& node){
    if(this != &node){
        if(mType & kDataArray) mValue.array->Release();
        mValue = node.mValue;
        mType = node.mType;
        if(mType & kDataArray) mValue.array->AddRef();
    }
    return *this;
}

// // // fn_803239E8
// // bool HasSpace(const char *str) {
// //     while (*str != '\0') {
// //         if (*str++ == ' ')
// //             return true;
// //     }
// //     return false;
// // }

// // TextStream &operator<<(TextStream &ts, const Hmx::Object *obj) {
// //     if (obj != nullptr) {
// //         ts << obj->Name();
// //     } else
// //         ts << "<null>";
// //     return ts;
// // }

// // extern char *DataVarName(const DataNode *);
// // extern Symbol DataFuncName(DataFunc *);

// // // fn_8032364C
// // void DataNode::Print(TextStream &ts, bool b) const {
// //     switch (type) {
// //     case kDataUnhandled:
// //         ts << "kDataUnhandled";
// //         break;
// //     case kDataInt:
// //         ts << value.intVal;
// //         break;
// //     case kDataString:
// //         if (b)
// //             ts << value.symVal->m_string;
// //         else {
// //             ts << "\"";
// //             char *tok = strtok(value.symVal->m_string, "\"");
// //             while (tok != nullptr) {
// //                 ts << tok;
// //                 tok = strtok(nullptr, "\"");
// //                 if (tok != nullptr) {
// //                     ts << "\\q";
// //                     tok[-1] = '\"';
// //                 }
// //             }
// //             ts << "\"";
// //         }
// //         break;
// //     case kDataSymbol:
// //         if (!HasSpace(value.strVal))
// //             ts << value.strVal;
// //         else
// //             ts << "'" << value.strVal << "'";
// //         break;
// //     case kDataGlob:
// //         ts << "<glob " << -value.dataArray->GetNodeCount() << ">";
// //         break;
// //     case kDataFloat:
// //         ts << value.floatVal;
// //         break;
// //     case kDataArray:
// //     case kDataCommand:
// //     case kDataProperty:
// //         value.dataArray->Print(ts, type, b);
// //         break;
// //     case kDataObject:
// //         ts << value.objVal;
// //         break;
// //     case kDataVariable:
// //         ts << '$' << DataVarName(value.varVal);
// //         break;
// //     case kDataFunc:
// //         ts << DataFuncName(value.funcVal);
// //         break;
// //     case kDataDefine:
// //         ts << "\n#define " << value.strVal << "\n";
// //         break;
// //     case kDataUndef:
// //         ts << "\n#undef " << value.strVal << "\n";
// //         break;
// //     case kDataIfdef:
// //         ts << "\n#ifdef " << value.strVal << "\n";
// //         break;
// //     case kDataIfndef:
// //         ts << "\n#ifndef " << value.strVal << "\n";
// //         break;
// //     case kDataAutorun:
// //         ts << "\n#autorun\n";
// //         break;
// //     case kDataElse:
// //         ts << "\n#else\n";
// //         break;
// //     case kDataEndif:
// //         ts << "\n#endif\n";
// //         break;
// //     case kDataInclude:
// //         ts << "\n#include " << value.strVal << "\n";
// //         break;
// //     case kDataMerge:
// //         ts << "\n#merge " << value.strVal << "\n";
// //         break;
// //     }
// // }

// // void DataNode::Save(BinStream &bs) const {
// //     int theType = type;
// //     switch (theType) {
// //     case kDataUnhandled:
// //         theType = kDataInt;
// //         break;
// //     case kDataInt:
// //         theType = kDataUnhandled;
// //         break;
// //     }
// //     bs << (unsigned int)theType;
// //     switch (theType) {
// //     case kDataSymbol:
// //     case kDataIfdef:
// //     case kDataDefine:
// //     case kDataInclude:
// //     case kDataMerge:
// //     case kDataIfndef:
// //     case kDataUndef:
// //         bs << value.strVal;
// //         break;
// //     case kDataFloat:
// //         bs << value.floatVal;
// //         break;
// //     case kDataString:
// //     case kDataGlob:
// //         value.dataArray->SaveGlob(bs, (type - 0x12) == 0);
// //         break;
// //     case kDataArray:
// //     case kDataCommand:
// //     case kDataProperty:
// //         value.dataArray->Save(bs);
// //         break;
// //     case kDataObject:
// //         if (value.objVal != nullptr)
// //             bs << value.objVal->Name();
// //         else
// //             bs << "\0";
// //         break;
// //     case kDataVariable:
// //         bs << DataVarName(value.varVal);
// //         break;
// //     case kDataFunc:
// //         bs << DataFuncName(value.funcVal);
// //         break;
// //     case kDataUnhandled:
// //     case kDataInt:
// //     case kDataElse:
// //     case kDataEndif:
// //     case kDataAutorun:
// //         bs << (unsigned int)value.intVal;
// //         break;
// //     }
// // }
