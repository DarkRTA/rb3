#include "utl/EncryptXTEA.h"

#include <string.h>

XTEABlockEncrypter::XTEABlockEncrypter() {
    mNonce[0] = 0;
    mNonce[1] = 0;
}

void XTEABlockEncrypter::SetKey(const unsigned char *uc) { memcpy(mKey, uc, 0x10); }

void XTEABlockEncrypter::SetNonce(const unsigned long long *nonce, unsigned int shift) {
    mNonce[0] = nonce[0] + shift;
    mNonce[1] = nonce[1] + shift;
}

void XTEABlockEncrypter::Encrypt(const XTEABlock *in, XTEABlock *out) {
    unsigned long long *nonce = mNonce;
    for (int i = 0; i < 2; i++) {
        out->mData[i] = in->mData[i] ^ Encipher(*nonce, mKey);
        *nonce += 1;
        nonce++;
    }
}

unsigned long long
XTEABlockEncrypter::Encipher(unsigned long long nonce, unsigned int *key) {
    unsigned long v[2] = { (nonce >> 32), (nonce & 0xFFFFFFFF) }; // only god knows if this is right
    unsigned int sum = 0;
    for (int i = 0; i < 4; i++) {
        v[1] += (v[0] + (v[0] << 4 ^ v[0] >> 5)) ^ sum + (key[(sum & 3)]);
        sum += 0x9E3779B9;
        v[0] += (v[1] + (v[1] << 4 ^ v[1] >> 5)) ^ sum + key[(sum >> 11) & 3];
    }
    return *v;
}
