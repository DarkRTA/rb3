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
    void AddData(int, int, int, const T&);

    std::vector<RangedData<T>*> mRangeDataArray;
};

class RangeSection {
public:
    RangeSection(){}
    RangeSection(int i, float f) : unk0(i), unk4(f), unk8(3.4028235E+38f), unkc(-3.4028235E+38f) {}
    int unk0; // tick
    float unk4;
    float unk8;
    float unkc;
};
