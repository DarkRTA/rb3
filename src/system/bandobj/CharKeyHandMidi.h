#pragma once
#include "char/CharWeightable.h"
#include "rndobj/Highlightable.h"
#include "char/CharIKFingers.h"

class CharKeyHandMidi : public virtual RndHighlightable, public CharWeightable {
public:
    CharKeyHandMidi();
    virtual ~CharKeyHandMidi();
    virtual void Highlight();
    OBJ_CLASSNAME(CharKeyHandMidi);
    OBJ_SET_TYPE(CharKeyHandMidi);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual void Enter();
    virtual void SetName(const char*, ObjectDir*);

    ObjPtr<CharIKFingers, ObjectDir> unk28; // 0x28
};