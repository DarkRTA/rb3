#pragma once
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "rndobj/Highlightable.h"
#include "char/Character.h"
#include "obj/ObjVector.h"

/** "Puts a head bone into a position, doing IK on the spine to achieve it." */
class CharIKHead : public RndHighlightable, public CharWeightable, public CharPollable {
public:
    class Point {
    public:
        Point(Hmx::Object *o) : unk0(o), unkc(0, 0, 0), unk18(0), unk1c(0) {}

        ObjPtr<RndTransformable> unk0; // 0x0
        Vector3 unkc; // 0xc
        float unk18; // 0x18
        float unk1c; // 0x1c
        Vector3 unk20;
        // int unk20, unk24, unk28;
    };

    CharIKHead();
    virtual ~CharIKHead();
    virtual void Highlight();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);
    OBJ_CLASSNAME(CharIKHead);
    OBJ_SET_TYPE(CharIKHead);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void SetName(const char *, class ObjectDir *);

    void UpdatePoints(bool);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharIKHead)
    static void Init() { REGISTER_OBJ_FACTORY(CharIKHead) }

    ObjVector<Point> mPoints; // 0x28
    /** "The head bone which will be moved to the target" */
    ObjPtr<RndTransformable> mHead; // 0x34
    /** "The first spine bone in the chain to be moved" */
    ObjPtr<RndTransformable> mSpine; // 0x40
    /** "If non null, will be the thing that actually hits the target" */
    ObjPtr<RndTransformable> mMouth; // 0x4c
    /** "The target to hit" */
    ObjPtr<RndTransformable> mTarget; // 0x58
    Vector3 mHeadFilter; // 0x64
    /** "allowable head movement relative to the target" */
    float mTargetRadius; // 0x70
    /** "how much to blend the original world space head matrix in" */
    float mHeadMat; // 0x74
    /** "Another bone to get the same world space delta" */
    ObjPtr<RndTransformable> mOffset; // 0x78
    /** "World space axis scaling to apply to delta before applying to offset bone." */
    Vector3 mOffsetScale; // 0x84
    float mSpineLength; // 0x90
    bool mUpdatePoints; // 0x94
    ObjPtr<Character> mMe; // 0x98
    Vector3 mDebugTarget; // 0xa4
};
