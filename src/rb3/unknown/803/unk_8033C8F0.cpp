#include "hmx/object.hpp"
#include "data.hpp"
#include "textfile.hpp"
#include "formatstring.hpp"
#include "debug.hpp"

Symbol TextFile::ClassName() const {
    return StaticClassName();
}

TextFile::~TextFile(){
    if(unk20 != 0){
        delete this;
    }
}

void TextFile::SetName(const char* c, ObjectDir* dir){
    Hmx::Object::SetName(c, dir);
    delete this;
    unk20 = 0;
}

DataNode TextFile::OnPrint(DataArray* da){
    if(unk20 != 0){
        for(int i = 2; i < da->GetNodeCount(); i++){
            DataNode* eval = EvaluateNodeAtIndex(da, i);
            eval->Print(*this, true);
        }
    }
    return DataNode(0);
}

DataNode TextFile::OnPrintf(DataArray* da){
    if(unk20 != 0){
        FormatString fs(da->GetStrAtIndex(2));
        for(int i = 3; i < da->GetNodeCount(); i++){
            fs << *EvaluateNodeAtIndex(da, i);
        }
        Print(fs.Str());
    }
    return DataNode(0);
}

extern Symbol SymPrint, SymReflect;
extern char* PathName(const Hmx::Object*);

DataNode TextFile::Handle(DataArray* da, bool b){
    Symbol match = match;
    match = da->GetSymAtIndex(1);
    if(match == SymPrint){
        DataNode print = OnPrint(da);
        if(print.GetType() != kDataUnhandled) return DataNode(print);
    }
    static Symbol SymPrintf("printf");
    if(match == SymPrintf){
        DataNode node_printf = OnPrintf(da);
        if(node_printf.GetType() != kDataUnhandled) return DataNode(node_printf);
    }
    if(match == SymReflect){
        DataNode ref = OnReflect(da);
        if(ref.GetType() != kDataUnhandled) return DataNode(ref);
    }
    // if no match, fall to here
    {
    DataNode base = Hmx::Object::Handle(da, false);
    if(base.GetType() != kDataUnhandled) return DataNode(base);
    }
    if(b) PathName(this);
    return DataNode(kDataUnhandled, 0);
}

extern DataArray* SystemConfig(Symbol, Symbol, Symbol);

void TextFile::SetType(Symbol s){
    static DataArray* types = SystemConfig(StaticClassName(), "types", "objects");
    if(s.IsNull()) SetTypeDef(nullptr);
    else {
        DataArray* found = types->FindArray(s, false);
        if(found != nullptr){
            SetTypeDef(found);
        }
        else {
            PathName(this);
            ClassName();
            SetTypeDef(nullptr);
        }
    }
}

extern DataArray* SystemConfig(Symbol);

void InitObject(Hmx::Object* obj){
    static DataArray* objects = SystemConfig("objects");
    static Symbol initSym("init");
    obj->ClassName();
    DataArray* found1 = objects->FindArray(initSym, true);
    DataArray* found2 = found1->FindArray(initSym, false);
    if(found2 != nullptr)
        found2->ExecuteScript(1, obj, nullptr, 1);
}

char* PathName(const Hmx::Object* obj){
    if(obj != nullptr) ((Hmx::Object*)obj)->FindPathName();
    else return "NULL Object";
}

const char* SafeName(Hmx::Object* obj){
    if(obj != nullptr) return obj->Name();
    else return "NULL";
}