#pragma once
#include "Shuttle.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/BeatMasterSink.h"
#include "game/BandUser.h"
#include "game/Player.h"
#include "game/SongDB.h"
#include "math/Interp.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "os/DiscErrorMgr_Wii.h"
#include "os/Timer.h"
#include "types.h"
#include "utl/SongPos.h"

class Game : public BeatMasterSink, public Hmx::Object, public DiscErrorMgrWii::Callback {
public:
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
    virtual void Beat(int, int);
    virtual void UpdateSongPos(const SongPos &);
    virtual void HandleSubmix(int, const char *);
    virtual DataNode Handle(DataArray *, bool);
    virtual void DiscErrorEnd() {}

    void SetPaused(bool, bool, bool);
    void SetGameOver(bool);
    bool ResumedNoScore() const;
    bool IsActiveUser(BandUser *) const;
    bool IsWaiting();
    float GetMusicSpeed();
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
    bool InTrainer() const { return mProperties.mInTrainer; }
    bool InDrumTrainer() const { return mProperties.mInDrumTrainer; }
    bool CodaEnabled() const { return mProperties.mEnableCoda; }

    Properties mProperties; // 0x24
    SongPos mSongPos; // 0x40
    SongDB *mSongDB; // 0x54
    int unk58;
    BeatMaster *mMaster; // 0x5c
    std::vector<int> unk60;
    bool mIsPaused; // 0x68
    bool unk69;
    bool unk6a;
    bool unk6b;
    bool unk6c;
    bool unk6d;
    bool unk6e;
    bool unk6f;
    float unk70;
    int unk74;
    Timer unk78;
    int unka8;
    float unkac;
    bool unkb0;
    float unkb4;
    bool unkb8;
    bool unkb9;
    int unkbc;
    float unkc0;
    bool unkc4;
    int unkc8;
    int unkcc;
    int unkd0;
    Shuttle *mShuttle; // 0xd4
    int unkd8;
    float unkdc;
    ATanInterpolator mInterpolator; // 0xe0
    float unk11c;
    bool unk120;
    bool unk121;
    float unk124;
    float unk128;
    bool unk12c;
    float unk130;
    float unk134;
    bool unk138;
    bool unk139;
    int unk13c;
    float unk140;
    int unk144;
    bool unk148;
    float unk14c;
    bool unk150;
    std::vector<int> unk154;

    // int unk1c;
    // int unk20;
    // bool unk24;
    // u8 pad[0x40];
    // bool mIsPaused; // 0x68 iunno
    // u8 pad2[115];
    // float unk_0xdc;
};

DECLARE_MESSAGE(GameEndedMsg, "game_ended");
END_MESSAGE
;

extern Game * /*you just lost*/ TheGame;
