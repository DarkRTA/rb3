#ifndef UTL_STRINGTABLE_H
#define UTL_STRINGTABLE_H

class StringTable {
public:
    int list;
    int unknown;
    
    StringTable(int);
    const char* Add(const char*);
};

#endif

// class StringTable {
//     // total size: 0x14
//     class vector mBuffers; // offset 0x0, size 0xC
//     char * mCurChar; // offset 0xC, size 0x4
//     int mCurBuf; // offset 0x10, size 0x4
// };
