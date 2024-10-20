#pragma once
#include "meta_band/TexLoadPanel.h"
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class EyebrowsProvider : public UIListProvider, public Hmx::Object {
public:
    EyebrowsProvider(const std::vector<DynamicTex*>&);
    virtual ~EyebrowsProvider(){}
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const { return unk20.size(); }

    void Update(Symbol);
    
    std::vector<Symbol> unk20; // 0x20
    const std::vector<DynamicTex*>& unk28; // 0x28
    Symbol unk2c; // 0x2c
};