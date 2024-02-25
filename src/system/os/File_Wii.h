#ifndef OS_FILEWII_H
#define OS_FILEWII_H

bool FileIsLocal(const char*);
bool FileIsDLC(const char*);
extern "C" int FileDelete();
extern "C" int FileMkDir();

#endif
