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

    ObjPtr<RndTransformable, ObjectDir> mSleeve; // 0x10
    ObjPtr<RndTransformable, ObjectDir> mTopSleeve; // 0x1c
    Vector3 mPos; // 0x28
    Vector3 mLastPos; // 0x34
    float mLastDT; // 0x40
    float mInertia; // 0x44
    float mGravity; // 0x48
    float mRange; // 0x4c
    float mNegLength; // 0x50
    float mPosLength; // 0x54
    float mStiffness; // 0x58
    ObjPtr<Character, ObjectDir> mMe; // 0x5c
};

#endif
