/*
    Compile unit: C:\rockband2\system\src\obj\DirLoader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805EA348 -> 0x805ED0E8
*/
unsigned char sPrintTimes; // size: 0x1, address: 0x80A54F88
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x805EA348 -> 0x805EA420
class DirLoader * DirLoader::Find(const class FilePath & file /* r29 */) {
    // Local variables
    const class list & l; // r30
    struct _List_iterator i; // r1+0x18
    class DirLoader * dl; // r0

    // References
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x805EA420 -> 0x805EA498
class ObjectDir * DirLoader::GetDir(class DirLoader * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805EA498 -> 0x805EA50C
class ObjectDir * DirLoader::LoadObjects(const class FilePath & file /* r0 */) {
    // Local variables
    class DirLoader l; // r1+0x8

    // References
    // -> class LoadMgr TheLoadMgr;
}

enum FileType {
    kRead = 0,
    kWrite = 1,
};
struct ChunkInfo {
    // total size: 0x810
    int mID; // offset 0x0, size 0x4
    int mChunkInfoSize; // offset 0x4, size 0x4
    int mNumChunks; // offset 0x8, size 0x4
    int mMaxChunkSize; // offset 0xC, size 0x4
    int mChunks[512]; // offset 0x10, size 0x800
};
class ChunkStream : public BinStream {
    // total size: 0x8A0
    class File * mFile; // offset 0xC, size 0x4
    class String mFilename; // offset 0x10, size 0xC
    unsigned char mFail; // offset 0x1C, size 0x1
    enum FileType mType; // offset 0x20, size 0x4
    struct ChunkInfo mChunkInfo; // offset 0x24, size 0x810
    int mCurBufSize; // offset 0x834, size 0x4
    char * mBuffers[2]; // offset 0x838, size 0x8
    char * mCurReadBuffer; // offset 0x840, size 0x4
    class Timer mStartTime; // offset 0x848, size 0x38
    int mRecommendedChunkSize; // offset 0x880, size 0x4
    int mCurBufferIdx; // offset 0x884, size 0x4
    unsigned char mCurBufferReady; // offset 0x888, size 0x1
    int mCurBufOffset; // offset 0x88C, size 0x4
    unsigned char mChunkInfoPending; // offset 0x890, size 0x1
    int * mCurChunk; // offset 0x894, size 0x4
    int * mChunkEnd; // offset 0x898, size 0x4
};
// Range: 0x805EA50C -> 0x805EA5D0
class Symbol DirLoader::GetDirClass() {
    // Local variables
    class ChunkStream d; // r1+0x20
    int rev; // r1+0x18
    class Symbol name; // r1+0x14

    // References
    // -> const char * gNullStr;
}

static unsigned char testedDirSort; // size: 0x1, address: 0x80A54F89
struct ClassAndNameSort {
    // total size: 0x4
protected:
    class DataArray * mClassNames; // offset 0x0, size 0x4
};
// Range: 0x805EA5D0 -> 0x805EACF0
void DirLoader::SaveObjects(class BinStream & d /* r28 */, class ObjectDir * dir /* r29 */, const char * path /* r25 */) {
    // Local variables
    class list objects; // r1+0xA8
    class ObjDirItr i; // r1+0xB0
    class DataArray * sort; // r25
    int i; // r26
    class Symbol c; // r1+0x88
    struct _List_iterator j; // r1+0x84
    class ObjectDir * od; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> class Debug TheDebug;
    // -> static unsigned char testedDirSort;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x805EACF0 -> 0x805EAD34
static unsigned char LittleEndian() {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x805EAD5C -> 0x805EAE7C
void * DirLoader::DirLoader(class DirLoader * const this /* r31 */, class Callback * callback /* r27 */, class BinStream * stream /* r30 */, class ObjectDir * proxy /* r28 */) {
    // References
    // -> struct [anonymous] __vt__36ObjPtrList<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__9DirLoader;
}

// Range: 0x805EAE7C -> 0x805EAEB0
unsigned char DirLoader::IsLoaded() {}

// Range: 0x805EAEB0 -> 0x805EAFF4
void DirLoader::PollLoading(class DirLoader * const this /* r31 */) {
    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class LoadMgr TheLoadMgr;
}

static class Symbol CompositeTexture; // size: 0x4, address: 0x80A54F8C
static class Symbol RenderedTex; // size: 0x4, address: 0x80A54F94
static class Symbol TexRenderer; // size: 0x4, address: 0x80A54F9C
static class Symbol LayerDir; // size: 0x4, address: 0x80A54FA4
static class Symbol WorldFx; // size: 0x4, address: 0x80A54FAC
static class Symbol BandFx; // size: 0x4, address: 0x80A54FB4
static class Symbol Slider; // size: 0x4, address: 0x80A54FBC
static class Symbol BandSlider; // size: 0x4, address: 0x80A54FC4
static class Symbol TextEntry; // size: 0x4, address: 0x80A54FCC
static class Symbol BandTextEntry; // size: 0x4, address: 0x80A54FD4
static class Symbol Placer; // size: 0x4, address: 0x80A54FDC
static class Symbol BandPlacer; // size: 0x4, address: 0x80A54FE4
static class Symbol ButtonEx; // size: 0x4, address: 0x80A54FEC
static class Symbol BandButton; // size: 0x4, address: 0x80A54FF4
static class Symbol LabelEx; // size: 0x4, address: 0x80A54FFC
static class Symbol BandLabel; // size: 0x4, address: 0x80A55004
static class Symbol PictureEx; // size: 0x4, address: 0x80A5500C
static class Symbol BandPicture; // size: 0x4, address: 0x80A55014
static class Symbol UIPanel; // size: 0x4, address: 0x80A5501C
static class Symbol PanelDir; // size: 0x4, address: 0x80A55024
static class Symbol WorldInstance; // size: 0x4, address: 0x80A5502C
static class Symbol WorldObject; // size: 0x4, address: 0x80A55034
static class Symbol Group; // size: 0x4, address: 0x80A5503C
static class Symbol View; // size: 0x4, address: 0x80A55044
static class Symbol String; // size: 0x4, address: 0x80A5504C
static class Symbol Line; // size: 0x4, address: 0x80A55054
static class Symbol MeshGenerator; // size: 0x4, address: 0x80A5505C
static class Symbol Generator; // size: 0x4, address: 0x80A55064
static class Symbol TexMovie; // size: 0x4, address: 0x80A5506C
static class Symbol Movie; // size: 0x4, address: 0x80A55074
// Range: 0x805EAFF4 -> 0x805EB5F4
class Symbol DirLoader::FixClassName(class DirLoader * const this /* r29 */, class Symbol & c /* r30 */) {
    // References
    // -> static class Symbol Movie;
    // -> static class Symbol TexMovie;
    // -> static class Symbol Generator;
    // -> static class Symbol MeshGenerator;
    // -> static class Symbol Line;
    // -> static class Symbol String;
    // -> static class Symbol View;
    // -> static class Symbol Group;
    // -> static class Symbol WorldObject;
    // -> static class Symbol WorldInstance;
    // -> static class Symbol PanelDir;
    // -> static class Symbol UIPanel;
    // -> static class Symbol BandPicture;
    // -> static class Symbol PictureEx;
    // -> static class Symbol BandLabel;
    // -> static class Symbol LabelEx;
    // -> static class Symbol BandButton;
    // -> static class Symbol ButtonEx;
    // -> static class Symbol BandPlacer;
    // -> static class Symbol Placer;
    // -> static class Symbol BandTextEntry;
    // -> static class Symbol TextEntry;
    // -> static class Symbol BandSlider;
    // -> static class Symbol Slider;
    // -> static class Symbol BandFx;
    // -> static class Symbol WorldFx;
    // -> static class Symbol LayerDir;
    // -> static class Symbol TexRenderer;
    // -> static class Symbol RenderedTex;
    // -> static class Symbol CompositeTexture;
}

// Range: 0x805EB5F4 -> 0x805EB800
void DirLoader::OpenFile(class DirLoader * const this /* r31 */) {
    // Local variables
    const char * file; // r28

    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
}

// Range: 0x805EB800 -> 0x805EB9C4
unsigned char DirLoader::SetupDir(class DirLoader * const this /* r29 */, class Symbol & className /* r30 */) {
    // Local variables
    class ObjectDir * newDir; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> class Debug TheDebug;
}

// Range: 0x805EB9C4 -> 0x805EBDB8
void DirLoader::LoadHeader(class DirLoader * const this /* r30 */) {
    // Local variables
    class Symbol defaultDir; // r1+0x40
    class Symbol className; // r1+0x3C
    char name[128]; // r1+0x50
    int hashSize; // r1+0x38
    int stringSize; // r1+0x34
    class Symbol streamType; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__8FilePath;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x805EBDB8 -> 0x805EC164
void DirLoader::CreateObjects(class DirLoader * const this /* r30 */) {
    // Local variables
    class Symbol className; // r1+0x28
    char name[128]; // r1+0x30
    class Object * object; // r28

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class LoadMgr TheLoadMgr;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

// Range: 0x805EC164 -> 0x805EC2C0
void DirLoader::LoadResources(class DirLoader * const this /* r28 */) {
    // Local variables
    class FilePathTracker _fptracker; // r1+0x14
    class FilePath resource; // r1+0x8

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x805EC2C0 -> 0x805EC36C
static void ReadDead(class BinStream & d /* r31 */) {
    // Local variables
    unsigned char c; // r1+0x8
}

// Range: 0x805EC36C -> 0x805EC4EC
void DirLoader::LoadDir(class DirLoader * const this /* r31 */) {
    // Local variables
    class FilePathTracker _fptracker; // r1+0xC
    unsigned char old; // r29

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x805EC4EC -> 0x805EC9A8
void DirLoader::LoadObjs(class DirLoader * const this /* r30 */) {
    // Local variables
    class FilePathTracker _fptracker; // r1+0x14

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class LoadMgr TheLoadMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x805EC9A8 -> 0x805EC9AC
void DirLoader::DoneLoading() {}

// Range: 0x805EC9AC -> 0x805ECA60
void DirLoader::Replace(class DirLoader * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805ECA60 -> 0x805ECE5C
void DirLoader::Cleanup(class DirLoader * const this /* r31 */) {
    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__8FilePath;
    // -> unsigned char sPrintTimes;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x805ECE5C -> 0x805ED0E8
void * DirLoader::~DirLoader(class DirLoader * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__9DirLoader;
}

struct {
    // total size: 0x34
} __vt__9DirLoader; // size: 0x34, address: 0x809296B0

