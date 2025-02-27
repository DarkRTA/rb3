#pragma once
#include "GemPlayer.h"
#include "bandtrack/GemManager.h"
#include "beatmatch/GameGem.h"
#include "bandtrack/GemTrack.h"
#include "beatmatch/GameGemList.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/Metronome.h"
#include "game/TrainerGemTab.h"
#include "game/TrainerPanel.h"
#include "ui/UIPanel.h"

class GemTrainerPanel : public TrainerPanel {
public:
    GemTrainerPanel();
    OBJ_CLASSNAME(GemTrainerPanel);
    OBJ_SET_TYPE(GemTrainerPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~GemTrainerPanel();
    virtual void Draw();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void HandlePlayerDeleted(Player *);
    virtual void StartSectionImpl();
    virtual bool ShouldStartEarly() const;
    virtual void UpdateProgressMeter();
    virtual void NewDifficulty(int, int);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual float GetLessonCompleteSpeed(int) const;
    virtual void HitNotify(int) {}
    virtual bool MissNotify(int) { return false; }
    virtual void Looped() {}
    virtual bool ShouldDrawTab() const;
    virtual void PostCopyGems() {}

    void AddBeatMask(int);
    void HandleTrackShifting();
    void HandleLooping();
    bool ShouldLoop(int) const;
    void CopyGems(int);
    bool GetFretboardView(const GameGem &) const;
    int GetPatternSize() const;
    bool IsGemInFutureLoop(int) const;
    void CopyGems(std::vector<GameGem> &, int, int &, int &);
    Difficulty GetDifficulty() const;
    void ClearGems();
    void SetLoopPoints();
    const GameGem &GetLastGameGemInSection(int &) const;
    void SetSpeedRatio(float);
    void ScoreOnFinalGem(int);
    void SetTab(int);
    void EnableMetronome(bool);
    void SetMetronomeVolume(int, int);
    bool ShouldMissCauseFail() const;
    int GetNumLoops() const;
    int NumGems() const { return mPattern.size(); }

    std::vector<GameGem> mPattern; // 0x54
    GemPlayer *mGemPlayer; // 0x5c
    GameGemList *mGameGemLists[kNumDifficulties]; // 0x60
    GemTrack *mTrack; // 0x70
    GemManager *mGemManager; // 0x74
    Difficulty mDifficulty; // 0x78
    LocalBandUser *mLocalUser; // 0x7c
    int mWriteTick; // 0x80
    int mScoreTick; // 0x84
    std::vector<GameGem> mSongGems[kNumDifficulties]; // 0x88
    bool mAddBeatMask; // 0x80
    bool mAddBeatMaskImmediately; // 0xa9
    int mNumLoops; // 0xac
    int unkb0;
    TrainerGemTab *mTab; // 0xb4
    Metronome *mMetronome; // 0xb8
    float unkbc;
    float unkc0;
    float unkc4;
    bool mDrawTab; // 0xc8
    bool unkc9;
    int unkcc;
    bool unkd0;
};

extern GemTrainerPanel *TheGemTrainerPanel;

class GemTrainerLoopPanel : public UIPanel {
public:
    GemTrainerLoopPanel() {}
    OBJ_CLASSNAME(GemTrainerLoopPanel);
    OBJ_SET_TYPE(GemTrainerLoopPanel);
    virtual ~GemTrainerLoopPanel() {}
    virtual void Poll();
};