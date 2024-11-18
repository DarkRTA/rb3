#include "bandtrack/TrackPanel.h"
#include "Track.h"
#include "bandobj/BandScoreboard.h"
#include "bandobj/BandTrack.h"
#include "bandobj/EndingBonus.h"
#include "bandobj/TrackInstruments.h"
#include "bandobj/TrackPanelDirBase.h"
#include "bandobj/VocalTrackDir.h"
#include "decomp.h"
#include "game/BandUserMgr.h"
#include "game/Game.h"
#include "game/Player.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ModifierMgr.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/System.h"
#include "os/Timer.h"
#include "rndobj/Anim.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/PropAnim.h"
#include "synth/Sequence.h"
#include "ui/UIPanel.h"
#include "utl/Loader.h"
#include "utl/Messages.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include <cmath>

TrackPanel* TheTrackPanel;

TrackPanel* GetTrackPanel(){
    return TheTrackPanel;
}

TrackPanelDirBase* GetTrackPanelDir(){
    return TheTrackPanel->mTrackPanelDir;
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
        if(mTrackSlots[i].mInstrument == kInstVocals){
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
    float secs = TheTaskMgr.Seconds(TaskMgr::kRealTime) * 1000.0f;
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

void TrackPanel::PostHandleAddPlayer(Player* player){
    DoPostHandleAddPlayer(player->GetUser());
}

void TrackPanel::DoPostHandleAddPlayer(BandUser* user){
    int slot = user->GetSlot();
    TrackInstrument inst = mTrackSlots[slot].mInstrument;
    mTrackPanelDir->AssignTrack(slot, inst, false);
    Track* track = mTrackSlots[slot].mTrack;
    BandTrack* bandTrack = mTrackPanelDir->GetBandTrackInSlot(slot);
    MILO_ASSERT(track && bandTrack, 0x26F);
    MILO_ASSERT(inst == bandTrack->GetInstrument(), 0x270);
    track->SetDir(bandTrack->AsRndDir());
    bandTrack->Init(track);
    track->PostInit();
    mTrackPanelDir->ReapplyConfiguration(true);
    if(inst != kInstVocals && mTrackPanelDir->TracksExtended()){
        RndAnimatable* anim = bandTrack->AsRndDir()->Find<RndAnimatable>("intro_anim.grp", true);
        anim->SetFrame(0, 1);
        EventTrigger* trig = bandTrack->AsRndDir()->Find<EventTrigger>("track_in_delayed.trig", false);
        if(trig) trig->Trigger();
    }
    mTrackSlots[slot].mTrack->PlayerInit();
}

void TrackPanel::HandleRemoveUser(BandUser* user){
    Track* track = GetTrack(user, false);
    if(track){
        int idx = -1;
        for(int i = 0; i < mTrackSlots.size(); i++){
            TrackSlot& curslot = mTrackSlots[i];
            if(curslot.mTrack == track){
                curslot.mTrack = nullptr;
                curslot.mInstrument = kInstNone;
                idx = i;
                break;
            }
        }
        if(idx == -1) MILO_FAIL("Couldn't find slot for removed user!");
        mTrackPanelDir->RemoveTrack(idx);
        mTrackPanelDir->ConfigureTracks(!IsGameOver());
    }
}

void TrackPanel::PostHandleRemoveUser(BandUser* user){
    Track* track = user->GetTrack();
    if(std::find(mTracks.begin(), mTracks.end(), track) != mTracks.end()){
        mTracks.erase(std::find(mTracks.begin(), mTracks.end(), track));
        delete track;
    }
}

void TrackPanel::PlaySequence(const char* name, float f1, float f2, float f3){
    if(mTrackPanelDir){
        Sequence* seq = mTrackPanelDir->Find<Sequence>(name, false);
        if(seq){
            seq->Play(f1, f2, f3);
        }
        else MILO_WARN("TrackPanel::PlaySequence() - Sequence '%s' not found in %s", name, mTrackPanelDir->mPathName);
    }
}

void TrackPanel::StopSequence(const char* name, bool b){
    if(mTrackPanelDir){
        Sequence* seq = mTrackPanelDir->Find<Sequence>(name, false);
        if(seq){
            seq->Stop(b);
        }
        else MILO_WARN("TrackPanel::StopSequence() - Sequence '%s' not found in %s", name, mTrackPanelDir->mPathName);
    }
}

void TrackPanel::SetMainGoalConfiguration(TourGoalConfig cfg){
    mTourGoalConfig = cfg;
    if(cfg != kConfigInvalid && mDir){
        RndDir* rdir = mDir->Find<RndDir>("scoreboard", false);
        if(rdir){
            RndPropAnim* anim = rdir->Find<RndPropAnim>("configuration.anim", true);
            if(anim){
                float f7;
                switch(mTourGoalConfig){
                    case kConfigScoreStars:
                        f7 = 0.0f;
                        break;
                    case kConfigScoreStarsGoal:
                        f7 = 1.0f;
                        break;
                    case kConfigScoreGoal:
                        f7 = 2.0f;
                        break;
                    case kConfigStarsGoal:
                        f7 = 3.0f;
                        break;
                    case kConfigGoal:
                        f7 = 4.0f;
                        break;
                    default:
                        f7 = 0.0f;
                        break;
                }
                float fmodded = std::fmod(f7 + 1.0f, 5.0f);
                anim->SetFrame(fmodded, 1);
                anim->SetFrame(f7, 1);
            }
        }
    }
}

void TrackPanel::MainGoalReset(){
    if(mTrackPanelDir){
        RndDir* rdir = mTrackPanelDir->Find<RndDir>("tour_goal_notify", false);
        if(rdir){
            rdir->SetShowing(false);
            rdir->Find<EventTrigger>("hide.trig", true)->Trigger();
            unk60 = false;
        }
    }
}

void TrackPanel::ShowMainGoalInfo(bool show){
    if(mScoreboard){
        RndDir* rdir = mScoreboard->Find<RndDir>("tour_goal_main", false);
        if(rdir){
            EventTrigger* trig;
            if(show){
                trig = rdir->Find<EventTrigger>("show.trig", true);
            }
            else {
                trig = rdir->Find<EventTrigger>("hide.trig", true);
            }
            trig->Trigger();
        }
    }
}

DECOMP_FORCEACTIVE(TrackPanel, "top", "bottom", "tg_main_text_top.lbl", "tg_main_text_bottom.lbl", "desc",
    "tracker_broadcast_display", "tg_desc.lbl", "tg_desc_display.trig", "tg_main_succeed.trig", "tg_main_fail.trig")

void TrackPanel::SendTrackerDisplayMessage(const Message& msg) const {
    if(mScoreboard){
        RndDir* rdir = mScoreboard->Find<RndDir>("tracker_band_display", false);
        if(!rdir) MILO_WARN("Couldn't find tracker_band_display object in TrackPanel!");
        else rdir->HandleType(msg);
    }
}

void TrackPanel::SendTrackerBroadcastDisplayMessage(const Message& msg) const {
    if(!unk62){
        RndDir* rdir = mTrackPanelDir->Find<RndDir>("tracker_broadcast_display", false);
        if(rdir) rdir->HandleType(msg);
    }
}

void TrackPanel::TrackerDisplayReset() const {
    SendTrackerDisplayMessage(hide_msg);
    SendTrackerBroadcastDisplayMessage(hide_msg);
}

void TrackPanel::Unload(){
    CleanUpReloadChecks();
    for(int i = 0; i < mTracks.size(); i++){
        mTracks[i]->Unload();
    }
    mDir->SetProperty("gem_tracks", 0);
    CleanUpTracks();
    DeleteAll(mTracks);
    if(mTrackPanelDir) mTrackPanelDir->CleanUpChordMeshes();
    mTrackPanelDir = nullptr;
    UIPanel::Unload();
}

void TrackPanel::StartPulseAnims(){
    if(!unk5f){
        float delay = mTrackPanelDir->GetPulseAnimStartDelay(true);
        mTrackPanelDir->StartPulseAnims(delay);
        for(int i = 0; i < mTracks.size(); i++){
            mTracks[i]->StartPulseAnims(delay);
        }
        unk5f = true;
    }
}

DECOMP_FORCEACTIVE(TrackPanel, "hud_track_poll")

void TrackPanel::Draw(){
    START_AUTO_TIMER("hud_track_draw");
    if(unk5c) UIPanel::Draw();
}

DECOMP_FORCEACTIVE(TrackPanel, "track/tracksystem.milo", "track/vocals.milo", "config/track_graphics.dta", "track/rail_streak.milo")

void TrackPanel::SetSmasherGlowing(int iii, bool b){
    for(int i = 0; i < mTracks.size(); i++){
        mTracks[i]->SetSmasherGlowing(iii, b);
    }
}

void TrackPanel::PopSmasher(int iii){
    for(int i = 0; i < mTracks.size(); i++){
        mTracks[i]->PopSmasher(iii);
    }
}

void TrackPanel::CleanUpReloadChecks(){
    for(std::map<Symbol, DepChecker*>::iterator it = unk64.begin(); it != unk64.end(); ++it){
        delete it->second;
    }
    unk64.clear();
}

DataNode TrackPanel::ForEachTrack(const DataArray* arr){
    DataNode* var = arr->Var(2);
    DataNode node = *var;
    for(int i = 0; i < mTracks.size(); i++){
        *var = mTracks[i];
        for(int j = 3; j < arr->Size(); j++){
            arr->Command(j)->Execute();
        }
    }
    *var = node;
    return 0;
}

void TrackPanel::GetTrackOrder(std::vector<TrackInstrument>* out, bool) const {
    MILO_ASSERT(out && out->empty(), 0x4E9);
    for(int i = 0; i < mTrackSlots.size(); i++){
        out->push_back(mTrackSlots[i].mInstrument);
    }
}

int TrackPanel::GetTrackCount() const {
    return mTrackSlots.size();
}

int TrackPanel::GetNumPlayers() const {
    return TheBandUserMgr->GetNumParticipants();
}

bool TrackPanel::InGame() const {
    return TheGame;
}

int TrackPanel::GetTrackSlot(Player* player){
    for(int i = 0; i < mTrackSlots.size(); i++){
        if(mTrackSlots[i].mTrack && mTrackSlots[i].mTrack->GetPlayer() == player) return i;
    }
    return -1;
}

void TrackPanel::UpdateJoinInProgress(bool b1, bool b2){
    mTrackPanelDir->UpdateJoinInProgress(b1, b2);
}

void TrackPanel::FailedJoinInProgress(){
    mTrackPanelDir->FailedJoinInProgress();
}

void TrackPanel::SetSuppressUnisonDisplay(bool b){
    EndingBonus* bonus = mTrackPanelDir->GetEndingBonus();
    if(bonus) bonus->SetSuppressUnisonDisplay(b);
}

void TrackPanel::UnisonStart(int iii){
    EndingBonus* bonus = mTrackPanelDir->GetEndingBonus();
    if(bonus){
        int u3 = 0;
        for(int i = 0; i < mTracks.size(); i++){
            int tracknum = mTracks[i]->GetTrackNum();
            if(iii & (1 << tracknum)){
                u3 |= (1 << mTracks[i]->unk58);
            }
        }
        bonus->UnisonStart(u3);
    }
}

void TrackPanel::UnisonPlayerSuccess(Player* player){
    if(player){
        EndingBonus* bonus = mTrackPanelDir->GetEndingBonus();
        int slot = GetTrackSlot(player);
        if(bonus && slot != -1){
            bonus->PlayerSuccess(slot);
        }
    }
}

void TrackPanel::UnisonPlayerFailure(Player* player){
    if(player){
        EndingBonus* bonus = mTrackPanelDir->GetEndingBonus();
        int slot = GetTrackSlot(player);
        if(bonus && slot != -1){
            bonus->PlayerFailure(slot);
        }
    }
}

void TrackPanel::SetSuppressTambourineDisplay(bool b){
    for(int i = 0; i < mTrackSlots.size(); i++){
        if(mTrackSlots[i].mInstrument == kInstVocals){
            Track* track = mTrackSlots[i].mTrack;
            if(track){
                BandTrack* btrack = track->GetBandTrack();
                if(btrack){
                    btrack->SetSuppressSoloDisplay(b);
                }
            }
        }
    }
}

void TrackPanel::SetSuppressPlayerFeedback(bool b){
    for(int i = 0; i < mTrackSlots.size(); i++){
        Track* track = mTrackSlots[i].mTrack;
        if(track){
            BandTrack* btrack = track->GetBandTrack();
            if(btrack){
                btrack->SetPlayerFeedbackShowing(!b);
            }
        }
    }
}

int TrackPanel::GetNoCrowdMeter() const {
    MetaPerformer::Current();
    return 0;
}

DECOMP_FORCEACTIVE(TrackPanel, "initial_display_level")

bool TrackPanel::SlotReservedForVocals(int slot) const {
    return slot == mReservedVocalSlot;
}

bool TrackPanel::GameResumedNoScore() const {
    return TheGame->ResumedNoScore();
}

BEGIN_HANDLERS(TrackPanel)
    HANDLE_ACTION(set_smasher_glowing, SetSmasherGlowing(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(pop_smasher, PopSmasher(_msg->Int(2)))
    HANDLE_ACTION(track_reset, Reset())
    HANDLE_ACTION(reload, Reload())
    HANDLE_EXPR(get_first_track, GetTrack())
    HANDLE(foreach_track, ForEachTrack)
    HANDLE_EXPR(my_track_panel_dir, mTrackPanelDir)
    if (sym == get_pause_menu){
        _msg->Int(2);
        return NULL_OBJ;
    }
    HANDLE_EXPR(get_user_from_track_num, (BandUser*)GetUserFromTrackNum(_msg->Int(2)))
    HANDLE_ACTION(play_seq, PlaySequence(_msg->Str(2), 0, 0, 0))
    HANDLE_ACTION(stop_seq, StopSequence(_msg->Str(2), false))
    HANDLE_ACTION(update_join_in_progress, UpdateJoinInProgress(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(failed_join_in_progress, FailedJoinInProgress())
    HANDLE_EXPR(get_num_tracks, (int)mTracks.size())
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x5C5)
END_HANDLERS