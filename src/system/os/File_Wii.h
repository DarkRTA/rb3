#ifndef OS_FILEWII_H
#define OS_FILEWII_H

struct FileStat {
    unsigned int st_mode;
    unsigned int st_size;
    unsigned long st_ctime;
    unsigned long st_atime;
    unsigned long st_mtime;
};

bool FileIsLocal(const char*);
bool FileIsDLC(const char*);
extern "C" int FileGetStat(const char* iFilename, FileStat* iBuffer);
extern "C" int FileDelete();
extern "C" int FileMkDir();
extern "C" void FileEnumerate(const char*, void(*)(const char*, const char*), bool, const char*, bool);
void FileQualifiedFilename(char*, int, const char*);

#endif
