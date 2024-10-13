#include "tour/TourCharRemote.h"
#include "game/BandUserMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "tour/TourChar.h"

TourCharRemote::TourCharRemote(){

}

TourCharRemote::~TourCharRemote(){

}

void TourCharRemote::SyncLoad(BinStream& bs){
    bs >> mName;
    bs >> mGuid;
    mBandCharDesc->Load(bs);
}

RndTex* TourCharRemote::GetTexAtPatchIndex(int i, bool b) const {
    BandUser* user = TheBandUserMgr->GetUserWithChar(this);
    MILO_ASSERT(user, 0x38);
    if(b && !ThePlatformMgr.CanSeeUserCreatedContent(user->mOnlineID)) return nullptr;
    else for(int n = 0; n < unk4c.size(); n++){
        if(i == unk4c[n].index){
            return unk4c[n].patch;
        }
    }
    return nullptr;
}

BEGIN_HANDLERS(TourCharRemote)
    HANDLE_SUPERCLASS(TourChar)
    HANDLE_CHECK(0x4A)
END_HANDLERS