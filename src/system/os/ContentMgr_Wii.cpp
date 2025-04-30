#include "os/ContentMgr_Wii.h"
#include "decomp.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "revolution/cnt/cnt.h"
#include "revolution/mem/mem_allocator.h"
#include <revolution/CNT.h>

MEMAllocator gCNTAllocator;

void (*CNTSDFinishRSO)(void);
void (*CNTSDCacheClearRSO)(void);

Timer gLastPlatformErrorTimer;

WiiContentMgr TheWiiContentMgr;

DECOMP_FORCEACTIVE(ContentMgr_Wii, "_unresolved func.\n")

void unresolved_cntsdModule() {
    OSReport("\nError: call cntsdModule unlinked function.\n");
}

void CM_CNTSDCacheClearRSO() { CNTSDCacheClearRSO(); }

void DoIndentPrint(int i) {
    while (i--) {
        MILO_LOG("\t");
    }
}

WiiContent::WiiContent(
    Symbol s, unsigned long long ux, unsigned int ui, bool b1, bool b2
) {
    mName = s;
    mTitleId = ux;
    mContentId = ui;
    unk2c = b1;
    unk20 = 3;
    unk24 = 0;
    unk31 = 0;
    unk32 = 0;
    unk8 = b2;
    unk30 = 0;
    unk1c = 0;
}

WiiContent::~WiiContent() {
    int oldState = unk8;
    // switch/case for unk8
    if (oldState > 1 && oldState - 9U > 1) {
        if (oldState == 2 || oldState == 4) {
            Unmount();
            while (unk8 == 2) {
                Timer::Sleep(2);
                Poll();
            }
        } else if (oldState != 5) {
            MILO_LOG("Unknown state: %d", oldState);
        }
    }
}

void *WiiContent::GetHandle(long *handle) {
    unk30++;
    if (unk1c != nullptr) {
        *handle = 0;
        return unk1c;
    }
    unk1c = new CNTHandle;
    *handle = nullptr;
    *handle =
        (s32)contentInitHandleTitleNAND(mTitleId, mContentId, unk1c, &gCNTAllocator);
    if (*handle) {
        MILO_FAIL("CM: %s: CNTInitHandleTitle Failed: %i\n", mName.Str(), (long)*handle);
        delete unk1c;
        unk1c = nullptr;
        unk30 = 0;
    }
    return unk1c;
}

extern "C" void InitAllocator(MEMAllocator *) {}

WiiContentMgr::WiiContentMgr() {}

void WiiContentMgr::PreInit() {}

void WiiContentMgr::Init() {
    gLastPlatformErrorTimer.Restart();
    CNTInit();
    InitAllocator(&gCNTAllocator);
    ContentMgr::Init();
    ThePlatformMgr.AddSink(this);

    CM_CNTSDCacheClearRSO();
}

void WiiContentMgr::Terminate() {
    CNTSDFinishRSO();
    MILO_LOG("CM: Unmounting Content\n");
    TheWiiContentMgr.UnmountContents("");
    MILO_LOG("CM: Clearing the Cache\n");
    CM_CNTSDCacheClearRSO();
}

void WiiContent::Enumerate(
    const char *cc, void (*func)(const char *, const char *), bool, const char *cc2
) {
    if (unk8 != 4) {
        MILO_LOG("CM: Enumerate: %s not mounted\n", cc);
        return;
    }
    s32 handle;
    if (GetHandle(&handle) == 0) {
        MILO_LOG("CM: Enumerate: could not get handle for %s\n", cc);
        return;
    }
}

void WiiContentMgr::NotifyUnmounted(Content *c) {
    WiiContent *pc = dynamic_cast<WiiContent *>(c);
    MILO_ASSERT(pc, 2839);
    FOREACH (cb, mCallbacks) {
        (*cb)->ContentUnmounted(pc->FileName().Str());
    }
}

void WiiContentMgr::NotifyFailed(Content *c) {
    WiiContent *pc = dynamic_cast<WiiContent *>(c);
    MILO_ASSERT(pc, 2849);
    MILO_LOG("CM: Calling ContentFailed for %s\n", c->FileName());
    FOREACH (cb, mCallbacks) {
        (*cb)->ContentFailed(pc->FileName().Str());
    }
}
