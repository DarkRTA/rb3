#ifndef BANDOBJ_STARDISPLAY_H
#define BANDOBJ_STARDISPLAY_H

#include "bandobj/BandLabel.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "rndobj/Text.h"
#include "ui/UIComponent.h"

class StarDisplay : public UIComponent {
    StarDisplay();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual ~StarDisplay();
    OBJ_CLASSNAME(StarDisplay)
    OBJ_SET_TYPE(StarDisplay)
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void CopyMembers(const UIComponent*, Hmx::Object::CopyType);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Update();
    virtual void Enter();

    void SetValues(int, int);
    void SetToToken(Symbol);
    void UpdateDisplay();
    void DrawShowing();
    
    static Symbol GetSymbolForStarCount(int);
    static int GetStarCountForSymbol(Symbol);
    static void Init();

    DECLARE_REVS
    NEW_OBJ(StarDisplay)

    BandLabel* unk_0x10C; // 0x10C
    BandLabel* unk_0x110; // 0x110
    bool unk_0x114; void SetForceMixedMode(bool); // 0x114
    bool unk_0x115; void SetShowDenominator(bool b); // 0x115
    bool unk_0x116; // 0x116
    int mStars; // 0x118
    int unk_0x11C; // 0x11C
    RndText::Alignment unk_0x120; void SetAlignment(RndText::Alignment); // 0x120
    Symbol unk_0x124; // 0x124
    Symbol unk_0x128; // 0x128
}; 

#endif // BANDOBJ_STARDISPLAY_H
