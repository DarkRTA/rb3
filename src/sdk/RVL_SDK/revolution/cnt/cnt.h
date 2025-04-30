#ifndef RVL_SDK_PPC_ARCH_H
#define RVL_SDK_PPC_ARCH_H

#include "revolution/ARC.h"
#include "revolution/DVD.h"
#include "revolution/mem/mem_allocator.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum CNTDirMode {
    ARC = 1,
    DVD = 2
};

typedef struct _CNTDir {
    union {
        ARCDir arc; // 0x0
        struct {
            u32 pad; // ???
            DVDDir dvd;
        };
    };
    u8 type; // 0x10
} CNTDir;

typedef struct _CNTDirEntry {
    union {
        ARCEntry arc;
        struct {
            u32 pad; // ???
            DVDDirEntry dvd;
        };
    };
    u8 type;
} CNTDirEntry;

typedef struct _CNTHandle {
    union {
        ARCHandle arc;
    };
    u8 type;
    u8 pad_to_0x28[3]; // stupid hack
} CNTHandle;

void CNTInit(void);

void CNTReleaseHandle(CNTHandle *);
CNTHandle *
contentInitHandleTitleNAND(u64 title_id, u32 content_id, void *r6, MEMAllocator *);
u32 contentConvertPathToEntrynumDVD(const char *path);

BOOL CNTOpenDir(CNTHandle *handle, const char *path, CNTDir *dir);
BOOL CNTReadDir(CNTDir *, CNTDirEntry *);
BOOL CNTCloseDir(CNTDir *);

#ifdef __cplusplus
}
#endif
#endif
