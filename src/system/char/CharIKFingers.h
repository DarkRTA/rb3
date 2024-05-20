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
        bool unk0;
        float unk4;
        float unk8;
        float unkc;
        float unk10;
        float unk14;
        float unk18;
        float unk1c;
        ObjPtr<RndTransformable, ObjectDir> unk20;
        ObjPtr<RndTransformable, ObjectDir> unk2c;
        ObjPtr<RndTransformable, ObjectDir> unk38;
        ObjPtr<RndTransformable, ObjectDir> unk44;
        float unk50;
        float unk54;
        float unk58;
        float unk5c;
        int unk60;
        int unk64;
        bool unk68;
        float unk6c;
        float unk70;
        float unk74;
        float unk78;
        float unk7c;
        float unk80;
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

    ObjPtr<RndTransformable, ObjectDir> mHand;
    ObjPtr<RndTransformable, ObjectDir> mElbow;
    ObjPtr<RndTransformable, ObjectDir> mShoulder;
    int mBlendInFrames;
    int mBlendOutFrames;
    bool mResetHandDest;
    bool mResetCurHandTrans;
    Transform mCurHandTrans; // 0x58
    Transform mDestHandTrans; // 0x88
    float mFingerCurledLength; // 0xb8
    Vector3 mDestForwardVector; // 0xbc
    Vector3 mCurForwardVector; // 0xc8
    Vector3 mHandKeyboardOffset; // 0xd4

    int unk[8]; // 0xe0 - 0x100

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
