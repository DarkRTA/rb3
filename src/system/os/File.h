#ifndef OS_FILE_H
#define OS_FILE_H
#include "utl/Str.h"
#include <revolution/DVD.h>

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
    virtual void GetFileHandle(DVDFileInfo*&) = 0;
    virtual int Truncate(int){ return 0; }

    static int sOpenCount[4];
};

const char* FileRoot();
const char* FileExecRoot();
const char* FileSystemRoot();

extern "C" void FileNormalizePath();
extern "C" const char* FileMakePath(const char* root, const char* file);
extern "C" const char* FileRelativePath(const char* root, const char* filepath);
extern "C" const char* FileGetPath(const char*, char*);
extern "C" const char* FileGetExt(const char* root);
extern "C" const char* FileGetDrive(const char* file);
extern "C" const char* FileGetBase(const char* file, char* base);
extern "C" const char* FileGetName(const char* file);
extern "C" int FileOpen(const char* iFilename, int iMode);
extern "C" int FileClose(int iFd);
extern "C" int FileWrite(int iFd, void* iBuff, unsigned int iLen);
const char* FileLocalize(const char* iFilename, char* buffer);
extern "C" bool FileMatch();

#endif
