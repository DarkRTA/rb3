#ifndef MATH_STREAMCHECKSUM_H
#define MATH_STREAMCHECKSUM_H
#include "math/SHA1.h"

class StreamChecksum {
public:
    int mState; // this is an enum - what the state enums are? that's anybody's guess
    CSHA1 mSHA1;

    void Begin();
    void Update(const unsigned char*, unsigned int);
    void End();
    void GetHash(unsigned char*);
};

class StreamChecksumValidator {
public:
    StreamChecksum mStreamChecksum;
    unsigned char* mSignature;
    const char* mFile;

    void Begin(const char*, bool);
    void Update(const unsigned char*, unsigned int);
    void End();
    void Validate();
    void HandleError(const char*);
    bool SetFileChecksum(bool);
    bool ValidateChecksum(const unsigned char*);
};

#endif
