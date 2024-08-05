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

struct FileStat {
    unsigned int st_mode;
    unsigned int st_size;
    unsigned long st_ctime;
    unsigned long st_atime;
    unsigned long st_mtime;
};

extern "C" {

    void FileInit();
    void FileTerminate();

    const char* FileMakePath(const char* root, const char* file, char*);
    const char* FileRelativePath(const char* root, const char* filepath);

    const char* FileGetPath(const char*, char*);
    const char* FileGetExt(const char* root);
    const char* FileGetDrive(const char* file);
    const char* FileGetBase(const char* file, char* base);
    const char* FileGetName(const char* file);
    int FileGetStat(const char* iFilename, FileStat* iBuffer);

    int FileOpen(const char* iFilename, int iMode);
    int FileClose(int iFd);
    int FileDelete(const char*);
    int FileWrite(int iFd, void* iBuff, unsigned int iLen);
    int FileMkDir();

    bool FileMatch(const char*, const char*);
    void FileEnumerate(const char*, void(*)(const char*, const char*), bool, const char*, bool);
    void FileRecursePattern(const char*, void (*)(char const *,char const *), bool);

}

File* NewFile(const char*, int);

const char* FileRoot();
const char* FileExecRoot();
const char* FileSystemRoot();

void FileNormalizePath(const char*);
void FileQualifiedFilename(String&, const char*);
void FileQualifiedFilename(char*, int, const char*);
const char* FileLocalize(const char* iFilename, char* buffer);

bool FileReadOnly(const char* filepath);
bool FileExists(const char* filepath, int);
bool FileIsLocal(const char*);
bool FileIsDLC(const char*);

#endif
