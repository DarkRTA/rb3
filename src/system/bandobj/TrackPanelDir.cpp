#include "bandobj/TrackPanelDir.h"
#include "bandobj/TrackPanelInterface.h"
#include "bandobj/GemTrackDir.h"
#include "obj/ObjVersion.h"
#include "rndobj/TexRenderer.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

INIT_REVS(TrackPanelDir);

TrackPanelDir::TrackPanelDir() : unk244(1), mTestMultiplier(1), unk24c(0), unk250(0), mVocalTrack(this, 0), mCrowdMeter(this, 0), mBandScoreMultiplier(this, 0),
    mBandScoreMultiplierTrig(this, 0), mEndingBonus(this, 0), mScoreboard(this, 0), mPulseAnimGrp(this, 0),
    unk2ac(1), unk2ad(0), mTracksExtended(0), mGemTrackRsrcMgr(this, 0), mVocals(1), mVocalsNet(0) {
    for(int i = 0; i < 4; i++){
        mGemTracks.push_back(ObjPtr<GemTrackDir, ObjectDir>(this, 0));
        mGemNet[i] = 0;
    }
    mGemInst[0] = 0;
    mGemInst[1] = 1;
    mGemInst[2] = 2;
    mGemInst[3] = -1;
}

TrackPanelDir::~TrackPanelDir(){
    delete mGemTrackRsrcMgr;
}

SAVE_OBJ(TrackPanelDir, 0x3F)

void TrackPanelDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    TrackPanelDirBase::PreLoad(bs);
}

void TrackPanelDir::PostLoad(BinStream& bs){
    TrackPanelDirBase::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if(gRev < 1){
        int i;
        bs >> i >> i >> i >> i;
    }
}

BEGIN_COPYS(TrackPanelDir)
    COPY_SUPERCLASS(TrackPanelDirBase)
END_COPYS

void TrackPanelDir::SyncObjects(){
    PanelDir::SyncObjects();
    if(!mBandScoreMultiplier) mBandScoreMultiplier = Find<RndDir>("star_meter_multiplier", true);
    if(!mBandScoreMultiplierTrig) mBandScoreMultiplierTrig = Find<EventTrigger>("star_multiplier_number.trig", true);
    if(!mCrowdMeter) mCrowdMeter = Find<BandCrowdMeter>("crowd_meter", true);
    if(!mEndingBonus) mEndingBonus = Find<EndingBonus>("ending_bonus", true);
    if(!mVocalTrack) mVocalTrack = Find<VocalTrackDir>("vocals", true);
    if(!mApplauseMeter) mApplauseMeter = Find<RndDir>("applause_meter", true);
    if(!mBandLogoRival) mBandLogoRival = Find<RndDir>("bandlogo_rival", true);
    if(!mBandLogo) mBandLogo = Find<RndDir>("bandlogo", true);
    if(!mScoreboard) mScoreboard = Find<RndDir>("scoreboard", true);
    if(!mPulseAnimGrp) mPulseAnimGrp = Find<RndGroup>("beat_anims.grp", false);
    if(!mGemTracks[0]){
        mGemTracks[0] = Find<GemTrackDir>("track_0", true);
        mGemTracks[0]->SetGemTrackID(0);
    }
    if(!mGemTracks[1]){
        mGemTracks[1] = Find<GemTrackDir>("track_1", true);
        mGemTracks[1]->SetGemTrackID(1);
    }
    if(!mGemTracks[2]){
        mGemTracks[2] = Find<GemTrackDir>("track_2", true);
        mGemTracks[2]->SetGemTrackID(2);
    }
    if(!mGemTracks[3]){
        mGemTracks[3] = Find<GemTrackDir>("track_3", true);
        mGemTracks[3]->SetGemTrackID(3);
    }
    if(!mVocalTrack->mEndgameFeedback) mVocalTrack->mEndgameFeedback = Find<RndDir>("endgame_feedback_vox", false);
    if(!mGemTrackRsrcMgr || !mGemTrackRsrcMgr->unk1c){
        RELEASE(mGemTrackRsrcMgr);
        ObjectDir* dir = Find<ObjectDir>("gem_track_resources", false);
        if(dir) mGemTrackRsrcMgr = new GemTrackResourceManager(dir);
    }
}

