#include "meta_band/CharSync.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/CharData.h"
#include "meta_band/ProfileMgr.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

CharSync* TheCharSync;

void CharSync::Init(BandUserMgr* mgr){
    mgr = mgr ? mgr : TheBandUserMgr;
    TheCharSync = new CharSync(mgr);
    TheCharSync->SetName("char_sync", ObjectDir::Main());
}

CharSync::CharSync(BandUserMgr* mgr) : mUserMgr(mgr) {
    MILO_ASSERT(mUserMgr, 0x35);
    TheProfileMgr.AddSink(this, PrimaryProfileChangedMsg::Type());
    TheProfileMgr.AddSink(this, ProfileChangedMsg::Type());
}

CharSync::~CharSync(){
    TheProfileMgr.RemoveSink(this, ProfileChangedMsg::Type());
    TheProfileMgr.RemoveSink(this, PrimaryProfileChangedMsg::Type());
}

#pragma push
#pragma dont_inline on
void CharSync::UpdateCharCache(){
    // whoops depends on BandUI
}
#pragma pop

DataNode CharSync::OnMsg(const PrimaryProfileChangedMsg&){
    UpdateCharCache();
    return 1;
}

DataNode CharSync::OnMsg(const ProfileChangedMsg& msg){
    BandProfile* p = msg.GetProfile();
    if(p){
        LocalBandUser* u = msg.GetProfile()->GetLocalBandUser();
        CharData* data = nullptr;
        if(p) data = p->GetLastCharUsed();
        if(data && TheBandUserMgr->IsCharAvailable(data)){
            u->SetChar(data);
        }
    }
    UpdateCharCache();
    return 1;
}

BEGIN_HANDLERS(CharSync)
    HANDLE_ACTION(update_char_cache, UpdateCharCache())
    HANDLE_MESSAGE(PrimaryProfileChangedMsg)
    HANDLE_MESSAGE(ProfileChangedMsg)
    HANDLE_CHECK(0x15F)
END_HANDLERS