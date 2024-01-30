#ifndef RB3_INTPACKER_HPP
#define RB3_INTPACKER_HPP

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

    unsigned char* unk0;
    unsigned int pos;
    unsigned int unk8;
    
};

#endif
