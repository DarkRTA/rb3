/*
    Compile unit: C:\rockband2\system\src\os\ContentMgr_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805A7410 -> 0x805AC184
*/
long (* CNTSDInitRSO)(void *, long); // size: 0x4, address: 0x80A548B8
int (* CNTSDIsInsertedRSO)(); // size: 0x4, address: 0x80A548BC
long (* CNTSDListFirstRSO)(unsigned char (*)[1092], unsigned long long, unsigned long *); // size: 0x4, address: 0x80A548C0
long (* CNTSDListNextRSO)(unsigned char (*)[1092], unsigned long *); // size: 0x4, address: 0x80A548C4
long (* CNTSDRestoreGetBlocksRSO)(unsigned long long, unsigned long, unsigned char *, unsigned long, unsigned long *, unsigned long *); // size: 0x4, address: 0x80A548C8
enum CNTSDThreadStatus {
    CNTSD_THREAD_NOT_INITIALIZED = 0,
    CNTSD_THREAD_STACK_INITIALIZED = 1,
    CNTSD_THREAD_READY_TO_START = 2,
    CNTSD_THREAD_CREATED_RESUMED = 3,
    CNTSD_THREAD_DONE = 4,
};
struct CNTSDThreadInfo {
    // total size: 0x350
    struct OSThread thread; // offset 0x0, size 0x318
    enum CNTSDThreadStatus status; // offset 0x318, size 0x4
    void * stack; // offset 0x31C, size 0x4
    unsigned long stackSize; // offset 0x320, size 0x4
    long priority; // offset 0x324, size 0x4
    unsigned short attribute; // offset 0x328, size 0x2
    void * (* func)(void *); // offset 0x32C, size 0x4
    unsigned long long args8B[1]; // offset 0x330, size 0x8
    void * args4B[5]; // offset 0x338, size 0x14
};
long (* CNTSDInitThreadRSO)(struct CNTSDThreadInfo *, void *, unsigned long); // size: 0x4, address: 0x80A548CC
long (* CNTSDSetThreadRestoreRSO)(struct CNTSDThreadInfo *, unsigned char *, unsigned long, struct CNTSDProgressInfo *); // size: 0x4, address: 0x80A548D0
long (* CNTSDStartThreadRSO)(struct CNTSDThreadInfo *); // size: 0x4, address: 0x80A548D4
long (* CNTSDGetFreeKBytesRSO)(); // size: 0x4, address: 0x80A548D8
long (* CNTSDBackupRSO)(unsigned long long, unsigned long, unsigned char *, unsigned long, unsigned long *, struct CNTSDProgressInfo *); // size: 0x4, address: 0x80A548DC
long (* CNTSDSetThreadBackupRSO)(struct CNTSDThreadInfo *, unsigned long long, unsigned long, unsigned char *, unsigned long, unsigned long *, struct CNTSDProgressInfo *); // size: 0x4, address: 0x80A548E0
long (* CNTSDFinishThreadRSO)(struct CNTSDThreadInfo *, void *); // size: 0x4, address: 0x80A548E4
long (* CNTSDDeleteBackupRSO)(unsigned long long, unsigned short); // size: 0x4, address: 0x80A548E8
void (* (* CNTSDSetEventCallbackRSO)(void (*)(int)))(int); // size: 0x4, address: 0x80A548EC
struct RSOExportFuncTable {
    // total size: 0x8
    const char * symbol_name; // offset 0x0, size 0x4
    unsigned long * symbol_ptr; // offset 0x4, size 0x4
};
static struct RSOExportFuncTable exp_tbl_cntsdModule[14]; // size: 0x70, address: 0x80922430
struct RSOObjectLink {
    // total size: 0x8
    struct RSOObjectInfo * next; // offset 0x0, size 0x4
    struct RSOObjectInfo * prev; // offset 0x4, size 0x4
};
struct RSOObjectInfo {
    // total size: 0x1C
    struct RSOObjectLink link; // offset 0x0, size 0x8
    unsigned long numSections; // offset 0x8, size 0x4
    unsigned long sectionInfoOffset; // offset 0xC, size 0x4
    unsigned long nameOffset; // offset 0x10, size 0x4
    unsigned long nameSize; // offset 0x14, size 0x4
    unsigned long version; // offset 0x18, size 0x4
};
struct RSOSymbolHeader {
    // total size: 0xC
    unsigned long tableOffset; // offset 0x0, size 0x4
    unsigned long tableSize; // offset 0x4, size 0x4
    unsigned long stringOffset; // offset 0x8, size 0x4
};
struct RSOObjectHeader {
    // total size: 0x58
    struct RSOObjectInfo info; // offset 0x0, size 0x1C
    unsigned long bssSize; // offset 0x1C, size 0x4
    unsigned char prologSection; // offset 0x20, size 0x1
    unsigned char epilogSection; // offset 0x21, size 0x1
    unsigned char unresolvedSection; // offset 0x22, size 0x1
    unsigned char bssSection; // offset 0x23, size 0x1
    unsigned long prolog; // offset 0x24, size 0x4
    unsigned long epilog; // offset 0x28, size 0x4
    unsigned long unresolved; // offset 0x2C, size 0x4
    unsigned long internalRelOffset; // offset 0x30, size 0x4
    unsigned long internalRelSize; // offset 0x34, size 0x4
    unsigned long externalRelOffset; // offset 0x38, size 0x4
    unsigned long externalRelSize; // offset 0x3C, size 0x4
    struct RSOSymbolHeader expHeader; // offset 0x40, size 0xC
    struct RSOSymbolHeader impHeader; // offset 0x4C, size 0xC
};
struct RSOObjectHeader * cntsdModule; // size: 0x4, address: 0x80A548F0
// Range: 0x805A7410 -> 0x805A74B0
unsigned char CntSdRsoInit() {
    // References
    // -> struct RSOObjectHeader * cntsdModule;
}

