#include "bandtrack/GemTrack.h"
#include "GemManager.h"
#include "bandobj/BandTrack.h"
#include "bandobj/GemTrackDir.h"
#include "beatmatch/FillInfo.h"
#include "beatmatch/PlayerTrackConfig.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/GameConfig.h"
#include "game/GemPlayer.h"
#include "meta_band/GameplayOptions.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Anim.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include "utl/TimeConversion.h"

bool sEnableShift = true;
bool sUpdateShifting;

DataNode ToggleShift(DataArray* arr){
    sUpdateShifting = true;
    sEnableShift = !sEnableShift;
    return sEnableShift;
}

GemTrack::GemTrack(BandUser* user) : Track(user), mResetFills(0), unk69(SystemConfig("scoring", "overdrive")->FindInt("fills")), mTrackDir(this, 0), unk78(-1), unk7c(-1), mGemManager(0),
    unkb4(0), unkb6(0), unkb7(1), unkc4(-1.0f), unkc8(-1.0f), mUpcomingShiftMaskAnim(this, 0), mKeyIntroTasks(this, kObjListNoNull) {
    DataRegisterFunc("toggle_key_shifting", ToggleShift);
}

GemTrack::~GemTrack(){
    RELEASE(mGemManager);
    mKeyIntroTasks.DeleteAll();
}

void GemTrack::Init(){
    bool lefty = false;
    BandUser* pUser = (BandUser*)mTrackConfig.GetBandUser();
    MILO_ASSERT(pUser, 0x5F);
    GameplayOptions* options = pUser->GetGameplayOptions();
    MILO_ASSERT(options, 0x61);
    if(options) lefty = options->GetLefty();
    PlayerTrackConfigList* pCfg = TheGameConfig->GetConfigList();
    MILO_ASSERT(pCfg, 0x66);
    unsigned int cymlanes = pCfg->GetGameCymbalLanes();
    int tracknum = TheGameConfig->GetTrackNum(pUser->mUserGuid);
    pUser->GetDifficulty();
    mTrackConfig.SetLefty(lefty);
    mTrackConfig.SetGameCymbalLanes(cymlanes);
    mTrackConfig.SetTrackNum(tracknum);
    if(pUser->GetPlayer()){
        PlayerInit();
    }
    mUpcomingShiftMaskAnim = mTrackDir->Find<RndAnimatable>("keys_upcoming_shift.anim", true);
}

void GemTrack::PlayerInit(){
    BandUser* pUser = (BandUser*)mTrackConfig.GetBandUser();
    MILO_ASSERT(pUser, 0x80);
    GemPlayer* player = dynamic_cast<GemPlayer*>(pUser->GetPlayer());
    if(player){
        mTrackConfig.SetTrackNum(TheGameConfig->GetTrackNum(pUser->mUserGuid));
        mTrackConfig.SetMaxSlots(player->GetMaxSlots());
        mTrackConfig.SetDisableHopos(pUser->GetControllerType() == kControllerKeys);
        HandleNewSong();
    }
}

void GemTrack::PostInit(){
    UpdateShifts();
    if(mCurrentRangeShift != mRangeShifts.end()){
        ApplyShiftImmediately(*mCurrentRangeShift);
        mCurrentRangeShift++;
    }
}

void GemTrack::ResetFills(bool reset){
    mResetFills = reset;
}

void GemTrack::RebuildBeats(){
    mTrackDir->ClearAllWidgets();
    float secs = MsToTick((TheTaskMgr.Seconds(TaskMgr::b) + mTrackDir->BottomSeconds()) * 1000.0f);
    unk7c = unk78 = secs;
}

void GemTrack::ApplyShiftImmediately(const RangeShift& shift){
    float f1 = shift.unk14;
    float min = Min(shift.unkc, 15.0f - f1);
    MILO_ASSERT(mTrackDir, 0xB6);
    if(f1 != unkc4){
        mTrackDir->SetDisplayRange(f1);
        unkc4 = f1;
    }
    if(min != unkc8){
        mTrackDir->SetDisplayOffset(min, true);
        unkc8 = min;
    }
}

DECOMP_FORCEACTIVE(GemTrack, "set_drum_fill_complete.trig", "key_mash.wid", "deploy_beard.anim",
    "Authored keyboard range section at tick %d is unexpected size: %d (should be %d)", "Authored range section exceeds displayable keyboard range: %.0f - %.0f @ tick %d",
    "flip_shift_arrows", "key_shift_right.wid", "key_shift_left.wid", "startKey <= endKey", "bar_measure.wid", "bar_beat.wid", "bar_half_beat.wid", "mGemManager",
    "guitar_solo_mask.wid", "bar_blue_beat.wid", "finish_line.wid", "keys_upcoming_shift.wid")

