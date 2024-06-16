#include "synth/SampleData.h"

SampleDataAllocFunc SampleData::sAlloc = 0;
SampleDataFreeFunc SampleData::sFree = 0;
BinStream& operator>>(BinStream& bs, SampleMarker& m);

void SampleData::SetAllocator(SampleDataAllocFunc a, SampleDataFreeFunc f){
    sAlloc = a;
    sFree = f;
}

SampleData::SampleData() : mData(0), mMarkers() {
    Reset();
}

SampleData::~SampleData(){
    sFree(mData);
}

void SampleData::Load(BinStream& bs, const FilePath& fp){
    Reset();
    int rev;
    bs >> rev;
    if(rev < 0xF){
        int fmt;
        bs >> fmt >> mNumSamples >> mSampleRate >> mSizeBytes;
        bool b = true;
        mFormat = (Format)fmt;
        if(rev > 10){
            bs >> b;
        }
        if(b){
            // platformmgr
        }
        if(rev > 0xD) bs >> mMarkers;
    }
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

int SampleData::NumMarkers() const { return mMarkers.size(); }
const SampleMarker& SampleData::GetMarker(int i) const { return mMarkers[i]; }

BinStream& operator>>(BinStream& bs, SampleMarker& m){
    bs >> m.name;
    bs >> m.sample;
    return bs;
}