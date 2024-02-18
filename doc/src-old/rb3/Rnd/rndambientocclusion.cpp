#include "Rnd/rndambientocclusion.hpp"

RndAmbientOcclusion::RndAmbientOcclusion(){

}

void RndAmbientOcclusion::Save(BinStream& bs){

}

void RndAmbientOcclusion::Copy(const Hmx::Object* obj, Hmx::Object::CopyType ty){
    Hmx::Object::Copy(obj, ty);
}

extern char* PathName(const Hmx::Object*);

DataNode RndAmbientOcclusion::Handle(DataArray* da, bool b){
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

bool RndAmbientOcclusion::SyncProperty(DataNode& node, DataArray* da, int i, PropOp op){
    if(da->GetNodeCount() == i){
        return true;
    }
    else {
        Symbol b = da->GetSymAtIndex(i);
        return false;
    }
}

RndAmbientOcclusion::~RndAmbientOcclusion(){

}

Symbol RndAmbientOcclusion::ClassName() const {
    return StaticClassName();
}

extern DataArray* SystemConfig(Symbol, Symbol, Symbol);

void RndAmbientOcclusion::SetType(Symbol s){
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
