#ifndef UTL_STRINGTABLE_H
#define UTL_STRINGTABLE_H
#include <vector>

class StringTable {
public:
    struct Buf {
        int size;
        char* chars;
    };
    
    std::vector<Buf> mBuffers; // 0x0
    char* mCurChar; // 0x8
    int mCurBuf; // 0xc

    NEW_POOL_OVERLOAD(StringTable);
    DELETE_POOL_OVERLOAD(StringTable);
    
    StringTable(int);
    ~StringTable();
    const char* Add(const char*);
    void AddBuf(int);
    void Clear();
    void Reserve(int);
    int Size() const;
    int UsedSize() const;
};

#endif
