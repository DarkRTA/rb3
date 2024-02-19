#ifndef MATH_STREAMCHECKSUM_H
#define MATH_STREAMCHECKSUM_H
#include "math/SHA1.h"

class StreamChecksum {
public:
    int mUnknown; // looks like some sort of state (began, finalized, ended, etc)
    CSHA1 mSHA1;
};

#endif
