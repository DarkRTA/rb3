#ifndef BANDOBJ_CROWDAUDIO_H
#define BANDOBJ_CROWDAUDIO_H
#include "obj/Object.h"
#include "rndobj/Poll.h"
#include "synth/BinkClip.h"
#include "synth/Faders.h"
#include "utl/TimeConversion.h"

enum ExcitementLevel {
    kExcitementBoot,
    kExcitementBad,
    kExcitementOkay,
    kExcitementGreat,
    kExcitementPeak,
    kNumExcitements
};

class CrowdAudio : public RndPollable {
    CrowdAudio();
    OBJ_CLASSNAME(CrowdAudio)
    OBJ_SET_TYPE(CrowdAudio)
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();
    virtual ~CrowdAudio();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void SetTypeDef(DataArray*);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);

    void StopAllMoggs();
    void SetEnabled(bool);
    void SetPaused(bool);
    void PlaySequence(const char*);
    void StopSequence(const char*);
    void SetExcitement(ExcitementLevel);
    bool PlayExcitementLoop();
    void MaybeClap(float);
    void UpdateVolume();
    bool PlayLoop(const DataArray*, bool);
    void PlayCloseupAudio();
    void StopCloseupAudio();
    void OnIntro();
    void OnLose();
    void OnOutro();
    void OnMusicStart();
    void OnWin();
    void OnEnd();
    void SetBank(ObjectDir*);

    int MsToLastClapBeat(float f){ return MsToBeat(f); }

    DECLARE_REVS;
    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(CrowdAudio)
    }
    NEW_OBJ(CrowdAudio);

    ObjPtr<BinkClip, ObjectDir> mCurrentMogg; // 0x8
    ObjPtr<BinkClip, ObjectDir> mOldMogg; // 0x14
    ObjPtr<BinkClip, ObjectDir> mFadingMogg; // 0x20
    Fader* mMainFader; // 0x2c
    bool mWantDuck; // 0x30
    float mResultsDuck; // 0x34
    float mResultsFadeDuration; // 0x38
    Fader* mResultsFader; // 0x3c
    float mFadeInFromLoadingDuration; // 0x40
    Fader* mEntryFader; // 0x44
    float mVenueChangeFadeDuration; // 0x48
    ExcitementLevel mLevel; // 0x4c
    ExcitementLevel mOverrideExcitementLevel; // 0x50
    ExcitementLevel mOverrideExcitementLevelPrev; // 0x54
    float mLoopChangeTime; // 0x58
    DataArray* mIntro; // 0x5c
    DataArray* mVenueIntro; // 0x60
    DataArray* mLevels; // 0x64
    DataArray* mVenueOutro; // 0x68
    int mState; // 0x6c - should be enum State?
    float mCrowdVol; // 0x70
    float mCamShotVol; // 0x74
    float mClapOffsetMs; // 0x78
    bool mEnabled; // 0x7c
    bool mCrowdReacts; // 0x7d
    int mLastClapBeat; // 0x80
    bool mClapAllowed; // 0x84
    ObjPtr<ObjectDir, ObjectDir> mBank; // 0x88
    Fader* mCurrentBankFader; // 0x94
    Fader* mOtherBankFader; // 0x98
    Fader* mReleaseFader; // 0x9c
    float mCrossfadeDuration; // 0xa0
    float mReleaseTime; // 0xa4
    bool mPaused; // 0xa8
    bool mShouldPlayVenueIntro; // 0xa9
    bool mShouldPlayVenueOutro; // 0xaa
    bool mWon; // 0xab
    bool mRestarting; // 0xac
    Fader* mCloseupFader; // 0xb0
    float mCloseupFadeDuration; // 0xb4
};

extern CrowdAudio* TheCrowdAudio;

#endif // BANDOBJ_CROWDAUDIO_H