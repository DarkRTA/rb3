#ifndef OS_ASYNCFILECNT_H
#define OS_ASYNCFILECNT_H
#include "os/AsyncFile.h"
#include "utl/Str.h"

class AsyncFileCNT : public AsyncFile {
public:
    AsyncFileCNT(const char *, int);
    virtual ~AsyncFileCNT();
    virtual int V_Unk16(int *); // fn_802E8774

    virtual void _Open(); // fn_802E8784
    virtual int V_Unk19(); // fn_802E88C0
    virtual int _Write(const void *, int); // fn_802E88C8
    virtual int V_Unk21(); // fn_802E88CC
    virtual void _SeekToTell(); // fn_802E88D4
    virtual void _ReadAsync(void *, int); // fn_802E892C
    virtual int _ReadDone(); // fn_802E89FC
    virtual void _Close(); // fn_802E8AA4

    unsigned int unk38;
    int unk3c;
    int unk40;
    int unk44; // probably a class
    char unk48;
    char unk49;
    char unk4a;
    int unk4c, unk50, unk54, unk58, unk5c, unk60, unk64, unk68, unk6c, unk70, unk74;
    int unk78;
};

#endif

// class AsyncFileCNT : public AsyncFile {
//     // total size: 0x23C0
// public:
//     void * mTempBufferCNT; // offset 0x3C, size 0x4
//     int mReadSizeCNT; // offset 0x40, size 0x4
//     int mReadResultCNT; // offset 0x44, size 0x4
// private:
//     unsigned char mReadInProgress; // offset 0x48, size 0x1
//     unsigned char mCNTReadThreadStack[8192]; // offset 0x60, size 0x2000
//     struct OSThread mCNTReadThread; // offset 0x2060, size 0x318
//     struct CNTFileInfo mCNTFileInfo; // offset 0x2378, size 0x44
// };
