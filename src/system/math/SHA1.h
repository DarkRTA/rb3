#ifndef MATH_SHA1_H
#define MATH_SHA1_H

union SHA1_WORKSPACE_BLOCK {
    unsigned char c[64];
    unsigned long l[16];
};

class CSHA1 {
public:
    unsigned long m_state[5];
    unsigned long m_count[2];
    unsigned long m_reserved1[1];
    unsigned char m_buffer[64];
    unsigned char m_digest[20];
    unsigned long m_reserved2[3];
    unsigned char m_workspace[64];
    SHA1_WORKSPACE_BLOCK * m_block;
};

#endif
