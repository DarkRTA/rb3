#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class FaceTypeProvider : public UIListProvider, public Hmx::Object {
public:
    FaceTypeProvider();
    virtual ~FaceTypeProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;

    void Update(Symbol);

    std::vector<Symbol> unk20; // 0x20
};