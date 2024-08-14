#include "MD5.h"
#include <string.h>
#include "macros.h"

namespace Quazal {

    MD5::MD5() {
        finalized = false;
        count[0] = 0;
        count[1] = 0;
        state[0] = 0x67452301L;
        state[1] = 0xefcdab89L;
        state[2] = 0x98badcfeL;
        state[3] = 0x10325476L;
    }

    void MD5::update(const unsigned char *data, unsigned int length) {
        if (finalized) {
            return;
        }

        unsigned int nl = count[0];
        unsigned int l = nl + ((length) << 3);
        count[0] = l;

        nl = nl >> 3 & 0x3F;
        if (l < (length << 3))
            count[1]++;

        unsigned int n = 0x40 - nl;
        count[1] += (length >> 29);

        if (length >= n) {
            memcpy(buffer + nl, data, n);
            transform(buffer);
            for (; n + 0x3F < length; n += 0x40) {
                transform(data + n);
            }
            nl = 0;
        } else {
            n = 0;
        }

        memcpy(buffer + nl, data + n, length - n);
    }

    void MD5::finalize() {
        if (finalized) {
            return;
        }

        static unsigned char PADDING[0x40] = { 0x80 };

        unsigned char dest[sizeof(*count) * 2];
        encode(dest, count, sizeof(count));

        unsigned int l = count[0] >> 3 & 0x3F;
        update(PADDING, l < 0x38 ? 0x38 - l : 0x78 - l);
        update(dest, sizeof(dest));
        encode(digest, state, sizeof(state));

        memset(buffer, 0, 1);
        finalized = true;
    }

    void MD5::transform(const unsigned char *data) {
        unsigned int local_state[4];
        unsigned int XX[16];

#define A local_state[3]
#define B local_state[2]
#define C local_state[1]
#define D local_state[0]

        A = state[0];
        B = state[1];
        C = state[2];
        D = state[3];

        decode(XX, data, sizeof(XX));

        // Round 0
        FF(A, B, C, D, XX[0], 7, 0xd76aa478L);
        FF(D, A, B, C, XX[1], 12, 0xe8c7b756L);
        FF(C, D, A, B, XX[2], 17, 0x242070dbL);
        FF(B, C, D, A, XX[3], 22, 0xc1bdceeeL);
        FF(A, B, C, D, XX[4], 7, 0xf57c0fafL);
        FF(D, A, B, C, XX[5], 12, 0x4787c62aL);
        FF(C, D, A, B, XX[6], 17, 0xa8304613L);
        FF(B, C, D, A, XX[7], 22, 0xfd469501L);
        FF(A, B, C, D, XX[8], 7, 0x698098d8L);
        FF(D, A, B, C, XX[9], 12, 0x8b44f7afL);
        FF(C, D, A, B, XX[10], 17, 0xffff5bb1L);
        FF(B, C, D, A, XX[11], 22, 0x895cd7beL);
        FF(A, B, C, D, XX[12], 7, 0x6b901122L);
        FF(D, A, B, C, XX[13], 12, 0xfd987193L);
        FF(C, D, A, B, XX[14], 17, 0xa679438eL);
        FF(B, C, D, A, XX[15], 22, 0x49b40821L);

        // Round 1
        GG(A, B, C, D, XX[1], 5, 0xf61e2562L);
        GG(D, A, B, C, XX[6], 9, 0xc040b340L);
        GG(C, D, A, B, XX[11], 14, 0x265e5a51L);
        GG(B, C, D, A, XX[0], 20, 0xe9b6c7aaL);
        GG(A, B, C, D, XX[5], 5, 0xd62f105dL);
        GG(D, A, B, C, XX[10], 9, 0x02441453L);
        GG(C, D, A, B, XX[15], 14, 0xd8a1e681L);
        GG(B, C, D, A, XX[4], 20, 0xe7d3fbc8L);
        GG(A, B, C, D, XX[9], 5, 0x21e1cde6L);
        GG(D, A, B, C, XX[14], 9, 0xc33707d6L);
        GG(C, D, A, B, XX[3], 14, 0xf4d50d87L);
        GG(B, C, D, A, XX[8], 20, 0x455a14edL);
        GG(A, B, C, D, XX[13], 5, 0xa9e3e905L);
        GG(D, A, B, C, XX[2], 9, 0xfcefa3f8L);
        GG(C, D, A, B, XX[7], 14, 0x676f02d9L);
        GG(B, C, D, A, XX[12], 20, 0x8d2a4c8aL);

        // Round 2
        HH(A, B, C, D, XX[5], 4, 0xfffa3942L);
        HH(D, A, B, C, XX[8], 11, 0x8771f681L);
        HH(C, D, A, B, XX[11], 16, 0x6d9d6122L);
        HH(B, C, D, A, XX[14], 23, 0xfde5380cL);
        HH(A, B, C, D, XX[1], 4, 0xa4beea44L);
        HH(D, A, B, C, XX[4], 11, 0x4bdecfa9L);
        HH(C, D, A, B, XX[7], 16, 0xf6bb4b60L);
        HH(B, C, D, A, XX[10], 23, 0xbebfbc70L);
        HH(A, B, C, D, XX[13], 4, 0x289b7ec6L);
        HH(D, A, B, C, XX[0], 11, 0xeaa127faL);
        HH(C, D, A, B, XX[3], 16, 0xd4ef3085L);
        HH(B, C, D, A, XX[6], 23, 0x04881d05L);
        HH(A, B, C, D, XX[9], 4, 0xd9d4d039L);
        HH(D, A, B, C, XX[12], 11, 0xe6db99e5L);
        HH(C, D, A, B, XX[15], 16, 0x1fa27cf8L);
        HH(B, C, D, A, XX[2], 23, 0xc4ac5665L);

        // Round 3
        II(A, B, C, D, XX[0], 6, 0xf4292244L);
        II(D, A, B, C, XX[7], 10, 0x432aff97L);
        II(C, D, A, B, XX[14], 15, 0xab9423a7L);
        II(B, C, D, A, XX[5], 21, 0xfc93a039L);
        II(A, B, C, D, XX[12], 6, 0x655b59c3L);
        II(D, A, B, C, XX[3], 10, 0x8f0ccc92L);
        II(C, D, A, B, XX[10], 15, 0xffeff47dL);
        II(B, C, D, A, XX[1], 21, 0x85845dd1L);
        II(A, B, C, D, XX[8], 6, 0x6fa87e4fL);
        II(D, A, B, C, XX[15], 10, 0xfe2ce6e0L);
        II(C, D, A, B, XX[6], 15, 0xa3014314L);
        II(B, C, D, A, XX[13], 21, 0x4e0811a1L);
        II(A, B, C, D, XX[4], 6, 0xf7537e82L);
        II(D, A, B, C, XX[11], 10, 0xbd3af235L);
        II(C, D, A, B, XX[2], 15, 0x2ad7d2bbL);
        II(B, C, D, A, XX[9], 21, 0xeb86d391L);

        state[0] += A;
        state[1] += B;
        state[2] += C;
        state[3] += D;

#undef A
#undef B
#undef C
#undef D

        memset(XX, 0, sizeof(XX));
    }

