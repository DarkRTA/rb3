#include "os/ArkFile.h"

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
