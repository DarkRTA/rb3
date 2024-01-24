#include "rndanimatable.hpp"
#include "symbols.hpp"

RndAnimatable::RndAnimatable(){
    frame = 0.0f;
    rate = 0;
}

void RndAnimatable::Save(BinStream& bs){

}

extern char* PathName(const Hmx::Object*);

DataNode RndAnimatable::Handle(DataArray* da, bool b){
    Symbol sym = da->GetSymAtIndex(1);
    if(sym == SymSetFrame){
        SetFrame(da->GetFloatAtIndex(2), 1.0f);
        return DataNode(0);
    }
    if(sym == SymFrame){
        return DataNode(frame);
    }
    if(sym == SymSetKey){
        SetKey(da->GetFloatAtIndex(2));
        return DataNode(0);
    }
    if(sym == SymEndFrame){
        return DataNode(EndFrame());
    }
    if(sym == SymStartFrame){
        return DataNode(StartFrame());
    }
    if(sym == SymAnimate){
        DataNode node = OnAnimate(da);
        if(node.GetType() != kDataUnhandled) return DataNode(node);
    }
    if(sym == SymStopAnimation){
        StopAnimation();
        return DataNode(0);
    }
    if(sym == SymIsAnimating){
        return DataNode(IsAnimating());
    }
    if(sym == SymConvertFrames){
        DataNode node = OnConvertFrames(da);
        if(node.GetType() != kDataUnhandled) return DataNode(node);
    }
    if(b) PathName(this);
    return DataNode(kDataUnhandled, 0);
}

extern DataArray* SystemConfig(Symbol, Symbol, Symbol);

void RndAnimatable::SetType(Symbol s){
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

Symbol RndAnimatable::StaticClassName(){
    static Symbol name("Anim");
    return name;
}

Symbol RndAnimatable::ClassName() const {
    return StaticClassName();
}