void TrackPanelDir::AssignTracks(){
    MILO_ASSERT(TheLoadMgr.EditMode(), 0xA3);
    mInstruments.clear();
    for(int i = 0; i < 5; i++) mInstruments.push_back(kInstNone);
    if(mVocals){
        mInstruments[2] = kInstVocals;
        mVocalTrack->SetSimulatedNet(mVocalsNet);
    }
    for(int i = 0; i < 4; i++){
        if(i < 2) mInstruments[i] = (TrackInstrument)mGemInst[i];
        else mInstruments[i + 1] = (TrackInstrument)mGemInst[i];
        mGemTracks[i]->SetSimulatedNet(mGemNet[i]);
    }
    mVocalTrack->SetUsed(false);
    for(int i = 0; i < mGemTracks.size(); i++){
        mGemTracks[i]->SetUsed(false);
    }
    mTracks.clear();
    unk24c = 0;
    int i11 = 0;
    unk250 = 0;
    for(int i = 0; i < mInstruments.size(); i++){
        mTracks.push_back(ObjPtr<BandTrack, ObjectDir>(this, 0));
        if(mInstruments[i] == kInstNone){
            if(!ReservedVocalPlayerSlot(i)) i11++;
        }
        else {
            if(mInstruments[i] == kInstVocals){
                if(unk250) MILO_FAIL("too many vocal tracks");
                mTracks[i] = mVocalTrack;
                unk250++;
            }
            else {
                if(i11 >= mGemTracks.size()) MILO_FAIL("too many gem tracks");
                GemTrackDir* trackdir = mGemTracks[i11];
                trackdir->unk488 = unk24c;
                mTracks[i] = trackdir;
                i11++;
                unk24c++;
            }
            mTracks[i]->SetTrackIdx(i);
            mTracks[i]->SetInstrument(mInstruments[i]);
            mTracks[i]->SetUsed(true);
        }
    }
}

void TrackPanelDir::SetTrackPanel(TrackPanelInterface* interface){
    mTrackPanel = interface;
    if(mInstruments.empty()){
        mInstruments.resize(mTrackPanel->GetTrackCount(), kInstNone);
    }
}

void TrackPanelDir::AssignTrack(int iSlot, TrackInstrument iInstrument, bool b){
    MILO_ASSERT(iInstrument != kInstNone, 0xF0);
    if(mTracks.size() == 0){
        for(int i = 0; i < mTrackPanel->GetTrackCount(); i++){
            mTracks.push_back(ObjPtr<BandTrack, ObjectDir>(this, 0));
        }
    }
    TrackInstrument oldInstrument = mInstruments[iSlot];
    if(iInstrument != oldInstrument){
        bool wasPending = oldInstrument == kInstPending;
        MILO_ASSERT((oldInstrument == kInstNone) || wasPending, 0x103);
        MILO_ASSERT(wasPending || (mTracks[iSlot] == NULL), 0x104);
        if(iInstrument == kInstVocals){
            MILO_ASSERT(ReservedVocalPlayerSlot(iSlot), 0x10A);
            mTracks[iSlot] = mVocalTrack;
            unk250++;
        }
        else {
            MILO_ASSERT(!ReservedVocalPlayerSlot(iSlot), 0x112);
            GemTrackDir* gemTrackDir = mGemTracks[iSlot];
            MILO_ASSERT(wasPending || !gemTrackDir->InUse(), 0x115);
            mTracks[iSlot] = gemTrackDir;
            gemTrackDir->unk488 = unk24c;
            if(!wasPending) unk24c++;
        }
        mTracks[iSlot]->SetTrackIdx(iSlot);
        mTracks[iSlot]->SetInstrument(iInstrument);
        mTracks[iSlot]->SetUsed(true);
        mInstruments[iSlot] = iInstrument;
        mTracks[iSlot]->SetupSmasherPlate();
        if(b) mTracks[iSlot]->Reset();
    }
}

