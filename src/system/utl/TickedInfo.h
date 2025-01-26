#pragma once
#include <vector>
#include "os/Debug.h"

template <class T> class TickedInfo {
public:
    TickedInfo(int i, T t) : mTick(i), mInfo(t) {}
    TickedInfo<T>& operator=(const T& item){
        mInfo = item;
    }
    int mTick;
    T mInfo;
};

template <class T> class TickedInfoCollection {
public:
    TickedInfoCollection() : mInfos() {}
    bool AddInfo(int tick, T item){
        if(mInfos.empty() || mInfos.back().mTick <= tick){
            mInfos.push_back(TickedInfo<T>(tick, item));
            return true;
        }
        else return false;
    }
    void SetInfo(int idx, const T& item){
        MILO_ASSERT(0 <= idx && idx < mInfos.size(), 0x52);
        mInfos[idx] = item;
    }
    bool Cmp(int tick, const TickedInfo<T>& info){
        return tick < info.mTick;
    }
    void Clear(){ mInfos.clear(); }
    int Size() const { return mInfos.size(); }

    std::vector<TickedInfo<T> > mInfos;
};