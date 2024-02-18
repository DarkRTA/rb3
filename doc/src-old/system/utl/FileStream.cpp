#include "utl/FileStream.h"

extern File *NewFile(const char *, int);

// fn_8034C9F8
// ctor
FileStream::FileStream(const char *file, FileType type, bool lilEndian)
    : BinStream(lilEndian), mChecksum(0), mBytesChecksummed(0) {
    int fsize;
    if (type == kRead) {
        fsize = 2;
    } else if (type == kReadNoArk) {
        fsize = 0x10002;
    } else {
        fsize = 0xA04;
        if (type == kAppend) {
            fsize = 0x304;
        }
    }
    mFilename = file;
    mFile = NewFile(file, fsize);
    mFail = (mFile == 0);
}

// fn_8034CAB8
// ctor
FileStream::FileStream(File* file, bool lilEndian) : BinStream(lilEndian) {
    mChecksum = 0;
    mBytesChecksummed = 0;
    mFile = file;
    mFail = false;
}

FileStream::~FileStream(){
    if(!mFilename.empty()){
        delete mFile;
    }
    DeleteChecksum();
}

void FileStream::ReadImpl(void* data, int bytes){
    if(mFile->Read(data, bytes) != bytes) mFail = true;
    else if(mChecksum != 0){
        mChecksum->Update((const unsigned char*)data, bytes);
        mBytesChecksummed += bytes;
    }
}

void FileStream::WriteImpl(const void* data, int bytes){
    if(mFile->V_Unk5((char*)data, bytes) != bytes) mFail = true;
}

void FileStream::Flush(){
    mFile->Flush();
}

void FileStream::SeekImpl(int offset, SeekType t){
    int d[3] = { 0, 1, 2 };
    int res = mFile->Seek(offset, d[t]);
    if(res < 0) mFail = true;
}

int FileStream::Tell(){
    return mFile->Tell();
}

bool FileStream::Eof(){
    return mFile->Eof() != false;
}

bool FileStream::Fail(){
    return mFail;
}

void FileStream::DeleteChecksum(){
    delete mChecksum;
    mChecksum = 0;
    mBytesChecksummed = 0;
}

void FileStream::StartChecksum(){
    DeleteChecksum();
    mChecksum = new StreamChecksum();
    if(!mChecksum->Begin(Name(), false)) DeleteChecksum();
}
