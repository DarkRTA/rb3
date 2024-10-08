#pragma once
#include "obj/Object.h"
#include "ui/UIListProvider.h"

class Modifier {
public:
    Modifier(DataArray*);
    bool IsHidden() const;
    bool CustomLocation() const;
    bool SaveValue() const;
    bool UseSaveValue() const;
    bool DefaultEnabled() const;
    bool DelayedEffect() const;

    DataArray* mData; // 0x0
    bool mDefaultEnabled; // 0x4
};

class ModifierMgr : public Hmx::Object, public UIListProvider {
public:
    ModifierMgr();
    virtual ~ModifierMgr();
    virtual DataNode Handle(DataArray*, bool);
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual bool IsHidden(int) const;
    virtual bool IsActive(int) const;

    bool IsModifierActive(Symbol) const;

    static void Init();

    std::vector<Modifier*> unk20; // 0x20
    std::vector<Modifier*> unk28; // 0x28
};

extern ModifierMgr* TheModifierMgr;