#ifndef RB3_STREAMCHECKSUM_HPP
#define RB3_STREAMCHECKSUM_HPP
#include "csha1.hpp"

class StreamChecksum {
public:
    const unsigned char* mSignature;
    const char* mFile;
    CSHA1 mSHA1;

    StreamChecksum();
    ~StreamChecksum();
    bool Begin(const char *, bool);
    unsigned int SetFileChecksum(bool);
    void Update(unsigned const char *, unsigned int);
    void End();
    void Validate();
    int ValidateChecksum(unsigned const char *);
    void HandleError(const char *);
};

#endif
