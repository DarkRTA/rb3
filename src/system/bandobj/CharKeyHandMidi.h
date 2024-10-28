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

    void RunTest();
    void EndTest();

    DataNode OnFingersUp(DataArray*);
    DataNode OnFingersDown(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharKeyHandMidi)
    static void Init() {
        Register();
    }
    REGISTER_OBJ_FACTORY_FUNC(CharKeyHandMidi)

    ObjPtr<CharIKFingers, ObjectDir> mIKObject; // 0x28
    ObjPtr<RndTransformable, ObjectDir> mFirstSpot; // 0x34
    ObjPtr<RndTransformable, ObjectDir> mSecondSpot; // 0x40
    std::vector<Vector3> unk4c; // 0x4c
    std::vector<Vector3> unk54; // 0x54
    std::vector<int> unk5c; // 0x5c
    int unk64; // 0x64
    int unk68; // 0x68
    std::vector<int> unk6c; // 0x6c
    int unk74; // 0x74
    bool unk78; // 0x78
    ObjPtr<Character, ObjectDir> unk7c; // 0x7c
    float unk88; // 0x88
    bool mIsRightHand; // 0x8c
};