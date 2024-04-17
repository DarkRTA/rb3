#ifndef OS_ARCHIVE_H
#define OS_ARCHIVE_H

#include "utl/HxGuid.h"
#include "utl/Str.h"
#include "types.h"
#include <vector>

class ArkHash {
    public:
    ArkHash();
    int GetHashValue(const char*) const;
    int Read(BinStream&, int);
    int operator[](int) const;
    int a,b,c,d,e;
};

class FileEntry {
public:
    u64 mOffset;
    u32 mFilename;
    u32 unk_c, unk_10, unk_14;
};

BinStream& operator>>(BinStream&, FileEntry&);

const int preinitArk = 1;

class Archive {
    public:
    Archive(const char*, int);
    void GetFileInfo(const char*, int&, unsigned long long&, int&, int&);
    void Read(int);
    void Enumerate(const char*, void (*)(const char*, const char*), bool, const char*);
    const char* GetArkfileName(int) const;
    void GetGuid(HxGuid&) const;

    int unk_0;
    std::vector<uint, u16> unk_4;
    std::vector<String, u16> mFilenames;
    std::vector<int> unk_14;
    std::vector<int> unk_1c;
    ArkHash mHash;
    String mArkName;
    int i, j; bool b;
    HxGuid mGuid;

};

Archive* TheArchive;

#endif // OS_ARCHIVE_H