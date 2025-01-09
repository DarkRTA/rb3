#ifndef RVL_SDK_FS_H
#define RVL_SDK_FS_H
#include "private/iostypes.h"
#include "revolution/IPC.h"
#include "private/iosrestypes.h"
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

#define FS_MAX_PATH 64

#define ISFS_ERROR_OK               0
#define ISFS_ERROR_INVALID          -101
#define ISFS_ERROR_ACCESS           -102
#define ISFS_ERROR_CORRUPT          -103
#define ISFS_ERROR_NOTREADY         -104
#define ISFS_ERROR_EXISTS           -105
#define ISFS_ERROR_NOEXISTS         -106
#define ISFS_ERROR_MAXFILES         -107
#define ISFS_ERROR_MAXBLOCKS        -108
#define ISFS_ERROR_MAXFD            -109
#define ISFS_ERROR_MAXDEPTH         -110
#define ISFS_ERROR_OPENFD           -111
#define ISFS_ERROR_BADBLOCK         -112
#define ISFS_ERROR_ECC              -113
#define ISFS_ERROR_ECC_CRIT         -114
#define ISFS_ERROR_NOTEMPTY         -115
#define ISFS_ERROR_HMAC             -116
#define ISFS_ERROR_UNKNOWN          -117
#define ISFS_ERROR_BUSY             -118
#define ISFS_ERROR_SHUTDOWN         -119


typedef s32 ISFSError;
typedef void (*ISFSCallback) (ISFSError, void *ctxt);

typedef struct {
    u32 blockSize;
    u32 freeBlocks;
    u32 occupiedBlcocks;
    u32 badBlocks;
    u32 reservedBlocks;
    u32 freeInodes;
    u32 occupedInodes;
} ISFSStats;

typedef struct {
    u32 size;
    u32 offset;
} ISFSFileStats;

typedef struct {
    IOSUid ownerId;
    IOSGid groupId;
    u8 path[FS_MAX_PATH];
    u8 ownerAccess;
    u8 groupAccess;
    u8 othersAccess;
    u8 attr;
} ISFSPathAttrArgs;

typedef struct {
    u8 path1[FS_MAX_PATH];
    u8 path2[FS_MAX_PATH];
} ISFSPathsArgs;

typedef void (*FSAsyncCallback)(s32, void*);

typedef struct FSStats {
    char UNK_0x0[0x1C];
} FSStats;

// Could be more fields, but not larger than 32B
typedef struct FSFileStats {
    u32 length;   // at 0x0
    u32 position; // at 0x4
} FSFileStats ALIGN(32);

typedef struct FSFileAttr {
    u32 ownerId; // at 0x0
    u16 groupId; // at 0x4
    u8 attr;     // at 0x6
    u8 perm;     // at 0x7
} FSFileAttr;

s32 ISFS_OpenLib(void);
s32 ISFS_CreateDir(const char* path, u32 attr, u32 ownerPerm, u32 groupPerm,
                   u32 otherPerm);
s32 ISFS_CreateDirAsync(const char* path, u32 attr, u32 ownerPerm,
                        u32 groupPerm, u32 otherPerm, FSAsyncCallback callback,
                        void* callbackArg);
s32 ISFS_ReadDir(const char* path, char* filesOut, u32* fileCountOut);
s32 ISFS_ReadDirAsync(const char* path, char* filesOut, u32* fileCountOut,
                      FSAsyncCallback callback, void* callbackArg);
s32 ISFS_GetAttr(const char* path, u32* ownerIdOut, u16* groupIdOut,
                 u32* attrOut, u32* ownerPermOut, u32* groupPermOut,
                 u32* otherPermOut);
s32 ISFS_GetAttrAsync(const char* path, u32* ownerIdOut, u16* groupIdOut,
                      u32* attrOut, u32* ownerPermOut, u32* groupPermOut,
                      u32* otherPermOut, FSAsyncCallback callback,
                      void* callbackArg);
s32 ISFS_Delete(const char* path);
s32 ISFS_DeleteAsync(const char* path, FSAsyncCallback callback,
                     void* callbackArg);
s32 ISFS_Rename(const char* from, const char* to);
s32 ISFS_RenameAsync(const char* from, const char* to, FSAsyncCallback callback,
                     void* callbackArg);
s32 ISFS_GetUsage(const char* path, s32* blockCountOut, s32* fileCountOut);
s32 ISFS_CreateFile(const char* path, u32 attr, u32 ownerPerm, u32 groupPerm,
                    u32 otherPerm);
s32 ISFS_CreateFileAsync(const char* path, u32 attr, u32 ownerPerm,
                         u32 groupPerm, u32 otherPerm, FSAsyncCallback callback,
                         void* callbackArg);
s32 ISFS_Open(const char* path, IPCOpenMode mode);
s32 ISFS_OpenAsync(const char* path, IPCOpenMode mode, FSAsyncCallback callback,
                   void* callbackArg);
s32 ISFS_GetFileStats(IOSFd fd, ISFSFileStats* statsOut);
s32 ISFS_GetFileStatsAsync(IOSFd fd, ISFSFileStats* statsOut,
                           FSAsyncCallback callback, void* callbackArg);
s32 ISFS_Seek(IOSFd fd, s32 offset, IPCSeekMode mode);
s32 ISFS_SeekAsync(IOSFd fd, s32 offset, IPCSeekMode mode,
                   FSAsyncCallback callback, void* callbackArg);
s32 ISFS_Read(IOSFd fd, void* dst, s32 len);
s32 ISFS_ReadAsync(IOSFd fd, void* dst, s32 len, FSAsyncCallback callback,
                   void* callbackArg);
s32 ISFS_Write(IOSFd fd, const void* src, s32 len);
s32 ISFS_WriteAsync(IOSFd fd, const void* src, s32 len, FSAsyncCallback callback,
                    void* callbackArg);
s32 ISFS_Close(IOSFd fd);
s32 ISFS_CloseAsync(IOSFd fd, FSAsyncCallback callback, void* callbackArg);
s32 ISFS_ShutdownAsync(FSAsyncCallback callback, void* callbackArg);



#ifdef __cplusplus
}
#endif
#endif
