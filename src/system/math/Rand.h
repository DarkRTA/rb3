#ifndef MATH_RAND_H
#define MATH_RAND_H

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
};

#endif
