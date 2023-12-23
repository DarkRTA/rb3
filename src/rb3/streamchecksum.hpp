#ifndef RB3_STREAMCHECKSUM_HPP
#define RB3_STREAMCHECKSUM_HPP
#include "csha1.hpp"

class StreamChecksum {
public:
    char *file_checksum; // either a char*, or char**/Symbol
    char *unk4;
    CSHA1 unk8; // either CSHA1 or CSHA1*

    void Begin(const char *, bool);
    unsigned int SetFileChecksum(bool);
    void Update(unsigned const char *, unsigned int);
    void End();
    void Validate();
    int ValidateChecksum(unsigned const char *);
    void HandleError(const char *);
};

#endif
