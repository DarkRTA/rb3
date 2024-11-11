#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Str.h"
#include "utl/MakeString.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "obj/DataUtl.h"
#include "obj/DataFunc.h"
#include <map>
#include "decomp.h"

std::map<Symbol, DataNode> gDataVars;
DataNode gEvalNode[8];
int gEvalIndex;

DataNode& DataVariable(Symbol s){
    return gDataVars[s];
}

bool DataVarExists(Symbol s){
    const std::map<Symbol, DataNode>::iterator it = gDataVars.find(s);
    return it != gDataVars.end();
}

const char* DataVarName(const DataNode* node){
    for(std::map<Symbol, DataNode>::iterator it = gDataVars.begin(); it != gDataVars.end(); it++ ){
        if((&it->second) == node){
            return it->first.Str();
        }
    }
    return "<null>";
}

bool DataNode::CompatibleType(DataType ty) const {
    DataType thisType = mType;
    if(thisType == ty) return true;
    switch (thisType) {
        case kDataInt:
            return ty == kDataFloat;
        case kDataSymbol:
            return ty == kDataString || ty == kDataObject;
        case kDataString:
            return ty == kDataObject;
        default:
            return false;
    }
    return true;
}

DataNode& UseQueue(const DataNode& node){
    int i;
    gEvalNode[gEvalIndex] = node;
    i = gEvalIndex;
    gEvalIndex = gEvalIndex + 1 & 7;
    return gEvalNode[i];
}

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

