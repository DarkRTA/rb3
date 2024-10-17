#include "meta_band/TrainingMgr.h"
#include "beatmatch/TrackType.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "meta_band/LessonMgr.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include <cstddef>

namespace {
    TrainingMgr* TheTrainingMgr;
}

TrainingMgr::TrainingMgr() : mUser(0), mMinimumDifficulty(kDifficultyEasy), mReturnScreen(gNullStr), mQuitToken(gNullStr), mCurrentLesson(1) {
    SetName("training_mgr", ObjectDir::Main());
}

TrainingMgr::~TrainingMgr(){

}

void TrainingMgr::Init(){
    MILO_ASSERT(TheTrainingMgr == NULL, 0x2C);
    TheTrainingMgr = new TrainingMgr();
}

TrainingMgr* TrainingMgr::GetTrainingMgr(){ return TheTrainingMgr; }

void TrainingMgr::SetUser(LocalBandUser* pUser){
    MILO_ASSERT(pUser, 0x3E);
    mUser = pUser;
}

void TrainingMgr::UnparticipateUsers(){
    std::vector<LocalBandUser*> users;
    TheBandUserMgr->GetLocalBandUsersInSession(users);
    for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
        LocalBandUser* pLocalBandUser = *it;
        MILO_ASSERT(pLocalBandUser, 0x4E);
        if(pLocalBandUser != mUser){
            pLocalBandUser->mParticipating = false;
        }
    }
}

void TrainingMgr::ParticipateUsers(){
    std::vector<LocalBandUser*> users;
    TheBandUserMgr->GetLocalBandUsersInSession(users);
    for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
        LocalBandUser* pLocalBandUser = *it;
        MILO_ASSERT(pLocalBandUser, 0x5D);
        pLocalBandUser->mParticipating = true;
    }
}

void TrainingMgr::SetDifficulty(Difficulty d){
    MILO_ASSERT(mUser, 100);
    mUser->SetDifficulty(d);
}

void TrainingMgr::SetPreferredScoreType(ScoreType ty){
    MILO_ASSERT(mUser, 0x6A);
    mUser->SetPreferredScoreType(ty);
}

void TrainingMgr::SetTrackType(TrackType ty){
    MILO_ASSERT(mUser, 0x70);
    mUser->SetTrackType(ty);
}

void TrainingMgr::SetMinimumDifficulty(Difficulty d){ mMinimumDifficulty = d; }

void TrainingMgr::SetReturnInfo(Symbol s1, Symbol s2){
    mReturnScreen = s1;
    mQuitToken = s2;
}

void TrainingMgr::SetCurrentLesson(int cur){ mCurrentLesson = cur; }
void TrainingMgr::ClearCurrentLesson(){ mCurrentLesson = 1; }

Symbol TrainingMgr::GetModeFromLessonName(Symbol s){
    LessonMgr* pLessonMgr = LessonMgr::GetLessonMgr();
    MILO_ASSERT(pLessonMgr, 0x8C);
    Lesson* pLesson = pLessonMgr->GetLesson(s);
    MILO_ASSERT(pLesson, 0x8F);
    return pLesson->mTrainer;
}

Symbol TrainingMgr::GetModeFromTrackType(TrackType ty){
    Symbol ret;
    if(ty == kTrackRealGuitar){
        ret = pro_song_lessons_real_guitar;
    }
    else if(ty == kTrackRealBass){
        ret = pro_song_lessons_real_guitar;
    }
    else if(ty == kTrackRealKeys){
        ret = pro_song_lessons_keyboard;
    }
    else {
        MILO_ASSERT(0, 0xA6);
    }
    return ret;
}

TrackType TrainingMgr::GetTrackTypeFromLessonName(Symbol s){
    LessonMgr* pLessonMgr = LessonMgr::GetLessonMgr();
    MILO_ASSERT(pLessonMgr, 0xAE);
    Lesson* pLesson = pLessonMgr->GetLesson(s);
    MILO_ASSERT(pLesson, 0xB1);
    return pLesson->mTrackType;
}

Symbol TrainingMgr::GetSongFromLessonName(Symbol s){
    LessonMgr* pLessonMgr = LessonMgr::GetLessonMgr();
    MILO_ASSERT(pLessonMgr, 0xBB);
    Lesson* pLesson = pLessonMgr->GetLesson(s);
    MILO_ASSERT(pLesson, 0xBE);
    return pLesson->mSong;
}

Difficulty TrainingMgr::GetDifficultyFromLessonName(Symbol s){
    LessonMgr* pLessonMgr = LessonMgr::GetLessonMgr();
    MILO_ASSERT(pLessonMgr, 0xC8);
    Lesson* pLesson = pLessonMgr->GetLesson(s);
    MILO_ASSERT(pLesson, 0xCB);
    return pLesson->GetDifficulty();
}

BEGIN_HANDLERS(TrainingMgr)
    HANDLE_ACTION(set_user, SetUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(get_user, mUser)
    HANDLE_ACTION(unparticipate_users, UnparticipateUsers())
    HANDLE_ACTION(participate_users, ParticipateUsers())
    HANDLE_ACTION(set_track_type, SetTrackType((TrackType)_msg->Int(2)))
    HANDLE_ACTION(set_preferred_score_type, SetPreferredScoreType((ScoreType)_msg->Int(2)))
    HANDLE_ACTION(set_difficulty, SetDifficulty((Difficulty)_msg->Int(2)))
    HANDLE_ACTION(set_minimum_difficulty, SetMinimumDifficulty((Difficulty)_msg->Int(2)))
    HANDLE_EXPR(get_minimum_difficulty, mMinimumDifficulty)
    HANDLE_ACTION(set_return_info, SetReturnInfo(_msg->Sym(2), _msg->Sym(3)))
    HANDLE_EXPR(get_return_screen, mReturnScreen)
    HANDLE_EXPR(get_quit_token, mQuitToken)
    HANDLE_ACTION(set_current_lesson, SetCurrentLesson(_msg->Int(2)))
    HANDLE_EXPR(get_current_lesson, mCurrentLesson)
    HANDLE_ACTION(clear_current_lesson, ClearCurrentLesson())
    HANDLE_EXPR(get_mode_from_lesson_name, GetModeFromLessonName(_msg->Sym(2)))
    HANDLE_EXPR(get_mode_from_track_type, GetModeFromTrackType((TrackType)_msg->Int(2)))
    HANDLE_EXPR(get_track_type_from_lesson_name, GetTrackTypeFromLessonName(_msg->Sym(2)))
    HANDLE_EXPR(get_song_from_lesson_name, GetSongFromLessonName(_msg->Sym(2)))
    HANDLE_EXPR(get_difficulty_from_lesson_name, GetDifficultyFromLessonName(_msg->Sym(2)))
    HANDLE_CHECK(0x102)
END_HANDLERS