void TrackPanelDir::RemoveTrack(int iSlot){
    TrackInstrument inst = mInstruments[iSlot];
    if(inst != kInstNone){
        if(inst == kInstVocals){
            MILO_ASSERT(ReservedVocalPlayerSlot(iSlot), 0x13C);
            unk250--;
        }
        else {
            MILO_ASSERT(!ReservedVocalPlayerSlot(iSlot), 0x144);
            unk24c--;
        }
        if(mEndingBonus) mEndingBonus->DisablePlayer(mTracks[iSlot]->mTrackIdx);
        mTracks[iSlot]->SetUsed(false);
        mTracks[iSlot]->ReleaseSmasherPlate();
        mTracks[iSlot] = 0;
        mInstruments[iSlot] = kInstNone;
    }
}

void TrackPanelDir::ConfigureTracks(bool b){
    Hmx::Object* modeobj = FindObject("gamemode", true);
    bool b18 = false;
    if(modeobj){
        if(modeobj->Property("is_practice", true)->Int()) b18 = true;
    }
    if(TheLoadMgr.EditMode()) AssignTracks();
    for(int i = 0; i < mGemTracks.size(); i++){
        ConfigureTrack(i);
    }
    RndCam* camcam = Find<RndCam>("Cam.cam", true);
    camcam->SetLocalPos(Vector3(0,0,0));
    Vector3 rot(0,0,0);
    camcam->SetLocalRot(rot);
    const char* aspectstr = MakeString(TheRnd->GetAspect() == Rnd::kRegular ? "regular" : "wide");
    const char* objname = !unk24c ? MakeString("vocal_only_%s", aspectstr) : MakeString("%1d_player_%s", unk24c, aspectstr);
    SetConfiguration(Find<Hmx::Object>(objname, true), b);
    bool b1 = !b18;
    if(mTrackPanel){
        b1 = b1 && mTrackPanel->GameResumedNoScore();
    }
    if(b1){
        float f19 = 1.0f;
        if(mVocalTrack->InUse() && !mPerformanceMode) f19 = 0;
        Find<RndTransAnim>("scoreboard_to_top.tnm", true)->SetFrame(f19, 1.0f);
        Find<RndTransAnim>("applause_meter_to_top.tnm", true)->SetFrame(f19, 1.0f);
        Find<RndTransAnim>("mtv_overlay_to_top.tnm", true)->SetFrame(f19, 1.0f);
        bool b15 = true;
        if(mTrackPanel) b15 = mTrackPanel->ShowApplauseMeter();
        Find<RndGroup>("scoreboard.grp", true)->SetShowing(true);
        Find<RndGroup>("applause_meter.grp", true)->SetShowing(b15);
    }
    else {
        Find<RndGroup>("scoreboard.grp", true)->SetShowing(false);
        Find<RndGroup>("applause_meter.grp", true)->SetShowing(false);
    }
    if(b18){
        Find<RndTransAnim>("mtv_overlay_to_top.tnm", true)->SetFrame(0.1f, 1.0f);
    }
    unk224 = unk24c > 2;
    for(int i = 0; i < mGemTracks.size(); i++){
        SetPlayerLocal(mGemTracks[i]);
    }
    if(unk250 && b){
        mVocalTrack->unk2a7 = false;
        SetPlayerLocal(mVocalTrack);
        mVocalTrack->UpdateConfiguration();
    }
    if(mTrackPanel){
        bool single = mTrackPanel->GetNumPlayers() == 1;
        for(int i = 0; i < mTracks.size(); i++){
            if(mTracks[i]){
                mTracks[i]->CombineStreakMultipliers(single);
            }
        }
        SetMultiplier(mBandScoreMultiplier->Property("last_multiplier", true)->Int(), true);
    }
    unk2ac = true;
}

