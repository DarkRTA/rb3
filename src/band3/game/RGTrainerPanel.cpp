#include "game/RGTrainerPanel.h"
#include "beatmatch/RGUtl.h"
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

RGTrainerPanel::RGTrainerPanel() : unke4(0), unke5(0), unke8(-1), unkec(-1.0f), unkf0(0), unk24c(0) {

}

RGTrainerPanel::~RGTrainerPanel(){
    
}