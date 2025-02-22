#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class PracticeSection {
public:
    PracticeSection()
        : unk4(0), unk8(0), unkc(0), unk10(0), unk14(1), unk18(0), unk1c(0), unk20(0) {}
    Symbol unk0; // practice section name
    int unk4; // tick
    int unk8; // some other tick
    float unkc;
    float unk10;
    bool unk14;
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