#include "game/RGTrainerPanel.h"
#include "bandobj/BandLabel.h"
#include "bandtrack/GemTrack.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/RGState.h"
#include "beatmatch/RGUtl.h"
#include "beatmatch/TrackType.h"
#include "game/Defines.h"
#include "game/GameMode.h"
#include "game/GemTrainerPanel.h"
#include "game/ProTrainerPanel.h"
#include "game/TrainerPanel.h"
#include "meta_band/AppLabel.h"
#include "meta_band/BandProfile.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMgr.h"
#include "obj/ObjMacros.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "rndobj/Anim.h"
#include "rndobj/EventTrigger.h"
#include "synth/Sequence.h"
#include "synth/Sfx.h"
#include "synth/Synth.h"
#include "utl/DataPointMgr.h"
#include "utl/Messages.h"
#include "utl/Messages4.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

RGTrainerPanel* TheRGTrainerPanel;

void ProTrainerPanel::Enter(){
    GemTrainerPanel::Enter();
    if(mGemPlayer){
        LocalBandUser* localuser = mGemPlayer->GetUser()->GetLocalBandUser();
        BandProfile* profile = TheProfileMgr.GetProfileForUser(localuser);
        if(!profile) return;
        int songID = TheSongMgr->GetSongIDFromShortName(MetaPerformer::Current()->Song(), true);
        Difficulty diff = localuser->GetDifficulty();
        mSpeedCompleted.resize(GetNumSections());
        for(int i = 0; i < GetNumSections(); i++){
            if(IsSongSectionComplete(profile, songID, diff, i)){
                mSpeedCompleted[i] = 1.0f;
            }
            else mSpeedCompleted[i] = 0;
        }
    }
    RndDir* legendDir = mDir->Find<RndDir>("chord_legend", true);
    for(int i = 1; i <= 0x16; i++){
        const char* labelstr = MakeString("fret_%02d.lbl", i);
        BandLabel* fretLabel = legendDir->Find<BandLabel>(labelstr, true);
        fretLabel->SetInt(i, false);
    }
    for(int i = 0; i < 6; i++){
        const char* labelstr = MakeString("string_%02d.lbl", i + 1);
        AppLabel* appLabel = legendDir->Find<AppLabel>(labelstr, true);
        appLabel->SetPitch(RGGetTuning(i), 0);
    }
}

void ProTrainerPanel::SetLessonComplete(int lesson){
    if(!TheGameMode->Property("song_lessons", true)->Int()){
        TrainerPanel::SetLessonComplete(lesson);
    }
    else {
        LocalBandUser* localuser = mGemPlayer->GetUser()->GetLocalBandUser();
        BandProfile* profile = TheProfileMgr.GetProfileForUser(localuser);
        if(profile){
            int songID = TheSongMgr->GetSongIDFromShortName(MetaPerformer::Current()->Song(), true);
            Difficulty diff = localuser->GetDifficulty();
            static Message msg("get_speed_modifier", 0);
            msg[0] = lesson;
            DataNode handled = Handle(msg, true);
            mSpeedCompleted[GetCurrSection()] = std::max(mSpeedCompleted[GetCurrSection()], handled.Float());
            SetSongSectionComplete(profile, songID, diff, GetCurrSection());
        }
    }
}

float ProTrainerPanel::GetLessonCompleteSpeed(int lessonNum) const {
    if(!TheGameMode->Property("song_lessons", true)->Int()){
        return GemTrainerPanel::GetLessonCompleteSpeed(lessonNum);
    }
    else {
        MILO_ASSERT(lessonNum < mSpeedCompleted.size(), 0x79);
        return mSpeedCompleted[lessonNum];
    }
}

bool ProTrainerPanel::AllSectionsFinished() const {
    if(!TheGameMode->Property("song_lessons", true)->Int()){
        return TrainerPanel::AllSectionsFinished();
    }
    else {
        for(int i = 0; i < mSpeedCompleted.size(); i++){
            if(mSpeedCompleted[i] < 1.0f) return false;
        }
        return true;
    }
}

