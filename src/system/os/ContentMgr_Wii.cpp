#include "os/ContentMgr_Wii.h"
#include "decomp.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "revolution/cnt/cnt.h"
#include "revolution/ec/ec.h"
#include "revolution/mem/mem_allocator.h"
#include <revolution/CNT.h>

MEMAllocator gCNTAllocator;

void (*CNTSDInitRSO)(void *workBuffer, int workBufferSize);
bool (*CNTSDIsInsertedRSO)(void);
void (*CNTSDListFirstRSO)(void);
void (*CNTSDListNextRSO)(void);
void (*CNTSDRestoreGetBlocksRSO)(void);
void (*CNTSDInitThreadRSO)(void);
void (*CNTSDSetThreadRestoreRSO)(void);
void (*CNTSDStartThreadRSO)(void);
void (*CNTSDCardGetAvailableBlocksRSO)(void);
void (*CNTSDGetBackupBlocksFromCntRSO)(void);
void (*CNTSDBackupRSO)(void);
void (*CNTSDSetThreadBackupRSO)(void);
void (*CNTSDFinishThreadRSO)(void);
void (*CNTSDFinishRSO)(void);
int (*CNTSDDeleteBackupRSO)(unsigned long long titleId, unsigned short contentId);
void (*CNTSDNANDCheckRSO)(void);
void (*CNTSDGetAvailableAreaRSO)(void);
void (*CNTSDGetTmpDirUsageRSO)(void);
void (*CNTSDGetUserAvailableAreaRSO)(void);
void (*CNTSDCacheClearRSO)(void);
void (*CNTSDCacheInUseRSO)(void);
void (*CNTSDCachePushDeleteContentVRSO)(void);
void (*CNTSDCachePopRSO)(void);
void (*FAMountRSO)(void);
void (*FAIsWriteProtectedRSO)(void);
void (*CNTSDSetEventCallbackRSO)(void *);

Timer gLastPlatformErrorTimer;

WiiContentMgr TheWiiContentMgr;

void *gCNTThreadStackBuffer;
void *gCNTThreadWorkBuffer;

CNTSDThreadInfo *gCNTThreadInfo;

DECOMP_FORCEACTIVE(ContentMgr_Wii, "_unresolved func.\n")

void unresolved_cntsdModule() {
    OSReport("\nError: call cntsdModule unlinked function.\n");
}

void CM_CNTSDCacheClearRSO() { CNTSDCacheClearRSO(); }

void SDCallback(int unk) {
    ThePlatformMgr.mStorageChanged = true;
    if (unk == 0) {
        WiiContent::mSDCardRemoved = true;
    }
}

void HandleErrorFromRestore(WiiContent *content, OpResult result) {}

int ConvertCNTSDError(int error) { return 0; }

void DoIndentPrint(int i) {
    while (i--) {
        MILO_LOG("\t");
    }
}

WiiContent::WiiContent(
    Symbol name,
    unsigned long long titleId,
    unsigned int contentId,
    bool inNand,
    bool needsMount
) {
    mName = name;
    mTitleId = titleId;
    mContentId = contentId;
    mLocation = inNand ? kLocationHDD : kLocationRemovableMem;
    unk20 = 3;
    unk24 = 0;
    unk31 = 0;
    unk32 = 0;
    mState = needsMount ? kNeedsMounting : kUnmounted;
    unk30 = 0;
    mHandle = nullptr;
}

WiiContent::~WiiContent() {
    int oldState = mState;
    // switch/case for mState
    if (oldState > 1 && oldState - 9U > 1) {
        if (oldState == kMounting || oldState == kMounted) {
            Unmount();
            while (mState == kMounting) {
                Timer::Sleep(2);
                Poll();
            }
        } else if (oldState != kAlwaysMounted) {
            MILO_LOG("Unknown state: %d", oldState);
        }
    }
}

Symbol WiiContent::FileName() { return mName; }

Symbol WiiContent::DisplayName() { return mName; }

const char *WiiContent::Root() { return mName.Str(); }

ContentLocT WiiContent::Location() { return mLocation; }

int WiiContent::OnMemcard() { return true; }

void WiiContent::Mount() {
    if (mState == kUnmounted) {
        mState = kNeedsMounting;
        return;
    } else if (mState != kMounting) {
        return;
    } else if (unk31) {
        unk32 = true;
    }
}

