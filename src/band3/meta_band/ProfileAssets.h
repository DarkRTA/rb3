#ifndef METABAND_PROFILEASSETS_H
#define METABAND_PROFILEASSETS_H

#include <vector>
#include "utl/Symbol.h"
#include "BandProfile.h"

class ProfileAssets {
    ProfileAssets(BandProfile*);
    virtual ~ProfileAssets();

    void Clear();
    void AddAsset(Symbol);
    bool HasAsset(Symbol) const;
    bool IsNew(Symbol) const;
    void SetOld(Symbol);
    void SaveSize(int);

    std::vector<Symbol> mSymbols;
};

#endif // METABAND_PROFILEASSETS_H