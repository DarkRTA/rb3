#ifndef MATH_RAND2_H
#define MATH_RAND2_H

/** Used for decrypting encrypted BinStreams */
class Rand2 {
public:
    Rand2(int);
    int Int();
    int mSeed;
};

#endif