void WiiContent::Backup() {
    int oldState = mState;
    if (oldState == kMounted || (oldState > kUnmounted && oldState < kUnmounting)) {
        Unmount();
        while (mState == kMounting) {
            Timer::Sleep(2);
            Poll();
        }
        if (mState == kUnmounted && oldState == kMounted) {
            TheWiiContentMgr.NotifyUnmounted(this);
        }
    }
    mState = kNeedsBackup;
}

void WiiContent::StartMount() {
    mState = kMounting;
    unk31 = false;
    unk32 = false;
    unk24 = 0;
    if (mLocation == kLocationRemovableMem) {
        unk20 = 0;
        unk28 = 1;
        ThreadCall(this);
    } else {
        unk20 = 2;
    }
}

void WiiContent::StartBackup() {
    if (ThePlatformMgr.IsShuttingDown()) {
        MILO_LOG("WiiContent: skipping backup because we are shutting down.\n");
        return;
    }
    mState = kBackingUp;
    unk31 = false;
    unk24 = 0;
    unk20 = 0;
    ThreadStart();
    ThreadDone(1);
}

CNTHandle *WiiContent::GetHandle(long *result) {
    unk30++;
    if (mHandle != nullptr) {
        *result = 0;
        return mHandle;
    }
    mHandle = new CNTHandle;
    *result = 0;
    *result =
        (s32)contentInitHandleTitleNAND(mTitleId, mContentId, mHandle, &gCNTAllocator);
    if (*result) {
        MILO_FAIL("CM: %s: CNTInitHandleTitle Failed: %i\n", mName.Str(), (long)*result);
        delete mHandle;
        mHandle = nullptr;
        unk30 = 0;
    }
    return mHandle;
}

int WiiContent::FreeHandle() {
    unk30--;
    int r = 0;
    if (unk30 < 1) {
        unk30 = 0;
        if (mHandle != NULL) {
            r = CNTReleaseHandle(mHandle);
            delete mHandle;
            mHandle = NULL;
        }
    }
    return r;
}

void WiiContent::Delete() {
    int r = 0;
    int oldState = mState;
    if (oldState == kMounted || (oldState > kUnmounted && oldState < kUnmounting)) {
        Unmount();
        while (mState == kMounting) {
            Timer::Sleep(2);
            Poll();
        }
        if (mState == kUnmounted && oldState == kMounted) {
            TheWiiContentMgr.NotifyUnmounted(this);
        }
    }
    if (mState == kUnmounted || oldState == kFailed) {
        if (mLocation == kLocationHDD) {
            unsigned short contentIds[1] = { mContentId };
            int ecR = EC_DeleteContents(mTitleId, contentIds, 1);
            if (ecR == 0) {
                mState = kDeleted;
                r = 0;
            } else {
                mState = kFailed;
                r = 1;
            }
        } else if (mLocation == kLocationRemovableMem) {
            int cntsdR = CNTSDDeleteBackupRSO(mTitleId, mContentId);
            if (cntsdR == 0) {
                mState = kDeleted;
                r = 0;
            } else {
                r = ConvertCNTSDError(cntsdR);
                mState = kFailed;
            }
        }
    } else {
        mState = kFailed;
        r = 1;
    }
    if (mState == kDeleted) {
        // some write
    } else {
        TheWiiContentMgr.NotifyFailed(this);
    }
    // some other write
}

void WiiContent::PollTransfer() {
    MILO_ASSERT(unk20 == 1, 1119);
    if (unk20 == 1) {
    }
}

void WiiContent::Poll() {
    int oldState = mState;
    if (oldState == kNeedsMounting) {
        StartMount();
    } else if (oldState == kMounting) {
        if (unk20 == 1) {
            PollTransfer();
        }
        int oldTransferState = unk20;
        if (oldTransferState != 0) {
            if (oldTransferState == 1) {
                ThePlatformMgr.mHomeMenuDisabled = true;
                if (ThePlatformMgr.mHomeMenuWii->mSDIconActive == false) {
                    ThePlatformMgr.mHomeMenuWii->ActivateSDIcon(true);
                }
            } else if (oldTransferState == 2) {
                if (unk31 == false) {
                    if (unk24 == 0) {
                        s32 result;
                        GetHandle(&result);
                        if (result == 0) {
                            // CNTHandle::DebugPrintContents(handle);
                            mState = kMounted;
                        } else {
                            MILO_FAIL(
                                "CM: %s: CNTInitHandleTitle Failed: %i\n",
                                mName.Str(),
                                result
                            );
                            unk24 = 1;
                            mState = kFailed;
                        }
                        FreeHandle();
                    } else {
                        if (mHandleRestoreErrors == true) {
                            HandleErrorFromRestore(this, (OpResult)unk24);
                        }
                        mState = kFailed;
                    }
                } else if (unk32 == false) {
                    mState = kUnmounted;
                } else {
                    StartMount();
                }
            } else {
                MILO_ASSERT("0", 636);
                unk24 = 1;
                mState = kFailed;
            }
        }
        if (mState != kMounting) {
            unk20 = 3;
            unk31 = false;
            unk32 = false;
            ThePlatformMgr.mHomeMenuDisabled = false;
        }
    } else if (oldState == kNeedsBackup) {
        StartBackup();
    } else if (oldState == kBackingUp) {
    }
}

