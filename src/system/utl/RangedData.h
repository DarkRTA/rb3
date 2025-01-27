#pragma once
#include <algorithm>
#include <vector>

/**
 * @brief A collection of RangedData.
 * 
 * @tparam T The data type.
 */
template <class T> class RangedDataCollection {
public:
    /**
     * @brief Data that is relevant from a set range of ticks.
     * 
     * @tparam D The data type.
     */
    template <class D> class RangedData {
    public:
        RangedData(int start, int end, T data) : mStartTick(start), mEndTick(end), mData(data) {}
        static bool CompareRangeStarts(int tick, const RangedData& data){
            return tick < data.mStartTick;
        }
        static bool CompareRangeEnds(int tick, const RangedData& data){
            return tick < data.mEndTick;
        }
        /** Check if a supplied tick is within the tick bounds of this RangedData. */
        bool CheckBounds(int tick) const {
            if(tick >= mStartTick && tick < mEndTick) return true;
            else return false;
        }

        int mStartTick; // 0x0
        int mEndTick; // 0x4
        T mData; // 0x8
    };

    void Clear(){ mRangeDataArray.clear(); }
    /** Add a new RangedData to a particular index's collection.
     *  @param [in] dataIdx The index to add the RangedData to.
     *  @param [in] startTick The starting tick of the RangedData.
     *  @param [in] endTick The ending tick of the RangedData.
     *  @param [in] item The item field of the RangedData.
     */
    void AddData(int dataIdx, int startTick, int endTick, const T& item){
        while(mRangeDataArray.size() <= dataIdx){
            std::vector<RangedData<T> > data;
            mRangeDataArray.push_back(data);
        }
        mRangeDataArray[dataIdx].push_back(RangedData<T> (startTick, endTick, item));
    }
    //
    // TODO: these are all placeholder method names.
    // RBVR and RB4 appear to have RangedData symbols - reference these to get the actual names.
    //
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
    /** Get the last possible RangedData RD, such that RD's startTick <= the supplied tick.
     * @param [in] dataIdx The index to add the RangedData to.
     * @param [in] tick The supplied tick.
     * @returns The RangedData with the above conditions.
     */
    const RangedData<T>* GetRangeData(int dataIdx, int tick){ // RangedDataLessEqStart?
        if(dataIdx >= mRangeDataArray.size()) return nullptr;
        else if(mRangeDataArray[dataIdx].empty()) return nullptr;
        else {
            const std::vector<RangedData<T> >& vec = mRangeDataArray[dataIdx];
            const RangedData<T>* data = std::upper_bound(vec.begin(), vec.end(), tick, RangedData<T>::CompareRangeStarts);
            if(data == mRangeDataArray[dataIdx].begin()) return nullptr;
            else {
                const RangedData<T>* before = &data[-1];
                if(!before->CheckBounds(tick)) return nullptr; 
                else return &data[-1];
            }
        }
    }
    /** Get the first possible RangedData RD, such that RD's endTick <= the supplied tick.
     * @param [in] dataIdx The index to add the RangedData to.
     * @param [in] tick The supplied tick.
     * @returns The RangedData with the above conditions.
     */
    const RangedData<T>* RangeDataEnd(int dataIdx, int tick){
        if(dataIdx >= mRangeDataArray.size()) return nullptr;
        else if(mRangeDataArray[dataIdx].empty()) return nullptr;
        else {
            const std::vector<RangedData<T> >& vec = mRangeDataArray[dataIdx];
            const RangedData<T>* data = std::upper_bound(vec.begin(), vec.end(), tick, RangedData<T>::CompareRangeEnds);
            if(data == mRangeDataArray[dataIdx].end()) return nullptr;
            else return data;
        }
    }
    bool GetNext(int dataIdx, int tick, T& data, int& startTick, int& endTick){
        const RangedData<T>* rangedData = RangeDataEnd(dataIdx, tick);
        if(rangedData == nullptr) return false;
        else {
            data = rangedData->mData;
            startTick = rangedData->mStartTick;
            endTick = rangedData->mEndTick;
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

    /** An array of RangedData, laid out as a vector of vectors. */
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
