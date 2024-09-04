#ifndef BANDOBJ_CROWDAUDIO_H
#define BANDOBJ_CROWDAUDIO_H

#include "obj/Object.h"
#include "rndobj/Poll.h"
#include "synth/BinkClip.h"
#include "synth/Faders.h"

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
    void PlayExcitementLoop();
    void MaybeClap(float);
    void UpdateVolume();
    bool PlayLoop(const DataArray*, bool);
    void PlayCloseupAudio();
    void StopCloseupAudio();

    static void Init();
    NEW_OBJ(CrowdAudio);

    ObjPtr<BinkClip, ObjectDir> mCurrentMogg; // 0x8
    ObjPtr<BinkClip, ObjectDir> mOldMogg; // 0x14
    ObjPtr<BinkClip, ObjectDir> mFadingMogg; // 0x20
    Fader* mMainFader; // 0x2c
    bool mWantDuck; // 0x30
    float mResultsDuck; // 0x34
    float mResultsFadeDuration; // 0x38
    Fader* mResultsFader; // 0x3c
    float unk40; // 0x40
    Fader* mEntryFader; // 0x44
    float unk48; // 0x48
    ExcitementLevel mLevel; // 0x4c
    ExcitementLevel mOverrideExcitementLevel; // 0x50
    int unk54; // 0x54
    float mLoopChangeTime; // 0x58
    DataArray* mIntro; // 0x5c
    DataArray* mVenueIntro; // 0x60
    DataArray* unk64; // 0x64
    DataArray* mVenueOutro; // 0x68
    int mState; // 0x6c - should be enum State?
    float unk70; // 0x70
    float unk74; // 0x74
    float unk78; // 0x78
    bool mEnabled; // 0x7c
    bool mCrowdReacts; // 0x7d
    int unk80; // 0x80
    bool unk84; // 0x84
    ObjPtr<ObjectDir, ObjectDir> unk88; // 0x88
    Fader* mCurrentBankFader; // 0x94
    Fader* mOtherBankFader; // 0x98
    Fader* mReleaseFader; // 0x9c
    float unka0; // 0xa0
    float unka4; // 0xa4
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