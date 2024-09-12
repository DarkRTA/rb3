#pragma once
#include "rndobj/Dir.h"
#include "rndobj/EventTrigger.h"
#include "obj/Task.h"
#include "bandobj/BandLabel.h"

class EndingBonus : public RndDir {
public:
    EndingBonus();
    OBJ_CLASSNAME(EndingBonus);
    OBJ_SET_TYPE(EndingBonus);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~EndingBonus(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();

    bool unk18c; // 0x18c
    bool unk18d; // 0x18d
    int unk190; // 0x190
    bool unk194; // 0x194
    ObjPtr<Task, ObjectDir> unk198; // 0x198
    std::vector<int> unk1a4; // 0x1a4
    std::vector<int> unk1ac; // 0x1ac
    ObjPtr<BandLabel, ObjectDir> unk1b4; // 0x1b4
    ObjPtr<EventTrigger, ObjectDir> unk1c0; // 0x1c0
    ObjPtr<EventTrigger, ObjectDir> unk1cc; // 0x1cc
    ObjPtr<EventTrigger, ObjectDir> unk1d8; // 0x1d8
    ObjPtr<EventTrigger, ObjectDir> unk1e4; // 0x1e4
    ObjPtr<EventTrigger, ObjectDir> unk1f0; // 0x1f0
    ObjPtr<EventTrigger, ObjectDir> unk1fc; // 0x1fc
    ObjPtr<EventTrigger, ObjectDir> unk208; // 0x208
};