void ProTrainerPanel::NewDifficulty(int i1, int i2){
    GemTrainerPanel::NewDifficulty(i1, i2);
    for(int i = 0; i < mSpeedCompleted.size(); i++){
        mSpeedCompleted[i] = 0;
    }
}

RGTrainerPanel::RGTrainerPanel() : mLegendMode(0), unke5(0), mLegendGemID(-1), unkec(-1.0f), mLefty(0), mIsBass(0) {

}

RGTrainerPanel::~RGTrainerPanel(){

}

void RGTrainerPanel::SetupIsBass(){
    if(mTrack){
        mIsBass = mTrack->GetType() == real_bass;
    }
    else if(mGemPlayer){
        BandUser* user = mGemPlayer->GetUser();
        if(user){
            switch(user->GetTrackType()){
                case kTrackRealGuitar:
                case kTrackRealGuitar22Fret:
                    mIsBass = false;
                    break;
                case kTrackRealBass:
                case kTrackRealBass22Fret:
                    mIsBass = true;
                    break;
                default:
                    break;
            }
        }
    }
}

void RGTrainerPanel::Enter(){
    TheRGTrainerPanel = this;
    ProTrainerPanel::Enter();
    SetupIsBass();
    unkec = -1.0f;
    mTutor.Clear();
    mChordLegend = mDir->Find<RndDir>("chord_legend", true);
}

void RGTrainerPanel::Exit(){
    GemTrainerPanel::Exit();
    TheRGTrainerPanel = 0;
}

void RGTrainerPanel::Poll(){
    GemTrainerPanel::Poll();
    if(mGemPlayer){
        if(unke5){
            SetLegendModeImpl(mLegendMode);
            unke5 = false;
        }
        if(mLegendMode){
            HandleChordLegend(true);
        }
    }
}

void RGTrainerPanel::HandleChordLegend(bool b){
    if(mLefty != mGemPlayer->GetUser()->GetGameplayOptions()->GetLefty()){
        HandleLegendLefty(true);
    }
    GemTrack* track = dynamic_cast<GemTrack*>(mGemPlayer->GetUser()->mTrack);
    MILO_ASSERT(track, 0xEF);
    if(mLegendGemID >= 0){
        if(mLegendGemID < unk60[GetDifficulty()]->NumGems()){
            GameGem& gem = unk60[GetDifficulty()]->GetGem(mLegendGemID);
            if(b){
                float secs = TheTaskMgr.Seconds(TaskMgr::b);
        //         dVar19 = (double)TaskMgr::Seconds((TaskMgr *)&TheTaskMgr,1);
        //         fVar2 = *(float *)this_01;
        //         if (fVar2 < (float)(dVar19 * 1000.0)) {
        //           fVar3 = (float)(dVar19 * 1000.0) - 16.0;
        //           if (fVar3 < fVar2) {
        //             fVar3 = fVar2;
        //           }
        //           TaskMgr::SetSeconds((TaskMgr *)&TheTaskMgr,fVar3 / 1000.0,false);
        //           (**(code **)(*(int *)(*(int *)(iVar7 + 0x74) + 4) + 0x1c4))();
        //         }
            }
            bool boolbuf[12];
            bool masterbool = true;
            for(int i = 0; i < mFingerSteps.size(); i++){
                bool thisbool = mFingerSteps[i].unk10;
                boolbuf[i] = thisbool;
                masterbool &= thisbool;
            }
            bool fingertest = TestFingers(gem);
            if(!gem.IsMuted()){
                for(int i = 0; i < mFingerSteps.size(); i++){
                    FingerStep& cur = mFingerSteps[i];
                    if(boolbuf[i] != cur.unk10){
                        const char* stepproganimstr = MakeString("step_progress_%02d.anim", i + 1);
                        RndAnimatable* stepproganim = mDir->Find<RndAnimatable>(stepproganimstr, true);

                        if(cur.unk10){
                            stepproganim->SetFrame(19.0f, 1);
                            mDir->Find<Sfx>("fret_success.cue", true)->Play(0, 0, 0);
                        }
                        else {
                            if(cur.mHighString < 0){
                                if(mMatcher.GetState()->GetFret(cur.mLowString)){
                                    goto lol;
                                }
                                mDir->Find<Sfx>("fret_release.cue", true)->Play(0, 0, 0);
                            }
                            else {
                        lol:
                                mDir->Find<Sequence>("fret_fail.cue", true)->Play(0, 0, 0);
                            }
                            stepproganim->SetFrame(0, 1);
                        }
                    }
                }
                if(masterbool != fingertest){
                    const char* stepproganimstr = MakeString("step_progress_%02d.anim", mFingerSteps.size() + 1);
                    RndAnimatable* stepproganim = mDir->Find<RndAnimatable>(stepproganimstr, true);
                    if(fingertest){
                        stepproganim->SetFrame(19.0f, 1);
                    }
                    else {
                        stepproganim->SetFrame(0, 1);
                    }                    
                }
            }
        }
    }
}

