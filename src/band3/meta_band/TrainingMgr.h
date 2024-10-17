#pragma once
#include "beatmatch/TrackType.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "obj/Object.h"

class TrainingMgr : public Hmx::Object {
public:
    TrainingMgr();
    virtual ~TrainingMgr();
    virtual DataNode Handle(DataArray*, bool);

    void SetUser(LocalBandUser*);
    void ParticipateUsers();
    void UnparticipateUsers();
    void SetDifficulty(Difficulty);
    void SetPreferredScoreType(ScoreType);
    void SetTrackType(TrackType);
    void SetMinimumDifficulty(Difficulty);
    void SetReturnInfo(Symbol, Symbol);
    void SetCurrentLesson(int);
    void ClearCurrentLesson();
    Symbol GetModeFromLessonName(Symbol);
    Symbol GetModeFromTrackType(TrackType);
    TrackType GetTrackTypeFromLessonName(Symbol);
    Symbol GetSongFromLessonName(Symbol);
    Difficulty GetDifficultyFromLessonName(Symbol);

    static void Init();
    static TrainingMgr* GetTrainingMgr();

    LocalBandUser* mUser; // 0x1c
    Difficulty mMinimumDifficulty; // 0x20
    Symbol mReturnScreen; // 0x24
    Symbol mQuitToken; // 0x28
    int mCurrentLesson; // 0x2c
};
