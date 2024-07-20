#ifndef CHAR_CHARFACESERVO_H
#define CHAR_CHARFACESERVO_H
#include "char/CharPollable.h"
#include "char/CharBonesMeshes.h"
#include "obj/ObjPtr_p.h"

class CharFaceServo : public CharPollable, public CharBonesMeshes {
public:
    CharFaceServo();
    OBJ_CLASSNAME(CharFaceServo);
    OBJ_SET_TYPE(CharFaceServo);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Enter();
    virtual ~CharFaceServo();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void ScaleAdd(CharClip*, float, float, float);
    virtual void ReallocateInternal();

    void TryScaleDown();
    void SetClips(ObjectDir*);
    void SetClipType(Symbol);
    float BlinkWeightLeft() const;
    void ApplyProceduralWeights();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<ObjectDir, ObjectDir> mClips; // 0x6c
    Symbol mClipType; // 0x78
    ObjPtr<CharClip, ObjectDir> mBaseClip; // 0x7c
    Symbol mBlinkClipLeftName; // 0x88
    Symbol mBlinkClipLeftName2; // 0x8c
    Symbol mBlinkClipRightName; // 0x90
    Symbol mBlinkClipRightName2; // 0x94
    ObjPtr<CharClip, ObjectDir> mBlinkClipLeft; // 0x98
    ObjPtr<CharClip, ObjectDir> mBlinkClipLeft2; // 0xa4
    ObjPtr<CharClip, ObjectDir> mBlinkClipRight; // 0xb0
    ObjPtr<CharClip, ObjectDir> mBlinkClipRight2; // 0xbc
    float mBlinkWeightLeft; // 0xc8
    float mBlinkWeightRight; // 0xcc
    bool mNeedScaleDown; // 0xd0
    float mProceduralBlinkWeight; // 0xd4
    bool mAppliedProceduralBlink; // 0xd8
};

#endif
