#pragma once
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "rndobj/Highlightable.h"
#include "char/CharIKFingers.h"

class CharKeyHandMidi : public RndHighlightable, public CharWeightable, public CharPollable {
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

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<CharIKFingers, ObjectDir> unk28; // 0x28
    ObjPtr<RndTransformable, ObjectDir> unk34; // 0x34
    ObjPtr<RndTransformable, ObjectDir> unk40; // 0x40
    std::vector<Vector3> unk4c;
    std::vector<Vector3> unk54;
    std::vector<int> unk5c;
    int unk64;
    int unk68;
    std::vector<int> unk6c;
    int unk74;
    bool unk78;
    ObjPtr<Character, ObjectDir> unk7c;
    float unk88;
    bool unk8c;
};