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

    DECLARE_REVS;
    
    ObjVector<int> mPoints; // change vector type
    ObjPtr<RndTransformable, ObjectDir> mHead;
    ObjPtr<RndTransformable, ObjectDir> mSpine;
    ObjPtr<RndTransformable, ObjectDir> mMouth;
    ObjPtr<RndTransformable, ObjectDir> mTarget;
    Vector3 mHeadFilter;
    float mTargetRadius;
    float mHeadMat;
    ObjPtr<RndTransformable, ObjectDir> mOffset;
    Vector3 mOffsetScale;
    float mSpineLength;
    bool mUpdatePoints;
    ObjPtr<Character, ObjectDir> mMe;
    Vector3 mDebugTarget;
};

#endif
