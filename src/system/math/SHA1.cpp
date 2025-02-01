#include "math/SHA1.h"
#include <stdio.h>
#include <string.h>

#include "decomp.h"

DECOMP_FORCEACTIVE(SHA1, "rb")

CSHA1::CSHA1() {
    &m_block->c = &m_workspace;
    Reset();
}

CSHA1::~CSHA1() { Reset(); }

void CSHA1::Reset() {
    m_state[0] = 0x67452301;
    m_state[1] = 0xEFCDAB89;
    m_state[2] = 0x98BADCFE;
    m_state[3] = 0x10325476;
    m_state[4] = 0xC3D2E1F0;
    m_count[0] = 0;
    m_count[1] = 0;
}

// shoutouts to clibs' implementation of sha1: https://github.com/clibs/sha1

#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))
#define blk0(i) m_block->l[i]
#define blk(i)                                                                           \
    (m_block->l[i & 15] =                                                                \
         rol(m_block->l[(i + 13) & 15] ^ m_block->l[(i + 8) & 15]                        \
                 ^ m_block->l[(i + 2) & 15] ^ m_block->l[i & 15],                        \
             1))

/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */
#define R0(v, w, x, y, z, i)                                                             \
    z += ((w & (x ^ y)) ^ y) + blk0(i) + 0x5A827999 + rol(v, 5);                         \
    w = rol(w, 30);
#define R1(v, w, x, y, z, i)                                                             \
    z += ((w & (x ^ y)) ^ y) + blk(i) + 0x5A827999 + rol(v, 5);                          \
    w = rol(w, 30);
#define R2(v, w, x, y, z, i)                                                             \
    z += (w ^ x ^ y) + blk(i) + 0x6ED9EBA1 + rol(v, 5);                                  \
    w = rol(w, 30);
#define R3(v, w, x, y, z, i)                                                             \
    z += (((w | x) & y) | (w & x)) + blk(i) + 0x8F1BBCDC + rol(v, 5);                    \
    w = rol(w, 30);
#define R4(v, w, x, y, z, i)                                                             \
    z += (w ^ x ^ y) + blk(i) + 0xCA62C1D6 + rol(v, 5);                                  \
    w = rol(w, 30);

void CSHA1::Transform(unsigned long *pState, const unsigned char *pBuffer) {
    unsigned long a, b, c, d, e;

    a = pState[0];
    b = pState[1];
    c = pState[2];
    d = pState[3];
    e = pState[4];
    memcpy(m_block->c, pBuffer, 0x40);
    R0(a, b, c, d, e, 0);
    R0(e, a, b, c, d, 1);
    R0(d, e, a, b, c, 2);
    R0(c, d, e, a, b, 3);
    R0(b, c, d, e, a, 4);
    R0(a, b, c, d, e, 5);
    R0(e, a, b, c, d, 6);
    R0(d, e, a, b, c, 7);
    R0(c, d, e, a, b, 8);
    R0(b, c, d, e, a, 9);
    R0(a, b, c, d, e, 10);
    R0(e, a, b, c, d, 11);
    R0(d, e, a, b, c, 12);
    R0(c, d, e, a, b, 13);
    R0(b, c, d, e, a, 14);
    R0(a, b, c, d, e, 15);
    R1(e, a, b, c, d, 16);
    R1(d, e, a, b, c, 17);
    R1(c, d, e, a, b, 18);
    R1(b, c, d, e, a, 19);
    R2(a, b, c, d, e, 20);
    R2(e, a, b, c, d, 21);
    R2(d, e, a, b, c, 22);
    R2(c, d, e, a, b, 23);
    R2(b, c, d, e, a, 24);
    R2(a, b, c, d, e, 25);
    R2(e, a, b, c, d, 26);
    R2(d, e, a, b, c, 27);
    R2(c, d, e, a, b, 28);
    R2(b, c, d, e, a, 29);
    R2(a, b, c, d, e, 30);
    R2(e, a, b, c, d, 31);
    R2(d, e, a, b, c, 32);
    R2(c, d, e, a, b, 33);
    R2(b, c, d, e, a, 34);
    R2(a, b, c, d, e, 35);
    R2(e, a, b, c, d, 36);
    R2(d, e, a, b, c, 37);
    R2(c, d, e, a, b, 38);
    R2(b, c, d, e, a, 39);
    R3(a, b, c, d, e, 40);
    R3(e, a, b, c, d, 41);
    R3(d, e, a, b, c, 42);
    R3(c, d, e, a, b, 43);
    R3(b, c, d, e, a, 44);
    R3(a, b, c, d, e, 45);
    R3(e, a, b, c, d, 46);
    R3(d, e, a, b, c, 47);
    R3(c, d, e, a, b, 48);
    R3(b, c, d, e, a, 49);
    R3(a, b, c, d, e, 50);
    R3(e, a, b, c, d, 51);
    R3(d, e, a, b, c, 52);
    R3(c, d, e, a, b, 53);
    R3(b, c, d, e, a, 54);
    R3(a, b, c, d, e, 55);
    R3(e, a, b, c, d, 56);
    R3(d, e, a, b, c, 57);
    R3(c, d, e, a, b, 58);
    R3(b, c, d, e, a, 59);
    R4(a, b, c, d, e, 60);
    R4(e, a, b, c, d, 61);
    R4(d, e, a, b, c, 62);
    R4(c, d, e, a, b, 63);
    R4(b, c, d, e, a, 64);
    R4(a, b, c, d, e, 65);
    R4(e, a, b, c, d, 66);
    R4(d, e, a, b, c, 67);
    R4(c, d, e, a, b, 68);
    R4(b, c, d, e, a, 69);
    R4(a, b, c, d, e, 70);
    R4(e, a, b, c, d, 71);
    R4(d, e, a, b, c, 72);
    R4(c, d, e, a, b, 73);
    R4(b, c, d, e, a, 74);
    R4(a, b, c, d, e, 75);
    R4(e, a, b, c, d, 76);
    R4(d, e, a, b, c, 77);
    R4(c, d, e, a, b, 78);
    R4(b, c, d, e, a, 79);

    pState[0] += a;
    pState[1] += b;
    pState[2] += c;
    pState[3] += d;
    pState[4] += e;
}

