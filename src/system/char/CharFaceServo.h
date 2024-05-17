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

    DELETE_OVERLOAD;

    ObjPtr<ObjectDir, ObjectDir> mClips;
    Symbol mClipType;
    ObjPtr<CharClip, ObjectDir> mBaseClip;
    Symbol mBlinkClipLeftName;
    Symbol mBlinkClipLeftName2;
    Symbol mBlinkClipRightName;
    Symbol mBlinkClipRightName2;
    ObjPtr<CharClip, ObjectDir> mBlinkClipLeft;
    ObjPtr<CharClip, ObjectDir> mBlinkClipLeft2;
    ObjPtr<CharClip, ObjectDir> mBlinkClipRight;
    ObjPtr<CharClip, ObjectDir> mBlinkClipRight2;
    float mBlinkWeightLeft;
    float mBlinkWeightRight;
    bool mNeedScaleDown;
    float mProceduralBlinkWeight;
    bool mAppliedProceduralBlink;
};

#endif
