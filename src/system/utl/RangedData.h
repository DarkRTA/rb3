#pragma once
#include <vector>

template <class T> class RangedData {
public:
    int mStartTick;
    int mEndTick;
    T data;
};

template <class T> class RangedDataCollection {
public:
    void Clear(){ mRangeDataArray.clear(); }

    std::vector<RangedData<T>*> mRangeDataArray;
};

class RangeSection {
public:
    int unk0;
    float unk4;
    float unk8;
    float unkc;
};
