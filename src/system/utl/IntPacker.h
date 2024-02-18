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
