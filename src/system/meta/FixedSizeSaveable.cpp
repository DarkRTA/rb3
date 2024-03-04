#include "meta/FixedSizeSaveable.h"

FixedSizeSaveable::FixedSizeSaveable() : mSaveSizeMethod(0) {
    
}

FixedSizeSaveable::~FixedSizeSaveable(){
    
}

void FixedSizeSaveable::Init(int i1, int i2){
    sSaveVersion = i1;
    sMaxSymbols = i2;
}
