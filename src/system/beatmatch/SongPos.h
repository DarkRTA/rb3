#ifndef BEATMATCH_SONGPOS_H
#define BEATMATCH_SONGPOS_H

class SongPos {
public:
    SongPos() : mTotalTick(0), mMeasure(0), mBeat(0), mTick(0) {}
    SongPos(float tt, float tb, int m, int b, int t) : mTotalTick(tt), mTotalBeat(tb), mMeasure(m), mBeat(b), mTick(t) {}
    
    float mTotalTick; // 0x0
    float mTotalBeat; // 0x4
    int mMeasure; // 0x8
    int mBeat; // 0xc
    int mTick; // 0x10
};

#endif