void TrackPanelDir::ConfigureTrack(int i){
    GemTrackDir* cur = mGemTracks[i];
    if(cur->mInUse) cur->mNumTracks = unk24c;
}

void TrackPanelDir::ConfigureCrowdMeter(){
    Hmx::Object* modeobj = FindObject("gamemode", true);
    bool practice = modeobj && modeobj->Property("is_practice", true)->Int();
    if(practice || (mTrackPanel && mTrackPanel->GetNoCrowdMeter()) || (mTrackPanel && mTrackPanel->GameResumedNoScore())){
        mCrowdMeter->Disable();
        mCrowdMeter->SetShowing(false);
        return;
    }
    mCrowdMeter->UpdatePlayers(mInstruments);
    mCrowdMeter->Enable();
    bool show = modeobj && modeobj->Property("show_crowd_meter", true)->Int() || TheLoadMgr.EditMode();
    mCrowdMeter->SetShowing(show);
}

void TrackPanelDir::SetConfiguration(Hmx::Object* o, bool b){
    TrackPanelDirBase::SetConfiguration(o, b);
    ApplyVocalTrackShowingStatus();
    ConfigureCrowdMeter();
}

void TrackPanelDir::ReapplyConfiguration(bool b){
    TrackPanelDirBase::ReapplyConfiguration(true);
    ApplyVocalTrackShowingStatus();
    ConfigureCrowdMeter();
}

void TrackPanelDir::ApplyVocalTrackShowingStatus(){
    MILO_ASSERT(mVocalTrack, 500);
    mVocalTrack->SetShowing(mVocalTrack->mInUse);
    mVocalTrack->mIsTop = true;
}

void TrackPanelDir::SetBotbBandIcon(ObjectDir* target, RndDir* source, bool b3){
    if(!target || !source){
        if(!target) MILO_WARN("Could not find botb band logo target");
        if(!source) MILO_WARN("Could not find botb band logo source");
    }
    else {
        RndTex* tex = b3 ? target->Find<RndTex>("logo_target.tex", false) : target->Find<RndTex>("logo_target_rival.tex", false);
        RndTexRenderer* texrenderer = target->Find<RndTexRenderer>("band_logo.rndtex", false);
        RndMat* logomat = target->Find<RndMat>("logo.mat", false);
        if(tex && texrenderer && logomat){
            texrenderer->SetProperty(output_texture, tex);
            texrenderer->SetDraw(source);
            logomat->SetDiffuseTex(tex);
        }
        else {
            if(!tex) MILO_WARN("Could not find logo_target.tex");
            if(!texrenderer) MILO_WARN("Could not find band_logo.rndtex");
            if(!texrenderer) MILO_WARN("Could not find logo.mat");
        }
    }
}

#pragma push
#pragma pool_data off
void TrackPanelDir::SetupApplauseMeter(int i1, const char* c2, const char* c3, RndDir* dir4, RndDir* dir5, bool b6, Symbol s7){
    if(b6){
        Find<BandLabel>("other_band_name.lbl", true)->SetTextToken(c3);
        Find<BandLabel>("this_band_name.lbl", true)->SetTextToken(c2);
        if(mBandLogoRival && dir5) SetBotbBandIcon(mBandLogoRival, dir5, false);
        if(mBandLogo && dir4) SetBotbBandIcon(mBandLogo, dir4, true);
        Find<RndGroup>("applause_meter.grp", true)->SetShowing(true);
    }
    if(mScoreboard){
        static Message set_opponent_score("set_opponent_score", 0);
        if(s7 == stars){
            set_opponent_score[0] = (float)i1 / 100.0f;
        }
        else set_opponent_score[0] = i1;
        mScoreboard->HandleType(set_opponent_score);
        static Message set_config("set_config", "botb");
        if(s7 == stars){
            SetApplauseMeterScale(i1, 0);
            set_config[0] = "botb_star";
            unk2ac = true;
        }
        else if(s7 == streak){
            SetApplauseMeterScale(i1, 0);
            set_config[0] = "botb";
            unk2ac = false;
        }
        else {
            set_config[0] = "botb";
            unk2ac = true;
        }
        mScoreboard->HandleType(set_config);
    }
}
#pragma pop

