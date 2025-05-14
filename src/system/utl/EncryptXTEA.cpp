#include "utl/EncryptXTEA.h"

#include <string.h>

XTEABlockEncrypter::XTEABlockEncrypter() {
    mNonce[0] = 0;
    mNonce[1] = 0;
}

void XTEABlockEncrypter::SetKey(const unsigned char *uc) { memcpy(mKey, uc, 0x10); }

void XTEABlockEncrypter::SetNonce(const unsigned long long *ull, unsigned int ui) {
    mNonce[0] = ull[0] + ui;
    mNonce[1] = ull[1] + ui;
}

unsigned long long
XTEABlockEncrypter::Encipher(unsigned long long ull, unsigned int *ui) {
    unsigned long v[2] = { (ull >> 32), (ull & 0xFFFFFFFF) }; // only god knows if this is
                                                                      // right
    unsigned int sum = 0;
    for (int i = 0; i < 4; i++) {
        v[1] += (v[0] + (v[0] << 4 ^ v[0] >> 5)) ^ sum + (ui[(sum & 3)]);
        sum += 0x9E3779B9;
        v[0] += (v[1] + (v[1] << 4 ^ v[1] >> 5)) ^ sum + ui[(sum >> 11) & 3];
    }
    return *v;
}
