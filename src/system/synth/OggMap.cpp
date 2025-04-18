#include "synth/OggMap.h"
#include "os/Debug.h"

OggMap::OggMap() : mGran(1000), mLookup() {
    mLookup.push_back(std::pair<int, int>(0, 0));
}

OggMap::~OggMap() { mLookup.clear(); }

void OggMap::Read(BinStream &bs) {
    int version;
    bs >> version;
    if (version < 0xb)
        MILO_FAIL("Incorrect oggmap version.");
    bs >> mGran >> mLookup;
}

void OggMap::GetSeekPos(int sampTarget, int &seekPos, int &actSamp) {
    MILO_ASSERT(!mLookup.empty(), 0x54);
    int i14 = sampTarget / mGran;
    int i18 = mLookup.size() - 1;
    ClampEq(i14, 0, i18);
    seekPos = mLookup[i14].first;
    actSamp = mLookup[i14].second;
}