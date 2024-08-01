#ifndef CHAR_CHAREYES_H
#define CHAR_CHAREYES_H
#include "rndobj/Highlightable.h"
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "char/CharEyeDartRuleset.h"
#include "rndobj/Trans.h"
#include "rndobj/Overlay.h"

class CharFaceServo;
class CharWeightSetter;
class CharLookAt;
class CharInterest;

class CharEyes : public RndHighlightable, public CharWeightable, public CharPollable {
public:

    class EyeDesc {
    public:
        EyeDesc(Hmx::Object*);
        EyeDesc(const EyeDesc&);
        EyeDesc& operator=(const EyeDesc&);

        ObjOwnerPtr<CharLookAt, ObjectDir> mEye; // 0x0
        ObjPtr<RndTransformable, ObjectDir> mUpperLid; // 0xc
        ObjPtr<RndTransformable, ObjectDir> mLowerLid; // 0x18
        ObjPtr<RndTransformable, ObjectDir> mLowerLidBlink; // 0x24
        ObjPtr<RndTransformable, ObjectDir> mUpperLidBlink; // 0x30
    };

    class CharInterestState {
    public:
        CharInterestState(Hmx::Object*);
        CharInterestState(const CharInterestState&);
        CharInterestState& operator=(const CharInterestState&);

        ObjOwnerPtr<CharInterest, ObjectDir> mInterest; // 0x0
    };

    CharEyes();
    virtual ~CharEyes();
    virtual void Highlight();
    OBJ_CLASSNAME(CharEyes);
    OBJ_SET_TYPE(CharEyes);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual void Enter();
    virtual void Exit();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void ListPollChildren(std::list<RndPollable*>&) const;

    static bool sDisableEyeDart;
    static bool sDisableEyeJitter;
    static bool sDisableInterestObjects;
    static bool sDisableProceduralBlink;
    static bool sDisableEyeClamping;

    ObjVector<EyeDesc> mEyes; // 0x28
    ObjVector<CharInterestState> mInterests; // 0x34
    ObjPtr<CharFaceServo, ObjectDir> mFaceServo; // 0x40
    ObjPtr<CharWeightSetter, ObjectDir> mCamWeight; // 0x4c
    float unk58, unk5c, unk60;
    int unk64;
    ObjPtr<RndTransformable, ObjectDir> mViewDirection; // 0x68
    ObjPtr<CharLookAt, ObjectDir> mHeadLookAt; // 0x74
    float mMaxExtrapolation, unk84, unk88, unk8c, unk90, unk94;
    bool unk98;
    RndOverlay* unk9c;
    int unka0;
    float unka4, unka8, unkac, unkb4, unkb8, unkbc, unkc0;
    bool unkc4, unkc5;
    ObjPtr<CharInterest, ObjectDir> unkc8; // 0xc8
    ObjPtr<CharInterest, ObjectDir> unkd4; // 0xd4
    int unke0;
    bool unke4;
    float unke8, unkec, unkf0, unkf4;
    CharEyeDartRuleset::EyeDartRulesetData unkf8;
    bool unk124;
    float unk128;
    int unk12c, unk130, unk134, unk138;
    bool unk13c;
    float unk140;
    int unk144;
    float unk148, unk14c;
    int unk150, unk154, unk158;
    bool unk15c, unk15d;
};

#endif

// class CharEyes : public RndHighlightable, public CharWeightable, public CharPollable {
//     // total size: 0xD0
// protected:
//     class ObjVector mEyes; // offset 0x28, size 0x10
//     class ObjVector mInterests; // offset 0x38, size 0x10
//     class ObjPtr mFaceServo; // offset 0x48, size 0xC
//     class ObjPtr mCamWeight; // offset 0x54, size 0xC
//     class Vector3 mTarget; // offset 0x60, size 0x10
//     class Vector3 mLastFacing; // offset 0x70, size 0x10
//     float mLastCang; // offset 0x80, size 0x4
//     float mLastLook; // offset 0x84, size 0x4
//     float mMaxEyeCang; // offset 0x88, size 0x4
//     float mAvDelta; // offset 0x8C, size 0x4
//     float mLastBlinkWeight; // offset 0x90, size 0x4
//     unsigned char mBlinkDetect; // offset 0x94, size 0x1
// };