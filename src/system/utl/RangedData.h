#pragma once
#include <algorithm>
#include <vector>

template <class T> class RangedDataCollection {
public:
    template <class D> class RangedData {
    public:
        RangedData(int start, int end, T data) : mStartTick(start), mEndTick(end), mData(data) {}
        static bool CompareRangeStarts(int tick, const RangedData& data){
            return tick < data.mStartTick;
        }
        static bool CompareRangeEnds(int tick, const RangedData& data){
            return tick < data.mEndTick;
        }
        bool CheckBounds(int tick) const {
            if(tick >= mStartTick && tick < mEndTick) return true;
            else return false;
        }

        int mStartTick; // 0x0
        int mEndTick; // 0x4
        T mData; // 0x8
    };

    void Clear(){ mRangeDataArray.clear(); }
    void AddData(int idx, int startTick, int endTick, const T& item){
        while(mRangeDataArray.size() <= idx){
            std::vector<RangedData<T> > data;
            mRangeDataArray.push_back(data);
        }
        mRangeDataArray[idx].push_back(RangedData<T> (startTick, endTick, item));
    }
    bool StartsAt(int idx, int start, int& end){
        const RangedData<T>* data = GetRangeData(idx, start);
        if(!data) return false;
        else if(data->mStartTick == start){
            end = data->mEndTick;
            return true;
        }
        else return false;
    }
    T GetData(int idx, int tick){
        const RangedData<T>* data = GetRangeData(idx, tick);
        if(data == nullptr) return T();
        else return data->mData;
    }
    const RangedData<T>* GetRangeData(int idx, int tick){
        if(idx >= mRangeDataArray.size()) return nullptr;
        else if(mRangeDataArray[idx].empty()) return nullptr;
        else {
            const std::vector<RangedData<T> >& vec = mRangeDataArray[idx];
            const RangedData<T>* data = std::upper_bound(vec.begin(), vec.end(), tick, RangedData<T>::CompareRangeStarts);
            if(data == mRangeDataArray[idx].begin()) return nullptr;
            else {
                const RangedData<T>* before = &data[-1];
                if(!before->CheckBounds(tick)) return nullptr; 
                else return &data[-1];
            }
        }
    }
    const RangedData<T>* RangeDataEnd(int idx, int tick){
        if(idx >= mRangeDataArray.size()) return nullptr;
        else if(mRangeDataArray[idx].empty()) return nullptr;
        else {
            const std::vector<RangedData<T> >& vec = mRangeDataArray[idx];
            const RangedData<T>* data = std::upper_bound(vec.begin(), vec.end(), tick, RangedData<T>::CompareRangeEnds);
            if(data == mRangeDataArray[idx].end()) return nullptr;
            else return data;
        }
    }
    bool GetNext(int idx, int tick, T& data, int& i1, int& i2){
        const RangedData<T>* rangedData = RangeDataEnd(idx, tick);
        if(rangedData == nullptr) return false;
        else {
            data = rangedData->mData;
            i1 = rangedData->mStartTick;
            i2 = rangedData->mEndTick;
            return true;
        }
    }
    bool AtTick(int i1, int i2, T& item){
        const RangedData<T>* data = GetRangeData(i1, i2);
        if(data == nullptr){
            return false;
        }
        else {
            item = data->mData;
            return true;
        }
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