void GemTrack::UpdateShiftsToTick(int tick){
    UpdateShifts();
    std::vector<RangeShift>::iterator it = mRangeShifts.begin();
    mCurrentRangeShift = it;
    for(; it != mRangeShifts.end(); ++it){
        if(it->unk0 <= tick){
            mCurrentRangeShift = it;
        }
        else break;
    }
    if(mCurrentRangeShift != mRangeShifts.end()){
        ApplyShiftImmediately(*mCurrentRangeShift);
        mCurrentRangeShift++;
    }
}

void GemTrack::UpdateLeftyFlip(){
    bool lefty = false;
    GameplayOptions* options = ((BandUser*)mTrackConfig.GetBandUser())->GetGameplayOptions();
    MILO_ASSERT(options, 0xEA);
    if(options) lefty = options->GetLefty();
    mTrackConfig.SetLefty(lefty);
    if(mGemManager) mGemManager->UpdateLeftyFlip(true);
    ResetFills(true);
    mTrackDir->UpdateLeftyFlip(lefty);
    unkb6 = true;
}

void GemTrack::UpdateFills(){
    const BandUser* user = mTrackConfig.GetBandUser();
    if(!user->GetPlayer() || !user->GetPlayer()->IsDeployingBandEnergy()) return;
    else {
        Symbol s;
        for(int i = 0; i < mTrackConfig.GetMaxSlots(); i++){
            if(mGemManager->GetWidgetName(s, i, fill)){
                mGemManager->GetWidgetByName(s)->Clear();
            }
        }
        Symbol symlist[3] = { crash, crash_cymbal, beard };
        for(int i = 0; i < 3U; i++){
            if(mGemManager->GetWidgetName(s, 4, symlist[i])){
                mGemManager->GetWidgetByName(s)->Clear();
            }
        }
    }
}

void GemTrack::ChangeDifficulty(Difficulty diff, int iii){
    mGemManager->ClearGems(true);
    mGemManager->SetupGems(iii);
    UpdateShiftsToTick(iii);
    mTrackDir->ClearAllWidgets();
    float secs = MsToTick((TheTaskMgr.Seconds(TaskMgr::b) + mTrackDir->TopSeconds()) * 1000.0f);
    unk7c = unk78 = secs;
}

void GemTrack::DropIn(int tick){
    UpdateShiftsToTick(tick);
}

void GemTrack::SetPlayerState(const PlayerState& state){
    mPlayerState = state;
}

void GemTrack::RedrawTrackElements(float f){
    DrawTrackElements(MsToTick(mTrackDir->BottomSeconds() * 1000.0f + f), MsToTick(mTrackDir->TopSeconds() * 1000.0f + f));
}

void GemTrack::SetDir(RndDir* rdir){
    mTrackDir = dynamic_cast<GemTrackDir*>(rdir);
    MILO_ASSERT(mTrackDir, 0x42A);
    mTrackDir->Enter();
    mTrackDir->SetShowing(true);
    Init();
}

void GemTrack::HandleNewSong(){
    if(mGemManager){
        mGemManager->SetupGems(0);
    }
    else {
        mGemManager = new GemManager(mTrackConfig, mTrackDir);
    }
    if(mTrackConfig.IsKeyboardTrack()){
        mGemManager->UpdateEnabledSlots();
    }
}

void GemTrack::See(float f, int i){
    int mask = mGemManager->GetSlotsForGem(i);
    if(mTrackConfig.IsDrumTrack() && ((mask & 1) == 1)){
        mTrackDir->SeeKick();
    }
}

void GemTrack::Hit(float f, int i1, int i2){
    mGemManager->Hit(f, i1, i2);
    int slots = mGemManager->GetSlotsForGem(i1);
    mTrackDir->GemHit(slots);
}

void GemTrack::Miss(float f, int i1, int i2){
    mGemManager->Miss(f, i1, i2);
}

void GemTrack::Pass(int i){
    mGemManager->Pass(i);
    int slots = mGemManager->GetSlotsForGem(i);
    mTrackDir->GemPass(i, slots);
}

void GemTrack::Ignore(int i){
    mGemManager->Ignore(i);
}

void GemTrack::PartialHit(float f, int i1, unsigned int ui, int i2){
    mGemManager->PartialHit(f, i1, ui, i2);
}

void GemTrack::FillHit(int i1, int i2){
    mGemManager->FillHit(i1, i2);
}

void GemTrack::SetFretButtonPressed(int i1, bool b){
    mGemManager->SetSmasherGlowing(i1, b);
}

void GemTrack::ReleaseGem(float f, int i){
    mGemManager->Released(f, i);
}

void GemTrack::Jump(float f){
    if(mGemManager){
        mGemManager->Jump(f);
        if(f <= 0 && mTrackDir){
            mTrackDir->ClearAllWidgets();
            mGemManager->SetGemsEnabled(0);
        }
        mCurrentRangeShift = mRangeShifts.begin();
    }
}

GemManager* GemTrack::GetGemManager(){ return mGemManager; }

