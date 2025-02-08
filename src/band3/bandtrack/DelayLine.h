#pragma once
#include <string.h>

template <class T, int N>
class DelayLine {
public:
    DelayLine() : mCur(0) { memset(mData, 0, sizeof(mData)); }
    void Clear() {
        memset(mData, 0, sizeof(mData));
        mCur = 0;
    }
    void Set(const T &data) {
        mCur++;
        if (mCur >= N) {
            mCur = 0;
        }
        mData[mCur] = data;
    }

    T mData[N];
    int mCur;
};