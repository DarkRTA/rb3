#ifndef RNDOBJ_SET_H
#define RNDOBJ_SET_H

#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include <vector>

class RndSet : public Hmx::Object {
public:
    RndSet();
    virtual ~RndSet(){}
    OBJ_CLASSNAME(Set);
    OBJ_SET_TYPE(Set);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void SetTypeDef(DataArray*);

    bool AllowedObject(Hmx::Object*);
    DataNode OnAllowedObjects(DataArray*);
    
    NEW_OVERLOAD;
    NEW_OBJ(RndSet);
    DECLARE_REVS;
    DELETE_OVERLOAD;

    static void Init(){
        REGISTER_OBJ_FACTORY(RndSet)
    }

    ObjPtrList<Hmx::Object, ObjectDir> mObjects; // 0x1c
    std::vector<Symbol> mProps; // 0x2c
};

#endif // RNDOBJ_SET_H
