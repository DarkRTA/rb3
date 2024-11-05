#include "bandtrack/TrackPanel.h"
#include "Track.h"
#include "bandobj/BandScoreboard.h"
#include "bandobj/TrackInstruments.h"
#include "bandobj/TrackPanelDirBase.h"
#include "decomp.h"
#include "game/BandUserMgr.h"
#include "game/Player.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ModifierMgr.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/System.h"
#include "ui/UIPanel.h"
#include "utl/Loader.h"
#include "utl/Messages3.h"
#include "utl/STLHelpers.h"

TrackPanel* TheTrackPanel;

TrackPanel* GetTrackPanel(){
    return TheTrackPanel;
}

TrackPanel::TrackPanel() : mConfig(SystemConfig("track_graphics")), unk4c(2), unk50(this, 0), unk5c(0), unk5d(0), unk5e(0), unk5f(0), unk60(0), unk61(1), unk62(0), mAutoVocals(0),
    unk7c(0), unk80(0), unk84(0), unk88(kConfigInvalid), unk8c(-1.0f) {
    for(int i = 0; i < 5; i++){
        mTrackSlots.push_back(TrackSlot());
    }
    TheTrackPanel = this;
}

TrackPanel::~TrackPanel(){
    CleanUpReloadChecks();
    TheTrackPanel = nullptr;
}

Track* TrackPanel::GetTrack(){
    MILO_ASSERT(mTracks.size() > 0, 0x6A);
    return mTracks.front();
}

Track* TrackPanel::GetTrack(Player* player, bool fail){
    for(int i = 0; i < mTracks.size(); i++){
        if(mTracks[i]->GetPlayer() == player){
            return mTracks[i];
        }
    }
    if(fail){
        MILO_FAIL("Bad player %s in TrackPanel::GetTrack\n", player->GetUser()->UserName());
    }
    return nullptr;
}

Track* TrackPanel::GetTrack(BandUser* user, bool fail){
    for(int i = 0; i < mTracks.size(); i++){
        if(mTracks[i]->GetUser() == user){
            return mTracks[i];
        }
    }
    if(fail){
        MILO_FAIL("Bad user %s in TrackPanel::GetTrack\n", user->UserName());
    }
    return nullptr;
}

DECOMP_FORCEACTIVE(TrackPanel, "Bad DataNode type %d in TrackPanel::GetTrack")

const BandUser* TrackPanel::GetUserFromTrackNum(int index){
    MILO_ASSERT_RANGE(index, 0, mTracks.size(), 0xA0);
    return mTracks[index]->GetBandUser();
}

void TrackPanel::FinishLoad(){
    UIPanel::FinishLoad();
    if(mDir && !unk80){
        unk80 = dynamic_cast<TrackPanelDirBase*>(mDir);
        unk80->SetTrackPanel(this);
        unk50 = unk80->Find<BandScoreboard>("scoreboard", false);
    }
}

void TrackPanel::Enter(){
    Reload();
    UIPanel::Enter();
}

void TrackPanel::Exit(){
    if(GetState() == kUp){
        CleanUpTracks();
        for(int i = 0; i < mTrackSlots.size(); i++){
            TrackSlot& curslot = mTrackSlots[i];
            curslot.mTrack = 0;
            curslot.mInstrument = kInstNone;
        }
        UIPanel::Exit();
    }
}

#define kTrackNumSlots 5

void TrackPanel::UpdateReservedVocalSlot(){
    MILO_ASSERT(mTrackSlots.size() == kTrackNumSlots, 0xF3);
    int u3 = -1;
    for(int i = 0; i < mTrackSlots.size(); i++){
        if(mTrackSlots[i].mInstrument == 3){
            u3 = i;
        }
    }
    if(u3 != -1) unk4c = u3;
    else unk4c = 4;
}

