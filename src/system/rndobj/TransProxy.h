#pragma once
#include "rndobj/Trans.h"

/**
 * @brief A RndTransformable but within a proxy.
 * Original _objects description:
 * "Stand-in for a RndTransformable inside of a proxy, so you can use it"
 */
class RndTransProxy : public RndTransformable {
public:
    RndTransProxy();
    OBJ_CLASSNAME(TransProxy)
    OBJ_SET_TYPE(TransProxy)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, CopyType);
    virtual void Load(BinStream &);
    virtual ~RndTransProxy() {}
    virtual void PreSave(BinStream &);
    virtual void PostSave(BinStream &);

    // setters
    void SetProxy(ObjectDir *);
    void SetPart(Symbol);
    void Sync(); // probably private

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndTransProxy)
    static void Init() { REGISTER_OBJ_FACTORY(RndTransProxy) }
    DECLARE_REVS;

    /** "Proxy object this will look into." */
    ObjPtr<ObjectDir> mProxy; // 0x90
    /** "The part inside it" */
    Symbol mPart; // 0x9c
};
