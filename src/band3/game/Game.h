#pragma once
#include "Shuttle.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/BeatMasterSink.h"
#include "beatmatch/FillInfo.h"
#include "game/Band.h"
#include "game/BandUser.h"
#include "game/Player.h"
#include "game/SongDB.h"
#include "game/TrackerManager.h"
#include "math/Interp.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "os/DiscErrorMgr_Wii.h"
#include "os/Timer.h"
#include "utl/SongInfoCopy.h"
#include "utl/SongPos.h"

enum GameState {
    kGameNeedIntro = 0,
    kGameNeedStart = 1,
    kGamePlaying = 2,
    kGameOver = 3
};

enum EndGameResult {
    kRestart = 0,
    kLost = 1,
    kWon = 2,
    kWonFinale = 3,
    kSkip = 4,
    kQuit = 5
};

class Game : public BeatMasterSink, public Hmx::Object, public DiscErrorMgrWii::Callback {
public:
    enum LoadState {
        kLoadingSong = 0,
        kWaitingForAudio = 1,
        kReady = 2
    };

    struct Properties {
        Properties();

        bool mInTrainer; // 0x0
        bool mInDrumTrainer; // 0x1
        bool mInPracticeMode; // 0x2
        bool mAllowOverdrivePhrases; // 0x3
        bool mEndWithSong; // 0x4
        bool mForceUseCymbals; // 0x5
        bool mForceDontUseCymbals; // 0x6
        bool mAllowAutoVocals; // 0x7
        bool mHasSongSections; // 0x8
        bool mLoadChars; // 0x9
        bool mLetterbox; // 0xa
        bool mCrowdReacts; // 0xb
        bool mIsPractice; // 0xc
        bool mEnableWhammy; // 0xd
        bool mEnableCapstrip; // 0xe
        bool mDisableGuitarFx; // 0xf
        bool mDisableKeysFx; // 0x10
        bool mEnableOverdrive; // 0x11
        bool mEnableCoda; // 0x12
        bool mCanSolo; // 0x13
        bool mHasBeatMask; // 0x14
        bool mCanLose; // 0x15
        bool mEnableStreak; // 0x16
        bool mShowStars; // 0x17
        bool mPlayStarSfx; // 0x18
    };
    Game();
    virtual ~Game();
    virtual void Beat(int, int) {}
    virtual void UpdateSongPos(const SongPos &) {}
    virtual void HandleSubmix(int, const char *) {}
    virtual DataNode Handle(DataArray *, bool);
    virtual void DiscErrorEnd();

    void SetPaused(bool, bool, bool);
    void SetGameOver(bool);
    bool ResumedNoScore() const;
    bool IsActiveUser(BandUser *) const;
    bool IsWaiting();
    int NumActivePlayers() const;
    void AddBonusPoints(BandUser *, int, int);
    void OnPlayerAddEnergy(Player *, float);
    void OnRemoteTrackerFocus(Player *, int, int, int);
    void OnRemoteTrackerPlayerProgress(Player *, float);
    void OnRemoteTrackerSectionComplete(Player *, int, int, int);
    void OnRemoteTrackerPlayerDisplay(Player *, int, int, int);
    void OnRemoteTrackerDeploy(Player *);
    void OnRemoteTrackerEndDeployStreak(Player *, int);
    void OnRemoteTrackerEndStreak(Player *, int, int);
    void OnPlayerQuarantined(Player *);
    Band *GetBand();
    void ForceTrackerStars(int);
    void RemovePlayer(Player *);
    void OnPlayerRemoved(Player *);
    void SetBackgroundVolume(float);
    void SetForegroundVolume(float);
    void SetStereo(bool);
    void PopulatePlayerLists();
    void LoadSong();
    bool IsLoaded();
    void PostLoad();
    void PrintBasePoints();
    void ResetVoiceChatState();
    bool IsReady();
    void Start();
    void Go();
    void AddPlayer(BandUser *);
    void SetRealtime(bool);
    void StartIntro();
    void Reset();
    bool HasIntro();
    float GetSongToTaskMgrMs();
    float GetSongMs() const;
    void UpdatePausedState(bool, bool);
    bool CanUserPause() const;
    void Restart(bool);
    void Poll();
    ExcitementLevel GetCrowdExcitement();
    void SetVocalPercussionBank(ObjectDir *);
    void SetDrumKitBank(ObjectDir *);
    Player *GetPlayerFromTrack(int, bool) const;
    float GetMusicSpeed() const;
    void SetMusicSpeed(float);
    void SetPitchMucker(bool);
    void SetMusicVolume(float);
    void SetIntroRealTime(float);
    int GetScoringTracks() const;
    EndGameResult GetResult(bool);
    EndGameResult GetResultForUser(BandUser *);
    Player *GetActivePlayer(int) const;
    void Jump(float, bool);
    void CheckRollbackEnd(float);
    void Replay();
    void Rollback(float, float);
    void EnableWorldPolling(bool);
    bool HandleRollbackAnimation();
    void ResetAudio();
    void SetVocalCueVolume(float);
    void AddMusicFader(Fader *);
    Performer *GetMainPerformer();
    bool AllowInput() const;
    void SetKickAutoplay(bool);
    void SetVocalPercussionBank(Player *, ObjectDir *);
    void SetDrumKitBank(Player *, ObjectDir *);
    void DropUser(BandUser *);
    void AddUser(BandUser *);
    void ReconcilePlayers();
    void SetInvalidScore(bool);
    void SetSkippedSong(bool);
    void SetResumeFraction(float);
    bool IsInvalidScore() const;
    bool SkippedSong() const;
    void OnPlayerSaved(Player *);
    void OvershellSetPaused(bool);
    Symbol GetSectionAtMs(float) const;
    void NeverAllowInput(bool b) { mNeverAllowInput = b; }
    float GetFractionCompleted() const;
    void OnStatsSynced();
    void AdjustForVocalPhrases(float &, float &) const;
    void ClearState();
    void E3CheatAutoplayAccuracy();
    const char *DebugCycleAutoplay();
    const char *DebugCycleAutoplayAccuracy();
    void SetNoFail(bool);

