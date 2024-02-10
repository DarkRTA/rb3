#ifndef OS_ARKFILE_H
#define OS_ARKFILE_H
#include <types.h>
#include "File.h"

class ArkFile : public File {
public:
    ArkFile(const char *, int);
    virtual ~ArkFile(); // fn_802E73FC
    virtual String Filename(){ return mFilename; } // fn_802E7810 // weak
    virtual int Read(void *, int); // fn_802E748C
    virtual bool ReadAsync(void *, int); // fn_802E7500
    virtual int V_Unk5(void *, int); // links to fn_802E76D8, which returns 0
    virtual bool Write(const void *, int); // links to fn_8077BAA0, which returns 0
    virtual unsigned int Seek(int, int); // fn_802E76E0
    virtual int Tell(); // fn_802E7728
    virtual void Flush(){} // fn_8076F540 - returns void // weak
    virtual bool Eof(); // fn_802E7730

    virtual bool Fail(); // fn_802E7748
    virtual unsigned int Size(); // fn_802E7758
    virtual unsigned int UncompressedSize(); // fn_802E7760
    virtual int ReadDone(int &); // fn_802E7790

    virtual int V_Unk16(int *); // fn_802E77E4

    virtual void _Open() = 0;

    void TaskDone(int);

    int mArkfileNum;
    unsigned long long mByteStart;
    int mSize; // 0x10
    int mUCSize; // 0x14
    s32 mNumOutstandingTasks;
    s32 mBytesRead;
    s32 mTell;
    s32 mFail;
    f32 mReadStartTime;
    s8 mReadAhead;
    String mFilename;
};
#endif
