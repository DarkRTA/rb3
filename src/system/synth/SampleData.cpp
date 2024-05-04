#include "synth/SampleData.h"

SampleDataAllocFunc SampleData::sAlloc = 0;
SampleDataFreeFunc SampleData::sFree = 0;

void SampleData::SetAllocator(SampleDataAllocFunc a, SampleDataFreeFunc f){
    sAlloc = a;
    sFree = f;
}

SampleData::SampleData() : mData(0), mMarkers() {
    Reset();
}

void SampleData::Reset(){
    sFree(mData);
    mData = 0;
    mFormat = kPCM;
    mSizeBytes = 0;
    mSampleRate = 0;
    mNumSamples = 0;
    mMarkers.clear();
}