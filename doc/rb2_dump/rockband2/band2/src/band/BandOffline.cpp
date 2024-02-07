/*
    Compile unit: C:\rockband2\band2\src\band\BandOffline.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8000E588 -> 0x8001019C
*/
class DataArray * types; // size: 0x4, address: 0x80A48E98
class Symbol name; // size: 0x4, address: 0x80A48EA0
class Symbol name; // size: 0x4, address: 0x80A48EA8
class BandOffline {
    // total size: 0x1
};
static class Symbol male; // size: 0x4, address: 0x80A48EB0
static class Symbol female; // size: 0x4, address: 0x80A48EB8
static class DataNode & glitch_venue; // size: 0x4, address: 0x80A48EC0
static class DataNode & glitch_song; // size: 0x4, address: 0x80A48EC8
enum FileType {
    kRead = 0,
    kWrite = 1,
    kReadNoArk = 2,
    kAppend = 3,
};
class FileStream : public BinStream {
    // total size: 0x28
    class File * mFile; // offset 0xC, size 0x4
    class String mFilename; // offset 0x10, size 0xC
    unsigned char mFail; // offset 0x1C, size 0x1
    class StreamChecksum * mChecksum; // offset 0x20, size 0x4
    int mBytesChecksummed; // offset 0x24, size 0x4
};
class TextFileStream : public TextStream {
    // total size: 0x2C
    class FileStream mFile; // offset 0x4, size 0x28
};
// Range: 0x8000E588 -> 0x8000EBA8
class DataNode BandOffline::MakeGlitchReport() {
    // Local variables
    const char * log_file; // r30
    class TextFileStream * temp_report; // r29
    class Timer t; // r1+0x80
    class GlitchReport * gr; // r28
    const class DataArray * songs; // r27
    int j; // r26
    class DataArray * venues; // r25
    int i; // r24
    int frame; // r23
    class TextFileStream real_report; // r1+0x50
    float s; // f31

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class TaskMgr TheTaskMgr;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12GlitchReport;
    // -> class Symbol name;
    // -> static class DataNode & glitch_song;
    // -> static class DataNode & glitch_venue;
    // -> class ContentMgr & TheContentMgr;
    // -> static class Symbol female;
    // -> static class Symbol male;
}

