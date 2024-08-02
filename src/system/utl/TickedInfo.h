#ifndef UTL_TICKEDINFO_H
#define UTL_TICKEDINFO_H
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
    bool AddInfo(int, T);
    bool Cmp(int tick, const TickedInfo<T>& info){
        return tick < info.mTick;
    }

    std::vector<TickedInfo<T> > mInfos;
};

#endif