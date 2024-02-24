#ifndef OS_FILE_H
#define OS_FILE_H
#include "utl/Str.h"

class File {
public:
    File(){ sOpenCount[0]++; }
    virtual ~File(){ sOpenCount[0]--; }
    virtual String Filename() const { return String(); }
    virtual int Read(void *, int) = 0;
    virtual bool ReadAsync(void *, int) = 0;
    virtual bool Write(const void *, int);
    virtual bool WriteAsync(const void*, int){ return false; }
    virtual int Seek(int, int) = 0;
    virtual int Tell() = 0;
    virtual void Flush() = 0;
    virtual bool Eof() = 0;
    virtual bool Fail() = 0;
    virtual int Size() = 0;
    virtual int UncompressedSize() = 0;
    virtual bool ReadDone(int &) = 0;
    virtual bool WriteDone(int & i){ 
        i = 0; 
        return true;
    }
    virtual void GetFileHandle(int*&) = 0; // this int should actually be a DVDFileInfo* &
    virtual int Truncate(int){ return 0; }

    static int sOpenCount[4];
};

#endif