// Range: 0x805A74B0 -> 0x805A74F8
void CntSdRsoTerminate() {
    // References
    // -> struct RSOObjectHeader * cntsdModule;
}

static struct MEMAllocator gCNTAllocator; // size: 0x10, address: 0x80983F60
static unsigned char gSDFailed; // size: 0x1, address: 0x80A548F4
// Range: 0x805A74F8 -> 0x805A7504
static void SDCallback() {
    // References
    // -> static unsigned char gSDFailed;
}

struct CNTHandleDVD {
    // total size: 0x24
    unsigned long index; // offset 0x0, size 0x4
    long rootDir; // offset 0x4, size 0x4
    long currDir; // offset 0x8, size 0x4
    unsigned char reserved[24]; // offset 0xC, size 0x18
};
union /* @class$10672ContentMgr_Wii_cpp */ {
    struct CNTHandleNAND nand; // offset 0x0, size 0x24
    struct CNTHandleDVD dvd; // offset 0x0, size 0x24
};
struct CNTHandle {
    // total size: 0x28
    union /* @class$10672ContentMgr_Wii_cpp */ {
        struct CNTHandleNAND nand; // offset 0x0, size 0x24
        struct CNTHandleDVD dvd; // offset 0x0, size 0x24
    } as; // offset 0x0, size 0x24
    unsigned char type; // offset 0x24, size 0x1
};
class WiiContent : public Content {
    // total size: 0x68
    unsigned long long mTitleIdx; // offset 0x8, size 0x8
    int mIdx; // offset 0x10, size 0x4
    enum State mState; // offset 0x14, size 0x4
    struct CNTHandle mHandle; // offset 0x18, size 0x28
    class Symbol mName; // offset 0x40, size 0x4
    class DataArray * mSongData; // offset 0x44, size 0x4
    enum WiiContentType mType; // offset 0x48, size 0x4
    int mOpenFiles; // offset 0x4C, size 0x4
    enum ContentLocT mLocation; // offset 0x50, size 0x4
    class String mDisplayName; // offset 0x54, size 0xC
    unsigned char mBackingUp; // offset 0x60, size 0x1
    unsigned char mBannerTransferred; // offset 0x61, size 0x1
};
enum WiiContentType {
    kContentPreview = 0,
    kContentSong = 1,
};
// Range: 0x805A7504 -> 0x805A75A8
void * WiiContent::WiiContent(class WiiContent * const this /* r30 */, class Symbol & name /* r12 */, enum WiiContentType type /* r11 */, enum ContentLocT location /* r6 */) {
    // References
    // -> struct [anonymous] __vt__10WiiContent;
}

