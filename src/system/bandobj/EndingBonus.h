#pragma once
#include "rndobj/Dir.h"
#include "rndobj/EventTrigger.h"
#include "obj/Task.h"
#include "bandobj/BandLabel.h"
#include "bandobj/UnisonIcon.h"

class EndingBonus : public RndDir {
public:
    class MiniIconData {
    public:
        MiniIconData(EndingBonus* b, UnisonIcon* u) : mIcon(b, u), mFailed(0), mSucceeded(0), mDisabled(0), mUsed(0) {}

        void Reset();
        void SetUsed(bool);
        void Succeeded();
        void Failed();
        void SetProgress(float);

        ObjPtr<UnisonIcon, ObjectDir> mIcon; // 0x0
        bool mFailed; // 0xc
        bool mSucceeded; // 0xd
        bool mDisabled; // 0xe
        bool mUsed; // 0xf
    };

    EndingBonus();
    OBJ_CLASSNAME(EndingBonus);
    OBJ_SET_TYPE(EndingBonus);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~EndingBonus(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();

    void Start(bool);
    void Success();
    void CodaEnd();
    void SetScore(int);
    void UnisonSucceed();
    void UnisonEnd();
    void Reset();
    void SetupEnding(bool);
    void SetIconText(int, const char*);
    void PlayerSuccess(int);
    void PlayerFailure(int);
    void SetSuppressUnisonDisplay(bool);
    void SetupUnison(int);
    void UnisonStart(int);
    void SetIconOrder(int, bool);
    void DisablePlayer(int);
    void EnablePlayer(int);
    void SetProgress(int, float);

    DataNode OnReset(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    bool mSuppressUnisonDisplay; // 0x18c
    bool mInUnison; // 0x18d
    int mScore; // 0x190
    bool mSucceeded; // 0x194
    ObjPtr<Task, ObjectDir> mCodaEndTask; // 0x198
    std::vector<TrackInstrument> mTrackOrder; // 0x1a4
    std::vector<MiniIconData> mIconData; // 0x1ac
    ObjPtr<BandLabel, ObjectDir> mScoreLabel; // 0x1b4
    ObjPtr<EventTrigger, ObjectDir> mUnisonStartTrig; // 0x1c0
    ObjPtr<EventTrigger, ObjectDir> mUnisonEndTrig; // 0x1cc
    ObjPtr<EventTrigger, ObjectDir> mUnisonSucceedTrig; // 0x1d8
    ObjPtr<EventTrigger, ObjectDir> mStartTrig; // 0x1e4
    ObjPtr<EventTrigger, ObjectDir> mEndTrig; // 0x1f0
    ObjPtr<EventTrigger, ObjectDir> mSucceedTrig; // 0x1fc
    ObjPtr<EventTrigger, ObjectDir> mResetTrig; // 0x208
};