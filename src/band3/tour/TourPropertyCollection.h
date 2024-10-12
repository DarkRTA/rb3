#pragma once
#include "meta/FixedSizeSaveable.h"
#include "utl/Symbol.h"

class TourPropertyCollection : public FixedSizeSaveable {
public:
    TourPropertyCollection();
    virtual ~TourPropertyCollection();
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    float GetPropertyValue(Symbol) const;
    void SetPropertyValue(Symbol, float);
    void Clear();

    static int SaveSize(int);

    std::map<Symbol, float> mTourProperties; // 0x8
};