#include "ProfileAssets.h"

ProfileAssets::ProfileAssets(BandProfile*) {
    ProfileAssets::Clear();
    ProfileAssets::SaveSize(0);
}

ProfileAssets::~ProfileAssets(){
    
}

void ProfileAssets::Clear() {
    mSymbols.clear();
}

void ProfileAssets::AddAsset(Symbol){}
bool ProfileAssets::HasAsset(Symbol) const{}
bool ProfileAssets::IsNew(Symbol) const{}
void ProfileAssets::SetOld(Symbol){}
void ProfileAssets::SaveSize(int){}