enum /* @enum$36095BandOffline_cpp */ {
    kDone = 0,
    kDiscoveryEnumerating = 1,
    kDiscoveryMounting = 2,
    kDiscoveryLoading = 3,
    kDiscoveryCheckIfDone = 4,
    kMounting = 5,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
enum ContentLocT {
    kLocationRemovableMem = 0,
    kLocationHDD = 1,
    kLocationRoot = 2,
};
class Callback {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
enum State {
    kUnmounted = 0,
    kNeedsMounting = 1,
    kMounting = 2,
    kUnmounting = 3,
    kMounted = 4,
    kAlwaysMounted = 5,
    kFailed = 6,
};
class Content {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct CallbackFile {
    // total size: 0x20
    class FilePath file; // offset 0x0, size 0xC
    class Callback * callback; // offset 0xC, size 0x4
    enum ContentLocT location; // offset 0x10, size 0x4
    class String name; // offset 0x14, size 0xC
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
enum CNTSDAction {
    CNTSD_PROGRESS_CONTINUE = 0,
    CNTSD_PROGRESS_CANCEL = 1,
};
struct CNTSDProgressInfo {
    // total size: 0x10
    unsigned long bytesProcessed; // offset 0x0, size 0x4
    unsigned long bytesTotal; // offset 0x4, size 0x4
    int done; // offset 0x8, size 0x4
    enum CNTSDAction action; // offset 0xC, size 0x4
};
struct ARCHandle {
    // total size: 0x1C
    void * archiveStartAddr; // offset 0x0, size 0x4
    void * FSTStart; // offset 0x4, size 0x4
    void * fileStart; // offset 0x8, size 0x4
    unsigned long entryNum; // offset 0xC, size 0x4
    char * FSTStringStart; // offset 0x10, size 0x4
    unsigned long FSTLength; // offset 0x14, size 0x4
    unsigned long currDir; // offset 0x18, size 0x4
};
struct CNTHandleNAND {
    // total size: 0x24
    struct ARCHandle ArcHandle; // offset 0x0, size 0x1C
    long FileDescriptor; // offset 0x1C, size 0x4
    struct MEMAllocator * allocator; // offset 0x20, size 0x4
};
struct CNTFileInfoNAND {
    // total size: 0x10
    struct CNTHandleNAND * CntHandle; // offset 0x0, size 0x4
    unsigned long startOffset; // offset 0x4, size 0x4
    unsigned long length; // offset 0x8, size 0x4
    long readOffset; // offset 0xC, size 0x4
};
struct CNTFileInfoDVD {
    // total size: 0x40
    struct DVDFileInfo fileInfo; // offset 0x0, size 0x3C
    long readOffset; // offset 0x3C, size 0x4
};
union /* @class$19181BandOffline_cpp */ {
    struct CNTFileInfoNAND nand; // offset 0x0, size 0x10
    struct CNTFileInfoDVD dvd; // offset 0x0, size 0x40
};
struct CNTFileInfo {
    // total size: 0x44
    union /* @class$19181BandOffline_cpp */ {
        struct CNTFileInfoNAND nand; // offset 0x0, size 0x10
        struct CNTFileInfoDVD dvd; // offset 0x0, size 0x40
    } as; // offset 0x0, size 0x40
    unsigned char type; // offset 0x40, size 0x1
};
class ContentMgr : public Object {
    // total size: 0x6C
protected:
    enum /* @enum$36095BandOffline_cpp */ {
        kDone = 0,
        kDiscoveryEnumerating = 1,
        kDiscoveryMounting = 2,
        kDiscoveryLoading = 3,
        kDiscoveryCheckIfDone = 4,
        kMounting = 5,
    } mState; // offset 0x28, size 0x4
    class list mCallbacks; // offset 0x2C, size 0x8
    class list mContents; // offset 0x34, size 0x8
    class list mExtraContents; // offset 0x3C, size 0x8
    unsigned char mDirty; // offset 0x44, size 0x1
    class Loader * mLoader; // offset 0x48, size 0x4
    class Callback * mCallback; // offset 0x4C, size 0x4
    enum ContentLocT mLocation; // offset 0x50, size 0x4
    class String mName; // offset 0x54, size 0xC
    int mRootLoaded; // offset 0x60, size 0x4
    class list mCallbackFiles; // offset 0x64, size 0x8
};
struct Glitch {
    // total size: 0x34
    float glitchMs; // offset 0x0, size 0x4
    float frameMs; // offset 0x4, size 0x4
    class String desc; // offset 0x8, size 0xC
    class SongPos songPos; // offset 0x14, size 0x14
    class vector events; // offset 0x28, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Glitch * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Glitch * * _M_start; // offset 0x0, size 0x4
    struct Glitch * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct GlitchEvent {
    // total size: 0x10
    float avGlitchMs; // offset 0x0, size 0x4
    class String eventName; // offset 0x4, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct GlitchEvent * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct GlitchEvent * _M_start; // offset 0x0, size 0x4
    struct GlitchEvent * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class GlitchReport : public Object {
    // total size: 0xA8
protected:
    class vector mGlitches; // offset 0x28, size 0xC
    class String mDesc; // offset 0x34, size 0xC
    class vector mEvents; // offset 0x40, size 0xC
    class Timer mTimer; // offset 0x50, size 0x38
    float mLastMs; // offset 0x88, size 0x4
    unsigned char mRunning; // offset 0x8C, size 0x1
    unsigned char mReporting; // offset 0x8D, size 0x1
    int mNumGlitches; // offset 0x90, size 0x4
    float mFrameMs; // offset 0x94, size 0x4
    float mGlitchMs; // offset 0x98, size 0x4
    class vector mGlitchEvents; // offset 0x9C, size 0xC
};
static class Timer * _t; // size: 0x4, address: 0x80A48ECC
// Range: 0x8000EBA8 -> 0x8000ECE8
void BandOffline::Poll() {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> class CharCache * TheCharCache;
    // -> class Rnd & TheRnd;
    // -> class TaskMgr TheTaskMgr;
    // -> static class Timer * _t;
    // -> class UIManager TheUI;
    // -> class Net TheNet;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Synth * TheSynth;
}

static char prefixes[5]; // size: 0x5, address: 0x80847C60
// Range: 0x8000ECE8 -> 0x8000ED30
static int GetStatKeeperIndex() {
    // Local variables
    char c; // r0

    // References
    // -> static char prefixes[5];
}

static class Message is_active; // size: 0x8, address: 0x80976B30
static class Message is_done; // size: 0x8, address: 0x80976B48
static char * insts[4]; // size: 0x10, address: 0x8085D560
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CompositeCharacter * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x8000ED30 -> 0x8000F8E0
class DataNode BandOffline::MakeCharClipBudget() {
    // Local variables
    class Object * cb; // r29
    const class DataArray * songs; // r28
    int tempos[3]; // r1+0x10C
    int i; // r27
    class CharStatKeeper totals[4]; // r1+0x398
    class CharStatKeeper maxes[4]; // r1+0x2D8
    class CharStatKeeper normalMaxes[4]; // r1+0x218
    class vector tempoSongs; // r1+0x100
    float totalDuration; // f30
    int tempo; // r26
    int j; // r25
    class Symbol song; // r1+0x64
    class CharStatKeeper stats[4]; // r1+0x158
    float duration; // r1+0x60
    class Message msg; // r1+0xA8
    class CompositeCharacter * dudes[4]; // r1+0xF0
    int index; // r21
    class ObjDirItr dude; // r1+0x118
    int i; // r21
    int i; // r21
    class TextFileStream log; // r1+0x12C
    int numSongs; // r21
    float invSongs; // f29
    float avDuration; // f28
    int i; // r23
    int i; // r25
    struct _Rb_tree_iterator it; // r1+0x5C
    int intensity; // r1+0x58
    class vector vec; // r1+0xE4
    struct _Rb_tree_iterator it; // r1+0x54
    class String groupName; // r1+0xD8
    class Message is_valid_group; // r1+0xA0
    int j; // r20
    class String group; // r1+0xCC

