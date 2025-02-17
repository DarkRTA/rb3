#pragma once
#include "bandobj/CrowdAudio.h"
#include "game/DirectInstrument.h"
#include "game/Game.h"
#include "game/GameConfig.h"
#include "game/HitTracker.h"
#include "game/Scoring.h"
#include "rndobj/Overlay.h"
#include "ui/UIPanel.h"
#include "obj/Msg.h"
#include "utl/DeJitter.h"
#include "utl/Profiler.h"

enum LoadingState {
    kLoadingState_NotReady = 0,
    kLoadingState_UILoaded = 1,
    kLoadingState_WorldLoaded = 2,
    kLoadingState_CharsLoaded = 3,
    kLoadingState_Ready = 4
};

class GamePanel : public UIPanel, public MsgSource {
public:
    GamePanel();
    OBJ_CLASSNAME(GamePanel);
    OBJ_SET_TYPE(GamePanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~GamePanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void SetPaused(bool);
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();
    virtual void FinishLoad();
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);

    void Reset();
    void CreateGame();
    void StartGame();
    void RunVocalTest();
    void SetPlayingTrackIntroUntil(float);
    void StartIntro();
    void SetExcitementLevel(ExcitementLevel);
    void UpdateNowBar();
    void SetDejitteredTime(float);
    void UpdateDeltaTimeOverlay();
    void PlayBandDiedCue();
    void SendRestartGameNetMsg(bool);
    void SendResumeNoScoreGameNetMsg(float);
    void ToggleInstrumentSynth();
    void ClearDrawGlitch();
    GameState GetGameState() const { return mGameState; }
    bool IsGameOver() const { return mGameState == kGameOver; }
    void SetGameOver() { mGameState = kGameOver; }

    DataNode OnStartLoadSong(DataArray *);

    Game *mGame; // 0x54
    RndOverlay *mTime; // 0x58
    RndOverlay *mLatency; // 0x5c
    RndOverlay *mDeltaTime; // 0x60
    bool unk64;
    float unk68;
    float unk6c;
    float unk70;
    ObjDirPtr<ObjectDir> mVocalPercussionBank; // 0x74
    ObjDirPtr<ObjectDir> mDrumKitBank; // 0x80
    bool mStartPaused; // 0x8c
    GameState mGameState; // 0x90
    bool mMultiEvent; // 0x94
    GameConfig mConfig; // 0x98
    Scoring *mScoring; // 0xd0
    Profiler mLoadProf; // 0xd4
    ExcitementLevel mExcitement; // 0x128
    ExcitementLevel mLastExcitement; // 0x12c
    bool unk130;
    bool mReplay; // 0x131
    DeJitter mDeJitter; // 0x134
    bool unk150;
    bool unk151;
    float unk154;
    LoadingState mLoadingState; // 0x158
    HitTracker *mHitTracker; // 0x15c
    DirectInstrument *mDirectInstrument; // 0x160
};

class LatencyCallback : public RndOverlay::Callback {
public:
    LatencyCallback() {}
    virtual ~LatencyCallback() {}
    virtual float UpdateOverlay(RndOverlay *, float);
};

extern GamePanel *TheGamePanel;