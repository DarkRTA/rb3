#ifndef RVL_SDK_DVD_FS_H
#define RVL_SDK_DVD_FS_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

//Forward declarations
typedef struct DVDFileInfo;

typedef struct DVDDir{
    u32 entryNum;
    u32 location;
    u32 next;
} DVDDir;

typedef struct DVDDirEntry{
    u32 entryNum;
    bool32 isDir;
    char* name;
} DVDDirEntry;

typedef void (*DVDCallback)(s32 result, struct DVDFileInfo* fileInfo);

typedef struct DVDFileInfo {
    DVDCommandBlock cb;
    u32 startAddr;
    u32 length;
    DVDCallback callback;
} DVDFileInfo;

extern bool32 __DVDLongFileNameFlag;

s32 DVDConvertPathToEntrynum(const char* pathPtr);
bool32 DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo);
bool32 DVDClose(DVDFileInfo* fileInfo);
bool32 DVDGetCurrentDir(char* path, u32 maxlen);
bool32 DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio);
s32 DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio);
u32 DVDGetTransferredSize(DVDCommandBlock* block);


#ifdef __cplusplus
}
#endif
#endif
