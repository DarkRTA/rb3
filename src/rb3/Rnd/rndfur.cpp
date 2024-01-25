#include "rndfur.hpp"

RndFur::RndFur(){

}

void RndFur::Copy(const Hmx::Object* obj, Hmx::Object::CopyType ty){
    dynamic_cast<const RndFur*>(obj);
    Hmx::Object::Copy(obj, ty);
}

void RndFur::Save(BinStream& bs){

}

extern char* PathName(const Hmx::Object*);

DataNode RndFur::Handle(DataArray* da, bool b){
    Symbol sym = da->GetSymAtIndex(1);
    {
    DataNode root = Hmx::Object::Handle(da, false);
    if(root.GetType() != kDataUnhandled){
        return DataNode(root);
    }
    }
    if(b) PathName(this);
    return DataNode(kDataUnhandled, 0);
}

bool RndFur::SyncProperty(DataNode& node, DataArray* da, int i, PropOp op){
    if(da->GetNodeCount() == i){
        return true;
    }
    else {
        Symbol b = da->GetSymAtIndex(i);
        return false;
    }
}

RndFur::~RndFur(){

}

Symbol RndFur::ClassName() const {
    return StaticClassName();
}

extern DataArray* SystemConfig(Symbol, Symbol, Symbol);

void RndFur::SetType(Symbol s){
    static DataArray* types = SystemConfig(StaticClassName(), "types", "objects");
    if(s.IsNull()){
        SetTypeDef(nullptr);
    }
    else {
        DataArray* found = types->FindArray(s, false);
        if(found){
            SetTypeDef(found);
        }
        else {
            PathName(this);
            ClassName();
            SetTypeDef(nullptr);
        }
    }
}