void RGTrainerPanel::StrumString(int str){
    if(mLegendMode){
        static Message msg("strum_string", 0);
        msg[0] = str + 1;
        Handle(msg, true);
    }
}

// these params correspond to fret and string, just not sure atm which is which
void RGTrainerPanel::SetFret(int i1, int i2){
    if(mLegendMode){
        if(i2 < 0) i2 = 0;
        FretButtonDown(PackRGData(i1, i2));
        static Message msg("set_finger_fret", 0, 0);
        msg[0] = i1 + 1;
        msg[1] = i2;
        Handle(msg, true);
    }
}

void RGTrainerPanel::Swing(int i){
    if(mLegendMode){
        if(TheTaskMgr.UISeconds() - unkec < 0.3f) return;
        mMatcher.Swing(i, TheTaskMgr.UISeconds() * 1000.0f);
        if(mMatcher.FretMatch(mPattern[mLegendGemID % mPattern.size()], 100.0f, TheTaskMgr.UISeconds() * 1000.0f, 0, TheTaskMgr.UISeconds() * 1000.0f, false, false, (RGMatchType)0)){
            GameGem& gem = unk60[GetDifficulty()]->GetGem(mLegendGemID);
            gem.mPlayed = true;
            Handle(end_chord_legend_msg, true);
        }
    }
}

void RGTrainerPanel::FretButtonDown(int i){
    if(mGemPlayer){
        mMatcher.FretDown(i, TheTaskMgr.UISeconds() * 1000.0f);
    }
}

void RGTrainerPanel::FretButtonUp(int i){
    mMatcher.FretUp(i, TheTaskMgr.UISeconds() * 1000.0f);
}

int RGTrainerPanel::GetFret(int i, int string) const {
    MILO_ASSERT(string >= 0 && string <= 5, 0x191);
    const GameGem& gem = mPattern[i % mPattern.size()];
    if(!gem.IsMuted()) return gem.GetFret(string);
    else return 0;
}

void RGTrainerPanel::SetLegendMode(bool mode){
    unke5 = true;
    mLegendMode = mode;
}

