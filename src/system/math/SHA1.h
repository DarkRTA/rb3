#ifndef MATH_SHA1_H
#define MATH_SHA1_H
#include "utl/BinStream.h"

union SHA1_WORKSPACE_BLOCK {
    unsigned char c[64];
    unsigned long l[16];
};

class CSHA1 {
public:
    struct Digest {
        unsigned char digits[20];
        void Copy(unsigned char *) const;
        void ReportHash(char *, unsigned char) const;
    };

    unsigned long m_state[5];
    unsigned long m_count[2];
    unsigned long m_reserved1[1];
    unsigned char m_buffer[64];
    Digest m_digest;
    unsigned long m_reserved2[3];
    unsigned char m_workspace[64];
    SHA1_WORKSPACE_BLOCK *m_block;

    CSHA1();
    ~CSHA1();
    void Reset();
    void Transform(unsigned long *, const unsigned char *);
    void Update(const unsigned char *, unsigned long);
    Digest *Final();
};

BinStream &operator>>(BinStream &, CSHA1::Digest &);

#endif
