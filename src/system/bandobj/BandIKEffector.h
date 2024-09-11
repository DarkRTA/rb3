#pragma once
#include "bandobj/BandCharacter.h"
#include "rndobj/Highlightable.h"
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "rndobj/Trans.h"

class BandIKEffector : public RndHighlightable, public CharWeightable, public CharPollable {
public:
    class Constraint {
    public:
        ObjPtr<RndTransformable, ObjectDir> mTarget; // 0x0
        ObjPtr<RndTransformable, ObjectDir> mFinger; // 0xc
        float mWeight; // 0x18
    };

    BandIKEffector();
    virtual ~BandIKEffector();
    virtual void Highlight();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    OBJ_CLASSNAME(BandIKEffector);
    OBJ_SET_TYPE(BandIKEffector);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void SetName(const char*, ObjectDir*);

    ObjPtr<RndTransformable, ObjectDir> unk28; // 0x28
    ObjPtr<RndTransformable, ObjectDir> unk34; // 0x34
    ObjPtr<BandIKEffector, ObjectDir> unk40; // 0x40
    ObjPtr<BandIKEffector, ObjectDir> unk4c; // 0x4c
    ObjVector<Constraint> unk58; // 0x58
    ObjPtr<BandCharacter, ObjectDir> unk64; // 0x64
};