#ifndef CHAR_CHARLOOKAT_H
#define CHAR_CHARLOOKAT_H
#include "rndobj/Highlightable.h"
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

class CharLookAt : public RndHighlightable, public CharWeightable, public CharPollable {
public:
    CharLookAt();
    virtual ~CharLookAt();
    virtual void Highlight();
    virtual void Poll();    
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    OBJ_CLASSNAME(CharLookAt);
    OBJ_SET_TYPE(CharLookAt);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Enter();

    void SyncLimits();
    
    ObjPtr<RndTransformable, ObjectDir> mSource;
    ObjPtr<RndTransformable, ObjectDir> mPivot;
    ObjPtr<RndTransformable, ObjectDir> mDest;
    float mHalfTime; // 0x4c
    float mMinYaw;
    float mMaxYaw;
    float mMinPitch;
    float mMaxPitch;
    float mMinWeightYaw;
    float mMaxWeightYaw;
    float mWeightYawSpeed; // 0x68
    float unk6c;
    float unk70;
    float unk74;
    float unk78;
    float mSourceRadius;
    Vector3 vec80;
    Box mBounds;
    bool mShowRange;
    bool mTestRange;
    float mTestRangePitch;
    float mTestRangeYaw;
    bool mAllowRoll;
    bool unkb1;
    bool mEnableJitter;
    float mYawJitterLimit;
    float mPitchJitterLimit;

};

#endif
