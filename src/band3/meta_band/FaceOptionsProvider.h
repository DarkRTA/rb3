#pragma once
#include "bandobj/BandHeadShaper.h"
#include "meta_band/TexLoadPanel.h"
#include "ui/UIListProvider.h"
#include "obj/Object.h"
#include "utl/Symbol.h"

class FaceOptionsProvider : public UIListProvider, public Hmx::Object {
public:
    FaceOptionsProvider(const std::vector<DynamicTex*>& vec) : mIcons(vec), mGender(gNullStr), mFaceOptionCount(0) {}
    virtual ~FaceOptionsProvider(){}
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual int NumData() const;

    void Update(Symbol s){
        mFaceOption = s.mStr;
        mFaceOptionCount = BandHeadShaper::GetCount(s);
    }

    const std::vector<DynamicTex*>& mIcons; // 0x20
    Symbol mGender; // 0x24
    String mFaceOption; // 0x28
    int mFaceOptionCount; // 0x34
};