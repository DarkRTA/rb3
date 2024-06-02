#ifndef RNDOBJ_TRANSPROXY_H
#define RNDOBJ_TRANSPROXY_H
#include "rndobj/Trans.h"

class RndTransProxy : public RndTransformable {
public:
    RndTransProxy();
    OBJ_CLASSNAME(TransProxy)
    OBJ_SET_TYPE(TransProxy)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~RndTransProxy(){}
    virtual void PreSave(BinStream&);
    virtual void PostSave(BinStream&);

    void SetProxy(ObjectDir*);
    void SetPart(Symbol);
    void Sync();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndTransProxy)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndTransProxy)
    }
    DECLARE_REVS;

    ObjPtr<ObjectDir, ObjectDir> mProxy;
    Symbol mPart;
};

#endif
