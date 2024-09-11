#pragma once
#include "rndobj/Poll.h"
#include "rndobj/Mesh.h"
#include "ui/UILabel.h"

class DialogDisplay : public RndPollable {
public:
    DialogDisplay();
    OBJ_CLASSNAME(DialogDisplay);
    OBJ_SET_TYPE(DialogDisplay);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~DialogDisplay();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<UILabel, ObjectDir> unk8; // 0x8
    ObjPtr<RndMesh, ObjectDir> unk14; // 0x14
    ObjPtr<RndMesh, ObjectDir> unk20; // 0x20
};