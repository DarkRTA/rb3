#include "TourGameModifier.h"
#include "obj/Data.h"

TourGameModifier::TourGameModifier() {}

TourGameModifier::~TourGameModifier() {}

void TourGameModifier::Init(const DataArray* i_pConfig) {
    mModifiers.clear();
    if (i_pConfig)
    for (int i = 1; i < i_pConfig->Size(); i++) {
        mModifiers.insert(i_pConfig->Sym(i));
    }
}