// Range: 0x805A75A8 -> 0x805A764C
void * WiiContent::~WiiContent(class WiiContent * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__10WiiContent;
}

// Range: 0x805A764C -> 0x805A7938
void WiiContent::Poll(class WiiContent * const this /* r31 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x805A7938 -> 0x805A7940
unsigned char WiiContent::OnMemcard() {}

// Range: 0x805A7940 -> 0x805A7A68
void WiiContent::Mount(class WiiContent * const this /* r31 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x805A7A68 -> 0x805A7BD8
void WiiContent::Unmount(class WiiContent * const this /* r29 */) {
    // Local variables
    long rv; // r0
    unsigned short id; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x805A7BD8 -> 0x805A7C80
long WiiContent::OpenContentFile(class WiiContent * const this /* r29 */, const char * filename /* r30 */, struct CNTFileInfo * cf /* r31 */) {
    // Local variables
    long rv; // r3

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805A7C80 -> 0x805A7D34
void WiiContent::CompleteMount(class WiiContent * const this /* r30 */) {
    // Local variables
    long rv; // r5

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> static struct MEMAllocator gCNTAllocator;
}

// Range: 0x805A7D34 -> 0x805A7E8C
void WiiContent::BackupToSDCard(class WiiContent * const this /* r31 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
}

class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
enum CNTSDResult {
    kDLCSuccess = 0,
    kDLCFailed = 1,
    kFailNoSDCard = 2,
    kFailSDIncompatible = 3,
    kBackupNoSDSpace = 4,
    kBackupSDWriteProtected = 5,
    kRestoreCorrupt = 6,
    kRestoreNoNANDSpace = 7,
    kRestoreNoNANDInodes = 8,
    kRestoreOutOfDate = 9,
    kRestoreNoLicense = 10,
};
class WiiContentMgr : public ContentMgr {
    // total size: 0x428
    class list mTitleIDs; // offset 0x6C, size 0x8
    class map mECInfoList; // offset 0x74, size 0x18
    struct CNTSDProgressInfo mProgress; // offset 0x8C, size 0x10
    struct CNTSDThreadInfo mThreadInfo; // offset 0xA0, size 0x350
    void * mCNTRestoreThreadWorkBuffer; // offset 0x3F0, size 0x4
    void * mCNTBackupThreadWorkBuffer; // offset 0x3F4, size 0x4
    void * mCNTThreadStackBuffer; // offset 0x3F8, size 0x4
    class DataArray * mContentList; // offset 0x3FC, size 0x4
    unsigned long mCurrentEnumIndex; // offset 0x400, size 0x4
    unsigned char mOpInProgress; // offset 0x404, size 0x1
    enum Mode mMode; // offset 0x408, size 0x4
    enum CNTSDResult mLastResult; // offset 0x40C, size 0x4
    int mLastResultValue; // offset 0x410, size 0x4
    unsigned char mNeedShopAccount; // offset 0x414, size 0x1
    class NetLoader * mNetLoader; // offset 0x418, size 0x4
    unsigned char mContentListDirty; // offset 0x41C, size 0x1
    unsigned char mInitComplete; // offset 0x41D, size 0x1
    unsigned int mRefreshDelay; // offset 0x420, size 0x4
};
static class WiiContentMgr gContentMgr; // size: 0x428, address: 0x80983F80
class ContentMgr & TheContentMgr; // size: 0x4, address: 0x80A548F8
// Range: 0x805A7E8C -> 0x805A7EA0
static void * WiiCntAlloc() {
    // Local variables
    void * retPtr; // r0
}

// Range: 0x805A7EA0 -> 0x805A7EA8
static void WiiCntFree() {}

static struct MEMAllocatorFunc cntAllocFunc; // size: 0x8, address: 0x8084E678
// Range: 0x805A7EA8 -> 0x805A7EB8
void InitAllocator() {
    // References
    // -> static struct MEMAllocatorFunc cntAllocFunc;
}

// Range: 0x805A7EB8 -> 0x805A7EF8
void * ecAlloc() {
    // Local variables
    void * p; // r0
}

// Range: 0x805A7EF8 -> 0x805A7F24
void * ecFree() {}

static class Symbol store; // size: 0x4, address: 0x80A54900
static class Symbol titles; // size: 0x4, address: 0x80A54908
struct ECNameValue {
    // total size: 0x8
    const char * name; // offset 0x0, size 0x4
    void * value; // offset 0x4, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x805A7F24 -> 0x805A83A4
void WiiContentMgr::Init(class WiiContentMgr * const this /* r29 */) {
    // Local variables
    struct ECNameValue args[2]; // r1+0x90
    int ret; // r0
    class DataArray * store_titles; // r27
    int i; // r26
    struct _List_iterator it; // r1+0x5C

    // References
    // -> void (* (* CNTSDSetEventCallbackRSO)(void (*)(int)))(int);
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std14_List_node<Ux>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class Symbol titles;
    // -> static class Symbol store;
    // -> static struct MEMAllocator gCNTAllocator;
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std14_List_node<Ux>; // size: 0x8, address: 0x809226B8
// Range: 0x805A83A4 -> 0x805A8800
void WiiContentMgr::Terminate(class WiiContentMgr * const this /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x58

    // References
    // -> void (* (* CNTSDSetEventCallbackRSO)(void (*)(int)))(int);
}

// Range: 0x805A8800 -> 0x805A886C
void WiiContentMgr::RestartEC(class WiiContentMgr * const this /* r31 */) {
    // Local variables
    struct ECNameValue args[2]; // r1+0x8
    int ret; // r0
}

enum Mode {
    kSDMode = 0,
    kNANDMode = 1,
};
// Range: 0x805A886C -> 0x805A8950
void WiiContentMgr::SetMode(class WiiContentMgr * const this /* r29 */, enum Mode mode /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x10
    enum State state; // r0
}

// Range: 0x805A8950 -> 0x805A8AE4
int WiiContentMgr::SDModeNANDCheck(class WiiContentMgr * const this /* r30 */) {
    // Local variables
    int num; // r31
    struct _List_iterator it; // r1+0x28
    struct ContentInfo * contentInfo; // r0
    int i; // r5
}

// Range: 0x805A8AE4 -> 0x805A8B40
int WiiContentMgr::SDModeSizeCheck() {
    // Local variables
    unsigned long answer; // r1+0x8
    long result; // r0
}

static unsigned short sContentIds[510]; // size: 0x3FC, address: 0x809843A8
// Range: 0x805A8B40 -> 0x805A8E6C
void WiiContentMgr::ClearNAND(class WiiContentMgr * const this /* r27 */) {
    // Local variables
    struct _List_iterator it; // r1+0x4C
    enum State state; // r0
    struct _List_iterator it; // r1+0x48
    unsigned int num; // r30
    struct ECContentInfo * info; // r29
    int i; // r28
    int rv; // r0

    // References
    // -> class Debug TheDebug;
    // -> static unsigned short sContentIds[510];
}

// Range: 0x805A8E6C -> 0x805A8EE8
unsigned long long WiiContentMgr::GetTitleIdFromCode(const char * code /* r31 */) {
    // Local variables
    unsigned long long titleID; // r1+0x8
}

// Range: 0x805A8EE8 -> 0x805A9600
void WiiContentMgr::UpdateNANDContentInfo(class WiiContentMgr * const this /* r26 */) {
    // Local variables
    int rv; // r31
    struct _List_iterator it; // r1+0xB8
    unsigned long long titleid; // r29
    int i; // r27

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805A9600 -> 0x805A982C
unsigned char WiiContentMgr::CheckContentIsPurchased(class WiiContentMgr * const this /* r26 */, unsigned long long titleid /* r28 */, int idx /* r29 */) {
    // Local variables
    struct ECContentInfo * info; // r31
    int i; // r30
}

// Range: 0x805A982C -> 0x805A98F0
unsigned char WiiContentMgr::CheckContent(class WiiContentMgr * const this /* r28 */, int idx /* r29 */) {
    // Local variables
    unsigned long long titleid; // r31
}

// Range: 0x805A98F0 -> 0x805AA018
void WiiContentMgr::CheckContents(class WiiContentMgr * const this /* r26 */) {
    // Local variables
    struct _List_iterator it; // r1+0x98
    unsigned long long titleid; // r29
    int i; // r27
    unsigned short num; // r1+0x8
    int rv; // r0
    struct _List_iterator it; // r1+0x94
    unsigned long long titleid; // r28
    int i; // r30
    unsigned char content1Exists; // r0
    unsigned char content2Exists; // r0
    int rv; // r0

    // References
    // -> long (* CNTSDDeleteBackupRSO)(unsigned long long, unsigned short);
    // -> class Debug TheDebug;
}

// Range: 0x805AA018 -> 0x805AA244
unsigned char WiiContentMgr::CheckContentOnNAND(class WiiContentMgr * const this /* r26 */, unsigned long long titleid /* r28 */, int idx /* r29 */) {
    // Local variables
    struct ECContentInfo * info; // r31
    int i; // r30
}

// Range: 0x805AA244 -> 0x805AA32C
unsigned char WiiContentMgr::CheckContentOnSD(unsigned long long titleid /* r30 */, int idx /* r31 */) {
    // Local variables
    unsigned char listInfo[1092]; // r1+0xC
    long rv; // r3
    unsigned long tempIdx; // r1+0x8

    // References
    // -> long (* CNTSDListNextRSO)(unsigned char (*)[1092], unsigned long *);
    // -> long (* CNTSDListFirstRSO)(unsigned char (*)[1092], unsigned long long, unsigned long *);
    // -> int (* CNTSDIsInsertedRSO)();
    // -> static unsigned char gSDFailed;
}

// Range: 0x805AA32C -> 0x805AA394
unsigned char WiiContentMgr::IsSDCorrupted() {
    // Local variables
    unsigned char * alignedWork; // r0
    unsigned long inodes; // r1+0x10
    unsigned long blocks; // r1+0xC
    int rv; // r0

    // References
    // -> long (* CNTSDRestoreGetBlocksRSO)(unsigned long long, unsigned long, unsigned char *, unsigned long, unsigned long *, unsigned long *);
}

// Range: 0x805AA394 -> 0x805AA468
unsigned char WiiContentMgr::DeleteContent(class WiiContentMgr * const this /* r25 */, unsigned long long titleidx /* r27 */, int idx /* r28 */, unsigned char sd /* r29 */, unsigned char title /* r30 */) {
    // Local variables
    unsigned short temp; // r1+0x8
    unsigned char found; // r31
    int rv; // r0

    // References
    // -> long (* CNTSDDeleteBackupRSO)(unsigned long long, unsigned short);
}

// Range: 0x805AA468 -> 0x805AA694
unsigned long WiiContentMgr::GetContentSize(class WiiContentMgr * const this /* r26 */, unsigned long long titleidx /* r28 */, int idx /* r29 */) {
    // Local variables
    struct ECContentInfo * info; // r31
    int i; // r30
}

// Range: 0x805AA694 -> 0x805AA794
long WiiContentMgr::GetContentFileHandle(class WiiContentMgr * const this /* r28 */, const char * filename /* r29 */, struct CNTFileInfo * cf /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x10
    class WiiContent * content; // r31
    long rv; // r0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805AA794 -> 0x805AA79C
enum State WiiContent::GetState() {}

// Range: 0x805AA79C -> 0x805AAA64
unsigned char WiiContentMgr::StartRestoreContentFromSD(class WiiContentMgr * const this /* r31 */, unsigned long long titleidx /* r26 */, int idx /* r30 */) {
    // Local variables
    unsigned long inodes; // r1+0xC
    unsigned long blocks; // r1+0x8
    long rv; // r4
    unsigned char * alignedWork; // r27

    // References
    // -> long (* CNTSDStartThreadRSO)(struct CNTSDThreadInfo *);
    // -> long (* CNTSDSetThreadRestoreRSO)(struct CNTSDThreadInfo *, unsigned char *, unsigned long, struct CNTSDProgressInfo *);
    // -> long (* CNTSDInitThreadRSO)(struct CNTSDThreadInfo *, void *, unsigned long);
    // -> long (* CNTSDRestoreGetBlocksRSO)(unsigned long long, unsigned long, unsigned char *, unsigned long, unsigned long *, unsigned long *);
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805AAA64 -> 0x805AAA6C
struct CNTSDProgressInfo * WiiContentMgr::GetProgress() {}

// Range: 0x805AAA6C -> 0x805AAAF0
int WiiContentMgr::GetPercentProgress() {
    // Local variables
    float p; // f1
    int percent; // r3
}

// Range: 0x805AAAF0 -> 0x805AACA4
unsigned char WiiContentMgr::FinishContentThread(class WiiContentMgr * const this /* r29 */) {
    // Local variables
    long rv; // r4
    long rvThread; // r1+0x8

    // References
    // -> long (* CNTSDFinishThreadRSO)(struct CNTSDThreadInfo *, void *);
    // -> class Debug TheDebug;
}

// Range: 0x805AACA4 -> 0x805AAF9C
unsigned char WiiContentMgr::StartBackupContentFromNAND(class WiiContentMgr * const this /* r30 */, unsigned long long titleidx /* r25 */, int idx /* r26 */) {
    // Local variables
    int rv; // r4
    unsigned long sizeAvailable; // r27
    unsigned long sizeRequired; // r1+0x10

    // References
    // -> long (* CNTSDStartThreadRSO)(struct CNTSDThreadInfo *);
    // -> long (* CNTSDSetThreadBackupRSO)(struct CNTSDThreadInfo *, unsigned long long, unsigned long, unsigned char *, unsigned long, unsigned long *, struct CNTSDProgressInfo *);
    // -> long (* CNTSDInitThreadRSO)(struct CNTSDThreadInfo *, void *, unsigned long);
    // -> long (* CNTSDBackupRSO)(unsigned long long, unsigned long, unsigned char *, unsigned long, unsigned long *, struct CNTSDProgressInfo *);
    // -> long (* CNTSDGetFreeKBytesRSO)();
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805AAF9C -> 0x805AB1DC
void WiiContentMgr::StartRefresh(class WiiContentMgr * const this /* r31 */) {
    // Local variables
    class DataArray * roots; // r29
    int i; // r28
    struct _List_iterator c; // r1+0x2C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std21_List_node<P7Content>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__11RootContent;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std21_List_node<P7Content>; // size: 0x8, address: 0x80922A70
// Range: 0x805AB1DC -> 0x805AB1E4
char * WiiContent::DisplayName() {}

// Range: 0x805AB1E4 -> 0x805AB1EC
enum ContentLocT WiiContent::Location() {}

// Range: 0x805AB1EC -> 0x805AB294
void WiiContentMgr::BackupContent(class WiiContentMgr * const this /* r29 */, class Symbol & contentName /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x14
}

// Range: 0x805AB294 -> 0x805AB538
unsigned char WiiContentMgr::MissingContentList(class WiiContentMgr * const this /* r28 */) {
    // Local variables
    struct _List_iterator it; // r1+0x40
    struct ECContentInfo * info; // r30
    int i; // r29
}

// Range: 0x805AB538 -> 0x805AB540
unsigned char WiiContentMgr::NeedContentListSave() {}

// Range: 0x805AB540 -> 0x805AB548
class Symbol WiiContent::FileName() {}

// Range: 0x805AB548 -> 0x805AB550
char * WiiContent::Root() {}

static class Symbol _s; // size: 0x4, address: 0x80A54910
static class Symbol _s; // size: 0x4, address: 0x80A54918
static class Symbol _s; // size: 0x4, address: 0x80A54920
static class Symbol _s; // size: 0x4, address: 0x80A54928
static class Symbol _s; // size: 0x4, address: 0x80A54930
static class Symbol _s; // size: 0x4, address: 0x80A54938
static class Symbol _s; // size: 0x4, address: 0x80A54940
static class Symbol _s; // size: 0x4, address: 0x80A54948
static class Symbol _s; // size: 0x4, address: 0x80A54950
static class Symbol _s; // size: 0x4, address: 0x80A54958
static class Symbol _s; // size: 0x4, address: 0x80A54960
static class Symbol _s; // size: 0x4, address: 0x80A54968
static class Symbol _s; // size: 0x4, address: 0x80A54970
static class Symbol _s; // size: 0x4, address: 0x80A54978
static class Symbol _s; // size: 0x4, address: 0x80A54980
static class Symbol _s; // size: 0x4, address: 0x80A54988
static class Symbol _s; // size: 0x4, address: 0x80A54990
static class Symbol _s; // size: 0x4, address: 0x80A54998
static class Symbol _s; // size: 0x4, address: 0x80A549A0
static class Symbol _s; // size: 0x4, address: 0x80A549A8
// Range: 0x805AB550 -> 0x805ABF0C
class DataNode WiiContentMgr::Handle(class WiiContentMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static unsigned char gSDFailed;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x805ABF0C -> 0x805ABF24
class DataNode WiiContentMgr::OnMsg() {}

// Range: 0x805ABF24 -> 0x805ABF74
class DataNode WiiContentMgr::OnMsg(class WiiContentMgr * const this /* r31 */) {}

// Range: 0x805ABF74 -> 0x805ABF7C
unsigned char WiiContentMgr::IsBusy() {}

// Range: 0x805ABF7C -> 0x805ABF84
enum Mode WiiContentMgr::GetMode() {}

// Range: 0x805ABF84 -> 0x805ABFDC
void WiiContentMgr::LockSystem() {
    // References
    // -> class SynthWii * TheWiiSynth;
}

struct {
    // total size: 0xB8
} __vt__13WiiContentMgr; // size: 0xB8, address: 0x80922E80
struct {
    // total size: 0x8
} __RTTI__13WiiContentMgr; // size: 0x8, address: 0x80922F68
class RootContent : public Content {
    // total size: 0x10
    class String mRoot; // offset 0x4, size 0xC
};
// Range: 0x805ABFDC -> 0x805ABFE4
char * RootContent::DisplayName() {}

// Range: 0x805ABFE4 -> 0x805AC014
class Symbol RootContent::FileName(class RootContent * const this /* r4 */) {}

// Range: 0x805AC014 -> 0x805AC01C
enum ContentLocT RootContent::Location() {}

// Range: 0x805AC01C -> 0x805AC024
unsigned char RootContent::OnMemcard() {}

// Range: 0x805AC024 -> 0x805AC02C
char * RootContent::Root() {}

// Range: 0x805AC02C -> 0x805AC034
enum State RootContent::GetState() {}

struct {
    // total size: 0x34
} __vt__11RootContent; // size: 0x34, address: 0x80922F70
struct {
    // total size: 0x8
} __RTTI__11RootContent; // size: 0x8, address: 0x80922FC0
struct {
    // total size: 0x34
} __vt__10WiiContent; // size: 0x34, address: 0x80922FC8
struct {
    // total size: 0x8
} __RTTI__10WiiContent; // size: 0x8, address: 0x80923018
struct {
    // total size: 0x34
} __vt__7Content; // size: 0x34, address: 0x809230D8
struct {
    // total size: 0x8
} __RTTI__7Content; // size: 0x8, address: 0x80923118
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
struct ContentInfo {
    // total size: 0x8
    struct ECContentInfo * info; // offset 0x0, size 0x4
    unsigned long count; // offset 0x4, size 0x4
};
struct pair {
    // total size: 0x10
    unsigned long long first; // offset 0x0, size 0x8
    struct ContentInfo second; // offset 0x8, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class list : public _List_base {
    // total size: 0x8
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    unsigned long long _M_data; // offset 0x8, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std72_Rb_tree_node<Q211stlpmtx_std40pair<CUx,Q213WiiContentMgr11ContentInfo>>; // size: 0x8, address: 0x809231B8
// Range: 0x805AC034 -> 0x805AC184
static void __sinit_\ContentMgr_Wii_cpp() {
    // References
    // -> class ContentMgr & TheContentMgr;
    // -> struct [anonymous] __vt__13WiiContentMgr;
    // -> struct [anonymous] __vt__10ContentMgr;
    // -> static class WiiContentMgr gContentMgr;
}


