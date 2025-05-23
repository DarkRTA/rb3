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

#define XTEA_SUM0 0x9e3779b9
#define XTEA_SUM1 0x3c6ef372
#define XTEA_SUM2 0xdaa66d2b
#define XTEA_SUM3 0x78dde6e4

unsigned long long
XTEABlockEncrypter::Encipher(unsigned long long nonce, unsigned int *key) {
    unsigned int v0 = (unsigned int)(nonce >> 32);
    unsigned int v1 = (unsigned int)(nonce);
    v1 += (v0 + (v0 << 4 ^ v0 >> 5) ^ key[0]);
    v0 += (v1 + (v1 << 4 ^ v1 >> 5) ^ key[3] + XTEA_SUM0);
    v1 += (v0 + (v0 << 4 ^ v0 >> 5) ^ key[1] + XTEA_SUM0);
    v0 += (v1 + (v1 << 4 ^ v1 >> 5) ^ key[2] + XTEA_SUM1);
    v1 += (v0 + (v0 << 4 ^ v0 >> 5) ^ key[2] + XTEA_SUM1);
    v0 += (v1 + (v1 << 4 ^ v1 >> 5) ^ key[1] + XTEA_SUM2);
    v1 += (v0 + (v0 << 4 ^ v0 >> 5) ^ key[3] + XTEA_SUM2);
    v0 += (v1 + (v1 << 4 ^ v1 >> 5) ^ key[0] + XTEA_SUM3);
    return (v0 << 32) | v1;
}
