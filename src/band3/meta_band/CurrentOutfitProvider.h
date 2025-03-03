#pragma once
#include "obj/Object.h"
#include "ui/UIListProvider.h"

class CurrentOutfitProvider : public UIListProvider, public Hmx::Object {
public:
    CurrentOutfitProvider();
    virtual ~CurrentOutfitProvider();
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual void UpdateExtendedText(int, int, UILabel *) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;

    void Update();

    std::vector<Symbol> unk20; // 0x20
};
