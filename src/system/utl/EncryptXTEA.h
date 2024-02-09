#ifndef UTL_ENCRYPTXTEA_H
#define UTL_ENCRYPTXTEA_H

struct XTEABlock {
    unsigned long long mData[2];
};

class XTEABlockEncrypter {
public:
    unsigned long long mNonce[2];
    unsigned int mKey[4];
    
    XTEABlockEncrypter();
    void SetKey(const unsigned char*);
    void SetNonce(const unsigned long long*, unsigned int);
    void Encrypt(const XTEABlock*, XTEABlock*);
    unsigned long long Encipher(unsigned long long, unsigned int*);
};

#endif
