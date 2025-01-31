#pragma once

class SongPos {
public:
    SongPos() : mTotalTick(0), mMeasure(0), mBeat(0), mTick(0) {}
    SongPos(float tt, float tb, int m, int b, int t) : mTotalTick(tt), mTotalBeat(tb), mMeasure(m), mBeat(b), mTick(t) {}
    
    float GetTotalTick() const { return mTotalTick; }
    float GetTotalBeat() const { return mTotalBeat; }
    int GetMeasure() const { return mMeasure; }
    int GetBeat() const { return mBeat; }
    int GetTick() const { return mTick; }

    float mTotalTick; // 0x0
    float mTotalBeat; // 0x4
    int mMeasure; // 0x8
    int mBeat; // 0xc
    int mTick; // 0x10
};