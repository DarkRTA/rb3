#include "Rso_Utl.h"
#include "decomp.h"
#include "os/Debug.h"
#include "revolution/os/OSError.h"
#include <cstddef>

#define MAX_RSO_INITERS 8
#define kRSOBufferSize 0x10EC00
#define kDefaultRSOBufferSize 0x89460

RsoInitFunc gRsoIniters[MAX_RSO_INITERS];
RsoDeinitFunc gRsoDeiniters[MAX_RSO_INITERS];
int gRsoIniterCount;

extern void *g_pRSOReserveBuf;
uint g_RSOBufOffset = 0;

extern void *g_pDefaultRSOBuf;
uint g_DefaultRSOBufOffset = 0;

DECOMP_FORCEACTIVE(Rso_Utl, "_unresolved func.\n")

void *RsoMemAlloc2Fake(int size) {
    size = size + 31 & ~31;
    MILO_ASSERT(size >= 0, 44);
    if (u32(g_pRSOReserveBuf) + g_RSOBufOffset + size >= 0x91000000) {
        OSReport(
            "ERROR: RSOs in MEM2 need to stay below the 16MB boundary.  The game is about to crash.\n"
        );
        return 0;
    }
    g_RSOBufOffset += size;
    MILO_ASSERT(g_RSOBufOffset <= kRSOBufferSize, 53);
    if (g_pRSOReserveBuf != NULL) {
        return (void *)(u32(g_pRSOReserveBuf) + g_RSOBufOffset - size);
    } else
        return NULL;
}

void *DefaultRSOMemAlloc2(int size) {
    size = size + 31 & ~31;
    MILO_ASSERT(size >= 0, 66);
    if (u32(g_pDefaultRSOBuf) + g_DefaultRSOBufOffset + size >= 0x91000000) {
        OSReport(
            "ERROR: RSOs in MEM2 need to stay below the 16MB boundary.  The game is about to crash.\n"
        );
        return 0;
    }
    g_DefaultRSOBufOffset += size;
    MILO_ASSERT(g_DefaultRSOBufOffset <= kDefaultRSOBufferSize, 75);
    if (g_pDefaultRSOBuf != NULL) {
        return (void *)(u32(g_pDefaultRSOBuf) + g_DefaultRSOBufOffset - size);
    } else
        return NULL;
}

void RsoAddIniter(RsoInitFunc init, RsoDeinitFunc deinit) {
    MILO_ASSERT(gRsoIniterCount < MAX_RSO_INITERS, 84);
    if (gRsoIniterCount < 8) {
        gRsoIniters[gRsoIniterCount] = init;
        gRsoDeiniters[gRsoIniterCount] = deinit;
        gRsoIniterCount++;
    }
}

DECOMP_FORCEACTIVE(Rso_Utl, "fast", "main")

void *LoadRsoFile(const char *filename, unsigned int &size, void *(*alloc)(int)) {
    File *rso = NewFile(filename, 0x10002);
    if (rso == NULL) {
        char buf[0x100];
        strncpy(buf, "../../system/run/", 0x100);
        strncat(buf, filename, 0x100);
        rso = NewFile(buf, 0x10002);
        if (rso == NULL) {
            MILO_FAIL("RSO: Couldn\'t load %s", filename);
            return NULL;
        }
    }
    int fsiz = rso->Size();
    void *ret = alloc(fsiz + 31 & ~31);
    if (ret == NULL)
        return NULL;
    size = rso->Read(ret, fsiz);
    delete rso;
    return ret;
}

void *RsoLoad(const char *filename, unsigned char **, void *(*alloc)(int)) {
    uint size;
    void *rso = LoadRsoFile(filename, size, alloc);
    if (rso == NULL) {
        return NULL;
    }
}
