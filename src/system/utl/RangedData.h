#ifndef UTL_RANGEDDATA_H
#define UTL_RANGEDDATA_H
#include <vector>

template <class T> class RangedData {
    int mStartTick;
    int mEndTick;
    T data;
};

template <class T> class RangedDataCollection {
    std::vector<RangedData<T>*> mRangeDataArray;
};

class RangeSection {
public:
    int unk0;
    float unk4;
    float unk8;
    float unkc;
};

#endif