void TrackPanelDir::SetApplauseMeterScale(int i1, int i2){
    if(mApplauseMeter){
        mApplauseMeter->SetProperty(max_diff, i1);
        mApplauseMeter->SetProperty(tie_window, tie_window);
    }
}

void TrackPanelDir::FadeBotbBandNames(bool b){
    if(b) Find<EventTrigger>("botb_band_names_fade_in.trig", true)->Trigger();
    else Find<EventTrigger>("botb_band_names_fade_out.trig", true)->Trigger();
}

void TrackPanelDir::CleanUpChordMeshes(){
    for(int i = 0; i < mGemTracks.size(); i++){
        mGemTracks[i]->FreeChordMeshes();
    }
}

TrackInstrument TrackPanelDir::GetInstrument(int trackIdx) const {
    MILO_ASSERT_RANGE(trackIdx, 0, mInstruments.size(), 0x275);
    return mInstruments[trackIdx];
}

void TrackPanelDir::DisablePlayer(int idx, bool enable){
    if(idx != -1){
        if(GetInstrument(idx) != kInstVocals) UnisonEnd();
        static Hmx::Object* gameMode = FindObject("gamemode", true);
        if(mCrowdMeter && gameMode){
            if(gameMode->Property("update_crowd_meter", true)->Int()){
                if(enable){
                    mCrowdMeter->EnablePlayer(idx);
                    mCrowdMeter->PlayerIcon(idx)->SetState(kCrowdMeterFailed, false);
                }
                else mCrowdMeter->DisablePlayer(idx);
            }
        }
        if(mEndingBonus) mEndingBonus->DisablePlayer(idx);
    }
}

void TrackPanelDir::EnablePlayer(int idx){
    if(idx != -1){
        GetInstrument(idx);
        static Hmx::Object* gameMode = FindObject("gamemode", true);
        if(mCrowdMeter && gameMode){
            if(gameMode->Property("update_crowd_meter", true)->Int()){
                mCrowdMeter->EnablePlayer(idx);
            }
        }
        if(mEndingBonus) mEndingBonus->EnablePlayer(idx);
    }
}

void TrackPanelDir::Reset(){
    ResetAll();
    SetMultiplier(1, false);
    mBandScoreMultiplier->HandleType(reset_msg);
    mCrowdMeter->SetTrackPanel(mTrackPanel);
    mCrowdMeter->Reset();
    mCrowdMeter->UpdatePlayers(mInstruments);
    unk2ad = false;
    if(mEndingBonus){
        mEndingBonus->mTrackOrder.clear();
        if(mTrackPanel){
            mTrackPanel->GetTrackOrder(&mEndingBonus->mTrackOrder, false);
        }
        else {
            for(int i = 0; i < mInstruments.size(); i++){
                mEndingBonus->mTrackOrder.push_back(mInstruments[i]);
            }
        }
        mEndingBonus->Reset();
        for(int i = 0; i < mTracks.size(); i++){
            if(mTracks[i]){
                mEndingBonus->SetIconText(i, mTracks[i]->GetTrackIcon());
                mEndingBonus->EnablePlayer(i);
            }
        }
    }
    UpdateTrackSpeed();
    if(mTrackPanel){
        bool show = mTrackPanel->ShowApplauseMeter();
        if(show){
            mApplauseMeter->HandleType(reset_msg);
        }
        Find<RndGroup>("applause_meter.grp", true)->SetShowing(show);
        static Message set_config("set_config", "");
        set_config[0] = show ? "botb" : "normal";
        if(mScoreboard) mScoreboard->HandleType(set_config);
    }
    mPerformanceMode = ModifierActive("mod_nohud");
    for(int i = 0; i < mTracks.size(); i++){
        BandTrack* track = mTracks[i];
        if(track) track->SetPerformanceMode(mPerformanceMode);
    }
    SetShowing(false);
    mTracksExtended = false;
    if(TheLoadMgr.EditMode()) PlayIntro();
}

