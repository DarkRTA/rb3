#ifndef OS_ARCHIVE_H
#define OS_ARCHIVE_H

#include "utl/HxGuid.h"
#include "utl/Str.h"
#include "types.h"
#include "os/Debug.h"
#include <vector>

class ArkHash {
public:
    ArkHash();
    int GetHashValue(const char*) const;
    int Read(BinStream&, int);
    char* operator[](int idx) const {
        MILO_ASSERT(idx < mTableSize, 0x99);
        return mTable[idx];
    }
    
    char* mHeap;
    char* mHeapEnd;
    char* mFree;
    char** mTable;
    int mTableSize;
};

class FileEntry {
public:
    u64 mOffset;
    int mHashedName;
    int mHashedPath;
    int mSize;
    int mUCSize;
};

BinStream& operator>>(BinStream&, FileEntry&);

const int preinitArk = 1;

enum Mode {
    kRead = 0,
    kWrite = 1,
};

class Archive {
    public:
    Archive(const char*, int);
    void GetFileInfo(const char*, int&, unsigned long long&, int&, int&);
    void Read(int);
    void Enumerate(const char*, void (*)(const char*, const char*), bool, const char*);
    const char* GetArkfileName(int) const;
    void GetGuid(HxGuid&) const;
    bool DebugArkOrder();
    bool HasArchivePermission(int) const;
    void SetArchivePermission(int, const int*);
    int GetArkfileCachePriority(int) const;
    int GetArkfileNumBlocks(int) const;

    int mNumArkfiles;
    std::vector<uint> mArkfileSizes;
    std::vector<String> mArkfileNames;
    std::vector<int> mArkfileCachePriority;
    std::vector<FileEntry> mFileEntries;
    ArkHash mHashTable;
    String mBasename;
    Mode mMode;
    uint mMaxArkfileSize;
    bool mIsPatched;
    HxGuid mGuid;
    const int* unk60;
    int unk64;

};

Archive* TheArchive;

#endif // OS_ARCHIVE_H