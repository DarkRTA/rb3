#ifndef OS_CDREADER_H
#define OS_CDREADER_H
#include <revolution/DVD.h>

bool CDReadDone();
int CDGetError();
int CDRead(int, int, int, void*);
int CDReadExternal(DVDFileInfo*&, int, unsigned long long);

#endif