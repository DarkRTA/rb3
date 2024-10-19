#pragma once
#include "meta_band/TexLoadPanel.h"
#include "ui/UIListProvider.h"
#include "obj/Object.h"
#include "utl/Symbol.h"

class FaceOptionsProvider : public UIListProvider, public Hmx::Object {
public:
    FaceOptionsProvider(const std::vector<DynamicTex*>& vec) : unk20(vec), mGender(gNullStr), unk30(0) {}
    virtual ~FaceOptionsProvider(){}
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual int NumData() const;

    const std::vector<DynamicTex*>& unk20;
    Symbol mGender; // 0x24
    String unk28;
    int unk30;
};