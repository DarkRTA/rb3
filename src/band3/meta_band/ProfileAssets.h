#ifndef METABAND_PROFILEASSETS_H
#define METABAND_PROFILEASSETS_H

#include <vector>
#include "utl/Symbol.h"
#include "BandProfile.h"

class ProfileAssets {
    ProfileAssets(BandProfile*);
    virtual ~ProfileAssets();

    void Clear();
    bool HasAsset(Symbol) const;
    bool IsNew(Symbol) const;
    void SetOld(Symbol);
    void SaveSize(int);

    std::vector<Symbol> mSymbols;

public:
    static void AddAsset(Symbol);
};

#endif // METABAND_PROFILEASSETS_H