void RGTrainerPanel::SetLegendModeImpl(bool mode){
    mLegendMode = mode;
    if(mode){
        mMatcher.Reset();
        unkec = TheTaskMgr.UISeconds();
        GameGem& gem = mPattern[mLegendGemID % mPattern.size()];
        for(int i = 0; i < 6U; i++){
            if(gem.GetFret(i) != (char)-1 && gem.GetRGNoteType(i) != 1){
                static Message used("set_string_used", 0);
                used[0] = i;
                mChordLegend->HandleType(used);
            }
            else {
                static Message unused("set_string_unused", 0);
                unused[0] = i;
                mChordLegend->HandleType(unused);
            }
        }
        InitFretSteps(gem);
        HandleChordLegend(false);
        for(int i = 0; i < 6U; i++){
            SetFret(i, mGemPlayer->GetRGFret(i));
        }
        HandleChordLegend(false);
        HandleLegendLefty(mLefty);
        TheSynth->StopAllSfx(false);
        for(int i = 0; i < mLegendGemID - 1; i++){
            // stuff happens here
        }
    }
    else if(mLegendGemID != -1){
        if(mLegendGemID < unk60[GetDifficulty()]->NumGems()){
            GameGem& gem = unk60[GetDifficulty()]->GetGem(mLegendGemID);
            gem.mPlayed = true;
            mLegendGemID = -1;
        }
        else {
            mLegendGemID = -1;
        }
    }
    SendDataPoint("trainers/chord_legend", enter_legend, mode);
}

void RGTrainerPanel::InitFretSteps(const GameGem& gem){
    mFretHand.SetFingers(gem);
    mFingerSteps.clear();
    for(int i = 0; i < 4; i++){
        int fret, lowstr, highstr;
        mFretHand.GetFinger(i, fret, lowstr, highstr);
        if(fret >= 0){
            if(gem.IsMuted()) fret = 0;
            FingerStep step;
            step.mFinger = i;
            step.mFret = fret;
            step.mLowString = lowstr;
            step.mHighString = highstr;
            step.unk10 = 0;
            mFingerSteps.push_back(step);
        }
    }

    if(gem.IsRealGuitarChord()){
        if(gem.IsMuted()){
            RndAnimatable* anim = mDir->Find<RndAnimatable>("num_steps.anim", true);
            anim->SetFrame(2, 1);
            BandLabel* lbl = mDir->Find<BandLabel>("chord_name.lbl", true);
            lbl->SetShowing(false);

            const char* lblstr = MakeString("step_%02d_text.lbl", 1);
            BandLabel* steptextlbl = mDir->Find<BandLabel>(lblstr, true);
            steptextlbl->SetTextToken(rg_chordbook_left_hand_doesnt_matter);

            const char* animstr = MakeString("step_config_%02d.anim", 1);
            RndAnimatable* stepanim = mDir->Find<RndAnimatable>(animstr, false);
            if(stepanim) stepanim->SetFrame(4, 1);

            const char* lblstr2 = MakeString("step_%02d_text.lbl", 2);
            BandLabel* steptextlbl2 = mDir->Find<BandLabel>(lblstr2, true);
            steptextlbl2->SetTextToken(rg_chordbook_step_strum);

            const char* animstr2 = MakeString("step_config_%02d.anim", 2);
            RndAnimatable* stepanim2 = mDir->Find<RndAnimatable>(animstr2, false);
            if(stepanim2) stepanim2->SetFrame(4, 1);
        }
        else {
            RndAnimatable* anim = mDir->Find<RndAnimatable>("num_steps.anim", true);
            anim->SetFrame(mFingerSteps.size() + 1, 1);
            BandLabel* lbl = mDir->Find<BandLabel>("chord_name.lbl", true);
            lbl->SetShowing(true);
            for(int i = 0; i < mFingerSteps.size(); i++){
                UpdateStepText(i, mFingerSteps[i]);
            }
            const char* lblstr = MakeString("step_%02d_text.lbl", mFingerSteps.size() + 1);
            BandLabel* steptextlbl = mDir->Find<BandLabel>(lblstr, true);
            steptextlbl->SetTextToken(rg_chordbook_step_strum);
            const char* animstr = MakeString("step_config_%02d.anim", mFingerSteps.size() + 1);
            RndAnimatable* stepanim = mDir->Find<RndAnimatable>(animstr, false);
            if(stepanim) stepanim->SetFrame(4, 1);
            for(int i = 0; i < mFingerSteps.size(); i++){
                const char* proganimstr = MakeString("step_progress_%02d.anim", i + 1);
                RndAnimatable* proganim = mDir->Find<RndAnimatable>(proganimstr, true);
                proganim->SetFrame(0, 1);
            }
        }
    }
    else {
        RndAnimatable* anim = mDir->Find<RndAnimatable>("num_steps.anim", true);
        anim->SetFrame(0, 1);
        BandLabel* lbl = mDir->Find<BandLabel>("chord_name.lbl", true);
        lbl->SetShowing(false);
    }
}

