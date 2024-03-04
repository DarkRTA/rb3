#ifndef META_METAMUSICSCENE_H
#define META_METAMUSICSCENE_H
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

    Symbol m_symName;
    std::list<Symbol> m_lScreens;
    DataArray* mMix;
};

#endif
