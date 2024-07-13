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
    RndTransformable* GetSource() const;
    void SetMinYaw(float);
    void SetMaxYaw(float);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    
    ObjPtr<RndTransformable, ObjectDir> mSource; // 0x28
    ObjPtr<RndTransformable, ObjectDir> mPivot; // 0x34
    ObjPtr<RndTransformable, ObjectDir> mDest; // 0x40
    float mHalfTime; // 0x4c
    float mMinYaw; // 0x50
    float mMaxYaw; // 0x54
    float mMinPitch; // 0x58
    float mMaxPitch; // 0x5c
    float mMinWeightYaw; // 0x60
    float mMaxWeightYaw; // 0x64
    float mWeightYawSpeed; // 0x68
    Vector3 unk6c; // 0x6c
    float unk78; // 0x78
    float mSourceRadius; // 0x7c
    Vector3 vec80; // 0x80
    Box mBounds; // 0x8c, 0x90, 0x94, 0x98, 0x9c, 0xa0
    bool mShowRange; // 0xa4
    bool mTestRange; // 0xa5
    float mTestRangePitch; // 0xa8
    float mTestRangeYaw; // 0xac
    bool mAllowRoll; // 0xb0
    bool unkb1; // 0xb1
    bool mEnableJitter; // 0xb2
    float mYawJitterLimit; // 0xb4
    float mPitchJitterLimit;

};

#endif