void RGTrainerPanel::UpdateStepText(int i, FingerStep& step){
    const char* labelstr = MakeString("step_%02d_text.lbl", i + 1);
    BandLabel* label = mDir->Find<BandLabel>(labelstr, true);
    static Message set_step_text("set_step_text", 0, 0, 0, 0, 0);
    set_step_text[0] = label;
    if(step.mHighString >= 0){
        set_step_text[1] = rg_chordbook_step_barre;
    }
    else {
        set_step_text[1] = rg_chordbook_step_finger;
    }
    set_step_text[2] = step.mFret;
    set_step_text[3] = RGStringToken(step.mLowString, false);
    if(step.mHighString >= 0){
        set_step_text[4] = RGStringToken(step.mHighString, false);
    }
    else {
        set_step_text[4] = set_step_text[3];
    }
    Handle(set_step_text, true);    
    const char* animstr = MakeString("step_config_%02d.anim", i + 1);
    RndAnimatable* stepcfganim = mDir->Find<RndAnimatable>(animstr, true);
    stepcfganim->SetFrame((float)step.mFinger + 0.001f, 1);
}

#define kMaxRGStrings 6U

Symbol RGTrainerPanel::RGStringToken(int str, bool abbrev){
    MILO_ASSERT(str <= kMaxRGStrings, 0x283);
    static Symbol stringTokens[6] = {
        "rg_chordbook_low_e_string",
        "rg_chordbook_a_string",
        "rg_chordbook_d_string",
        "rg_chordbook_g_string",
        "rg_chordbook_b_string",
        "rg_chordbook_high_e_string"
    };
    static Symbol stringTokensAbbrev[6] = {
        "rg_chordbook_low_e_short",
        "rg_chordbook_a_short",
        "rg_chordbook_d_short",
        "rg_chordbook_g_short",
        "rg_chordbook_b_short",
        "rg_chordbook_high_e_short"
    };
    if(abbrev){
        return stringTokensAbbrev[str];
    }
    else {
        return stringTokens[str];
    }
}

void RGTrainerPanel::HandleLegendLefty(bool b){
    mLefty = mGemPlayer->GetUser()->GetGameplayOptions()->GetLefty();
    float f2, f12;
    if(mLefty){
        f2 = 0.0f;
        f12 = 1.0f;
    }
    else {
        f2 = 1.0f;
        f12 = 0.0f;
    }
    RndDir* legendDir = mDir->Find<RndDir>("chord_legend", true);
    RndAnimatable* leftyAnim = legendDir->Find<RndAnimatable>("lefty_flip.anim", true);
    if(b){
        leftyAnim->Animate(f12, f12, kTaskUISeconds, 0, 0);
    }
    else {
        leftyAnim->SetFrame(f12, f2);
    }
    GemTrack* track = dynamic_cast<GemTrack*>(mGemPlayer->GetUser()->mTrack);
    track->UpdateLeftyFlip();
    EventTrigger* trig;
    if(mLefty){
        trig = mDir->Find<EventTrigger>("lefty.trig", true);
    }
    else {
        trig = mDir->Find<EventTrigger>("righty.trig", true);
    }
    trig->Trigger();
    PickFretboardView(unk60[GetDifficulty()]->GetGem(mLegendGemID));
}