void TrackPanel::CreateTracks(){
    if(!unk5d){
        for(int i = 0; i < mTrackSlots.size(); i++){
            TrackSlot& curslot = mTrackSlots[i];
            curslot.mTrack = 0;
            curslot.mInstrument = kInstNone;
        }
        MILO_ASSERT(mTrackSlots.size() == kTrackNumSlots, 299);

        int maxslot = TheBandUserMgr->MaxSlot();
        for(int i = 0; i <= maxslot; i++){
            BandUser* curuser = TheBandUserMgr->GetUserFromSlot(i);
            if(curuser && curuser->IsParticipating() && curuser->IsFullyInGame()){
                Track* curtrack = NewTrack(curuser);
                curtrack->SetName(MakeString("track%d", i), ObjectDir::Main());
                curtrack->unk58 = i;
                mTracks.push_back(curtrack);
                curuser->mTrack = curtrack;
                TrackSlot& curslot = mTrackSlots[i];
                curslot.mTrack = curtrack;
                curslot.mInstrument = GetTrackInstrument(curuser->GetTrackSym());
            }
        }
        UpdateReservedVocalSlot();
        BandUser* nulluser = TheBandUserMgr->GetNullUser();
        if(nulluser->GetPlayer()){
            int idx = unk4c;
            Track* nulltrack = NewTrack(nulluser);
            nulltrack->SetName(MakeString("track%d", idx), ObjectDir::Main());
            nulltrack->unk58 = idx;
            mTracks.push_back(nulltrack);
            nulluser->mTrack = nulltrack;
            TrackSlot& curslot = mTrackSlots[idx];
            curslot.mTrack = nulltrack;
            curslot.mInstrument = GetTrackInstrument(nulluser->GetTrackSym());
        }
        unk5d = true;
    }
}

void TrackPanel::Reset(){
    CleanUpTracks();
    CreateTracks();
    AssignAndInitTracks();
    unk8c = -1.0f;
    if(unk50) unk50->Reset();
    float secs = TheTaskMgr.Seconds(TaskMgr::b) * 1000.0f;
    Hmx::Object::Handle(on_reset_msg, true);
    unk80->ConfigureTracks(false);
    MetaPerformer::Current();
    unk80->Reset();
    SetMainGoalConfiguration(unk88);
    MainGoalReset();
    TrackerDisplayReset();
    SetSuppressTambourineDisplay(false);
    unk7c = secs;
    unk84 = 0;
    unk5c = true;
    unk5f = false;
    mAutoVocals = TheModifierMgr->IsModifierActive("mod_auto_vocals");
}

void TrackPanel::CleanUpTracks(){
    unk5c = false;
    if(unk5d){
        for(int i = 0; i < mTracks.size(); i++){
            BandUser* user = mTracks[i] ? (BandUser*)mTracks[i]->GetBandUser() : nullptr;
            if(user){
                user->mTrack = nullptr;
                if(user->GetPlayer()){
                    user->GetPlayer()->UnHookTrack();
                }
            }
        }
        DeleteAll(mTracks);
        ClearAndShrink(mTracks); // might be something else idk
        if(unk5d){
            for(int i = 0; i < mTrackSlots.size(); i++){
                unk80->RemoveTrack(i);
            }
            unk5d = false;
        }
    }
}

void TrackPanel::AssignAndInitTracks(){
    for(int i = 0; i < mTrackSlots.size(); i++){
        AssignTrack(i);
    }
}

void TrackPanel::AssignTrack(int idx){
    TrackInstrument inst = mTrackSlots[idx].mInstrument;
    if(inst != kInstNone){
        unk80->AssignTrack(idx, inst, false);
        if(inst != kInstPending){
            Track* track = mTrackSlots[idx].mTrack;
            BandTrack* trackDir = unk80->GetBandTrackInSlot(idx);
            MILO_ASSERT(track && trackDir, 0x1C7);
            MILO_ASSERT(inst == trackDir->GetInstrument(), 0x1C8);
            track->SetDir(trackDir->AsRndDir());
            trackDir->Init(track);
            track->PostInit();
        }
    }
}

void TrackPanel::Reload(){
    if(!IsLoaded()){
        MILO_FAIL("This shouldn't be happening - restart after win goes through same code path as next song.\n");
    }
    if(!IsLoaded()){
        if(!mLoader) Load();
        TheLoadMgr.PollUntilLoaded(mLoader, nullptr);
        CheckIsLoaded();
        if(!unk80) FinishLoad();
    }
    CleanUpTracks();
    unk80->ResetPlayers();
    if(unk50) unk50->Reset();
}