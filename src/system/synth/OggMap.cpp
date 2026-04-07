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

// this is probably really fake
template <class T>
inline bool ClampEq2(T &value, const T &min, const T &max) {
    // T temp = min;
    if (value < min) {
        value = min;
        return true;
    } else if (value > max) {
        value = max;
        return true;
    }
    return false;
}

void OggMap::GetSeekPos(int sampTarget, int &seekPos, int &actSamp) {
    const int min = 0;
    MILO_ASSERT(!mLookup.empty(), 0x54);
    int i14 = sampTarget / mGran;
    int i18 = mLookup.size() - 1;
    ClampEq2(i14, 0, i18);
    seekPos = mLookup[i14].first;
    actSamp = mLookup[i14].second;
}