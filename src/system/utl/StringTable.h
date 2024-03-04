#ifndef UTL_STRINGTABLE_H
#define UTL_STRINGTABLE_H
#include <vector>

class StringTable {
public:
    struct Buf {
        int size;
        char* chars;
    };
    
    std::vector<Buf> mBuffers;
    char* mCurChar;
    int mCurBuf;
    
    StringTable(int);
    ~StringTable();
    const char* Add(const char*);
    void AddBuf(int);
    void Clear();
};

#endif
