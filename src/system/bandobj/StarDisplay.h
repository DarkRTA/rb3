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
    void SetForceMixedMode(bool);
    void SetShowDenominator(bool b);
    void SetAlignment(RndText::Alignment);
    char GetStarIcon() const;
    char GetEmptyStarIcon() const;

    bool HasStarIcon() const;
    
    static Symbol GetSymbolForStarCount(int);
    static int GetStarCountForSymbol(Symbol);
    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(StarDisplay);
    }

    DECLARE_REVS
    NEW_OBJ(StarDisplay)

    BandLabel* mRsrcStarsLabel; // 0x10C
    BandLabel* mRsrcStarsMixedLabel; // 0x110
    bool mForceMixedMode; // 0x114
    bool mShowDenominator; // 0x115
    bool mShowEmptyStars; // 0x116
    int mStars; // 0x118
    int mTotalStars; // 0x11C
    RndText::Alignment mAlignment; // 0x120
    Symbol mIconOverride; // 0x124
    Symbol mEmptyIconOverride; // 0x128
}; 

#endif // BANDOBJ_STARDISPLAY_H