    // References
    // -> static char * insts[4];
    // -> static class Message is_done;
    // -> class TaskMgr TheTaskMgr;
    // -> class WorldDir * TheWorld;
    // -> static class Message is_active;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> class SongMgr & TheSongMgr;
    // -> class ContentMgr & TheContentMgr;
}

class CharStatKeeper {
    // total size: 0x30
public:
    class map mIntensities; // offset 0x0, size 0x18
    class map mGroups; // offset 0x18, size 0x18
};
// Range: 0x8000F8E0 -> 0x8000F964
void * CharStatKeeper::CharStatKeeper() {}

struct pair {
    // total size: 0x8
    int first; // offset 0x0, size 0x4
    float second; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
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
struct pair {
    // total size: 0x10
    class String first; // offset 0x0, size 0xC
    float second; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
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
// Range: 0x8000F964 -> 0x8000FA28
void * CharStatKeeper::~CharStatKeeper(class CharStatKeeper * const this /* r30 */) {}

// Range: 0x8000FA34 -> 0x8000FC24
void CharStatKeeper::OnPoll(class CharStatKeeper * const this /* r30 */, int intensity /* r6 */, class String & groupName /* r31 */, float dt /* f31 */) {}

class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x8000FC24 -> 0x8000FE80
void CharStatKeeper::AddEq(class CharStatKeeper * const this /* r30 */, const class CharStatKeeper & c /* r31 */) {
    // Local variables
    struct _Rb_tree_iterator it; // r1+0x5C
    struct _Rb_tree_iterator it; // r1+0x58
}

// Range: 0x8000FE80 -> 0x800100E4
void CharStatKeeper::MaxEq(class CharStatKeeper * const this /* r30 */, const class CharStatKeeper & c /* r31 */) {
    // Local variables
    struct _Rb_tree_iterator it; // r1+0x5C
    struct _Rb_tree_iterator it; // r1+0x58
}

// Range: 0x800100E4 -> 0x8001019C
void CharStatKeeper::ScaleEq(class CharStatKeeper * const this /* r31 */, float s /* f31 */) {
    // Local variables
    struct _Rb_tree_iterator it; // r1+0x1C
    struct _Rb_tree_iterator it; // r1+0x18
}

struct SortGroupPolls {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
struct pair {
    // total size: 0x10
    class String first; // offset 0x0, size 0xC
    float second; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct pair * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct pair * _M_start; // offset 0x0, size 0x4
    struct pair * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
struct pair {
    // total size: 0x8
    class Symbol first; // offset 0x0, size 0x4
    float second; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct pair * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct pair * _M_start; // offset 0x0, size 0x4
    struct pair * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__12GlitchReport; // size: 0x8, address: 0x8085D6A0
struct {
    // total size: 0x8
} __RTTI__18CompositeCharacter; // size: 0x8, address: 0x8085D718
struct {
    // total size: 0x8
} __RTTI__9Character; // size: 0x8, address: 0x8085D780
struct {
    // total size: 0x8
} __RTTI__6RndDir; // size: 0x8, address: 0x8085D7E0
struct {
    // total size: 0x8
} __RTTI__9MsgSource; // size: 0x8, address: 0x8085D808
struct {
    // total size: 0x8
} __RTTI__11RndPollable; // size: 0x8, address: 0x8085D850
struct {
    // total size: 0x8
} __RTTI__16RndTransformable; // size: 0x8, address: 0x8085D888
struct {
    // total size: 0x8
} __RTTI__13RndAnimatable; // size: 0x8, address: 0x8085D8B8
struct {
    // total size: 0x8
} __RTTI__11RndDrawable; // size: 0x8, address: 0x8085D8E8
struct {
    // total size: 0x8
} __RTTI__16RndHighlightable; // size: 0x8, address: 0x8085D918
class _Rb_global {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std15pair<6String,f>; // size: 0x8, address: 0x8085DA10
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std15pair<6Symbol,f>; // size: 0x8, address: 0x8085DA40
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std42_Rb_tree_node<Q211stlpmtx_std10pair<Ci,f>>; // size: 0x8, address: 0x8085DA90
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std48_Rb_tree_node<Q211stlpmtx_std16pair<C6String,f>>; // size: 0x8, address: 0x8085DAE0
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class Spotlight * mPtr; // offset 0x8, size 0x4
};
enum Shape {
    kConic = 0,
    kRect = 1,
    kSheet = 2,
    kQuadXYZ = 3,
    kQuadZ = 4,
};
struct BeamDef {
    // total size: 0x6C
    class RndMesh * mBeam; // offset 0x0, size 0x4
    unsigned char mIsCone; // offset 0x4, size 0x1
    float mLength; // offset 0x8, size 0x4
    float mTopRadius; // offset 0xC, size 0x4
    float mRadius; // offset 0x10, size 0x4
    float mTopSideBorder; // offset 0x14, size 0x4
    float mBottomSideBorder; // offset 0x18, size 0x4
    float mBottomBorder; // offset 0x1C, size 0x4
    float mOffset; // offset 0x20, size 0x4
    class Vector2 mTargetOffset; // offset 0x24, size 0x8
    float mBrighten; // offset 0x2C, size 0x4
    float mExpand; // offset 0x30, size 0x4
    enum Shape mShape; // offset 0x34, size 0x4
    int mNumSections; // offset 0x38, size 0x4
    int mNumSegments; // offset 0x3C, size 0x4
    class ObjPtr mXSection; // offset 0x40, size 0xC
    class ObjPtrList mCutouts; // offset 0x4C, size 0x14
    class ObjPtr mMat; // offset 0x60, size 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndMesh * mPtr; // offset 0x8, size 0x4
};
class Spotlight : public RndDrawable, public RndTransformable, public RndPollable {
    // total size: 0x390
protected:
    class ObjPtr mDiscMat; // offset 0x100, size 0xC
    class RndFlare * mFlare; // offset 0x10C, size 0x4
    unsigned char mFlareEnabled; // offset 0x110, size 0x1
    unsigned char mFlareIsBillboard; // offset 0x111, size 0x1
    float mFlareOffset; // offset 0x114, size 0x4
    float mSpotScale; // offset 0x118, size 0x4
    float mSpotHeight; // offset 0x11C, size 0x4
    class Transform mFloorSpotXfm; // offset 0x120, size 0x40
    class Transform mLensXfm; // offset 0x160, size 0x40
    class Color mColor; // offset 0x1A0, size 0x10
    float mIntensity; // offset 0x1B0, size 0x4
    class ObjOwnerPtr mColorOwner; // offset 0x1B4, size 0xC
    float mLensSize; // offset 0x1C0, size 0x4
    float mLensOffset; // offset 0x1C4, size 0x4
    class ObjPtr mLensMat; // offset 0x1C8, size 0xC
    struct BeamDef mBeam; // offset 0x1D4, size 0x6C
    class ObjPtrList mSlaves; // offset 0x240, size 0x14
    class ObjPtr mLightCanMesh; // offset 0x254, size 0xC
    class Transform mLightCanXfm; // offset 0x260, size 0x40
    float mLightCanOffset; // offset 0x2A0, size 0x4
    class ObjPtr mTarget; // offset 0x2A4, size 0xC
    unsigned char mTargetExists; // offset 0x2B0, size 0x1
    class ObjPtr mFloorSpotTarget; // offset 0x2B4, size 0xC
    float mLastFloorSpotHeight; // offset 0x2C0, size 0x4
    class Symbol mTargetSubpart; // offset 0x2C4, size 0x4
    unsigned char mCastShadow; // offset 0x2C8, size 0x1
    unsigned char mLightCanSort; // offset 0x2C9, size 0x1
    class Matrix3 mLastDirection; // offset 0x2D0, size 0x30
    unsigned char mFirstFrame; // offset 0x300, size 0x1
    float mDampingConstant; // offset 0x304, size 0x4
    class ObjPtrList mAdditionalObjects; // offset 0x308, size 0x14
    class Vector3 mLastTargetPosition; // offset 0x320, size 0x10
    unsigned char mAnimateColorFromPreset; // offset 0x330, size 0x1
    unsigned char mAnimatePosFromPreset; // offset 0x331, size 0x1
    unsigned char mAnimatingFromPreset; // offset 0x332, size 0x1
    class Quat mPresetOrient; // offset 0x340, size 0x10
    float mAlpha; // offset 0x350, size 0x4
};
struct SpotlightEntry {
    // total size: 0x30
    unsigned short mIntensity; // offset 0x0, size 0x2
    unsigned int mColor; // offset 0x4, size 0x4
    unsigned char mFlags; // offset 0x8, size 0x1
    class ObjPtr mTarget; // offset 0xC, size 0xC
    class Symbol mTargetSubpart; // offset 0x18, size 0x4
    class Quat mOrientation; // offset 0x20, size 0x10
};
struct _SpotlightEntryCompressedInternal {
    // total size: 0x20
    unsigned short mIntensity; // offset 0x0, size 0x2
    unsigned int mColor; // offset 0x4, size 0x4
    unsigned char mFlags; // offset 0x8, size 0x1
    class ObjPtr mTarget; // offset 0xC, size 0xC
    class Symbol mTargetSubpart; // offset 0x18, size 0x4
    struct ByteQuat mOrientation; // offset 0x1C, size 0x4
};
class SpotlightEntryCompressed {
    // total size: 0x4
protected:
    struct _SpotlightEntryCompressedInternal * mData; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class SpotlightEntryCompressed * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class SpotlightEntryCompressed * _M_start; // offset 0x0, size 0x4
    class SpotlightEntryCompressed * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
struct EnvironmentEntry {
    // total size: 0x30
    class Color mAmbientColor; // offset 0x0, size 0x10
    unsigned char mFogEnable; // offset 0x10, size 0x1
    float mFogStart; // offset 0x14, size 0x4
    float mFogEnd; // offset 0x18, size 0x4
    class Color mFogColor; // offset 0x20, size 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct EnvironmentEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct EnvironmentEntry * _M_start; // offset 0x0, size 0x4
    struct EnvironmentEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct EnvLightEntry {
    // total size: 0x30
    class Quat mOrientation; // offset 0x0, size 0x10
    class Vector3 mPosition; // offset 0x10, size 0x10
    unsigned int mColor; // offset 0x20, size 0x4
    float mRange; // offset 0x24, size 0x4
    unsigned int mType; // offset 0x28, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct EnvLightEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct EnvLightEntry * _M_start; // offset 0x0, size 0x4
    struct EnvLightEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct SpotlightDrawerEntry {
    // total size: 0xC
    float mTotal; // offset 0x0, size 0x4
    float mBaseIntensity; // offset 0x4, size 0x4
    float mSmokeIntensity; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct SpotlightDrawerEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct SpotlightDrawerEntry * _M_start; // offset 0x0, size 0x4
    struct SpotlightDrawerEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct _Bit_iterator_base {
    // total size: 0x8
    unsigned int * _M_p; // offset 0x0, size 0x4
    unsigned int _M_offset; // offset 0x4, size 0x4
};
struct _Bit_reference {
    // total size: 0x8
    unsigned int * _M_p; // offset 0x0, size 0x4
    unsigned int _M_mask; // offset 0x4, size 0x4
};
struct _Bit_iter : public _Bit_iterator_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned int * _M_data; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _Bvector_base {
    // total size: 0x14
protected:
    struct _Bit_iter _M_start; // offset 0x0, size 0x8
    struct _Bit_iter _M_finish; // offset 0x8, size 0x8
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x10, size 0x4
};
class vector : public _Bvector_base {
    // total size: 0x14
};
struct Keyframe {
    // total size: 0xA0
    class String mDescription; // offset 0x0, size 0xC
    class ObjVector mSpotlightEntries; // offset 0xC, size 0x10
    class vector mEnvironmentEntries; // offset 0x1C, size 0xC
    class vector mLightEntries; // offset 0x28, size 0xC
    class vector mSpotlightDrawerEntries; // offset 0x34, size 0xC
    class vector mSpotlightChanges; // offset 0x40, size 0x14
    class vector mEnvironmentChanges; // offset 0x54, size 0x14
    class vector mLightChanges; // offset 0x68, size 0x14
    class vector mSpotlightDrawerChanges; // offset 0x7C, size 0x14
    float mDuration; // offset 0x90, size 0x4
    float mFadeOutTime; // offset 0x94, size 0x4
    float mFrame; // offset 0x98, size 0x4
    struct _SpotlightEntryCompressedInternal * storageSpace; // offset 0x9C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Keyframe * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Keyframe * _M_start; // offset 0x0, size 0x4
    struct Keyframe * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Spotlight * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Spotlight * * _M_start; // offset 0x0, size 0x4
    class Spotlight * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndEnviron * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndEnviron * * _M_start; // offset 0x0, size 0x4
    class RndEnviron * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndLight * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndLight * * _M_start; // offset 0x0, size 0x4
    class RndLight * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class SpotlightDrawer * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class SpotlightDrawer * * _M_start; // offset 0x0, size 0x4
    class SpotlightDrawer * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndAnimatable * mPtr; // offset 0x8, size 0x4
};
struct Anim {
    // total size: 0x34
    class ObjPtr mAnim; // offset 0x0, size 0xC
    float mBlend; // offset 0xC, size 0x4
    unsigned char mWait; // offset 0x10, size 0x1
    float mDelay; // offset 0x14, size 0x4
    unsigned char mFilterEnable; // offset 0x18, size 0x1
    enum Rate mFilterRate; // offset 0x1C, size 0x4
    float mFilterStart; // offset 0x20, size 0x4
    float mFilterEnd; // offset 0x24, size 0x4
    float mFilterPeriod; // offset 0x28, size 0x4
    float mFilterScale; // offset 0x2C, size 0x4
    class Symbol mFilterType; // offset 0x30, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class ObjectDir * mPtr; // offset 0x8, size 0x4
};
struct ProxyCall {
    // total size: 0x1C
    class ObjPtr mProxy; // offset 0x0, size 0xC
    class Symbol mCall; // offset 0xC, size 0x4
    class ObjPtr mEvent; // offset 0x10, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class StlNodeAlloc {
    // total size: 0x1
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
class list : public _List_base {
    // total size: 0x8
};
class SynthPollable {
    // total size: 0xC
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    struct _List_iterator mItr; // offset 0x4, size 0x4
    unsigned char mIsActive; // offset 0x8, size 0x1
};
class SeqInst : public Object {
    // total size: 0x40
protected:
    class Sequence * mOwner; // offset 0x28, size 0x4
    float mRandVol; // offset 0x2C, size 0x4
    float mRandPan; // offset 0x30, size 0x4
    float mRandTp; // offset 0x34, size 0x4
    float mVolume; // offset 0x38, size 0x4
private:
    unsigned char mStarted; // offset 0x3C, size 0x1
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class GroupSeq : public Sequence {
    // total size: 0x8C
    class ObjPtrList mChildren; // offset 0x78, size 0x14
};
class Sequence : public Object, public SynthPollable {
    // total size: 0x78
protected:
    class ObjPtrList mInsts; // offset 0x34, size 0x14
    float mAvgVol; // offset 0x48, size 0x4
    float mVolSpread; // offset 0x4C, size 0x4
    float mAvgTranspose; // offset 0x50, size 0x4
    float mTransposeSpread; // offset 0x54, size 0x4
    float mAvgPan; // offset 0x58, size 0x4
    float mPanSpread; // offset 0x5C, size 0x4
    class FaderGroup mFaders; // offset 0x60, size 0x18
};
struct Node {
    // total size: 0xC
    class Sequence * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct HideDelay {
    // total size: 0x10
    class ObjPtr mHide; // offset 0x0, size 0xC
    float mDelay; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
enum TriggerOrder {
    kTriggerRandom = 0,
    kTriggerSequence = 1,
};
class EventTrigger : public Object {
    // total size: 0xB0
protected:
    class ObjList mAnims; // offset 0x28, size 0xC
    class ObjList mProxyCalls; // offset 0x34, size 0xC
    class ObjPtrList mSounds; // offset 0x40, size 0x14
    class ObjPtrList mShows; // offset 0x54, size 0x14
    class ObjList mHideDelays; // offset 0x68, size 0xC
    class list mTriggerEvents; // offset 0x74, size 0x8
    class list mEnableEvents; // offset 0x7C, size 0x8
    class list mDisableEvents; // offset 0x84, size 0x8
    class list mWaitForEvents; // offset 0x8C, size 0x8
    class ObjPtr mNextLink; // offset 0x94, size 0xC
    class Symbol mHandler; // offset 0xA0, size 0x4
    unsigned char mEnabled; // offset 0xA4, size 0x1
    unsigned char mWaiting; // offset 0xA5, size 0x1
    enum TriggerOrder mTriggerOrder; // offset 0xA8, size 0x4
    int mLastTriggerIndex; // offset 0xAC, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class EventTrigger * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct SpotlightEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct SpotlightEntry * _M_start; // offset 0x0, size 0x4
    struct SpotlightEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Keys : public vector {
    // total size: 0xC
};
class LightHue : public Object {
    // total size: 0x44
    class FileLoader * mLoader; // offset 0x28, size 0x4
    class FilePath mPath; // offset 0x2C, size 0xC
    class Keys mKeys; // offset 0x38, size 0xC
};
struct LightPresetTarget {
    // total size: 0x24
    class Character * mTarget; // offset 0x0, size 0x4
    class Symbol mBaseAnim; // offset 0x4, size 0x4
    float mBaseAmplitude; // offset 0x8, size 0x4
    float mBaseSpeed; // offset 0xC, size 0x4
    float mBasePhase; // offset 0x10, size 0x4
    class Symbol mAddAnim; // offset 0x14, size 0x4
    float mAddAmplitude; // offset 0x18, size 0x4
    float mAddSpeed; // offset 0x1C, size 0x4
    float mAddPhase; // offset 0x20, size 0x4
};
class LightPreset : public RndAnimatable {
    // total size: 0x134
protected:
    class ObjVector mKeyframes; // offset 0x10, size 0x10
    class vector mSpotlights; // offset 0x20, size 0xC
    class vector mEnvironments; // offset 0x2C, size 0xC
    class vector mLights; // offset 0x38, size 0xC
    class vector mSpotlightDrawers; // offset 0x44, size 0xC
    unsigned char mLooping; // offset 0x50, size 0x1
    class Symbol mCategory; // offset 0x54, size 0x4
    enum Platform mPlatformOnly; // offset 0x58, size 0x4
    class vector mAdjectives; // offset 0x5C, size 0xC
    int mMinExcitement; // offset 0x68, size 0x4
    int mMaxExcitement; // offset 0x6C, size 0x4
    class ObjPtr mTrigger; // offset 0x70, size 0xC
    float mFadeInTime; // offset 0x7C, size 0x4
    unsigned char mManual; // offset 0x80, size 0x1
    class ObjVector mSpotlightState; // offset 0x84, size 0x10
    class vector mEnvironmentState; // offset 0x94, size 0xC
    class vector mLightState; // offset 0xA0, size 0xC
    class vector mSpotlightDrawerState; // offset 0xAC, size 0xC
    const struct Keyframe * mLastKeyframe; // offset 0xB8, size 0x4
    float mLastBlend; // offset 0xBC, size 0x4
    float mStartBeat; // offset 0xC0, size 0x4
    float mManualFrameStart; // offset 0xC4, size 0x4
    int mManualFrame; // offset 0xC8, size 0x4
    int mLastManualFrame; // offset 0xCC, size 0x4
    float mManualFadeTime; // offset 0xD0, size 0x4
    float mCachedDuration; // offset 0xD4, size 0x4
    unsigned char mLocked; // offset 0xD8, size 0x1
    class LightHue * mHue; // offset 0xDC, size 0x4
    struct _SpotlightEntryCompressedInternal * storageSpace; // offset 0xE0, size 0x4
    class ObjPtr mBacklightEvent; // offset 0xE4, size 0xC
    struct LightPresetTarget * mTargets[6]; // offset 0xF0, size 0x18
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class LightPreset * mPtr; // offset 0x8, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class LightHue * mPtr; // offset 0x8, size 0x4
};
struct PresetOverride {
    // total size: 0x18
    class ObjPtr preset; // offset 0x0, size 0xC
    class ObjPtr hue; // offset 0xC, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct BitmapOverride {
    // total size: 0x18
    class ObjPtr original; // offset 0x0, size 0xC
    class ObjPtr replacement; // offset 0xC, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct MatOverride {
    // total size: 0x24
    class ObjPtr mesh; // offset 0x0, size 0xC
    class ObjPtr mat; // offset 0xC, size 0xC
    class ObjPtr origMat; // offset 0x18, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
class ShotTarget {
    // total size: 0x10
protected:
    class ObjPtr mEntity; // offset 0x0, size 0xC
    class Symbol mPartName; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ShotTarget * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ShotTarget * _M_start; // offset 0x0, size 0x4
    class ShotTarget * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class CamShotFrame {
    // total size: 0x120
public:
    float mDuration; // offset 0x0, size 0x4
    float mBlend; // offset 0x4, size 0x4
    float mBlendEase; // offset 0x8, size 0x4
    float mFrame; // offset 0xC, size 0x4
    float mFieldOfView; // offset 0x10, size 0x4
    float mZoomFOV; // offset 0x14, size 0x4
    class Transform mWorldOffset; // offset 0x20, size 0x40
    class Vector2 mScreenOffset; // offset 0x60, size 0x8
    float mTargetNoiseFreq; // offset 0x68, size 0x4
    float mTargetNoiseAmp; // offset 0x6C, size 0x4
    class Vector2 mMaxAngularOffset; // offset 0x70, size 0x8
    float mBlurDepth; // offset 0x78, size 0x4
    float mMaxBlur; // offset 0x7C, size 0x4
    float mMinBlur; // offset 0x80, size 0x4
    float mFocusedFocalPlaneMultiplier; // offset 0x84, size 0x4
    class ObjVector mTargets; // offset 0x88, size 0x10
    class Vector3 mLastTargetPos; // offset 0xA0, size 0x10
    class ShotTarget mParent; // offset 0xB0, size 0x10
    class Transform mLastParentPos; // offset 0xC0, size 0x40
    class ShotTarget mFocusTarget; // offset 0x100, size 0x10
    unsigned char mUseParentRotation; // offset 0x110, size 0x1
    class CamShot * mCamShot; // offset 0x114, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class CamShotFrame * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class CamShotFrame * _M_start; // offset 0x0, size 0x4
    class CamShotFrame * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Keys : public vector {
    // total size: 0xC
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndTransAnim * mPtr; // offset 0x8, size 0x4
};
class RndTransAnim : public RndAnimatable {
    // total size: 0x80
protected:
    class ObjPtr mTrans; // offset 0x10, size 0xC
    unsigned char mTransSpline; // offset 0x1C, size 0x1
    unsigned char mScaleSpline; // offset 0x1D, size 0x1
    unsigned char mRotSlerp; // offset 0x1E, size 0x1
    unsigned char mRotSpline; // offset 0x1F, size 0x1
    class Keys mRotKeys; // offset 0x20, size 0xC
    class Keys mTransKeys; // offset 0x2C, size 0xC
    class Keys mScaleKeys; // offset 0x38, size 0xC
    class ObjOwnerPtr mKeysOwner; // offset 0x44, size 0xC
    unsigned char mRepeatTrans; // offset 0x50, size 0x1
    unsigned char mFollowPath; // offset 0x51, size 0x1
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndTransAnim * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class Character * mPtr; // offset 0x8, size 0x4
};
class CharDef {
    // total size: 0x18
public:
    class ObjPtr mChar; // offset 0x0, size 0xC
    float mHeight; // offset 0xC, size 0x4
    float mDensity; // offset 0x10, size 0x4
    float mRadius; // offset 0x14, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0x50
public:
    class Transform _M_data; // offset 0x10, size 0x40
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class RndMultiMesh : public RndDrawable {
    // total size: 0x80
protected:
    class ObjPtr mMesh; // offset 0x34, size 0xC
    class list mTransforms; // offset 0x40, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct pair * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct pair * _M_start; // offset 0x0, size 0x4
    struct pair * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct CharData {
    // total size: 0x3C
    class CharDef mDef; // offset 0x0, size 0x18
    class RndMultiMesh * mMMesh; // offset 0x18, size 0x4
    class list mBackup; // offset 0x1C, size 0x8
    class vector m3DChars; // offset 0x24, size 0xC
    class vector m3DCharsCreated; // offset 0x30, size 0xC
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
enum CrowdRotate {
    kCrowdRotateNone = 0,
    kCrowdRotateFace = 1,
    kCrowdRotateAway = 2,
};
struct pair {
    // total size: 0x8
    int first; // offset 0x0, size 0x4
    int second; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct pair * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct pair * _M_start; // offset 0x0, size 0x4
    struct pair * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class WorldCrowd : public RndDrawable, public RndPollable {
    // total size: 0xD0
protected:
    class ObjPtr mPlacementMesh; // offset 0x3C, size 0xC
    class ObjList mChars; // offset 0x48, size 0xC
    int mNum; // offset 0x54, size 0x4
    enum CrowdRotate mRotate; // offset 0x58, size 0x4
    class Vector3 mCenter; // offset 0x60, size 0x10
    unsigned char m3DOnly; // offset 0x70, size 0x1
    float mCharFullness; // offset 0x74, size 0x4
    float mFlatFullness; // offset 0x78, size 0x4
    int mLod; // offset 0x7C, size 0x4
    class ObjPtr mImposterEnviron; // offset 0x80, size 0xC
    int mModifyStamp; // offset 0x8C, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class WorldCrowd * mPtr; // offset 0x8, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class Spotlight * mPtr; // offset 0x8, size 0x4
};
class CamShot : public RndAnimatable {
    // total size: 0x1B0
protected:
    class ObjVector mKeyframes; // offset 0x10, size 0x10
    unsigned char mLooping; // offset 0x20, size 0x1
    int mLoopKeyframe; // offset 0x24, size 0x4
    float mNear; // offset 0x28, size 0x4
    float mFar; // offset 0x2C, size 0x4
    unsigned char mDepthOfField; // offset 0x30, size 0x1
    float mFilter; // offset 0x34, size 0x4
    float mClampHeight; // offset 0x38, size 0x4
    float mFadeTime; // offset 0x3C, size 0x4
    class Symbol mCategory; // offset 0x40, size 0x4
    float mWeight; // offset 0x44, size 0x4
    class ObjPtr mPath; // offset 0x48, size 0xC
    float mPathEase; // offset 0x54, size 0x4
    enum Platform mPlatformOnly; // offset 0x58, size 0x4
    class ObjPtrList mHideList; // offset 0x5C, size 0x14
    class ObjPtrList mShowList; // offset 0x70, size 0x14
    class ObjPtrList mDrawOverrides; // offset 0x84, size 0x14
    class ObjPtrList mPostProcOverrides; // offset 0x98, size 0x14
    class ObjPtr mCrowd; // offset 0xAC, size 0xC
    enum CrowdRotate mCrowdRotate; // offset 0xB8, size 0x4
    unsigned char mPS3PerPixel; // offset 0xBC, size 0x1
    class vector mCrowdList; // offset 0xC0, size 0xC
    class ObjPtr mGlowSpot; // offset 0xCC, size 0xC
    int mFlags; // offset 0xD8, size 0x4
    class ObjPtrList mEndHideList; // offset 0xDC, size 0x14
    class ObjPtrList mEndShowList; // offset 0xF0, size 0x14
    class Vector3 mLastShakeOffset; // offset 0x110, size 0x10
    class Vector3 mLastShakeAngOffset; // offset 0x120, size 0x10
    class Vector3 mLastDesiredShakeOffset; // offset 0x130, size 0x10
    class Vector3 mLastDesiredShakeAngOffset; // offset 0x140, size 0x10
    class Vector3 mShakeVelocity; // offset 0x150, size 0x10
    class Vector3 mShakeAngVelocity; // offset 0x160, size 0x10
    class CamShotFrame * mLastNext; // offset 0x170, size 0x4
    class CamShotFrame * mLastPrev; // offset 0x174, size 0x4
    float mCachedDuration; // offset 0x178, size 0x4
    unsigned char mEnabled; // offset 0x17C, size 0x1
    unsigned char mFirstFrame; // offset 0x17D, size 0x1
    unsigned char mEnded; // offset 0x17E, size 0x1
    unsigned char mHided; // offset 0x17F, size 0x1
    unsigned char mTargetExists; // offset 0x180, size 0x1
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
struct hash {
    // total size: 0x1
};
struct equal_to : public binary_function {
    // total size: 0x1
};
struct unary_function {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
struct pair {
    // total size: 0xC
    class Symbol first; // offset 0x0, size 0x4
    class list second; // offset 0x4, size 0x8
};
struct _Select1st : public unary_function {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
struct _Slist_node_base {
    // total size: 0x4
    struct _Slist_node_base * _M_next; // offset 0x0, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct _Slist_node_base _M_data; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _Slist_base {
    // total size: 0x4
public:
    class _STLP_alloc_proxy _M_head; // offset 0x0, size 0x4
};
class slist : protected _Slist_base {
    // total size: 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct _Slist_node_base * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct _Slist_node_base * * _M_start; // offset 0x0, size 0x4
    struct _Slist_node_base * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class hashtable {
    // total size: 0x1C
    struct hash _M_hash; // offset 0x0, size 0x1
    struct equal_to _M_equals; // offset 0x1, size 0x1
    struct _Select1st _M_get_key; // offset 0x2, size 0x1
    class slist _M_elems; // offset 0x4, size 0x4
    class vector _M_buckets; // offset 0x8, size 0xC
    unsigned long _M_num_elements; // offset 0x14, size 0x4
    float _M_max_load_factor; // offset 0x18, size 0x4
};
class hash_map {
    // total size: 0x1C
    class hashtable _M_ht; // offset 0x0, size 0x1C
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CamShot * mPtr; // offset 0x8, size 0x4
};
class CameraManager {
    // total size: 0x44
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class WorldDir * mParent; // offset 0x4, size 0x4
    class hash_map mCameraShotCategories; // offset 0x8, size 0x1C
    class ObjPtr mNextShot; // offset 0x24, size 0xC
    class ObjPtr mCurrentCam; // offset 0x30, size 0xC
    float mCamStartTime; // offset 0x3C, size 0x4
    class FreeCamera * mFreeCam; // offset 0x40, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class LightPreset * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class LightPreset * * _M_start; // offset 0x0, size 0x4
    class LightPreset * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct unary_function {
    // total size: 0x1
};
struct pair {
    // total size: 0x10
    class Symbol first; // offset 0x0, size 0x4
    class vector second; // offset 0x4, size 0xC
};
struct _Select1st : public unary_function {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct _Slist_node_base _M_data; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _Slist_base {
    // total size: 0x4
public:
    class _STLP_alloc_proxy _M_head; // offset 0x0, size 0x4
};
class slist : protected _Slist_base {
    // total size: 0x4
};
class hashtable {
    // total size: 0x1C
    struct hash _M_hash; // offset 0x0, size 0x1
    struct equal_to _M_equals; // offset 0x1, size 0x1
    struct _Select1st _M_get_key; // offset 0x2, size 0x1
    class slist _M_elems; // offset 0x4, size 0x4
    class vector _M_buckets; // offset 0x8, size 0xC
    unsigned long _M_num_elements; // offset 0x14, size 0x4
    float _M_max_load_factor; // offset 0x18, size 0x4
};
class hash_map {
    // total size: 0x1C
    class hashtable _M_ht; // offset 0x0, size 0x1C
};
struct pair {
    // total size: 0x8
    class LightPreset * first; // offset 0x0, size 0x4
    float second; // offset 0x4, size 0x4
};
struct _Deque_iterator_base {
    // total size: 0x10
    struct pair * _M_cur; // offset 0x0, size 0x4
    struct pair * _M_first; // offset 0x4, size 0x4
    struct pair * _M_last; // offset 0x8, size 0x4
    struct pair * * _M_node; // offset 0xC, size 0x4
};
struct _Deque_iterator : public _Deque_iterator_base {
    // total size: 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct pair * * _M_data; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned long _M_data; // offset 0x0, size 0x4
};
class _Deque_base {
    // total size: 0x28
protected:
    struct _Deque_iterator _M_start; // offset 0x0, size 0x10
    struct _Deque_iterator _M_finish; // offset 0x10, size 0x10
    class _STLP_alloc_proxy _M_map; // offset 0x20, size 0x4
    class _STLP_alloc_proxy _M_map_size; // offset 0x24, size 0x4
};
class deque : protected _Deque_base {
    // total size: 0x28
};
class LightPresetManager {
    // total size: 0x90
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class vector mPool; // offset 0x4, size 0xC
    class LightPreset * * mPoolIter; // offset 0x10, size 0x4
    class hash_map mPresets; // offset 0x14, size 0x1C
    class vector mCategories; // offset 0x30, size 0xC
    class vector mAdjectives; // offset 0x3C, size 0xC
    int mExcitement; // offset 0x48, size 0x4
    class WorldDir * mParent; // offset 0x4C, size 0x4
    class LightPreset * mCurrentPreset; // offset 0x50, size 0x4
    class LightPreset * mOverridePreset; // offset 0x54, size 0x4
    float mPresetStartTime; // offset 0x58, size 0x4
    float mLastPresetStartTime; // offset 0x5C, size 0x4
    class LightPreset * mLastPreset; // offset 0x60, size 0x4
    class deque mScheduledPresets; // offset 0x64, size 0x28
    unsigned char mLastFrameSame; // offset 0x8C, size 0x1
    unsigned char mIgnoreLightingEvents; // offset 0x8D, size 0x1
};
class WorldDir : public PanelDir {
    // total size: 0x450
    enum TaskUnits mBlurUnits; // offset 0x24C, size 0x4
    float mBlurEndTime; // offset 0x250, size 0x4
    float mBlurGrow; // offset 0x254, size 0x4
    float mBlurRampOut; // offset 0x258, size 0x4
    class Rect mBlurRect; // offset 0x25C, size 0x10
    class RndMat * mBlurMat; // offset 0x26C, size 0x4
    class RndTex * mBlurTex; // offset 0x270, size 0x4
    float mBlurStartAlpha; // offset 0x274, size 0x4
    float mBlurCurAlpha; // offset 0x278, size 0x4
    class ObjList mPresetOverrides; // offset 0x27C, size 0xC
    class ObjList mBitmapOverrides; // offset 0x288, size 0xC
    class ObjList mMatOverrides; // offset 0x294, size 0xC
    class ObjPtrList mHideOverrides; // offset 0x2A0, size 0x14
    class ObjPtrList mCamShotOverrides; // offset 0x2B4, size 0x14
    class ObjPtrList mPS3PerPixelShows; // offset 0x2C8, size 0x14
    class ObjPtrList mPS3PerPixelHides; // offset 0x2DC, size 0x14
    class ObjPtrList mCrowds; // offset 0x2F0, size 0x14
    class RndMat * mGlowMat; // offset 0x304, size 0x4
    class FilePath mHudFilename; // offset 0x308, size 0xC
    class RndDir * mHudDir; // offset 0x314, size 0x4
    unsigned char mShowHud; // offset 0x318, size 0x1
    class CameraManager mCameraManager; // offset 0x31C, size 0x44
    class LightPresetManager mPresetManager; // offset 0x360, size 0x90
    unsigned char mEchoMsgs; // offset 0x3F0, size 0x1
    float mDeltaSincePoll[4]; // offset 0x3F4, size 0x10
    unsigned char mFirstPoll; // offset 0x404, size 0x1
    float mLastRndTime; // offset 0x408, size 0x4
    class RndDrawable * * mDrawItr; // offset 0x40C, size 0x4
    class RndGroup * mCrowdGroup; // offset 0x410, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
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
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct pair * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct pair * _M_start; // offset 0x0, size 0x4
    struct pair * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct SongRanking {
    // total size: 0x28
    class Symbol mInstrument; // offset 0x0, size 0x4
    class vector mAllSongs; // offset 0x4, size 0xC
    class vector mCoreSongs; // offset 0x10, size 0xC
    class vector mTierRanges; // offset 0x1C, size 0xC
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
struct Item {
    // total size: 0x8
    class Symbol mName; // offset 0x0, size 0x4
    int mLastPlayed; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Item * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Item * _M_start; // offset 0x0, size 0x4
    struct Item * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Jukebox {
    // total size: 0x10
    class vector mItems; // offset 0x0, size 0xC
    int mNumPlayed; // offset 0xC, size 0x4
};
class DataLoader : public Loader {
    // total size: 0x34
    class DataArray * mData; // offset 0x14, size 0x4
    class File * mFile; // offset 0x18, size 0x4
    class String mFilename; // offset 0x1C, size 0xC
    int mBufLen; // offset 0x28, size 0x4
    char * mBuffer; // offset 0x2C, size 0x4
    unsigned char mDtb; // offset 0x30, size 0x1
};
enum SongType {
    kSongAll = 0,
    kSongCoreOnly = 1,
};
enum MissingPartType {
    kMissingSelectCoop = 0,
    kMissingSelectH2H = 1,
    kMissingRankedH2H = 2,
    kMissingJukebox = 3,
};
class BufStream : public BinStream {
    // total size: 0x24
    char * mBuffer; // offset 0xC, size 0x4
    unsigned char mFail; // offset 0x10, size 0x1
    int mTell; // offset 0x14, size 0x4
    int mSize; // offset 0x18, size 0x4
    class StreamChecksum * mChecksum; // offset 0x1C, size 0x4
    int mBytesChecksummed; // offset 0x20, size 0x4
};
class SongMgr : public Object, public Callback {
    // total size: 0x80
protected:
    class DataArray * mSongs; // offset 0x2C, size 0x4
    class DataArray * mMissingSongData; // offset 0x30, size 0x4
    class map mSongLookup; // offset 0x34, size 0x18
    class list mSongRankings; // offset 0x4C, size 0x8
    class vector mSharedSongs; // offset 0x54, size 0xC
    class vector mSharedUnlocked; // offset 0x60, size 0xC
private:
    class Jukebox mSongJuke; // offset 0x6C, size 0x10
    unsigned char mRandomSongDebug; // offset 0x7C, size 0x1
};

