#include "utl/FileStream.h"
#include "os/File.h"
#include "os/Debug.h"

FileStream::FileStream(const char *file, FileType type, bool lilEndian)
    : BinStream(lilEndian), mChecksumValidator(0), mBytesChecksummed(0) {
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

FileStream::FileStream(File* f, bool b) : BinStream(b), mFilename(), mChecksumValidator(0), mBytesChecksummed(0) {
    mFile = f;
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
    else if(mChecksumValidator){
        mChecksumValidator->Update((const unsigned char*)data, bytes);
        mBytesChecksummed += bytes;
    }
}

void FileStream::WriteImpl(const void* data, int bytes){
    if(mFile->Write((char*)data, bytes) != bytes) mFail = true;
}

void FileStream::Flush(){
    MILO_ASSERT(!mFail, 0x4C);
    mFile->Flush();
}

void FileStream::SeekImpl(int offset, SeekType t){
    int d[3] = { 0, 1, 2 };
    MILO_ASSERT(!mFail, 0x55);
    int res = mFile->Seek(offset, d[t]);
    if(res < 0) mFail = true;
}

int FileStream::Tell(){
    MILO_ASSERT(!mFail, 0x5D);
    return mFile->Tell();
}

EofType FileStream::Eof(){
    MILO_ASSERT(!mFail, 0x64);
    return (EofType)(mFile->Eof() != false);
}

bool FileStream::Fail(){
    return mFail;
}

void FileStream::DeleteChecksum(){
    delete mChecksumValidator;
    mChecksumValidator = 0;
    mBytesChecksummed = 0;
}

void FileStream::StartChecksum(){
    DeleteChecksum();
    mChecksumValidator = new StreamChecksumValidator();
    if(!mChecksumValidator->Begin(Name(), false)) DeleteChecksum();
}

const char* FileStream::Name() const {
    return mFilename.c_str();
}

bool FileStream::ValidateChecksum(){
    if(!mChecksumValidator) return false;
    else {
        mChecksumValidator->End();
        MILO_ASSERT(mBytesChecksummed == Size(), 0x85);
        bool ret = false;
        if(mBytesChecksummed == Size() && mChecksumValidator->Validate()){
            ret = true;
        }
        return ret;
    }
}
