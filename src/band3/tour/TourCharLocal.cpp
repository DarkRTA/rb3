#include "tour/TourCharLocal.h"
#include "bandobj/BandCharDesc.h"
#include "meta_band/BandProfile.h"
#include "meta_band/ProfileMgr.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "tour/TourSavable.h"

TourCharLocal::TourCharLocal(){

}

TourCharLocal::~TourCharLocal(){
    for(std::map<int, PatchDir*>::iterator it = unk4c.begin(); it != unk4c.end(); ++it){
        RELEASE(it->second);
    }
    unk4c.clear();
}

void TourCharLocal::GenerateGUID(){ mGuid.Generate(); }

void TourCharLocal::SetFinalized(bool final){
    mIsFinalized = final;
    SetDirty(true, 3);
}

void TourCharLocal::SetCharacterName(const char* name){
    if(mName != name){
        mName = name;
        SetDirty(true, 7);
    }
}

void TourCharLocal::SetDirty(bool dirty, int mask){
    TourSavable::SetDirty(dirty, mask);
}

RndTex* TourCharLocal::GetTexAtPatchIndex(int i, bool b) const {
    BandProfile* profile = TheProfileMgr.GetProfileForChar(this);
    if(profile) return profile->GetTexAtPatchIndex(i);
    else return nullptr;
}

void TourCharLocal::SaveDb(BinStream& bs){
    BandProfile* pProfile = TheProfileMgr.GetProfileForChar(this);
    MILO_ASSERT(pProfile, 0x55);
    BandCharDesc* pBandCharDesc = GetBandCharDesc();
    MILO_ASSERT(pBandCharDesc, 0x59);
    pBandCharDesc->Save(bs);
    int numpatches = pBandCharDesc->mPatches.size();
    std::set<int> db;
    for(int i = 0; i < numpatches; i++){
        BandCharDesc::Patch& patch = pBandCharDesc->mPatches[i];
        int key = patch.mTexture;
        if(key >= 0){
            std::set<int>::iterator it = db.find(key);
            if(it == db.end()){
                PatchDir* pPatchDir = pProfile->mPatches[key];
                MILO_ASSERT(pPatchDir, 0x6F);
                pPatchDir->SaveRemote(bs);
                db.insert(key);
            }
        }   
    }
}

BEGIN_HANDLERS(TourCharLocal)
    HANDLE_SUPERCLASS(TourChar)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x9A)
END_HANDLERS