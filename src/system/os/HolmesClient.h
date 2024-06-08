#ifndef OS_HOLMESCLIENT_H
#define OS_HOLMESCLIENT_H

#include "os/File_Wii.h"
#include "utl/Str.h"

void HolmesClientInit();
void HolmesClientReInit();
void HolmesClientTerminate();
void HolmesClientEnumerate(const char*, void (*)(const char*, const char*), bool, const char*, bool);

FileStat* HolmesClientGetStat(const char*, FileStat&);

bool UsingHolmes(int);

char* HolmesFileShare();

unsigned int HolmesResolveIP();

#endif
