#ifndef OS_ARCHIVE_H
#define OS_ARCHIVE_H

#include "utl/HxGuid.h"
#include "utl/Str.h"
#include <vector>

class ArkHash {
    public:
    ArkHash();
    int GetHashValue(const char*) const;
    int Read(BinStream&, int);
    int a,b,c,d,e;
};

const int preinitArk = 1;

class Archive {
    public:
    Archive(const char*, int);
    void GetFileInfo(const char*, int&, unsigned long long&, int&, int&);
    void Read(int);

    int unk_0;
    std::vector<int> unk_4;
    std::vector<int> unk_c;
    std::vector<int> unk_14;
    std::vector<int> unk_1c;
    ArkHash mHash;
    String mArkName;
    int i, j; bool b;
    HxGuid mGuid;

};

#endif // OS_ARCHIVE_H