int DataNode::Int(const DataArray* source) const {
    DataNode& n = Evaluate();
#ifdef MILO_DEBUG
    if(n.mType != kDataInt){
        String s;
        n.Print(s, true);
        if(source) MILO_FAIL("Data %s is not Int (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
        else MILO_FAIL("Data %s is not Int", String(s));
    }
#endif
    return n.mValue.integer;
}

int DataNode::LiteralInt(const DataArray* source) const {
#ifdef MILO_DEBUG
    if(mType != kDataInt){
        String s;
        Print(s, true);
        if(source) MILO_FAIL("Data %s is not Int (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
        else MILO_FAIL("Data %s is not Int", String(s));
    }
#endif
    return mValue.integer;
}

Symbol DataNode::Sym(const DataArray* source) const {
    DataNode& n = Evaluate();
#ifdef MILO_DEBUG
    if(n.mType != kDataSymbol){
        String s;
        n.Print(s, true);
        if(source) MILO_FAIL("Data %s is not Symbol (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
        else MILO_FAIL("Data %s is not Symbol", String(s));
    }
#endif
    return STR_TO_SYM(n.mValue.symbol);
}

Symbol DataNode::LiteralSym(const DataArray* source) const {
#ifdef MILO_DEBUG
    if(mType != kDataSymbol){
        String s;
        Print(s, true);
        if(source) MILO_FAIL("Data %s is not Symbol (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
        else MILO_FAIL("Data %s is not Symbol", String(s));
    }
#endif
    return STR_TO_SYM(mValue.symbol);
}

Symbol DataNode::ForceSym(const DataArray* source) const {
    DataNode& n = Evaluate();
    if(n.mType == kDataSymbol){
        return STR_TO_SYM(n.mValue.symbol);
    }
    else {
#ifdef MILO_DEBUG
        if(n.mType != kDataString){
            String s;
            n.Print(s, true);
            if(source) MILO_FAIL("Data %s is not String (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
            else MILO_FAIL("Data %s is not String", String(s));
        }
#endif
        return Symbol(n.mValue.var->mValue.symbol);
    }
}

const char* DataNode::Str(const DataArray* source) const {
    DataNode& n = Evaluate();
    if(n.mType == kDataSymbol){
        return n.mValue.symbol;
    }
    else {
#ifdef MILO_DEBUG
        if(n.mType != kDataString){
            String s;
            n.Print(s, true);
            if(source) MILO_FAIL("Data %s is not String (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
            else MILO_FAIL("Data %s is not String", String(s));
        }
#endif
        return n.mValue.var->mValue.symbol;
    }
}

const char* DataNode::LiteralStr(const DataArray* source) const {
    if(mType == kDataSymbol){
        return mValue.symbol;
    }
    else {
#ifdef MILO_DEBUG
        if(mType != kDataString){
            String s;
            Print(s, true);
            if(source) MILO_FAIL("Data %s is not String (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
            else MILO_FAIL("Data %s is not String", String(s));
        }
#endif
        return mValue.var->mValue.symbol;
    }
}

#ifdef MILO_DEBUG
DECOMP_FORCEACTIVE(DataNode,
    "Data %s is not Glob (file %s, line %d)",
    "Data %s is not Glob"
)
#endif

float DataNode::Float(const DataArray* source) const {
    DataNode& n = Evaluate();
    if(n.mType == kDataInt){
        return n.mValue.integer;
    }
    else {
#ifdef MILO_DEBUG
        if(n.mType != kDataFloat){
            String s;
            n.Print(s, true);
            if(source) MILO_FAIL("Data %s is not Float (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
            else MILO_FAIL("Data %s is not Float", String(s));
        }
#endif
        return n.mValue.real;
    }
}

float DataNode::LiteralFloat(const DataArray* source) const {
    if(mType == kDataInt){
        return mValue.integer;
    }
    else {
#ifdef MILO_DEBUG
        if(mType != kDataFloat){
            String s;
            Print(s, true);
            if(source) MILO_FAIL("Data %s is not Float (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
            else MILO_FAIL("Data %s is not Float", String(s));
        }
#endif
        return mValue.real;
    }
}

DataFunc* DataNode::Func(const DataArray* source) const {
#ifdef MILO_DEBUG
    if(mType != kDataFunc){
        String s;
        Print(s, true);
        if(source) MILO_FAIL("Data %s is not Func (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
        else MILO_FAIL("Data %s is not Func", String(s));
    }
#endif
    return mValue.func;
}

Hmx::Object* DataNode::GetObj(const DataArray* source) const {
    DataNode& n = Evaluate();
    if(n.mType == kDataObject) return n.mValue.object;
    else {
        const char* str = n.LiteralStr(source);
        Hmx::Object* ret = 0;
        if(*str != '\0'){
            ret = gDataDir->FindObject(str, true);
#ifdef MILO_DEBUG
            if(ret == 0){
                const char* msg;
                if(PathName(gDataDir) != 0) msg = PathName(gDataDir);
                else msg = "**no file**";
                TheDebug.Fail(MakeString(kNotObjectMsg, str, msg));
            }
#endif

        }
        return ret;
    }
}

DataArray* DataNode::Array(const DataArray* source) const {
    DataNode& n = Evaluate();
#ifdef MILO_DEBUG
    if(n.mType != kDataArray){
        String s;
        n.Print(s, true);
        if(source) MILO_FAIL("Data %s is not Array (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
        else MILO_FAIL("Data %s is not Array", String(s));
    }
#endif
    return n.mValue.array;
}

DataArray* DataNode::LiteralArray(const DataArray* source) const {
#ifdef MILO_DEBUG
    if(mType != kDataArray){
        String s;
        Print(s, true);
        if(source) MILO_FAIL("Data %s is not Array (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
        else MILO_FAIL("Data %s is not Array", String(s));
    }
#endif
    return mValue.array;
}

#ifdef MILO_DEBUG
DECOMP_FORCEACTIVE(DataNode,
    "Data %s is not Property (file %s, line %d)",
    "Data %s is not Property"
)
#endif

DataArray* DataNode::Command(const DataArray* source) const {
#ifdef MILO_DEBUG
    if(mType != kDataCommand){
        String s;
        Print(s, true);
        if(source) MILO_FAIL("Data %s is not Command (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
        else MILO_FAIL("Data %s is not Command", String(s));
    }
#endif
    return mValue.array;
}

DataNode* DataNode::Var(const DataArray* source) const {
#ifdef MILO_DEBUG
    if(mType != kDataVar){
        String s;
        Print(s, true);
        if(source) MILO_FAIL("Data %s is not Var (file %s, line %d)", s.c_str(), source->mFile.mStr, (int)source->mLine);
        else MILO_FAIL("Data %s is not Var", String(s));
    }
#endif
    return mValue.var;
}

DataNode::DataNode(const DataNode& node){
    mValue = node.mValue;
    mType = node.mType;
    if(mType & kDataArray) mValue.array->AddRef();
}

DataNode::DataNode(const char* c){
    mValue.array = new DataArray(c, strlen(c) + 1);
    mType = kDataString;
}

DataNode::DataNode(const String& s){
    mValue.array = new DataArray(s.c_str(), s.length() + 1);
    mType = kDataString;
}

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
            obj2 = node.LiteralStr();
        }
        else {
            obj1 = LiteralStr();
            if(node.mValue.object != 0) obj2 = node.mValue.object->Name();
            else obj2 = "";
        }
        return strcmp(obj1, obj2) == 0;
    }
    else if(mType == kDataString || node.mType == kDataString){
        return strcmp(LiteralStr(), node.LiteralStr()) == 0;
    }
    else if(mType == kDataFloat || node.mType == kDataFloat){
        return LiteralFloat() == node.LiteralFloat();
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
    if(&node != this){
        if(mType & kDataArray) mValue.array->Release();
        mValue = node.mValue;
        mType = node.mType;
        if(mType & kDataArray) mValue.array->AddRef();
    }
    return *this;
}

inline bool HasSpace(const char *str) {
    while (*str != '\0') {
        if (*str++ == ' ')
            return true;
    }
    return false;
}

void DataNode::Print(TextStream& ts, bool b) const {
    switch(mType){
        case kDataUnhandled:
            ts << "kDataUnhandled";
            break;
        case kDataInt:
            ts << mValue.integer;
            break;
        case kDataString:
            if(b) ts << mValue.var->mValue.symbol;
            else {
                ts << "\"";
                char* tok = strtok((char*)mValue.var->mValue.symbol, "\"");
                while(tok){
                    ts << tok;
                    tok = strtok(0, "\"");
                    if(tok){
                        ts << "\\q";
                        tok[-1] = '\"';
                    }
                }
                ts << "\"";
            }
            break;
        case kDataSymbol:
            if(!HasSpace(mValue.symbol))
                ts << mValue.symbol;
            else ts << "'" << mValue.symbol << "'";
            break;
        case kDataGlob:
            ts << "<glob " << -mValue.array->Size() << ">";
            break;
        case kDataFloat:
            ts << mValue.real;
            break;
        case kDataArray:
        case kDataCommand:
        case kDataProperty:
            mValue.array->Print(ts, mType, b);
            break;
        case kDataObject:
            ts << mValue.object;
            break;
        case kDataVar:
            ts << '$' << DataVarName(mValue.var);
            break;
        case kDataFunc:
            ts << DataFuncName(mValue.func);
            break;
        case kDataDefine:
            ts << "\n#define " << mValue.symbol << "\n";
            break;
        case kDataUndef:
            ts << "\n#undef " << mValue.symbol << "\n";
            break;
        case kDataIfdef:
            ts << "\n#ifdef " << mValue.symbol << "\n";
            break;
        case kDataIfndef:
            ts << "\n#ifndef " << mValue.symbol << "\n";
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
            ts << "\n#include " << mValue.symbol << "\n";
            break;
        case kDataMerge:
            ts << "\n#merge " << mValue.symbol << "\n";
            break;
    }
}

bool DataNode::PrintUnused(TextStream& ts, bool b) const {
    MILO_WARN("Enable PRINT_UNUSED in Data.h to utilize DataNode::PrintUnused()");
    return false;
}

void DataNode::Save(BinStream& d) const {
    int theType = mType;
    switch (theType) {
        case kDataUnhandled:
            theType = kDataInt;
            break;
        case kDataInt:
            theType = kDataUnhandled;
            break;
    }
    d << theType;
    switch (theType) {
        case kDataSymbol:
        case kDataIfdef:
        case kDataDefine:
        case kDataInclude:
        case kDataMerge:
        case kDataIfndef:
        case kDataUndef:
            d << mValue.symbol;
            break;
        case kDataFloat:
            d << mValue.real;
            break;
        case kDataString:
        case kDataGlob:
            mValue.array->SaveGlob(d, (mType - 0x12) == 0);
            break;
        case kDataArray:
        case kDataCommand:
        case kDataProperty:
            mValue.array->Save(d);
            break;
        case kDataObject:
            if(mValue.object)
                d << mValue.object->Name();
            else d << "";
            break;
        case kDataVar:
            d << DataVarName(mValue.var);
            break;
        case kDataFunc:
            d << DataFuncName(mValue.func);
            break;
        case kDataUnhandled:
        case kDataInt:
        case kDataElse:
        case kDataEndif:
        case kDataAutorun:
            d << mValue.integer;
            break;
        default:
            MILO_FAIL("Unrecognized node type: %x", mType);
            break;
    }
}

inline BinStream& operator>>(BinStream& bs, DataType& ty){
    bs.ReadEndian(&ty, sizeof(ty));
    return bs;
}

void DataNode::Load(BinStream& d){
    static char buf[128];
    d >> mType;
    switch(mType){
        case kDataFunc: {
            Symbol sym;
            d >> sym;
            const std::map<Symbol, DataFunc*>::iterator it = gDataFuncs.find(sym);
            if(it == gDataFuncs.end()){
            #ifdef MILO_DEBUG
                TheDebug.Fail(MakeString("Couldn't bind %s", sym));
            #endif
            }
            mValue.func = it->second;
            break;
        }
        case kDataSymbol:
        case kDataIfdef:
        case kDataDefine:
        case kDataInclude:
        case kDataMerge:
        case kDataIfndef:
        case kDataUndef: {
            Symbol sym;
            d >> sym;
            mValue.symbol = sym.Str();
            break;
        }
        case kDataFloat:
            d >> mValue.real;
            break;
        case kDataString:
        case kDataGlob:
            mValue.array = new DataArray(0);
            mValue.array->LoadGlob(d, (mType - 0x12) == 0);
            break;
        case kDataArray:
        case kDataCommand:
        case kDataProperty:
            mValue.array = new DataArray(0);
            mValue.array->Load(d);
            break;
        case kDataObject:
            d.ReadString(buf, 0x80);
            mValue.object = gDataDir->FindObject(buf, true);
            #ifdef MILO_DEBUG
            if(mValue.object == 0 && *buf){
                TheDebug.Notify(MakeString("Couldn't find %s from %s", buf, gDataDir->Name()));
            }
            #endif
            break;
        case kDataVar: {
            Symbol sym;
            d >> sym;
            mValue.var = &gDataVars[sym];
            break;
        }
        case kDataUnhandled:
            mType = kDataInt;
            d >> mValue.integer;
            break;
        case kDataInt:
            mType = kDataUnhandled;
            d >> mValue.integer;
            break;
        case kDataElse:
        case kDataEndif:
        case kDataAutorun:
            d >> mValue.integer;
            break;
        default:
        #ifdef MILO_DEBUG
            TheDebug.Fail(MakeString("Unrecognized node type: %x", mType));
        #endif
            break;
    }
}
