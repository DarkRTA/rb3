#pragma once
#include <vector>
#include "os/Debug.h"

/**
 * @brief Info with an extra field to track the tick it occurs at.
 *
 * @tparam T The info type.
 */
template <class T>
class TickedInfo {
public:
    TickedInfo(int i, T t) : mTick(i), mInfo(t) {}
    TickedInfo<T> &operator=(const T &item) { mInfo = item; }
    int mTick;
    T mInfo;
};

/**
 * @brief A collection of TickedInfo structures.
 *
 * @tparam T The info type.
 */
template <class T>
class TickedInfoCollection {
public:
    TickedInfoCollection() : mInfos() {}
    /** Add a new TickedInfo to the collection.
     * @param [in] tick The tick at which this new item occurs at.
     * @param [in] item The item to add.
     */
    bool AddInfo(int tick, T item) {
        if (mInfos.empty() || mInfos.back().mTick <= tick) {
            mInfos.push_back(TickedInfo<T>(tick, item));
            return true;
        } else
            return false;
    }
    void SetInfo(int idx, const T &item) {
        MILO_ASSERT(0 <= idx && idx < mInfos.size(), 0x52);
        mInfos[idx] = item;
    }
    static bool Cmp(int tick, const TickedInfo<T> &info) { return tick < info.mTick; }
    void Clear() { mInfos.clear(); }
    int Size() const { return mInfos.size(); }
    void CopyFrom(const TickedInfoCollection &other) {
        mInfos.clear();
        mInfos.reserve(other.mInfos.size());
        mInfos.insert(mInfos.begin(), other.mInfos.begin(), other.mInfos.end());
    }
    std::vector<TickedInfo<T> > mInfos;
};