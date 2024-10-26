#include "meta_band/NextSongPanel.h"
#include "AppInlineHelp.h"
#include "bandobj/ReviewDisplay.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Game.h"
#include "game/Player.h"
#include "meta_band/BandProfile.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMgr.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/User.h"
#include "rndobj/Dir.h"
#include "rndobj/Draw.h"
#include "rndobj/Group.h"
#include "ui/UIPanel.h"
#include "utl/MakeString.h"
#include "utl/Symbols2.h"

void NextSongPanel::Enter(){
    unk98 = false;
    for(int i = 0; i < 4; i++){
        if(TheGame->IsActiveUser(TheBandUserMgr->GetUserFromSlot(i))){
            DeterminePerformanceAwards(i);
        }
    }
    UIPanel::Enter();
    mEnterTime = TheTaskMgr.UISeconds();
    for(int i = 0; i < 4; i++){
        unk70[i] = 0;
        unk84[i] = 0;
        unk80[i] = 0;
        HideAllDetailComponents(i);
        if(TheGame->IsActiveUser(TheBandUserMgr->GetUserFromSlot(i))){
            FillExpandedDetails(i);
        }
        ScrollExpandedDetails(i, 0, true);
    }
}

void NextSongPanel::Exit(){
    UIPanel::Exit();
    unk9c.clear();
}

bool NextSongPanel::Exiting() const {
    bool ret = true;
    if(!UIPanel::Exiting()){
        float mintimeprop = Property("min_time", true)->Float();
        float uisecs = TheTaskMgr.UISeconds();
        if(mintimeprop > uisecs - mEnterTime) ret = true;
        else ret = false;
    }
    return ret;
}

void NextSongPanel::FinishLoad(){
    UIPanel::FinishLoad();
    const DataArray* t = TypeDef();
    MILO_ASSERT(t, 0x5A);
    mDetailsPageSize = t->FindFloat(details_page_size);
    mDetailsFooterSize = t->FindFloat(details_footer_size);
    mDetailsScrollStep = t->FindFloat(details_scroll_step);
    const char* scrollgrpstr = t->FindStr(details_scroll_group);
    for(int i = 0; i < 4; i++){
        RndDir* rdir = mDir->Find<RndDir>(MakeString("slot%i", i), true);
        mScrollGroups[i] = rdir->Find<RndGroup>(scrollgrpstr, true);
        int hashtablesize = rdir->HashTableSize() + 0x100;
        int strtablesize = rdir->StrTableSize();
        rdir->Reserve(hashtablesize, strtablesize + 0x980);
    }
}

int NextSongPanel::GetMaxScrollPage(int i){
    return unk60[i] / mDetailsPageSize;
}

void NextSongPanel::DeterminePerformanceAwards(int i){
    BandUser* user = TheBandUserMgr->GetUserFromSlot(i);
    MILO_ASSERT(user, 0xAA);
    MILO_ASSERT(TheGame->IsActiveUser(user), 0xAB);
    Player* player = user->mPlayer;
    MILO_ASSERT(player, 0xAD);
    player->DeterminePerformanceAwards();
}

void NextSongPanel::HideAllDetailComponents(int i){
    const DataArray* t = TypeDef();
    MILO_ASSERT(t, 0xB6);
    const char* parentstr = t->FindStr(detail_component_parent);
    RndDir* rdir = mDir->Find<RndDir>(MakeString("slot%i", i), true);
    RndGroup* grp = rdir->Find<RndGroup>(parentstr, true);
    for(ObjPtrList<Hmx::Object, ObjectDir>::iterator it = grp->mObjects.begin(); it != grp->mObjects.end(); ++it){
        RndDrawable* d = dynamic_cast<RndDrawable*>(*it);
        if(d) d->SetShowing(false);
    }
}

bool NextSongPanel::CanChangeSongReview(int i) const {
    BandUser* user = TheBandUserMgr->GetUserFromSlot(i);
    MILO_ASSERT(user, 199);
    LocalBandUser* localUser = user->GetLocalBandUser();
    MILO_ASSERT(localUser, 0xCA);
    return localUser->CanSaveData();
}

void NextSongPanel::InitializeSongReviewDisplay(int i){
    RndDir* dir = mDir->Find<RndDir>(MakeString("slot%i", i), true);
    MILO_ASSERT(dir, 0xD3);
    ReviewDisplay* reviewDisplay = dir->Find<ReviewDisplay>("song_review.rvw", true);
    MILO_ASSERT(reviewDisplay, 0xD5);
    AppInlineHelp* reviewHelp = dir->Find<AppInlineHelp>("review.ihp", true);
    MILO_ASSERT(reviewHelp, 0xD8);
    BandUser* user = TheBandUserMgr->GetUserFromSlot(i);
    if(!user || !user->IsLocal()){
        reviewDisplay->SetShowing(false);
        reviewHelp->SetShowing(false);
    }
    else {
        LocalBandUser* localUser = user->GetLocalBandUser();
        MILO_ASSERT(localUser, 0xE3);
        if(TheGame->IsActiveUser(user) && localUser->CanSaveData()){
            reviewDisplay->SetShowing(true);
            reviewHelp->SetShowing(true);
            reviewHelp->SetOverrideUser(localUser);
            MetaPerformer* performer = MetaPerformer::Current();
            MILO_ASSERT(performer, 0xEF);
            int songID = TheSongMgr->GetSongIDFromShortName(performer->GetCompletedSong(), true);
            BandProfile* profile = TheProfileMgr.GetProfileForUser(localUser);
            MILO_ASSERT(profile, 0xF5);
            reviewDisplay->SetValues(profile->GetSongReview(songID), false);
        }
        else {
            reviewDisplay->SetShowing(false);
            reviewHelp->SetShowing(false);
        }
    }
}
