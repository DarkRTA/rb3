#include "string.hpp"
#include "textstream.hpp"
#include "filestream.hpp"
#include "binstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "file.hpp"

extern File *NewFile(const char *, int);

// fn_8034C9F8
// ctor
FileStream::FileStream(const char *c, FileType ft, bool b)
    : BinStream(b), unk20(0), unk24(0) {
    int fsize;
    if (ft == 0) {
        fsize = 2;
    } else if (ft == 2) {
        fsize = 0x10002;
    } else {
        fsize = 0xA04;
        if (ft == 3) {
            fsize = 0x304;
        }
    }
    fname = c;
    file = NewFile(c, fsize);
    failed = (file == 0);
}

// fn_8034CAB8
// ctor
FileStream::FileStream(File *f, bool b) : BinStream(b) {
    unk20 = 0;
    unk24 = 0;
    file = f;
    failed = false;
}

// fn_8034CB20
// dtor
FileStream::~FileStream() {
    if (!fname.empty()) {
        delete file;
    }
    DeleteChecksum();
    // fn_800E1114
}

// fn_8034CCA8
void FileStream::Flush() {
    file->Flush();
}

// fn_8034CD30
int FileStream::Tell() {
    return file->Tell();
}

// fn_8034CD44
bool FileStream::Eof() {
    return (file->Eof() != false);
}

// fn_8034CD7C
bool FileStream::Fail() {
    return failed;
}

void FileStream::ReadImpl(void *v, int i){
    if(file->Read(v, i) != i){
        failed = true;
    }
}

// fn_8034CC50
void FileStream::WriteImpl(const void *v, int i) {
    if(file->Write(v, i) != i){
        failed = true;
    }
}

// fn_8034CCBC
void FileStream::SeekImpl(int i, SeekType s) {

}