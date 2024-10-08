#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class PracticeSectionProvider : public UIListProvider, public Hmx::Object {
public:
    class PracticeSection {
    public:

    };

    PracticeSectionProvider();
    virtual ~PracticeSectionProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int DataIndex(Symbol) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    virtual void InitData(RndDir*);
    virtual UIColor* SlotColorOverride(int, int, class UIListWidget*, UIColor* c) const;
    virtual DataNode Handle(DataArray*, bool);
    
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