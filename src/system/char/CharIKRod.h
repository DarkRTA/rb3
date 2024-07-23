#ifndef CHAR_CHARIKROD_H
#define CHAR_CHARIKROD_H
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

class CharIKRod : public CharPollable {
public:
    CharIKRod();
    OBJ_CLASSNAME(CharIKRod);
    OBJ_SET_TYPE(CharIKRod);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~CharIKRod();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    bool ComputeRod(Transform&);
    void SyncBones();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<RndTransformable, ObjectDir> mLeftEnd; // 0x8
    ObjPtr<RndTransformable, ObjectDir> mRightEnd; // 0x14
    float mDestPos; // 0x20
    ObjPtr<RndTransformable, ObjectDir> mSideAxis; // 0x24
    bool mVertical; // 0x30
    ObjPtr<RndTransformable, ObjectDir> mDest; // 0x34
    Transform mXfm; // 0x40
};

#endif
