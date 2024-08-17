#include <ec/base64.h>
#include <MSL_C++/iterator>

#include "macros.h"

bool base64_init;
char base64_dec[256];
char base64_enc[64];

void init_base64() {
    for (int i = 0; i < 26; i++) {
        base64_enc[i] = 'A' + i;
    }
    for (int i = 26; i < 52; i++) {
        base64_enc[i] = 'G' + i;
    }
    for (int i = 52; i < 62; i++) {
        base64_enc[i] = -4 + i;
    }
    base64_enc[62] = '+';
    base64_enc[63] = '/';

    for (int i = 0; i < ARRAY_LENGTH(base64_dec); i++) {
        base64_dec[i] = -1;
    }
    for (int i = 0; i < ARRAY_LENGTH(base64_enc); i++) {
        base64_dec[(unsigned char)base64_enc[i]] = i;
    }

    base64_init = true;
}

namespace ec {

    template <typename InIter, typename OutIter>
    ECResult base64_decode(InIter begin, InIter end, OutIter dest) {
        if (!base64_init) {
            init_base64();
        }

        int decodedCount = 0;
        int decodedValue = 0;
        for (InIter it = begin; it != end;) {
            char c = *it++;
            if (c == '=') {
                if (decodedCount == 1) {
                    return ECResult_Failure;
                } else if (decodedCount == 2) {
                    *dest++ = (decodedValue >> 4) & 0xFF;
                } else if (decodedCount == 3) {
                    decodedValue *= 64;
                    *dest++ = (decodedValue >> 16) & 0xFF;
                    *dest++ = (decodedValue >> 8) & 0xFF;
                }

                return ECResult_Success;
            }

            if (base64_dec[(unsigned char)c] >= 0) {
                decodedCount++;
                decodedValue = decodedValue * 64 + base64_dec[(unsigned char)c];
                if (decodedCount >= 4) {
                    decodedCount = 0;
                    *dest++ = (decodedValue >> 16) & 0xFF;
                    *dest++ = (decodedValue >> 8) & 0xFF;
                    *dest++ = (decodedValue >> 0) & 0xFF;
                    decodedValue = 0;
                }
            }
        }

        return ECResult_Success;
    }

    ECResult base64_decode(const ECString &src, ECString &dest) {
        return base64_decode(src.begin(), src.end(), std::inserter(dest, dest.end()));
    }

    template <typename OutIter>
    ECResult base64_encode(const void *_src, unsigned long length, OutIter dest) {
        if (!base64_init) {
            init_base64();
        }

        const unsigned char *it = (unsigned char *)_src;
        const unsigned char *end = it + length;

        int encodedCount = 0;
        int encodedValue = 0;
        while (it != end) {
            encodedCount++;
            encodedValue = encodedValue * 256 + *it++;
            if (encodedCount >= 3) {
                *dest++ = base64_enc[encodedValue >> 18 & 0x3F];
                *dest++ = base64_enc[encodedValue >> 12 & 0x3F];
                *dest++ = base64_enc[encodedValue >> 6 & 0x3F];
                *dest++ = base64_enc[encodedValue >> 0 & 0x3F];
                encodedCount = 0;
            }
        }

        if (encodedCount == 1) {
            encodedValue *= 65536;
            *dest++ = base64_enc[encodedValue >> 18 & 0x3F];
            *dest++ = base64_enc[encodedValue >> 12 & 0x3F];
            *dest++ = '=';
            *dest++ = '=';
        } else if (encodedCount == 2) {
            encodedValue *= 256;
            *dest++ = base64_enc[encodedValue >> 18 & 0x3F];
            *dest++ = base64_enc[encodedValue >> 12 & 0x3F];
            *dest++ = base64_enc[encodedValue >> 6 & 0x3F];
            *dest++ = '=';
        }

        return ECResult_Success;
    }

    ECResult base64_encode(const void *src, unsigned long length, ECString &dest) {
        return base64_encode(src, length, std::inserter(dest, dest.end()));
    }

}
