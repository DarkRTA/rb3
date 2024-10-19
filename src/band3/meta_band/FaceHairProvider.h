#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class FaceHairProvider : public UIListProvider, public Hmx::Object {
public:
    FaceHairProvider();
    virtual ~FaceHairProvider();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;

    std::vector<Symbol> unk20; // 0x20
    std::vector<Symbol> unk28; // 0x28
    std::vector<Symbol>* unk30; // 0x30
};