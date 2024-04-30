#ifndef OS_FILE_H
#define OS_FILE_H
#include "utl/Str.h"
#include <revolution/DVD.h>

#define FILE_OPEN_NOARK 0x10000

class File {
public:
    File(){ sOpenCount[0]++; }
    virtual ~File(){ sOpenCount[0]--; }
    virtual class String Filename() const { class String str; return str; }
    virtual int Read(void *, int) = 0;
    virtual bool ReadAsync(void *, int) = 0;
    virtual int Write(const void *, int) = 0;
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
    virtual int GetFileHandle(DVDFileInfo*&) = 0;
    virtual int Truncate(int){ return 0; }

    static int sOpenCount[4];
};

class NullFile : public File {
public:
    NullFile(){}
    virtual ~NullFile(){}
    virtual int Read(void* v, int i){
        memset(v, 0, i);
        return i;
    }
    virtual bool ReadAsync(void* v, int i){
        Read(v, i);
        return true;
    }
    virtual int Write(const void* v, int i){ return i; }
    virtual int Seek(int, int){ return 0; }
    virtual int Tell(){ return 0; }
    virtual void Flush(){}
    virtual bool Eof(){ return true; }
    virtual bool Fail(){ return false; }
    virtual int Size(){ return 0; }
    virtual int UncompressedSize(){ return 0; }
    virtual bool ReadDone(int& i){
        i = 0;
        return true;
    }
    virtual int GetFileHandle(DVDFileInfo*&){ return 0; }
};

File* NewFile(const char*, int);

extern "C" void FileInit();
extern "C" void FileTerminate();

const char* FileRoot();
const char* FileExecRoot();
const char* FileSystemRoot();

extern "C" void FileNormalizePath();
extern "C" const char* FileMakePath(const char* root, const char* file, char*);
extern "C" const char* FileRelativePath(const char* root, const char* filepath);
bool FileReadOnly(const char* filepath);
bool FileExists(const char* filepath, int);
extern "C" const char* FileGetPath(const char*, char*);
extern "C" const char* FileGetExt(const char* root);
extern "C" const char* FileGetDrive(const char* file);
extern "C" const char* FileGetBase(const char* file, char* base);
extern "C" const char* FileGetName(const char* file);
extern "C" int FileOpen(const char* iFilename, int iMode);
extern "C" int FileClose(int iFd);
extern "C" int FileWrite(int iFd, void* iBuff, unsigned int iLen);
const char* FileLocalize(const char* iFilename, char* buffer);
extern "C" bool FileMatch(const char*, const char*);
extern "C" void FileRecursePattern(const char*, void (*)(char const *,char const *), bool);
void RecursePatternInternal(const char*, void (*)(const char*, const char*), bool, bool);

#endif
