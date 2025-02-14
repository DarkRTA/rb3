#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class PracticeSection {
public:
    int unk0;
    int unk4;
    int unk8;
    int unkc;
    int unk10;
    int unk14;
    int unk18;
    int unk1c;
    int unk20;
};

class PracticeSectionProvider : public UIListProvider, public Hmx::Object {
public:
    PracticeSectionProvider();
    virtual ~PracticeSectionProvider() {}
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual Symbol DataSymbol(int) const;
    virtual int DataIndex(Symbol) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    virtual void InitData(RndDir *);
    virtual UIColor *SlotColorOverride(int, int, class UIListWidget *, UIColor *c) const;
    virtual DataNode Handle(DataArray *, bool);

    const PracticeSection &GetSection(int) const;

    std::vector<PracticeSection> unk20; // 0x20
    Symbol unk28; // 0x28
    int unk2c;
    int unk30;
    float unk34;
    float unk38;
    bool unk3c;
    int unk40;
    int unk44;
    int unk48;
    int unk4c;
};