    bool InTrainer() const { return mProperties.mInTrainer; }
    bool InDrumTrainer() const { return mProperties.mInDrumTrainer; }
    bool CodaEnabled() const { return mProperties.mEnableCoda; }
    bool InPracticeMode() const { return mProperties.mInPracticeMode; }
    bool AllowOverdrivePhrases() const { return mProperties.mAllowOverdrivePhrases; }
    std::vector<Player *> &GetActivePlayers();
    BeatMaster *GetBeatMaster() const { return mMaster; }
    FillLogic GetFillLogic() const {
        return mDrumFillsMod ? kFillsRegular : kFillsDeployGemAndInvisible;
    }
    bool DrumFillsMod() const { return mDrumFillsMod; }
    bool IsPaused() const { return mIsPaused; }
    bool InRollback() const { return unkdc != -1.0f ? true : false; }

    DataNode OnJump(const DataArray *);
    DataNode OnLocalUserReadyToPlay(const DataArray *);
    DataNode OnSetShuttle(DataArray *);
    DataNode ForEachActivePlayer(const DataArray *);
    DataNode OnAdjustForVocalPhrases(DataArray *);
    DataNode OnMsg(const LocalUserLeftMsg &);
    DataNode OnMsg(const RemoteUserLeftMsg &);
    DataNode OnMsg(const RemoteLeaderLeftMsg &);
    DataNode OnMsg(const UIScreenChangeMsg &);
    DataNode OnMsg(const class NewOvershellLocalUserMsg &);
    DataNode OnMsg(const class GameEndedMsg &);

    Properties mProperties; // 0x24
    SongPos mSongPos; // 0x40
    SongDB *mSongDB; // 0x54
    SongInfo *mSongInfo; // 0x58
    BeatMaster *mMaster; // 0x5c
    std::vector<Player *> mAllActivePlayers; // 0x60
    bool mIsPaused; // 0x68
    bool mGameWantsPause; // 0x69
    bool mOvershellWantsPause; // 0x6a
    bool unk6b;
    bool unk6c; // 0x6c - screen saver?
    bool mPauseTime; // 0x6d
    bool mRealtime; // 0x6e
    bool unk6f;
    float mTimeOffset; // 0x70
    Timer mTime; // 0x78
    bool mHasIntro; // 0xa8
    float mLastPollMs; // 0xac
    bool mMuckWithPitch; // 0xb0
    float mMusicSpeed; // 0xb4
    bool mNeverAllowInput; // 0xb8
    bool unkb9;
    int mDemoMaxPctComplete; // 0xbc
    float mDemoMaxMs; // 0xc0
    bool unkc4;
    LoadState mLoadState; // 0xc8
    EndGameResult mResult; // 0xcc
    Band *mBand; // 0xd0
    Shuttle *mShuttle; // 0xd4
    float unkd8;
    float unkdc; // 0xdc - mRollbackEndMs?
    ATanInterpolator mInterpolator; // 0xe0
    float unk11c;
    bool unk120;
    bool mSkippedSong; // 0x121
    float unk124;
    float mResumeTime; // 0x128
    bool mInvalidScore; // 0x12c
    float unk130;
    float unk134;
    bool unk138;
    bool mDrumFillsMod; // 0x139
    int unk13c;
    float unk140;
    TrackerManager *mTrackerManager; // 0x144
    bool unk148;
    float mDisablePauseMs; // 0x14c
    bool unk150;
    std::vector<BandUser *> unk154;
};

DECLARE_MESSAGE(GameEndedMsg, "game_ended");
GameEndedMsg(int i, float f) : Message(Type(), i, f) {}
EndGameResult GetResult() const { return (EndGameResult)mData->Int(2); }
END_MESSAGE

void GameInit();
void GameTerminate();

extern Game * /*you just lost*/ TheGame;
