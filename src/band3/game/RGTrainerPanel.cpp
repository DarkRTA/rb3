#include "game/RGTrainerPanel.h"
#include "bandobj/BandLabel.h"
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
#include "os/Debug.h"
#include "rndobj/Anim.h"
#include "utl/Messages4.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

RGTrainerPanel* TheRGTrainerPanel;

void ProTrainerPanel::Enter(){
    GemTrainerPanel::Enter();
    if(mGemPlayer){
        LocalBandUser* localuser = mGemPlayer->unk230->GetLocalBandUser();
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
        LocalBandUser* localuser = mGemPlayer->unk230->GetLocalBandUser();
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
        BandUser* user = mGemPlayer->unk230;
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

void RGTrainerPanel::SetLegendMode(bool b){
    unke5 = true;
    mLegendMode = b;
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

Symbol RGTrainerPanel::RGStringToken(int, bool){
    
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