#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"
#include "meta_band/OvershellSlot.h"

class CymbalSelectionProvider : public UIListProvider, public Hmx::Object {
public:
    CymbalSelectionProvider(OvershellSlot*);
    virtual ~CymbalSelectionProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    
    void ReloadData();

    std::vector<Symbol> unk20;
    OvershellSlot* mSlot; // 0x28
};