void CSHA1::Update(const unsigned char *data, unsigned long len) {
    unsigned long i, j;

    j = m_count[0];
    j = (j / 8) % 64;
    m_count[0] += len * 8;
    if (m_count[0] < len * 8) {
        m_count[1]++;
    }
    m_count[1] += (len >> 29);

    if ((j + len) > 63) {
        i = 64 - j;
        memcpy(&m_buffer[j], data, i);
        Transform(m_state, m_buffer);
        for (; i + 63 < len; i += 64) {
            Transform(m_state, &data[i]);
        }
        j = 0;
    } else
        i = 0;

    if (len - i != 0)
        memcpy(&m_buffer[j], &data[i], len - i);
}

CSHA1::Digest *CSHA1::Final() {
    unsigned int i;
    unsigned char finalcount[8];
    unsigned char c;

    for (i = 0; i < 8; i++) {
        finalcount[i] =
            (unsigned char)((m_count[(i >= 4 ? 0 : 1)] >> ((3 - (i & 3)) * 8)) & 255);
    }

    Update((const unsigned char *)"\x80", 1);
    while ((m_count[0] & 504) != 448) {
        Update((const unsigned char *)"\x00", 1);
    }
    Update(finalcount, 8);
    for (i = 0; i < 20; i++) {
        m_digest.digits[i] =
            (unsigned char)((m_state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
    }
    memset(m_buffer, 0, 0x40);
    memset(m_state, 0, 0x14);
    memset(m_count, 0, 8);
    memset(finalcount, 0, 8);
    Transform(m_state, m_buffer);
    return &m_digest;
}

void CSHA1::Digest::Copy(unsigned char *c) const { memcpy(c, this, 0x14); }

void CSHA1::Digest::ReportHash(char *c1, unsigned char uc) const {
    char buf[24];
    unsigned int ui;
    if (c1) {
        if (uc == 0) {
            sprintf(buf, "%02X", digits[0]);
            strcpy(c1, buf);
            for (ui = 1; ui < 0x14; ui++) {
                sprintf(buf, "%02X", digits[ui & 0xFF]);
                strcat(c1, buf);
            }
        } else if (uc == 1) {
            sprintf(buf, "%u", digits[0]);
            strcpy(c1, buf);
            for (ui = 1; ui < 0x14; ui++) {
                sprintf(buf, " %u", digits[ui & 0xFF]);
                strcat(c1, buf);
            }
        } else
            strcpy(c1, "Error: Unknown report type!");
    }
}

BinStream &operator>>(BinStream &bs, CSHA1::Digest &digest) {
    bs.Read(digest.digits, 0x14);
    return bs;
}
