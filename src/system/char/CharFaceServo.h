#pragma once
#include "char/CharPollable.h"
#include "char/CharBonesMeshes.h"
#include "obj/ObjPtr_p.h"

/** "BonesMeshes for facial blending" */
class CharFaceServo : public CharPollable, public CharBonesMeshes {
public:
    CharFaceServo();
    OBJ_CLASSNAME(CharFaceServo);
    OBJ_SET_TYPE(CharFaceServo);
    virtual DataNode Handle(DataArray *, bool);
    virtual void Poll();
    virtual void Enter();
    virtual ~CharFaceServo();
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void ScaleAdd(CharClip *, float, float, float);
    virtual void ReallocateInternal();

    void TryScaleDown();
    void SetClips(ObjectDir *);
    void SetClipType(Symbol);
    float BlinkWeightLeft() const;
    void ApplyProceduralWeights();
    void SetProceduralBlinkWeight(float weight) { mProceduralBlinkWeight = weight; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharFaceServo)
    static void Init() { REGISTER_OBJ_FACTORY(CharFaceServo) }

    /** "pointer to visemes, must contain Blink and Base" */
    ObjPtr<ObjectDir> mClips; // 0x6c
    /** "Which clip type it can support" */
    Symbol mClipType; // 0x78
    ObjPtr<CharClip> mBaseClip; // 0x7c
    /** "Blink clip, used to close the left eye" */
    Symbol mBlinkClipLeftName; // 0x88
    /** "A second clip that contributes to closing the left eye" */
    Symbol mBlinkClipLeftName2; // 0x8c
    /** "Blink clip, used to close the right eye" */
    Symbol mBlinkClipRightName; // 0x90
    /** "A second clip that contributes to closing the right eye" */
    Symbol mBlinkClipRightName2; // 0x94
    ObjPtr<CharClip> mBlinkClipLeft; // 0x98
    ObjPtr<CharClip> mBlinkClipLeft2; // 0xa4
    ObjPtr<CharClip> mBlinkClipRight; // 0xb0
    ObjPtr<CharClip> mBlinkClipRight2; // 0xbc
    float mBlinkWeightLeft; // 0xc8
    float mBlinkWeightRight; // 0xcc
    bool mNeedScaleDown; // 0xd0
    float mProceduralBlinkWeight; // 0xd4
    bool mAppliedProceduralBlink; // 0xd8
};
