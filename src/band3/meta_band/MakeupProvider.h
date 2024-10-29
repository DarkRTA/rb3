#pragma once
#include "obj/Object.h"
#include "ui/UIListProvider.h"

class MakeupProvider : public UIListProvider, public Hmx::Object {
public:
    MakeupProvider(Symbol);
    virtual ~MakeupProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual void UpdateExtendedText(int, int, UILabel*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;

    void Update(Symbol);

    std::vector<Symbol> mMakeupEyes; // 0x20
    std::vector<Symbol> mMakeupLips; // 0x28
    std::vector<Symbol>* mCurrentMakeupList; // 0x30
};