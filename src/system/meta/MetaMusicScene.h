#pragma once
#include "obj/Data.h"
#include "utl/Symbol.h"
#include <list>

class MetaMusicScene {
public:
    MetaMusicScene(DataArray*);
    virtual ~MetaMusicScene();

    void Configure(DataArray*);
    Symbol GetName() const;
    const std::list<Symbol>& GetScreenList() const;
    DataArray* GetMix() const { return mMix; }

    Symbol m_symName; // 0x4
    std::list<Symbol> m_lScreens; // 0x8
    DataArray* mMix; // 0x10
};
