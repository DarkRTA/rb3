#pragma once
#include "ui/UIList.h"
#include "rndobj/TransAnim.h"
#include "synth/Sequence.h"

class HighlightObject {
public:
    HighlightObject(Hmx::Object*);

    ObjPtr<RndTransformable, ObjectDir> mTargetObj; // 0x0
    float mXOffset; // 0xc
    float mYOffset; // 0x10
    float mZOffset; // 0x14
};

class BandList : public UIList {
public:
    enum AnimState {

    };

    enum RevealState {

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

    void ConcealNow();
    void Conceal();
    void Reveal();
    bool IsAnimating();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int unk1e8; // 0x1e8
    std::map<int, AnimState> unk1ec; // 0x1ec
    std::map<int, float> unk204; // 0x204
    std::map<int, float> unk21c; // 0x21c
    std::map<int, RevealState> unk234; // 0x234
    std::map<int, float> unk24c; // 0x24c
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
    int unk2e8; // 0x2e8
    float unk2ec; // 0x2ec
    ObjVector<HighlightObject> mHighlightObjects; // 0x2f0
};