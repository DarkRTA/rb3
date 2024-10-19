#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class OutfitProvider : public UIListProvider, public Hmx::Object {
public:
    OutfitProvider();
    virtual ~OutfitProvider();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;

    std::vector<Symbol> unk20; // 0x20
};