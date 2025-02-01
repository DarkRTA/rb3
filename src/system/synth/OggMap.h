#pragma once
#include <vector>
#include "utl/BinStream.h"

class OggMap {
public:
    OggMap();
    virtual ~OggMap();

    void Read(BinStream &);
    void GetSeekPos(int, int &, int &);

    int mGran; // 0x4
    std::vector<std::pair<int, int> > mLookup; // 0x8
};