void GemTrack::OnMissPhrase(int i){
    if(mGemManager->OnMissPhrase(i)){
        BandTrack* track = GetBandTrack();
        if(track){
            GetBandTrack()->SpotlightFail(true);
        }
    }
}

BandTrack* GemTrack::GetBandTrack(){ return mTrackDir; }

float GemTrack::NextKickNoteMs() const {
    if(mTrackConfig.IsDrumTrack()){
        float secs = TheTaskMgr.Seconds(TaskMgr::b);
        BandUser* pUser = (BandUser*)mTrackConfig.GetBandUser();
        MILO_ASSERT(pUser, 0x4D1);

    }
  return 3.402823466385289e+38f;
}

void GemTrack::SetBonusGems(bool b){
    if(mGemManager){
        if(b){
            static Symbol unisonMask("unison_mask.wid");
            mGemManager->GetWidgetByName(unisonMask)->Clear();
        }
        mGemManager->SetBonusGems(b, mPlayerState);
    }
}

void GemTrack::SetInCoda(bool b){
    if(mGemManager) mGemManager->SetInCoda(b);
}

void GemTrack::UpdateEffects(int i){
    MILO_ASSERT(mTrackDir, 0x503);
    mTrackDir->OnUpdateFx(i);
}

void GemTrack::SetSmasherGlowing(int i, bool b){
    mGemManager->SetSmasherGlowing(i, b);
}

void GemTrack::PopSmasher(int i){
    mGemManager->PopSmasher(i);
}

void GemTrack::SetGemsEnabled(float f){
    if(mGemManager) mGemManager->SetGemsEnabled(f);
}

void GemTrack::SetGemsEnabledByPlayer(){
    SetGemsEnabled(GetPlayer()->mEnableMs);
}

void GemTrack::UpdateGems(){
    if(mGemManager){
        mGemManager->UpdateGemStates();
        UpdateFills();
    }
}

Hmx::Object* GemTrack::GetSmasher(int i){
    if(mGemManager) return mGemManager->GetSmasherObj(i);
    else return nullptr;
}

void GemTrack::ResetSmashers(bool b){
    if(mGemManager) mGemManager->ResetSmashers(b);
}

void GemTrack::UpdateSlotXfms(){
    if(mGemManager) mGemManager->UpdateSlotPositions();
}

void GemTrack::RefreshCurrentShift(){
    if(mCurrentRangeShift != mRangeShifts.end()){
        mCurrentRangeShift->unk10 = -1.0f;
        mCurrentRangeShift->unk8 = -1.0f;
    }
}

void GemTrack::PlayKeyIntros(){
    if(mGemManager){
        DataArray* cfg = SystemConfig("track_graphics");
        float f8 = cfg->FindFloat("key_intro_offset_ms");
        float f9 = cfg->FindFloat("key_intro_delay_ms");
        if(mTrackConfig.IsKeyboardTrack()){
            mGemManager->UpdateEnabledSlots();
            mKeyIntroTasks.DeleteAll();
        }
        int taskidx = 1;
        for(int i = 0; i < mTrackConfig.GetMaxSlots(); i++){
            MessageTask* task = new MessageTask(mGemManager->GetSmasherObj(i), intro_msg);
            TheTaskMgr.Start(task, (TaskUnits)2, ((float)taskidx * f8 + f9) / 1000.0f);
            mKeyIntroTasks.push_back(task);
            taskidx++;
        }
    }
}

void GemTrack::RemovePlayer(){
    if(mGemManager) mGemManager->HideGems();
    mTrackDir->ClearAllWidgets();
}

void GemTrack::OverrideRangeShift(float f1, float f2){
    if(f1 != unkc4){
        mTrackDir->SetDisplayRange(f1);
        unkc4 = f1;
    }
    if(f2 != unkc8){
        mTrackDir->SetDisplayOffset(f2, false);
        unkc8 = f2;
    }
}

BEGIN_HANDLERS(GemTrack)
    HANDLE_ACTION(on_miss_phrase, OnMissPhrase(_msg->Int(2)))
    HANDLE_ACTION(set_bonus_gems, SetBonusGems(_msg->Int(2)))
    HANDLE_EXPR(get_smasher, mGemManager ? mGemManager->GetSmasherObj(_msg->Int(2)) : NULL_OBJ)
    HANDLE_ACTION(enable_slot, SetEnableSlot(_msg->Int(2), true))
    HANDLE_ACTION(disable_slot, SetEnableSlot(_msg->Int(2), false))
    HANDLE_ACTION(update_gems, UpdateGems())
    HANDLE_ACTION(set_gems_enabled, SetGemsEnabled(_msg->Float(2)))
    HANDLE_ACTION(handle_new_song, HandleNewSong())
    HANDLE_EXPR(lefty, Lefty())
    HANDLE_EXPR(next_kick_ms, NextKickNoteMs())
    HANDLE_SUPERCLASS(Track)
    HANDLE_CHECK(0x5A7)
END_HANDLERS