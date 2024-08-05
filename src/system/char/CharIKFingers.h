#ifndef CHAR_CHARIKFINGERS_H
#define CHAR_CHARIKFINGERS_H
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "rndobj/Highlightable.h"
#include "char/Character.h"
#include "obj/ObjVector.h"
#include "char/CharCollide.h"

class CharIKFingers : public RndHighlightable, public CharWeightable, public CharPollable {
public:

    enum FingerNum {
        kFingerThumb,
        kFingerIndex,
        kFingerMiddle,
        kFingerRing,
        kFingerPinky,
        kFingerNone
    };

    class FingerDesc {
    public:
        FingerDesc() : unk0(0), unk8(0,0,0), unk14(0,0,0), mFinger01(0), mFinger02(0), mFinger03(0), mFingertip(0), unk60(0), unk64(0), unk68(1) {}
        ~FingerDesc(){}
        bool unk0;
        float unk4;
        Vector3 unk8; // 0x8
        Vector3 unk14; // 0x14
        ObjPtr<RndTransformable, ObjectDir> mFinger01; // 0x20
        ObjPtr<RndTransformable, ObjectDir> mFinger02; // 0x2c
        ObjPtr<RndTransformable, ObjectDir> mFinger03; // 0x38
        ObjPtr<RndTransformable, ObjectDir> mFingertip; // 0x44
        float unk50;
        float unk54;
        float unk58;
        float unk5c;
        int unk60;
        int unk64;
        bool unk68;
        Vector3 unk6c; // 0x6c
        Vector3 unk78; // 0x78
        bool unk84;
    };

    CharIKFingers();
    virtual ~CharIKFingers();
    virtual void Highlight();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    OBJ_CLASSNAME(CharIKFingers);
    OBJ_SET_TYPE(CharIKFingers);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void SetName(const char*, class ObjectDir*);

    void MeasureLengths();
    void SetFinger(Vector3, Vector3, FingerNum);
    void ReleaseFinger(FingerNum);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<RndTransformable, ObjectDir> mHand; // 0x28
    ObjPtr<RndTransformable, ObjectDir> mForeArm; // 0x34
    ObjPtr<RndTransformable, ObjectDir> mUpperArm; // 0x40
    int mBlendInFrames; // 0x4c
    int mBlendOutFrames; // 0x50
    bool mResetHandDest; // 0x54
    bool mResetCurHandTrans; // 0x55
    Transform mCurHandTrans; // 0x58
    Transform mDestHandTrans; // 0x88
    float mFingerCurledLength; // 0xb8
    Vector3 mDestForwardVector; // 0xbc
    Vector3 mCurForwardVector; // 0xc8
    Vector3 mHandKeyboardOffset; // 0xd4
    Hmx::Matrix3 mtx; // 0xe0
    float mHandMoveForward; // 0x104
    float mHandPinkyRotation; // 0x108
    float mHandThumbRotation; // 0x10c
    float mHandDestOffset; // 0x110
    bool mIsRightHand; // 0x114
    bool mMoveHand; // 0x115
    bool mIsSetup; // 0x116
    std::vector<FingerDesc> mFingers; // 0x118
    float mInv2ab; // 0x120
    float mAAPlusBB; // 0x124
    ObjPtr<RndTransformable, ObjectDir> mOutputTrans; // 0x128
    ObjPtr<RndTransformable, ObjectDir> mKeyboardRefBone; // 0x134
};

#endif
