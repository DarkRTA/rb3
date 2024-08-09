#ifndef BEATMATCH_SONGPOS_H
#define BEATMATCH_SONGPOS_H

class SongPos {
public:
    float mTotalTick; // 0x0
    float mTotalBeat; // 0x4
    int mMeasure; // 0x8
    int mBeat; // 0xc
    int mTick; // 0x10
};

#endif
