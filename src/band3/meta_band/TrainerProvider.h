#pragma once
#include "obj/Object.h"
#include "ui/UIListProvider.h"

class TrainerProvider : public UIListProvider, public Hmx::Object {
public:
    TrainerProvider();
    virtual ~TrainerProvider();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const { return mTrainers.size(); }
    
    std::vector<Symbol> mTrainers; // 0x20
};