#ifndef UTL_TICKEDINFO_H
#define UTL_TICKEDINFO_H
#include <vector>

template <class T> class TickedInfo {
public:
    int mTick;
    T mInfo;
};

template <class T> class TickedInfoCollection {
public:
    TickedInfoCollection() : mInfos() {}
    std::vector<TickedInfo<T>*> mInfos;
};

#endif
