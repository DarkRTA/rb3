#include "StringConversion.h"
#include "types.h"
#include <sdk/PowerPC_EABI_Support/MSL/MSL_C/string.h>

namespace {
    void Latin1ToUtf8(const char* in, char* out, unsigned int len) {
        u8 srch = *in;
        len--;
        while (srch != 0 && len != 0) {
            if ((s16)srch >= 0x80) {
                u8 nu_hi = ((u16)srch >> 6) & 0x1F;
                srch &= 0x3F;
                *out = nu_hi | 0xC0;
                *(out + 1) = srch | 0x80;
                len -= 2;
                out += 2;
            } else {
                *(out++) = srch;
                len--;
            }
            srch = *((const u8*)++in);
        }
        *out = 0;
    }
    void Utf8ToLatin1(const char* in, char* out, unsigned int len) {
        u8 srch = *in;
        len--;
        bool hitNonLatin1Char = false;
        while (srch != 0 && len != 0 && !hitNonLatin1Char) {
            if (srch <= 0x7F) {
                *out = srch;
                out++;
                len--;
            } else {
                if ((srch - 0xC0) <= 0x1F) {
                    u8 hi = *in;
                    len--;
                    u8 lo = *((const u8*)++in);
                    *out = ((hi - 0xC0) << 6) + lo - 0x80;
                    out++;
                } else {
                    hitNonLatin1Char = true;
                }
            }
            srch = *((const u8*)++in);
        }
        *out = 0;
    }
}

namespace Quazal {
namespace StringConversion {
    void Char8_2T(const char* in, char* out, unsigned int len) {
        strcpy(out, in); // BUG: should be strncpy(out, in, len);
    }

    void T2Char8(const char* in, char* out, unsigned int len) {
        strcpy(out, in); // BUG: should be strncpy(out, in, len);
    }

    void Utf8ToT(const char* in, char* out, unsigned int len) {
        Utf8ToLatin1(in, out, len);
    }

    void TToUtf8(const char* in, char* out, unsigned int len) {
        Latin1ToUtf8(in, out, len);
    }

    int GetTToUtf8BufferSize(const char* str) {
        return strlen(str) * 2 + 1;
    }

}
}

