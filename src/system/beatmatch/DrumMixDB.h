#pragma once
#include <vector>
#include "utl/Str.h"
#include "utl/TickedInfo.h"

class DrumMixDB {
public:
    DrumMixDB(int);
    ~DrumMixDB();
    void Clear();
    bool AddMix(int, int, const char *);
    TickedInfoCollection<String> &GetMixList(int);
    DrumMixDB *Duplicate() const;

    std::vector<TickedInfoCollection<String> *> mMixLists; // 0x0
};