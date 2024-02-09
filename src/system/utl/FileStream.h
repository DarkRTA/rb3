#ifndef UTL_FILESTREAM_H
#define UTL_FILESTREAM_H
#include "BinStream.h"
#include "Str.h"
#include "File.h"
#include "streamchecksum.hpp"

class FileStream : public BinStream {
public:
    enum FileType {
        FileType0,
        FileType1,
        FileType2,
        FileType3
    };

    FileStream(const char *, FileType, bool); // fn_8034C9F8
    FileStream(File *, bool); // RB2 says this is FileStream(File*, bool)
    virtual ~FileStream(); // fn_8034CB20
    virtual void Flush(); // fn_8034CCA8
    virtual int Tell(); // fn_8034CD30
    virtual bool Eof(); // fn_8034CD44
    virtual bool Fail(); // fn_8034CD7C
    virtual const char *Name() const; // fn_800C20FC
    virtual void ReadImpl(void *, int); // fn_8034CBCC
    virtual void WriteImpl(const void *, int); // fn_8034CC50
    virtual void SeekImpl(int, SeekType); // fn_8034CCBC

    void DeleteChecksum();
    void StartChecksum();

    File *file;
    String fname;
    bool failed;
    StreamChecksum *unk20;
    int unk24; // probably a ptr to another class
};

#endif

// enum FileType {
//     kRead = 0,
//     kWrite = 1,
//     kReadNoArk = 2,
//     kAppend = 3,
// };
// class FileStream : public BinStream {
//     // total size: 0x28
//     class File * mFile; // offset 0xC, size 0x4
//     class String mFilename; // offset 0x10, size 0xC
//     unsigned char mFail; // offset 0x1C, size 0x1
//     class StreamChecksum * mChecksum; // offset 0x20, size 0x4
//     int mBytesChecksummed; // offset 0x24, size 0x4
// };
