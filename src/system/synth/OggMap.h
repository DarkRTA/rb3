#ifndef SYNTH_OGGMAP_H
#define SYNTH_OGGMAP_H
#include <vector>
#include "utl/BinStream.h"

class OggMap {
public:
    OggMap();
    virtual ~OggMap();

    void Read(BinStream&);
    void GetSeekPos(int, int&, int&);

    int mGran;
    std::vector<std::pair<int, int> > mLookup;
};

#endif
