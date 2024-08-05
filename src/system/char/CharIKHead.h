#ifndef CHAR_CHARIKHEAD_H
#define CHAR_CHARIKHEAD_H
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "rndobj/Highlightable.h"
#include "char/Character.h"
#include "obj/ObjVector.h"

class CharIKHead : public RndHighlightable, public CharWeightable, public CharPollable {
public:
    class Point {
    public:
        Point(Hmx::Object* o) : unk0(o, 0), unkc(0,0,0), unk18(0), unk1c(0) {}

        ObjPtr<RndTransformable, ObjectDir> unk0; // 0x0
        Vector3 unkc; // 0xc
        float unk18; // 0x18
        float unk1c; // 0x1c
        int unk20, unk24, unk28;
    };

    CharIKHead();
    virtual ~CharIKHead();
    virtual void Highlight();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    OBJ_CLASSNAME(CharIKHead);
    OBJ_SET_TYPE(CharIKHead);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void SetName(const char*, class ObjectDir*);

    void UpdatePoints(bool);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    
    ObjVector<Point> mPoints; // 0x28
    ObjPtr<RndTransformable, ObjectDir> mHead; // 0x34
    ObjPtr<RndTransformable, ObjectDir> mSpine; // 0x40
    ObjPtr<RndTransformable, ObjectDir> mMouth; // 0x4c
    ObjPtr<RndTransformable, ObjectDir> mTarget; // 0x58
    Vector3 mHeadFilter; // 0x64
    float mTargetRadius; // 0x70
    float mHeadMat; // 0x74
    ObjPtr<RndTransformable, ObjectDir> mOffset; // 0x78
    Vector3 mOffsetScale; // 0x84
    float mSpineLength; // 0x90
    bool mUpdatePoints; // 0x94
    ObjPtr<Character, ObjectDir> mMe; // 0x98
    Vector3 mDebugTarget; // 0xa4
};

#endif
