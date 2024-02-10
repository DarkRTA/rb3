#include "File.h"
#include "file_ops.hpp"
#include "ArkFile.h"
#include "Archive.h"
#include "blockmgr.hpp"
#include "AsyncTask.h"

int File::sOpenCount[4];


// fn_802E73DC
File::File() {
    sOpenCount[0]++;
}

// fn_802E738C
File::~File() {
    sOpenCount[0]--;
}

// fn_802E7818
int File::V_Unk15(int *a) {
    *a = 0;
    return 1;
}

extern Archive *TheArchive;

// fn_802E72CC
ArkFile::ArkFile(const char *iFilename, int iMode)
    : mNumOutstandingTasks(0), mBytesRead(0), mTell(0), mFail(0), mReadAhead(1), mFilename(iFilename) {
    if (!TheArchive->GetFileInfo(
            FileMakePath(".", (char *)iFilename, nullptr), mArkfileNum, mByteStart, mSize, mUCSize
        )
        || (iMode & 4)) {
        mFail = 1;
    }
}

extern BlockMgr TheBlockMgr;

// fn_802E73FC
ArkFile::~ArkFile() {
    if (mNumOutstandingTasks > 0) {
        TheBlockMgr.KillBlockRequests(this);
    }
}

// fn_802E748C
int ArkFile::Read(void *c, int a) {
    if (ReadAsync(c, a) == 0)
        return 0;
    int ret = -1;
    while (ReadDone(ret) == 0)
        ;
    return ret;
}

// // fn_802E7500
// bool ArkFile::ReadAsync(void *c, int a) {
//     // this one's gross, i don't wanna do it
// }

// // Range: 0x805A16EC -> 0x805A191C
// unsigned char ArkFile::ReadAsync(class ArkFile * const this /* r29 */, void * iBuff /* r30 */, int iBytes /* r31 */) {
//     // Local variables
//     unsigned long long startByte; // r28
//     int startBlock; // r1+0x10
//     int numBlocks; // r1+0xC
//     int blockSize; // r1+0x8
//     int currBlock; // r26
//     int lastBlock; // r25
//     int startOffset; // r24
//     int endOffset; // r23
//     char * buff; // [invalid]
//     unsigned char tryFill; // r22
//     int endByte; // r4
//     class AsyncTask task; // r1+0x18

//     // References
//     // -> class BlockMgr TheBlockMgr;
//     // -> class Debug TheDebug;
//     // -> const char * kAssertStr;
// }

int ArkFile::V_Unk5(void *a, int b) {
    return 0;
}

unsigned int ArkFile::Seek(int offset, int mode) {
    switch (mode) {
    case 0:
        mTell = offset;
        break;
    case 1:
        mTell += offset;
        break;
    case 2:
        mTell = mSize + offset;
        break;
    default:
        break;
    }
    return mTell;
}

int ArkFile::Tell() {
    return mTell;
}

bool ArkFile::Eof() {
    return (mSize - mTell) == 0;
}

// fn_802E7748
bool ArkFile::Fail() {
    return (mFail != 0);
}

// fn_802E7758
unsigned int ArkFile::Size() {
    return mSize;
}

// fn_802E7760
unsigned int ArkFile::UncompressedSize() {
    return mUCSize;
}

// fn_802E7768
void ArkFile::TaskDone(int a) {
    mNumOutstandingTasks--;
    mBytesRead += a;
    mTell += a;
}

// fn_802E7790
int ArkFile::ReadDone(int &a) {
    TheBlockMgr.Poll();
    a = mBytesRead;
    return (mNumOutstandingTasks == 0);
}

// extern void fn_802EB6E4(int *, int, int, int);

// // fn_802E77E4
// int ArkFile::V_Unk16(int *a) {
//     // fn_802EB6E4(a, unk4, unkc + fpos, unkc + fpos);
// }