    void MD5::decode(unsigned int *dest, const unsigned char *src, unsigned int size) {
        if (size == 0) {
            return;
        }

        for (int i = 0; i < ((size + 3) / sizeof(*dest)); i++) {
            // clang-format off
            dest[i] = src[(i * 4) + 0] << 0 |
                src[(i * 4) + 1] << 8 |
                src[(i * 4) + 2] << 16 |
                src[(i * 4) + 3] << 24;
            // clang-format on
        }
    }

    void MD5::FF(
        unsigned int &a,
        unsigned int b,
        unsigned int c,
        unsigned int d,
        unsigned int k,
        unsigned int s,
        unsigned int t
    ) {
        a += t + k + ((b & c) | (~b & d));
        a = ROTATE_LEFT(a, s) + b;
    };

    void MD5::GG(
        unsigned int &a,
        unsigned int b,
        unsigned int c,
        unsigned int d,
        unsigned int k,
        unsigned int s,
        unsigned int t
    ) {
        a += t + k + ((b & d) | (c & ~d));
        a = ROTATE_LEFT(a, s) + b;
    }

    void MD5::HH(
        unsigned int &a,
        unsigned int b,
        unsigned int c,
        unsigned int d,
        unsigned int k,
        unsigned int s,
        unsigned int t
    ) {
        a += t + k + (d ^ (b ^ c));
        a = ROTATE_LEFT(a, s) + b;
    }

    void MD5::II(
        unsigned int &a,
        unsigned int b,
        unsigned int c,
        unsigned int d,
        unsigned int k,
        unsigned int s,
        unsigned int t
    ) {
        a += t + k + (c ^ (b | ~d));
        a = ROTATE_LEFT(a, s) + b;
    }
}
