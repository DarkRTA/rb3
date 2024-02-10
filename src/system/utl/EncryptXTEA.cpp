#include "EncryptXTEA.h"
#include "string.h"

XTEABlockEncrypter::XTEABlockEncrypter(){
    mNonce[0] = 0;
    mNonce[1] = 0;
}

void XTEABlockEncrypter::SetKey(const unsigned char* uc){
    memcpy(mKey, uc, 0x10);
}

void XTEABlockEncrypter::SetNonce(const unsigned long long* ull, unsigned int ui){
    mNonce[0] = *ull + ui;
    mNonce[1] = mNonce[0];
}
