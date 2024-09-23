#pragma once
#include "ui/UIList.h"
#include "rndobj/TransAnim.h"
#include "synth/Sequence.h"

class HighlightObject {
public:
    HighlightObject(Hmx::Object*);
    void Load(BinStream&);

    static int sRev;

    ObjPtr<RndTransformable, ObjectDir> mTargetObj; // 0x0
    float mXOffset; // 0xc
    float mYOffset; // 0x10
    float mZOffset; // 0x14
};

class BandList : public UIList {
public:
    enum AnimState {
        kOut = 0,
        kGoingIn = 1,
        kIn = 2,
        kGoingOut = 3
    };

    enum RevealState {
        kConcealed = 0,
        kRevealing = 1,
        kConcealing = 2,
        kRevealed = 3
    };

    enum BandListState {
        kReveal = 0,
        kConceal = 1,
        kImmediateConceal = 2
    };

    BandList();
    OBJ_CLASSNAME(BandList)
    OBJ_SET_TYPE(BandList)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~BandList();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void Exit();
    virtual void AdjustTrans(Transform&, const UIListElementDrawState&);
    virtual void AdjustTransSelected(Transform&);

    void StartPulseAnim(int);
    void StartFocusAnim(int, AnimState);
    void StartRevealAnim(int, Transform&);
    void RevealAnimPoll(int, Transform&);
    void UpdateFocusAndPulseAnims(int, Transform&);
    void UpdateRevealState(int, Transform&);
    void UpdateConcealState(int, Transform&);
    void UpdateRevealConcealState(int, Transform&);
    void UpdatePulseAnim(int, Transform&);
    void ForceConcealedStateOnAllEntries();
    void StartConcealAnim(int, Transform&);
    void ForceConcealed(int, Transform&);
    void ForceRevealed(int, Transform&);
    void ConcealAnimPoll(int, Transform&);
    void ConcealNow();
    void Conceal();
    void Reveal();
    void UpdateShowingState();
    bool RevealTimedOut();
    bool ConcealTimedOut();
    float GetRevealNumFrames() const;
    float GetRevealFramesPerSecond() const;
    float GetRevealStartFrame() const;
    float GetRevealEndFrame() const;
    float GetCurrentRevealFrame(float) const;
    float GetConcealNumFrames() const;
    float GetConcealFramesPerSecond() const;
    float GetConcealStartFrame() const;
    float GetConcealEndFrame() const;
    float GetCurrentConcealFrame(float) const;
    bool IsAnimating();
    bool IsRevealAnimFinished(float) const;
    bool IsConcealAnimFinished(float) const;
    void MakeRevealTransform(float, Transform&);
    void MakeConcealTransform(float, Transform&);
    bool SupportsRevealConcealAnim() const { return mRevealAnim || mConcealAnim; }
    bool IsRevealed(){ return mBandListState == kReveal && !IsAnimating(); }

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(BandList);
    }
    NEW_OBJ(BandList);
    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int mBandListRev; // 0x1e8
    std::map<int, AnimState> mAnimStates; // 0x1ec
    std::map<int, float> mStartTimes; // 0x204
    std::map<int, float> mFrames; // 0x21c
    std::map<int, RevealState> mRevealStates; // 0x234
    std::map<int, float> mRevealStartTimes; // 0x24c
    std::map<int, bool> unk264; // 0x264
    ObjPtr<RndTransAnim, ObjectDir> mFocusAnim; // 0x27c
    ObjPtr<RndTransAnim, ObjectDir> mPulseAnim; // 0x288
    ObjPtr<RndTransAnim, ObjectDir> mRevealAnim; // 0x294
    ObjPtr<RndTransAnim, ObjectDir> mConcealAnim; // 0x2a0
    ObjPtr<Sequence, ObjectDir> mRevealSound; // 0x2ac
    ObjPtr<Sequence, ObjectDir> mConcealSound; // 0x2b8
    float mRevealSoundDelay; // 0x2c4
    float mConcealSoundDelay; // 0x2c8
    float mRevealStartDelay; // 0x2cc
    float mRevealEntryDelay; // 0x2d0
    float mRevealScale; // 0x2d4
    float mConcealStartDelay; // 0x2d8
    float mConcealEntryDelay; // 0x2dc
    float mConcealScale; // 0x2e0
    bool mAutoReveal; // 0x2e4
    BandListState mBandListState; // 0x2e8
    float mShouldbeRevealedTimeStamp; // 0x2ec
    ObjVector<HighlightObject> mHighlightObjects; // 0x2f0
};