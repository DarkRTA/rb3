#ifndef CHAR_CHARSLEEVE_H
#define CHAR_CHARSLEEVE_H
#include "rndobj/Highlightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "char/Character.h"

class CharSleeve : public RndHighlightable, public CharPollable {
public:
    CharSleeve();
    virtual ~CharSleeve();
    virtual void Highlight();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    OBJ_CLASSNAME(CharSleeve);
    OBJ_SET_TYPE(CharSleeve);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void SetName(const char*, class ObjectDir*);

    DECLARE_REVS;
    DELETE_OVERLOAD;

    ObjPtr<RndTransformable, ObjectDir> mSleeve;
    ObjPtr<RndTransformable, ObjectDir> mTopSleeve;
    Vector3 mPos;
    Vector3 mLastPos;
    float mLastDT;
    float mInertia;
    float mGravity;
    float mRange;
    float mNegLength;
    float mPosLength;
    float mStiffness;
    ObjPtr<Character, ObjectDir> mMe;
};

#endif
