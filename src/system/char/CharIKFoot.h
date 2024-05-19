#ifndef CHAR_CHARIKFOOT_H
#define CHAR_CHARIKFOOT_H
#include "char/CharIKHand.h"
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "rndobj/Highlightable.h"
#include "char/Character.h"
#include "obj/ObjVector.h"
#include "char/CharCollide.h"

class CharIKFoot : public CharIKHand {
public:
    CharIKFoot();
    virtual ~CharIKFoot();
    virtual void Highlight();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    OBJ_CLASSNAME(CharIKHand);
    OBJ_SET_TYPE(CharIKHand);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Enter();
    virtual void SetName(const char*, class ObjectDir*);

    DELETE_OVERLOAD;
    
    ObjPtr<RndTransformable, ObjectDir> unk88;
    int unk94;
    ObjPtr<RndTransformable, ObjectDir> mData;
    int mDataIndex; // 0xa4
    int unk[4];
    ObjPtr<Character, ObjectDir> mMe; // 0xb8
};

#endif
