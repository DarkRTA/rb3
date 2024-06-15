#ifndef OS_HOLMESCLIENT_H
#define OS_HOLMESCLIENT_H

#include "os/File.h"
#include "os/File_Wii.h"
#include "types.h"
#include "utl/Str.h"

void HolmesClientInit();
void HolmesClientReInit();
void HolmesClientTerminate();
void HolmesClientEnumerate(const char*, void (*)(const char*, const char*), bool, const char*, bool);
bool HolmesClientOpen(const char*, int, uint&, int&);
void HolmesClientRead(int, int, int, void*, File*);
bool HolmesClientReadDone(File*);
void HolmesClientWrite(int, int, int, const void*);
void HolmesClientClose(File*, int);
void HolmesClientTruncate(int, int);

FileStat* HolmesClientGetStat(const char*, FileStat&);

bool UsingHolmes(int);

char* HolmesFileShare();

unsigned int HolmesResolveIP();

#endif
