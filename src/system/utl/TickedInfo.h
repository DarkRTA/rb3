#pragma once
#include <vector>

template <class T> class TickedInfo {
public:
    TickedInfo(int i, T t) : mTick(i), mInfo(t) {}
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
    bool Cmp(int tick, const TickedInfo<T>& info){
        return tick < info.mTick;
    }
    void Clear(){ mInfos.clear(); }

    std::vector<TickedInfo<T> > mInfos;
};