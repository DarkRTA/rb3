#pragma once
#include "rndobj/Poll.h"
#include "rndobj/Trans.h"

class BandRetargetVignette : public RndPollable {
public:
    BandRetargetVignette();
    OBJ_CLASSNAME(BandRetargetVignette);
    OBJ_SET_TYPE(BandRetargetVignette);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();
    virtual void ListPollChildren(std::list<RndPollable*>&) const;
    virtual ~BandRetargetVignette();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::list<String> unk8; // 0x8
    Symbol unk10; // 0x10
    Symbol unk14; // 0x14
    ObjPtr<RndTransformable, ObjectDir> unk18; // 0x18
};