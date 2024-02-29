#ifndef MATH_STRIPER_H
#define MATH_STRIPER_H
#include "math/Adjacency.h"
#include "math/CustomArray.h"

struct STRIPERRESULT {
    unsigned int NbStrips;
    unsigned int* StripLengths;
    void* StripRuns;
    bool AskForWords;
};

struct STRIPERCREATE {
    unsigned int NbFaces;
    unsigned int* DFaces;
    unsigned short* WFaces;
    bool AskForWords;
    bool OneSided;
    bool SGIAlgorithm;
    bool ConnectAllStrips;
};

class Striper {
public:
    Adjacencies* mAdj;
    bool* mTags;
    unsigned int mNbStrips;
    CustomArray* mStripLengths;
    CustomArray* mStripRuns;
    unsigned int mTotalLength;
    CustomArray* mSingleStrip;
    bool mAskForWords;
    bool mOneSided;
    bool mSGIAlgorithm;
    bool mConnectAllStrips;
};

#endif
