#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class InstrumentFinishProvider : public UIListProvider, public Hmx::Object {
public:
    InstrumentFinishProvider();
    virtual ~InstrumentFinishProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;

    void Update(Symbol);

    std::vector<Symbol> mFinishes; // 0x20
};