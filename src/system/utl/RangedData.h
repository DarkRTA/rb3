#pragma once
#include <vector>

template <class T> class RangedDataCollection {
public:
    template <class D> class RangedData {
    public:
        RangedData(int start, int end, T tData) : mStartTick(start), mEndTick(end), data(tData) {}
        bool CompareRangeStarts(const RangedData& other){
            return other.mStartTick < mStartTick;
        }

        int mStartTick;
        int mEndTick;
        T data;
    };

    void Clear(){ mRangeDataArray.clear(); }
    void AddData(int idx, int startTick, int endTick, const T& item){
        while(mRangeDataArray.size() <= idx){
            std::vector<RangedData<T> > data;
            mRangeDataArray.push_back(data);
        }
        mRangeDataArray[idx].push_back(RangedData<T> (startTick, endTick, item));
    }

    std::vector<std::vector<RangedData<T> > > mRangeDataArray;
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
