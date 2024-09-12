#pragma once
#include "rndobj/Dir.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/Group.h"
#include "rndobj/PropAnim.h"

class PitchArrow : public RndDir {
public:
    PitchArrow();
    OBJ_CLASSNAME(PitchArrowDir);
    OBJ_SET_TYPE(PitchArrowDir);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~PitchArrow(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void Poll();

    bool unk18c; // 0x18c
    float unk190; // 0x190
    float unk194; // 0x194
    float unk198; // 0x198
    float unk19c; // 0x19c
    int unk1a0; // 0x1a0
    float unk1a4; // 0x1a4
    bool unk1a8; // 0x1a8
    bool unk1a9; // 0x1a9
    bool unk1aa; // 0x1aa
    bool unk1ab; // 0x1ab
    Symbol unk1ac; // 0x1ac
    int unk1b0; // 0x1b0
    ObjPtr<RndPropAnim, ObjectDir> unk1b4; // 0x1b4
    ObjPtr<RndPropAnim, ObjectDir> unk1c0; // 0x1c0
    ObjPtr<RndPropAnim, ObjectDir> unk1cc; // 0x1cc
    ObjPtr<RndPropAnim, ObjectDir> unk1d8; // 0x1d8
    ObjPtr<RndPropAnim, ObjectDir> unk1e4; // 0x1e4
    ObjPtr<RndPropAnim, ObjectDir> unk1f0; // 0x1f0
    ObjPtr<RndPropAnim, ObjectDir> unk1fc; // 0x1fc
    ObjPtr<RndPropAnim, ObjectDir> unk208; // 0x208
    ObjPtr<EventTrigger, ObjectDir> unk214; // 0x214
    ObjPtr<EventTrigger, ObjectDir> unk220; // 0x220
    ObjPtr<EventTrigger, ObjectDir> unk22c; // 0x22c
    ObjPtr<EventTrigger, ObjectDir> unk238; // 0x238
    ObjPtr<EventTrigger, ObjectDir> unk244; // 0x244
    ObjPtr<EventTrigger, ObjectDir> unk250; // 0x250
    ObjPtr<RndGroup, ObjectDir> unk25c; // 0x25c
    ObjPtr<RndPropAnim, ObjectDir> unk268; // 0x268
    ObjPtr<RndGroup, ObjectDir> unk274; // 0x274
    bool unk280; // 0x280
    float unk284; // 0x284
    ObjPtr<RndPropAnim, ObjectDir> unk288; // 0x288
    float unk294; // 0x294
    float unk298; // 0x298
    float unk29c; // 0x29c
};