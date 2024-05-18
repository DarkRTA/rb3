#ifndef CHAR_CHARIKSCALE_H
#define CHAR_CHARIKSCALE_H
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

class CharIKScale : public CharWeightable, public CharPollable {
public:
    CharIKScale();
    OBJ_CLASSNAME(Poll);
    OBJ_SET_TYPE(Poll);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~CharIKScale();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);

    DELETE_OVERLOAD;
    
    ObjPtr<RndTransformable, ObjectDir> mDest;
    float mScale;
    ObjPtrList<RndTransformable, ObjectDir> mSecondaryTargets;
    float mBottomHeight;
    float mTopHeight;
    bool mAutoWeight;
};

#endif
