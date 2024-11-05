#include "bandtrack/TrackPanel.h"
#include "Track.h"
#include "bandobj/BandScoreboard.h"
#include "bandobj/TrackInstruments.h"
#include "bandobj/TrackPanelDirBase.h"
#include "bandobj/VocalTrackDir.h"
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
#include "rndobj/EventTrigger.h"
#include "ui/UIPanel.h"
#include "utl/Loader.h"
#include "utl/Messages3.h"
#include "utl/STLHelpers.h"

TrackPanel* TheTrackPanel;

TrackPanel* GetTrackPanel(){
    return TheTrackPanel;
}

TrackPanel::TrackPanel() : mConfig(SystemConfig("track_graphics")), mReservedVocalSlot(2), mScoreboard(this, 0), unk5c(0), unk5d(0), unk5e(0), unk5f(0), unk60(0), unk61(1), unk62(0), mAutoVocals(0),
    unk7c(0), mTrackPanelDir(0), unk84(0), mTourGoalConfig(kConfigInvalid), unk8c(-1.0f) {
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
    if(mDir && !mTrackPanelDir){
        mTrackPanelDir = dynamic_cast<TrackPanelDirBase*>(mDir);
        mTrackPanelDir->SetTrackPanel(this);
        mScoreboard = mTrackPanelDir->Find<BandScoreboard>("scoreboard", false);
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
    if(u3 != -1) mReservedVocalSlot = u3;
    else mReservedVocalSlot = 4;
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
            int idx = mReservedVocalSlot;
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
    if(mScoreboard) mScoreboard->Reset();
    float secs = TheTaskMgr.Seconds(TaskMgr::b) * 1000.0f;
    Hmx::Object::Handle(on_reset_msg, true);
    mTrackPanelDir->ConfigureTracks(false);
    MetaPerformer::Current();
    mTrackPanelDir->Reset();
    SetMainGoalConfiguration(mTourGoalConfig);
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
                mTrackPanelDir->RemoveTrack(i);
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
        mTrackPanelDir->AssignTrack(idx, inst, false);
        if(inst != kInstPending){
            Track* track = mTrackSlots[idx].mTrack;
            BandTrack* trackDir = mTrackPanelDir->GetBandTrackInSlot(idx);
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
        if(!mTrackPanelDir) FinishLoad();
    }
    CleanUpTracks();
    mTrackPanelDir->ResetPlayers();
    if(mScoreboard) mScoreboard->Reset();
}

void TrackPanel::HandleAddUser(BandUser* user){
    int userslot = user->GetSlot();
    TrackSlot& slot = mTrackSlots[userslot];
    MILO_ASSERT(slot.mTrack == NULL, 0x207);
    MILO_ASSERT(slot.mInstrument == kInstNone, 0x208);
    Track* newtrack = NewTrack(user);
    newtrack->SetName(MakeString("track%d", userslot), ObjectDir::Main());

    bool pushed = false;

    for(int i = 0; i < mTracks.size(); i++){
        if(mTracks[i]->unk58 > userslot){
            // mTracks.push_back(newtrack);
            pushed = true;
            break;
        }   
    }
    if(!pushed){
        mTracks.push_back(newtrack);
    }
    unk5d = true;
    newtrack->unk58 = userslot;
    user->mTrack = newtrack;
    slot.mTrack = newtrack;
    slot.mInstrument = GetTrackInstrument(user->GetTrackSym());
    UpdateReservedVocalSlot();
    AssignTrack(userslot);
    mTrackPanelDir->ConfigureTracks(!IsGameOver());
    if(slot.mInstrument == kInstVocals && mTrackPanelDir->TracksExtended()){
        BandTrack* vocalTrack = newtrack->GetBandTrack();
        MILO_ASSERT(vocalTrack, 0x236);
        RndDir* vocalTrackDir = vocalTrack->AsRndDir();
        MILO_ASSERT(vocalTrackDir, 0x239);
        EventTrigger* introTrig = vocalTrackDir->Find<EventTrigger>("play_intro.trig", false);
        if(introTrig) introTrig->Trigger();
    }
}

void TrackPanel::HandleAddPlayer(Player* player){
    BandUser* user = player->GetUser();
    MILO_ASSERT(user, 0x248);
    DoHandleAddPlayer(user);
}

void TrackPanel::DoHandleAddPlayer(BandUser* user){
    int slot = user->GetSlot();
    TrackInstrument inst = GetTrackInstrument(user->GetTrackSym());
    mTrackSlots[slot].mInstrument = inst;
    mTrackPanelDir->GetBandTrackInSlot(slot)->SetInstrument(inst);
}