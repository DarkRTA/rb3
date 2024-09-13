#pragma once
#include "ui/UIColor.h"
#include "ui/UIComponent.h"
#include "bandobj/BandLabel.h"
#include "rndobj/Mesh.h"

class InstrumentDifficultyDisplay : public UIComponent {
public:
    enum InstrumentState {
        kHidden,
        kName,
        kIcon
    };

    InstrumentDifficultyDisplay();
    OBJ_CLASSNAME(InstrumentDifficultyDisplay);
    OBJ_SET_TYPE(InstrumentDifficultyDisplay);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~InstrumentDifficultyDisplay();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Update();

    void SetValues(Symbol, int, int, bool);
    void UpdateDisplay();
    void SetInstrumentState(InstrumentState);

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(InstrumentDifficultyDisplay);
    }
    NEW_OBJ(InstrumentDifficultyDisplay);
    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int unk10c; // 0x10c
    RndMesh* unk110; // 0x110
    int unk114; // 0x114
    int unk118; // 0x118
    int unk11c; // 0x11c
    BandLabel* unk120; // 0x120
    InstrumentState mInstrumentState; // 0x124
    bool mHasPart; // 0x128
    int mDifficulty; // 0x12c
    int mNumVocalParts; // 0x130
    Symbol mInstrumentType; // 0x134
    ObjPtr<UIColor, ObjectDir> mInstrumentColorOverride; // 0x138
};