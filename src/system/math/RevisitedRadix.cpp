#include "math/RevisitedRadix.h"

RadixSorter::RadixSorter(){
    mIndices = 0;
    mIndices2 = 0;
    mCurrentSize = 0;
    mHistogram = new unsigned int[0x400];
    mOffset = new unsigned int[0x100];
    ResetIndices();
}

RadixSorter::~RadixSorter(){
    delete [] mOffset;
    mOffset = 0;
    delete [] mHistogram;
    mHistogram = 0;
    delete [] mIndices2;
    mIndices2 = 0;
    delete [] mIndices;
    mIndices = 0;
}

RadixSorter& RadixSorter::ResetIndices(){
    for(int i = 0; i < mCurrentSize; i++){
        mIndices[i] = i;
    }
}