void TrackPanelDir::ResetAll(){
    Find<EventTrigger>("reset_all.trig", true)->Trigger();
    mVocalTrack->Retract(true);
    for(int i = 0; i < mGemTracks.size(); i++){
        GemTrackDir* track = mGemTracks[i];
        if(track) track->Retract(true);
    }
}

void TrackPanelDir::ResetPlayers(){
    mInstruments.clear();
    mInstruments.resize(mTrackPanel->GetTrackCount(), kInstNone);
    mTracks.clear();
    unk24c = 0;
    unk250 = 0;
    for(int i = 0; i < mGemTracks.size(); i++){
        mGemTracks[i]->SetUsed(false);
    }
    mVocalTrack->SetUsed(false);
}

void TrackPanelDir::PlayIntro(){
    Find<EventTrigger>("intro.trig", true)->Trigger();
    for(int i = 0; i < mTracks.size(); i++){
        BandTrack* track = mTracks[i];
        if(track) track->PlayIntro();
    }
    SetShowing(!mPerformanceMode);
    mTracksExtended = true;
}

void TrackPanelDir::HideScore(){
    Find<EventTrigger>("reset_all.trig", true)->Trigger();
}

void TrackPanelDir::SetMultiplier(int mult, bool b){
    if(b) mBandScoreMultiplier->SetProperty("last_multiplier", -1);
    if(mult != mBandScoreMultiplier->Property("last_multiplier", true)->Int()){
        if(unk2ac && (mult > 1) && (!mTrackPanel || mTrackPanel->GetNumPlayers() > 1)){
            static Message set_multiplier("set_multiplier", 1);
            set_multiplier[0] = mult;
            TheTaskMgr.Start(new MessageTask(mBandScoreMultiplier, set_multiplier), kTaskUISeconds, 0);
            mBandScoreMultiplier->SetShowing(true);
            mBandScoreMultiplierTrig->Trigger();
        }
        else {
            mBandScoreMultiplier->SetShowing(false);
            mBandScoreMultiplier->SetProperty("last_multiplier", mult);
        }
        for(int i = 0; i < mTracks.size(); i++){
            BandTrack* track = mTracks[i];
            if(track) track->SetBandMultiplier(mult);
        }
    }
}

void TrackPanelDir::GameOver(){
    for(int i = 0; i < mTracks.size(); i++){
        BandTrack* track = mTracks[i];
        if(track) track->GameOver();
    }
}

void TrackPanelDir::GameWon(){
    Find<EventTrigger>("game_won.trig", true)->Trigger();
    for(int i = 0; i < mTracks.size(); i++){
        BandTrack* track = mTracks[i];
        if(track) track->GameWon();
    }
}

void TrackPanelDir::StartFinale(){
    Find<EventTrigger>("game_won.trig", true)->Trigger();
    TIMER_GET_CYCLES(tick);
    for(int i = 0; i < mTracks.size(); i++){
        mTracks[i]->StartFinale(tick);
    }
}

void TrackPanelDir::GameLost(){
    for(int i = 0; i < mTracks.size(); i++){
        BandTrack* track = mTracks[i];
        if(track) track->StopDeploy();
    }
    UnisonEnd();
    Find<EventTrigger>("game_lost.trig", true)->Trigger();
    GameOver();
    SetMultiplier(1, false);
}

