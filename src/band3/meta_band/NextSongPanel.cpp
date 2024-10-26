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
#include "rndobj/Dir.h"
#include "rndobj/Draw.h"
#include "rndobj/Group.h"
#include "ui/UIPanel.h"
#include "utl/MakeString.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

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

void NextSongPanel::IncrementSongReview(int i){
    BandUser* user = TheBandUserMgr->GetUserFromSlot(i);
    MILO_ASSERT(user, 0x106);
    LocalBandUser* localUser = user->GetLocalBandUser();
    MILO_ASSERT(localUser, 0x108);
    MILO_ASSERT(localUser->CanSaveData(), 0x109);
    BandProfile* profile = TheProfileMgr.GetProfileForUser(localUser);
    MILO_ASSERT(profile, 0x10B);
    MetaPerformer* performer = MetaPerformer::Current();
    MILO_ASSERT(performer, 0x10F);
    int songID = TheSongMgr->GetSongIDFromShortName(performer->GetCompletedSong(), true);
    int review = profile->GetSongReview(songID);
    review++;
    if(review > 5) review = 0;
    profile->SetSongReview(songID, review);
    SetReviewDisplayValue(i, review);
}

void NextSongPanel::SetReviewDisplayValue(int slot, int reviewValue){
    RndDir* dir = mDir->Find<RndDir>(MakeString("slot%i", slot), true);
    MILO_ASSERT(dir, 0x131);
    ReviewDisplay* reviewDisplay = dir->Find<ReviewDisplay>("song_review.rvw", true);
    MILO_ASSERT(reviewDisplay, 0x133);
    reviewDisplay->SetValues(reviewValue, true);
}

void NextSongPanel::UpdateScrollArrows(int i, bool b){
    int i7 = unk70[i];
    int i4 = GetMaxScrollPage(i);
    bool n1 = unk80[i];
    bool n2 = unk84[i];
    unk84[i] = i7 != i4;
    unk80[i] = i7;

    if((n1 || b) && !unk80[i]){
        static Message cMsg("trigger_hide_up_arrow", 0);
        cMsg[0] = i;
        Handle(cMsg, true);
    }
    else if((!n1 || b) && unk80[i]) {
        static Message cMsg("trigger_show_up_arrow", 0);
        cMsg[0] = i;
        Handle(cMsg, true);
    }

    if((n2 || b) && !unk84[i]){
        static Message cMsg("trigger_hide_down_arrow", 0);
        cMsg[0] = i;
        Handle(cMsg, true);
    }

    if((!n2 || b) && unk84[i]){
        static Message cMsg("trigger_show_down_arrow", 0);
        cMsg[0] = i;
        Handle(cMsg, true);
    }
}

void NextSongPanel::SetScrollExpandedDetails(int i, int j){
    unk70[i] = j;
    UpdateScrollArrows(i, false);
}

void NextSongPanel::FillExpandedDetails(int slot){
    DataArrayPtr ptr;
    int numDetails = CountOrCreateExpandedDetails(slot, ptr, true);
    ptr->Resize(numDetails);
    int newNumDetails = CountOrCreateExpandedDetails(slot, ptr, false);
    MILO_ASSERT(newNumDetails == numDetails, 0x18B);
    float f1 = 0;
    const DataArray* t = TypeDef();
    MILO_ASSERT(t, 0x19A);
    DataArray* detailTypesArr = t->FindArray(detail_types, true);
    DataArray* defaultTypeArr = t->FindArray(default_type, true);
    unk3c.clear();
    Symbol symb4(gNullStr);
    int i12 = 0;
    for(int n = 0; n < ptr->Size(); n++){
        float fHeight = defaultTypeArr->FindFloat(height);
        float fMarginTop = defaultTypeArr->FindFloat(margin_top);
        float fMarginBottom = defaultTypeArr->FindFloat(margin_bottom);
        float fReqPadOverride = defaultTypeArr->FindFloat(required_padding_override);
        DataArray* arr = ptr->Array(n);
        Symbol dataSym = arr->Sym(0);
        int i9 = f1 / mDetailsPageSize;
        if(dataSym == page_break){
            f1 = mDetailsPageSize * (i9 + 1);
        }
        else {
            if(dataSym == header){
                symb4 = arr->Sym(1);
                i12 = 1;
            }
            DataArray* foundarr = arr->FindArray(dataSym, false);
            if(foundarr){
                foundarr->FindData(height, fHeight, false);
                foundarr->FindData(margin_top, fMarginTop, false);
                foundarr->FindData(margin_bottom, fMarginBottom, false);
                foundarr->FindData(required_padding_override, fReqPadOverride, false);
            }
            float f2 = fMarginBottom + fMarginTop + fHeight;
            if(fReqPadOverride > 0) f2 = fReqPadOverride;
            float f3 = (i9 + 1) * mDetailsPageSize;
            if(f1 + f2 > f3 - mDetailsFooterSize){
                i12++;
                ptr->Insert(numDetails, DataArrayPtr(header_continued, symb4, i12));
                numDetails--;
                f1 = f3;
            }
            else {
                f1 += fMarginTop;
                if(dataSym != pad){
                    SetupDetailLine(arr, slot, foundarr->FindStr(resource_fmt), -f1);
                }
                f1 += fHeight;
                if(numDetails + 1 < ptr->Size()){
                    f1 += fMarginBottom;
                }
            }
        }
    }
    unk60[slot] = f1;
    RndDir* rdir = mDir->Find<RndDir>(MakeString("slot%i", slot), true);
    rdir->SyncObjects();
}