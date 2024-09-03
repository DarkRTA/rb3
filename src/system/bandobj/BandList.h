#pragma once
#include "ui/UIList.h"
#include "rndobj/TransAnim.h"
#include "synth/Sequence.h"

class HighlightObject {
public:
    HighlightObject(Hmx::Object*);
};

class BandList : public UIList {
public:
    enum AnimState {

    };

    enum RevealState {

    };

    BandList();
    OBJ_CLASSNAME(BandList)
    OBJ_SET_TYPE(BandList)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~BandList();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void Exit();
    virtual void AdjustTrans(Transform&, const UIListElementDrawState&);
    virtual void AdjustTransSelected(Transform&);

    void ConcealNow();
    void Conceal();

    int unk1e8; // 0x1e8
    std::map<int, AnimState> unk1ec; // 0x1ec
    std::map<int, float> unk204; // 0x204
    std::map<int, float> unk21c; // 0x21c
    std::map<int, RevealState> unk234; // 0x234
    std::map<int, float> unk24c; // 0x24c
    std::map<int, bool> unk264; // 0x264
    ObjPtr<RndTransAnim, ObjectDir> unk27c; // 0x27c
    ObjPtr<RndTransAnim, ObjectDir> unk288; // 0x288
    ObjPtr<RndTransAnim, ObjectDir> unk294; // 0x294
    ObjPtr<RndTransAnim, ObjectDir> unk2a0; // 0x2a0
    ObjPtr<Sequence, ObjectDir> unk2ac; // 0x2ac
    ObjPtr<Sequence, ObjectDir> unk2b8; // 0x2b8
    float unk2c4; // 0x2c4
    float unk2c8; // 0x2c8
    float unk2cc; // 0x2cc
    float unk2d0; // 0x2d0
    float unk2d4; // 0x2d4
    float unk2d8; // 0x2d8
    float unk2dc; // 0x2dc
    float unk2e0; // 0x2e0
    bool unk2e4; // 0x2e4
    int unk2e8; // 0x2e8
    float unk2ec; // 0x2ec
    ObjVector<HighlightObject> unk2f0; // 0x2f0
};