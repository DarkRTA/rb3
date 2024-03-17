#ifndef CHAR_CHARTASKMGR_H
#define CHAR_CHARTASKMGR_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"

class CharWeightable : public virtual Hmx::Object {
public:
    CharWeightable();
    OBJ_CLASSNAME(CharWeightable);
    OBJ_SET_TYPE(CharWeightable);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void SetWeight(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual ~CharWeightable();

    static unsigned short gRev;
    static unsigned short gAltRev;

    float mWeight;
    ObjOwnerPtr<CharWeightable, class ObjectDir> mWeightOwner;
};

#endif