extern "C" void *WiiCntAlloc(MEMAllocator *, u32 size) { return _MemAlloc(size, 0x20); }

extern "C" void WiiCntFree(MEMAllocator *, void *block) { _MemFree(block); }

extern "C" void InitAllocator(MEMAllocator *allocator) {
    static MEMAllocatorFuncs cntAllocFunc = { WiiCntAlloc, WiiCntFree };
    allocator->funcs = &cntAllocFunc;
}

void *ecAlloc(unsigned long size, unsigned long align) {
    void *r = NULL;
    if (size != 0)
        r = _MemAlloc(size, align);
    return r;
}
ECNameValue ecAllocFunc = { "alloc", ecAlloc };

int ecFree(void *block) {
    if (block != NULL)
        _MemFree(block);
    return 0;
}
ECNameValue ecFreeFunc = { "free", ecFree };

WiiContentMgr::WiiContentMgr() {
    //
}

void WiiContentMgr::PreInit() {}

void WiiContentMgr::Init() {
    gLastPlatformErrorTimer.Restart();
    CNTInit();
    InitAllocator(&gCNTAllocator);

    mMode = 1; // kNANDMode

    ContentMgr::Init();
    ThePlatformMgr.AddSink(this);

    ECNameValue ec_alloc_funcs[2];
    ec_alloc_funcs[0] = ecAllocFunc;
    ec_alloc_funcs[1] = ecFreeFunc;
    int ec_r = EC_Init(ec_alloc_funcs, 2);
    if (ec_r == -4080) {
        mNeedShopAccount = true;
    } else {
        mNeedShopAccount = false;
    }

    mSDBuffer = _MemAlloc(0x5680, 0x20);
    CNTSDInitRSO(mSDBuffer, 0x5680);
    mCNTSDInited = true;

    CNTSDSetEventCallbackRSO(SDCallback);

    gCNTThreadStackBuffer = _MemAlloc(0x8000, 0x20);
    gCNTThreadWorkBuffer = _MemAlloc(0x2BC40, 0x20);
    gCNTThreadInfo = new CNTSDThreadInfo;

    CM_CNTSDCacheClearRSO();
}

void WiiContentMgr::Terminate() {
    CNTSDFinishRSO();
    MILO_LOG("CM: Unmounting Content\n");
    TheWiiContentMgr.UnmountContents("");
    MILO_LOG("CM: Clearing the Cache\n");
    CM_CNTSDCacheClearRSO();
    if (mSDBuffer != NULL) {
        _MemFree(mSDBuffer);
        mSDBuffer = NULL;
    }
    CNTShutdown();
    if (gCNTThreadStackBuffer != NULL) {
        _MemFree(gCNTThreadStackBuffer);
        gCNTThreadStackBuffer = NULL;
    }
    if (gCNTThreadWorkBuffer != NULL) {
        _MemFree(gCNTThreadWorkBuffer);
        gCNTThreadWorkBuffer = NULL;
    }
    delete gCNTThreadInfo;
    gCNTThreadInfo = NULL;
}

void WiiContent::Enumerate(
    const char *cc, void (*func)(const char *, const char *), bool, const char *cc2
) {
    if (mState != kMounted) {
        MILO_LOG("CM: Enumerate: %s not mounted\n", cc);
        return;
    }
    s32 result;
    CNTHandle *handle = GetHandle(&result);
    if (handle == NULL) {
        MILO_LOG("CM: Enumerate: could not get handle for %s\n", cc);
        return;
    }
    CNTDir directory;
    if (CNTOpenDir((CNTHandle *)handle, cc, &directory) == false) {
        MILO_LOG("CM: Enumerate: could not open dir %s\n", cc);
        return;
    }
}

void WiiContent::SetPassiveErrorsEnabled(bool enabled) { mHandleRestoreErrors = enabled; }

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
