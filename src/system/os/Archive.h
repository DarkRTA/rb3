#ifndef OS_ARCHIVE_H
#define OS_ARCHIVE_H

class Archive {
public:
    int unk0, unk4, unk8, unkc, unk10, unk14, unk18, unk1c, unk20, unk24;
    // ArkHash at 0x28
    // String at 0x3C
    // 0x48 is some word
    bool GetFileInfo(const char *, int &, unsigned long long &, int &, int &);
};

#endif

// class ArkHash {
//     // total size: 0x14
//     char * mHeap; // offset 0x0, size 0x4
//     char * mHeapEnd; // offset 0x4, size 0x4
//     char * mFree; // offset 0x8, size 0x4
//     char * * mTable; // offset 0xC, size 0x4
//     int mTableSize; // offset 0x10, size 0x4
// };
// enum Mode {
//     kRead = 0,
//     kWrite = 1,
// };
// class Archive {
//     // total size: 0x50
//     int mNumArkfiles; // offset 0x0, size 0x4
//     class vector mArkfileSizes; // offset 0x4, size 0xC
//     class vector mArkfileNames; // offset 0x10, size 0xC
//     class vector mFileEntries; // offset 0x1C, size 0xC
//     class ArkHash mHashTable; // offset 0x28, size 0x14
//     class String mBasename; // offset 0x3C, size 0xC
//     enum Mode mMode; // offset 0x48, size 0x4
//     unsigned int mMaxArkfileSize; // offset 0x4C, size 0x4
// };
