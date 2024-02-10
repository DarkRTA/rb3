#include "FileStream.h"

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

// // fn_8034CCA8
// void FileStream::Flush() {
//     file->Flush();
// }

// // fn_8034CD30
// int FileStream::Tell() {
//     return file->Tell();
// }

// // fn_8034CD44
// bool FileStream::Eof() {
//     return (file->Eof() != false);
// }

// // fn_8034CD7C
// bool FileStream::Fail() {
//     return failed;
// }

// void FileStream::ReadImpl(void *v, int i){
//     if(file->Read(v, i) != i){
//         failed = true;
//     }
// }

// // fn_8034CC50
// void FileStream::WriteImpl(const void *v, int i) {
//     if(file->Write(v, i) != i){
//         failed = true;
//     }
// }

// // fn_8034CCBC
// void FileStream::SeekImpl(int i, SeekType s) {

// }
