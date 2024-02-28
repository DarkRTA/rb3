#include "os/ArkFile.h"
#include "os/Debug.h"

int ArkFile::Read(void *c, int a) {
    if(ReadAsync(c, a) == 0) return 0;
    int ret = -1;
    while(ReadDone(ret) == 0);
    return ret;
}

bool ArkFile::Write(const void*, int){
    TheDebug.Fail(MakeString("ERROR: Cannot write to a file in an archive!"));
    return false;
}

int ArkFile::Seek(int offset, int mode) {
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

int ArkFile::Tell(){
    return mTell;
}

bool ArkFile::Eof() {
    return (mSize - mTell) == 0;
}

bool ArkFile::Fail() {
    return (mFail != 0);
}

int ArkFile::Size(){
    return mSize;
}

int ArkFile::UncompressedSize(){
    return mUCSize;
}

void ArkFile::TaskDone(int a) {
    mNumOutstandingTasks--;
    mBytesRead += a;
    mTell += a;
}
