#include "synth/OggMap.h"
#include "os/Debug.h"

#pragma pool_data off
OggMap::OggMap() : mGran(1000), mLookup() {
    mLookup.push_back(std::pair<int,int>(0, 0));
}
#pragma pool_data reset

OggMap::~OggMap(){
    mLookup.clear();
}

void OggMap::Read(BinStream& bs){
    int version;
    bs >> version;
    if(version < 0xb) MILO_FAIL("Incorrect oggmap version.");
    bs >> mGran >> mLookup;
}

void OggMap::GetSeekPos(int sampTarget, int& seekPos, int& actSamp){
    MILO_ASSERT(!mLookup.empty(), 0x54);
}