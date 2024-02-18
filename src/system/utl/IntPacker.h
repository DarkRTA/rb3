#ifndef UTL_INTPACKER_H
#define UTL_INTPACKER_H

class IntPacker {
public:
    IntPacker(void*, unsigned int);
    void AddBool(bool);
    void AddS(int, unsigned int);
    void AddU(unsigned int, unsigned int);
    void Add(unsigned int, unsigned int);
    bool ExtractBool();
    int ExtractS(unsigned int);
    unsigned int ExtractU(unsigned int);
    void SetPos(unsigned int);

    unsigned char* mBuffer;
    unsigned int mPos;
    unsigned int mSize;
    
};

#endif

class IntPacker {
    // total size: 0xC
    unsigned char * mBuffer; // offset 0x0, size 0x4
    unsigned int mPos; // offset 0x4, size 0x4
    unsigned int mSize; // offset 0x8, size 0x4
};
