#pragma once
#include "obj/Object.h"
#include "ui/UIListProvider.h"
#include "meta/FixedSizeSaveableStream.h"

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
    Modifier* GetModifierAtListData(int) const;
    bool IsModifierUnlocked(Modifier*) const;
    bool IsModifierActive(Modifier*) const;
    bool HasModifier(Symbol);
    Modifier* GetModifier(Symbol, bool) const;
    void ToggleModifierEnabled(Symbol);
    bool IsModifierDelayedEffect(Symbol) const;
    int SaveSize(int);
    void DisableAutoVocals() const;
    void Save(FixedSizeSaveableStream&);
    void Load(FixedSizeSaveableStream&, int);

    static void Init();

    std::vector<Modifier*> mModifiers; // 0x20
    std::vector<Modifier*> mModifiersList; // 0x28
};

extern ModifierMgr* TheModifierMgr;