void TrackPanelDir::SetCrowdRating(float f){
    mCrowdMeter->SetCrowd(f);
}

void TrackPanelDir::Coda(){
    if(!unk2ad){
        Hmx::Object* modeobj = FindObject("gamemode", true);
        if(modeobj){
            if(!modeobj->Property("enable_coda", true)->Int()) return;
        }
        if((TheLoadMgr.EditMode() || (mTrackPanel && !mTrackPanel->IsGameOver())) && unk24c){
            Find<EventTrigger>("bre_start.trig", true)->Trigger();
            mEndingBonus->Start(!mTrackPanel->AutoVocals());
            for(int i = 0; i < mTracks.size(); i++){
                BandTrack* track = mTracks[i];
                if(track) track->EnterCoda();
            }
        }
        unk2ad = true;
    }
}

void TrackPanelDir::CodaEnd(){
    if(unk24c){
        mEndingBonus->CodaEnd();
        unk2ad = false;
    }
}

void TrackPanelDir::SetCodaScore(int i){
    if(unk24c) mEndingBonus->SetScore(i);
}

void TrackPanelDir::CodaSuccess(){
    Find<EventTrigger>("bre_success.trig", true)->Trigger();
    if(unk24c) mEndingBonus->Success();
}

void TrackPanelDir::SoloEnd(BandTrack* t, int i, Symbol s){
    t->SoloEnd(i, s);
}

void TrackPanelDir::UnisonStart(int i){
    if(!mPerformanceMode){
        mEndingBonus->UnisonStart(i);
        for(int x = 0; x < mGemTracks.size(); x++){
            GemTrackDir* track = mGemTracks[x];
            if(track->mInUse) track->UnisonStart();
        }
    }
}

void TrackPanelDir::UnisonEnd(){
    if(!mPerformanceMode){
        mEndingBonus->UnisonEnd();
        for(int x = 0; x < mGemTracks.size(); x++){
            GemTrackDir* track = mGemTracks[x];
            if(track->mInUse) track->UnisonEnd();
        }
    }
}

void TrackPanelDir::UnisonSucceed(){
    if(!mPerformanceMode) mEndingBonus->UnisonSucceed();
}

void TrackPanelDir::StartPulseAnims(float f){
    if(mPulseAnimGrp){
        mPulseAnimGrp->Animate(0, false, f, RndAnimatable::k480_fpb, 0, 960.0f, 0, 1.0f, loop);
    }
}

BEGIN_HANDLERS(TrackPanelDir)
    HANDLE_ACTION(game_won, GameWon())
    HANDLE_ACTION(game_lost, GameLost())
    HANDLE_ACTION(game_skip, GameLost())
    HANDLE_ACTION(set_crowd_rating, SetCrowdRating(_msg->Float(2)))
    HANDLE_ACTION(game_won_finale, GameWon())
    HANDLE_EXPR(tracks_extended, TracksExtended())
    HANDLE_SUPERCLASS(TrackPanelDirBase)
    HANDLE_CHECK(0x3F3)
END_HANDLERS

BEGIN_PROPSYNCS(TrackPanelDir)
    SYNC_PROP(vocals, mVocals)
    SYNC_PROP(vocals_net, mVocalsNet)
    SYNC_PROP(instrument_A, mGemInst[0])
    SYNC_PROP(inst_A_net, mGemNet[0])
    SYNC_PROP(instrument_B, mGemInst[1])
    SYNC_PROP(inst_B_net, mGemNet[1])
    SYNC_PROP(instrument_C, mGemInst[2])
    SYNC_PROP(inst_C_net, mGemNet[2])
    SYNC_PROP(instrument_D, mGemInst[3])
    SYNC_PROP(inst_D_net, mGemNet[3])
    SYNC_PROP(test_multiplier, mTestMultiplier)
    SYNC_SUPERCLASS(TrackPanelDirBase)
END_PROPSYNCS
