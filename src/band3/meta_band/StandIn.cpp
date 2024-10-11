#include "meta_band/StandIn.h"

StandIn::StandIn() : mName(gNullStr) {
    mSaveSizeMethod = &SaveSize;
}

StandIn::~StandIn(){

}

void StandIn::SetNone(){
    mName = gNullStr;
    mGuid.Clear();
}

void StandIn::SetName(Symbol name){
    mName = name;
    mGuid.Clear();
}

void StandIn::SetGuid(HxGuid guid){
    mName = gNullStr;
    mGuid = guid;
}

bool StandIn::IsNone() const {
    if(mGuid.IsNull() && mName.Null()) return true;
    else return false;
}

bool StandIn::IsPrefabCharacter() const {
    if(mGuid.IsNull() && !mName.Null()) return true;
    else return false;
}

bool StandIn::IsCustomCharacter() const {
    if(!mGuid.IsNull() && mName.Null()) return true;
    else return false;
}

int StandIn::SaveSize(int){
    int size = HxGuid::SaveSize() + 0x32;
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "StandIn", size);
    }
    return size;
}

void StandIn::SaveFixed(FixedSizeSaveableStream& bs) const {
    FixedSizeSaveable::SaveFixedSymbol(bs, mName);
    bs << mGuid;
}

void StandIn::LoadFixed(FixedSizeSaveableStream& bs, int){
    FixedSizeSaveable::LoadFixedSymbol(bs, mName);
    bs >> mGuid;
}