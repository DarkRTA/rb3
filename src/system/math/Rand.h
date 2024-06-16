#ifndef MATH_RAND_H
#define MATH_RAND_H

#include "utl/MemMgr.h"

class Rand {
public:
    Rand(int);
    void Seed(int);
    int Int();
    int Int(int, int);
    float Float();
    float Float(float, float);
    float Gaussian();

    unsigned int mRandIndex1;
    unsigned int mRandIndex2;
    unsigned int mRandTable[256];
    float mSpareGaussianValue;
    bool mSpareGaussianAvailable;

    NEW_OVERLOAD
    DELETE_OVERLOAD
};

void SeedRand(int);
int RandomInt();
int RandomInt(int, int);
float RandomFloat();
float RandomFloat(float, float);

#endif
