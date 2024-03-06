#include "math/Rand.h"
#include "os/Debug.h"
#include <math.h>
#include "os/OSFuncs.h"

Rand gRand(0x29A);

Rand::Rand(int i) : mRandIndex1(0), mRandIndex2(0), mRandTable(), mSpareGaussianAvailable(0) {
    Seed(i);
}

void Rand::Seed(int seed) {
    for (int i = 0; i < 0x100; i++) {
        int j = seed * 0x41C64E6D + 0x3039;
        seed = j * 0x41C64E6D + 0x3039;
        mRandTable[i] = ((j >> 16) & 0xFFFF) | (seed & 0x7FFF0000);
    }
    mRandIndex1 = 0;
    mRandIndex2 = 0x67;
}

int Rand::Int(int low, int high) {
    MILO_ASSERT(high > low, 0x2B);
    return low + Int() % (high - low);
}

inline float Rand::Float(float f1, float f2) {
    return ((f2 - f1) * Float() + f1);
}

float Rand::Float() {
    return ((Int() & 0xFFFF) / 65536.0f);
}


int Rand::Int() {
    unsigned int u3 = mRandTable[mRandIndex1];
    unsigned int u1 = mRandTable[mRandIndex2];
    mRandTable[mRandIndex1] = u3 ^ u1;
    if (0xF9 <= ++mRandIndex1)
        mRandIndex1 = 0;
    if (0xF9 <= ++mRandIndex2)
        mRandIndex2 = 0;
    return u3 ^ u1;
}

float Rand::Gaussian() {
    float f2, f3, f4, f5;

    if (mSpareGaussianAvailable) {
        mSpareGaussianAvailable = false;
        return mSpareGaussianValue;
    } else {
        do {
            do {
                f2 = Float(-1.0f, 1.0f);
                f3 = Float(-1.0f, 1.0f);
                f5 = f2 * f2 + f3 * f3;
            } while (f5 >= 1.0f);
        } while (0 == f5);
        f4 = log(f5);
        f5 = sqrt((-2.0f * f4) / f5);
        mSpareGaussianValue = f2 * f5;
        mSpareGaussianAvailable = true;
        return f3 * f5;
    }
}

void SeedRand(int seed) {
    gRand.Seed(seed);
}

int RandomInt() {
    MILO_ASSERT(MainThread(), 0x6C);
    return gRand.Int();
}

int RandomInt(int i1, int i2) {
    MILO_ASSERT(MainThread(), 0x73);
    return gRand.Int(i1, i2);
}

float RandomFloat() {
    MILO_ASSERT(MainThread(), 0x79);
    return gRand.Float();
}

float RandomFloat(float f1, float f2) {
    MILO_ASSERT(MainThread(), 0x7F);
    return gRand.Float(f1, f2);
}