bool RGTrainerPanel::TestFingers(const GameGem& gem){
    bool ret = true;
    for(int i = 0; i < mFingerSteps.size(); i++){
        FingerStep& step = mFingerSteps[i];
        step.unk10 = true;
        int i4 = step.mHighString;
        if(i4 < 0) i4 = step.mLowString;
        for(int i = step.mLowString; i <= i4 && step.unk10; i++){
            int rgfret = mMatcher.GetState()->GetFret(i);
            if(step.mFret == gem.GetFret(i) && rgfret != step.mFret){
                step.unk10 = false;
            }
        }
        ret &= step.unk10;
    }
    return ret;
}

bool RGTrainerPanel::GetLegendMode() const { return mLegendMode; }
void RGTrainerPanel::SetLegendGemID(int id){ mLegendGemID = id; }

void RGTrainerPanel::PickFretboardView(const GameGem& gem){
    if(!GetFretboardView(gem)){
        if(mLefty){
            mChordLegend->HandleType(show_high_frets_lefty_msg);
        }
        else {
            mChordLegend->HandleType(show_high_frets_msg);
        }
    }
    else if(mLefty){
        mChordLegend->HandleType(show_low_frets_lefty_msg);
    }
    else {
        mChordLegend->HandleType(show_low_frets_msg);
    }
}

void RGTrainerPanel::SetSongSectionComplete(BandProfile* profile, int i1, Difficulty diff, int i2){
    for(int i = 0; i <= diff; i++){
        if(mIsBass){
            profile->SetProBassSongLessonSectionComplete(i1, (Difficulty)i, GetCurrSection());
        }
        else {
            profile->SetProGuitarSongLessonSectionComplete(i1, (Difficulty)i, GetCurrSection());
        }
        if(AllSectionsFinished()){
            if(mIsBass){
                profile->SetProBassSongLessonComplete(i1, (Difficulty)i);
            }
            else {
                profile->SetProGuitarSongLessonComplete(i1, (Difficulty)i);
            }
        }
    }
}

bool RGTrainerPanel::IsSongSectionComplete(BandProfile* profile, int i1, Difficulty diff, int i2){
    SetupIsBass();
    if(mIsBass){
        return profile->IsProBassSongLessonSectionComplete(i1, diff, i2);
    }
    else {
        return profile->IsProGuitarSongLessonSectionComplete(i1, diff, i2);
    }
}

void RGTrainerPanel::HitNotify(int i){
    mTutor.Hit(i, mPattern[i % mPattern.size()]);
}

void RGTrainerPanel::MissNotify(int i){
    Difficulty diff = mGemPlayer->GetUser()->GetLocalBandUser()->GetDifficulty();
    mTutor.Miss(i, mPattern[i % mPattern.size()], diff);
}

void RGTrainerPanel::Looped(){
    mTutor.Loop();
}

bool RGTrainerPanel::ShouldDrawTab() const {
    return GemTrainerPanel::ShouldDrawTab() && !mLegendMode;
}

void RGTrainerPanel::StartSectionImpl(){
    GemTrainerPanel::StartSectionImpl();
    mTutor.Clear();
}

void RGTrainerPanel::NewDifficulty(int i1, int i2){
    Handle(end_chord_legend_no_rollback_msg, true);
    ProTrainerPanel::NewDifficulty(i1, i2);
}

BEGIN_HANDLERS(ProTrainerPanel)
    HANDLE_SUPERCLASS(GemTrainerPanel)
    HANDLE_CHECK(0x356)
END_HANDLERS

BEGIN_HANDLERS(RGTrainerPanel)
    HANDLE_EXPR(get_fret, GetFret(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(set_legend_mode, SetLegendMode(_msg->Int(2)))
    HANDLE_EXPR(get_legend_mode, mLegendMode)
    HANDLE_ACTION(set_legend_gem_id, SetLegendGemID(_msg->Int(2)))
    HANDLE_SUPERCLASS(ProTrainerPanel)
    HANDLE_CHECK(0x365)
END_HANDLERS