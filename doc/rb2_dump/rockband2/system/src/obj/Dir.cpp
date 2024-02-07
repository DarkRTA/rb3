/*
    Compile unit: C:\rockband2\system\src\obj\Dir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805E0D14 -> 0x805E721C
*/
class DataArray * types; // size: 0x4, address: 0x80A54EC8
const char * kNotObjectMsg; // size: 0x4, address: 0x80A47A08
class ObjectDir * sMainDir; // size: 0x4, address: 0x80A54ED0
static class ObjectDir * gDir; // size: 0x4, address: 0x80A54ED4
// Range: 0x805E0D14 -> 0x805E0D6C
void ObjectDir::Reserve(class ObjectDir * const this /* r30 */, int stringSize /* r31 */) {}

// Range: 0x805E0D6C -> 0x805E0D78
void ObjectDir::SetCurViewport() {}

// Range: 0x805E0D78 -> 0x805E0DF8
class Viewport & ObjectDir::CurViewport(class ObjectDir * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

static class Message msg; // size: 0x8, address: 0x809894B0
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x805E0DF8 -> 0x805E107C
void ObjectDir::SyncObjects(class ObjectDir * const this /* r31 */) {
    // Local variables
    class vector dirs; // r1+0x30
    int i; // r28
    int which; // r1+0x1C
    class ObjectDir * d; // r1+0x18

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
}

class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjectDir * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjectDir * * _M_start; // offset 0x0, size 0x4
    class ObjectDir * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x805E107C -> 0x805E10E0
void ObjectDir::SetSubDir(class ObjectDir * const this /* r31 */) {}

// Range: 0x805E10E0 -> 0x805E11E8
void ObjectDir::Save(class ObjectDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class FilePath sRoot;
}

// Range: 0x805E11E8 -> 0x805E12D0
void ObjectDir::SaveProxy(class ObjectDir * const this /* r28 */, class BinStream & d /* r29 */) {
    // Local variables
    class FilePathTracker _fptracker; // r1+0x8

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> unsigned char gLoadingProxyFromDisk;
}

// Range: 0x805E12D0 -> 0x805E1374
void ObjectDir::Load(class ObjectDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    class Loader * l; // r4

    // References
    // -> class LoadMgr TheLoadMgr;
}

static int gRev; // size: 0x4, address: 0x80A54EDC
// Range: 0x805E1374 -> 0x805E1480
class BinStream & __rs(class BinStream & d /* r30 */, class Viewport & c /* r31 */) {
    // Local variables
    float xfov; // r1+0x8

    // References
    // -> static int gRev;
}

static class DataArray * remaps; // size: 0x4, address: 0x80A54EE0
static class vector subDirs; // size: 0xC, address: 0x809894C4
static class DataArray * remaps; // size: 0x4, address: 0x80A54EE8
// Range: 0x805E1480 -> 0x805E25EC
void ObjectDir::PreLoad(class ObjectDir * const this /* r27 */, class BinStream & d /* r28 */) {
    // Local variables
    int hashSize; // r1+0x4C
    int stringSize; // r1+0x48
    class FilePath proxyFile; // r1+0x80
    class FilePath p; // r1+0x74
    class DataArray * arg; // r25
    char buf[128]; // r1+0x190
    char buf[128]; // r1+0x110
    char buf[128]; // r1+0x90
    int i; // r29
    class DataArray * arg; // r26
    int i; // r25
    unsigned int i; // r30
    unsigned int i; // r30
    int inlineProxy; // r1+0x44

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> const char * kAssertStr;
    // -> class FilePath sNull;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> static class DataArray * remaps;
    // -> static class vector subDirs;
    // -> static class DataArray * remaps;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

static class Message msg; // size: 0x8, address: 0x809894E0
// Range: 0x805E25EC -> 0x805E2A70
void ObjectDir::PostLoad(class ObjectDir * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int i; // r31
    char buf[128]; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class LoadMgr TheLoadMgr;
    // -> static int gRev;
    // -> class list sRevs;
}

// Range: 0x805E2A70 -> 0x805E2AC8
void ObjectDir::TransferLoaderState(class ObjectDir * const this /* r30 */, class ObjectDir * dir /* r31 */) {}

// Range: 0x805E2AC8 -> 0x805E2BAC
void ObjectDir::SetProxyFile(class ObjectDir * const this /* r30 */, unsigned char override /* r31 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class Debug TheDebug;
}

// Range: 0x805E2BAC -> 0x805E2CF8
void ObjectDir::Copy(class ObjectDir * const this /* r30 */, const class Object * o /* r31 */, enum CopyType type /* r29 */) {
    // Local variables
    const class ObjectDir * m; // r0
    int i; // r29
    int i; // r29

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
}

// Range: 0x805E2CF8 -> 0x805E2E38
class Object * ObjectDir::FindObject(class ObjectDir * const this /* r27 */, const char * name /* r28 */, unsigned char parentDirs /* r29 */) {
    // Local variables
    struct Entry * entry; // r0
    int i; // r30
    class Object * o; // r0

    // References
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805E2E38 -> 0x805E2E74
void ObjectDir::RemovingObject() {}

// Range: 0x805E2E74 -> 0x805E314C
void ObjectDir::AddedSubDir(class ObjectDir * const this /* r31 */, class ObjectDir * dir /* r30 */) {
    // Local variables
    class ObjDirItr i; // r1+0x18
}

// Range: 0x805E314C -> 0x805E3400
void ObjectDir::RemovingSubDir(class ObjectDir * const this /* r31 */) {
    // Local variables
    class ObjDirItr i; // r1+0x18
}

// Range: 0x805E3400 -> 0x805E35E8
void * ObjectDir::ObjectDir(class ObjectDir * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ29ObjectDir8Viewport;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__9ObjectDir;
}

struct {
    // total size: 0x8
} __RTTI__PQ29ObjectDir8Viewport; // size: 0x8, address: 0x80928B28
// Range: 0x805E35E8 -> 0x805E3758
void ObjectDir::ResetEditorState(class ObjectDir * const this /* r31 */) {}

// Range: 0x805E3758 -> 0x805E3970
void ObjectDir::ResetViewports() {}

// Range: 0x805E3970 -> 0x805E3C40
void ObjectDir::DeleteObjects(class ObjectDir * const this /* r31 */) {
    // Local variables
    class ObjDirItr obj; // r1+0x18
}

// Range: 0x805E3C40 -> 0x805E3C6C
unsigned char ObjectDir::InlineProxy() {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x805E3C6C -> 0x805E3C74
unsigned char ObjectDir::AllowsInlineProxy() {}

// Range: 0x805E3C74 -> 0x805E4058
void * ObjectDir::~ObjectDir(class ObjectDir * const this /* r28 */) {
    // References
    // -> const char * gNullStr;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__9ObjectDir;
}

// Range: 0x805E4058 -> 0x805E40F0
struct Entry * ObjectDir::FindEntry(class ObjectDir * const this /* r30 */, const char * name /* r1+0x8 */, unsigned char add /* r31 */) {
    // Local variables
    struct Entry * entry; // r3
    struct Entry e; // r1+0x10
}

// Range: 0x805E40F0 -> 0x805E41A0
static class DataNode OnLoadObjects(class DataArray * msg /* r31 */) {
    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x805E41A0 -> 0x805E41F8
static class DataNode OnPathName(class DataArray * msg /* r31 */) {}

// Range: 0x805E41F8 -> 0x805E42B8
static class DataNode OnReserveToFit(class DataArray * msg /* r27 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
}

// Range: 0x805E42B8 -> 0x805E432C
static class DataNode OnTestDuplicateObjNames(class DataArray * msg /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
}

// Range: 0x805E432C -> 0x805E4384
static class DataNode OnInitObject(class DataArray * msg /* r31 */) {}

// Range: 0x805E4384 -> 0x805E4400
void ObjectDir::PreInit() {
    // References
    // -> class ObjectDir * sMainDir;
    // -> class Symbol name;
}

// Range: 0x805E4400 -> 0x805E4404
void ObjectDir::Terminate() {}

static class DataArray * objects; // size: 0x4, address: 0x80A54EF0
// Range: 0x805E4404 -> 0x805E493C
void ObjectDir::Iterate(class ObjectDir * const this /* r28 */, class DataArray * a /* r29 */, unsigned char subDirs /* r27 */) {
    // Local variables
    class Symbol className; // r1+0x4C
    class DataArray * na; // r26
    class DataNode val; // r1+0x60
    class ObjDirItr o; // r1+0x68
    int j; // r26

    // References
    // -> static class DataArray * objects;
    // -> const char * gNullStr;
}

// Range: 0x805E493C -> 0x805E49D0
unsigned char ObjectDir::HasDirPtrs(const class ObjectDir * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
}

static class Symbol _s; // size: 0x4, address: 0x80A54EF8
static class Symbol _s; // size: 0x4, address: 0x80A54F00
static class Symbol _s; // size: 0x4, address: 0x80A54F08
static class Symbol _s; // size: 0x4, address: 0x80A54F10
static class Symbol _s; // size: 0x4, address: 0x80A54F18
static class Symbol _s; // size: 0x4, address: 0x80A54F20
static class Symbol _s; // size: 0x4, address: 0x80A54F28
static class Symbol _s; // size: 0x4, address: 0x80A54F30
static class Symbol _s; // size: 0x4, address: 0x80A54F38
static class Symbol _s; // size: 0x4, address: 0x80A54F40
static class Symbol _s; // size: 0x4, address: 0x80A54F48
static class Symbol _s; // size: 0x4, address: 0x80A54F50
static class Symbol _s; // size: 0x4, address: 0x80A54F58
static class Symbol _s; // size: 0x4, address: 0x80A54F60
static class Symbol _s; // size: 0x4, address: 0x80A54F68
// Range: 0x805E49D0 -> 0x805E5C54
class DataNode ObjectDir::Handle(class ObjectDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x5C
    class MessageTimer _mt; // r1+0x90
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode _n; // r1+0x60

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x805E5C54 -> 0x805E6254
class DataNode ObjectDir::OnListObjs(class ObjectDir * const this /* r27 */, class DataArray * a /* r24 */) {
    // Local variables
    class Symbol class_name; // r1+0x38
    unsigned char no_null; // r0
    unsigned char subdir_only; // r0
    unsigned char curdir_only; // r0
    class DataArray * no_objs; // r29
    int idx; // r28
    class DataArrayPtr da; // r1+0x58
    class ObjDirItr i; // r1+0x60
    int i; // r24

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x805E6254 -> 0x805E6318
class DataNode ObjectDir::OnFind(class ObjectDir * const this /* r30 */, class DataArray * a /* r29 */) {
    // Local variables
    class Object * o; // r0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805E6318 -> 0x805E66E0
static class ObjectDir * SyncSubDir(const class FilePath & p /* r30 */) {
    // Local variables
    class Loader * l; // r0
    class DirLoader * dl; // r0
    class ObjectDir * dir; // r31
    class ObjDirItr o; // r1+0x24

    // References
    // -> static class ObjectDir * gDir;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x805E66E0 -> 0x805E6D94
unsigned char PropSyncSubDirs(class vector & s /* r28 */, class DataNode & n /* r29 */, class DataArray * prop /* r31 */, int i /* r30 */, enum PropOp op /* r27 */) {
    // Local variables
    class ObjDirPtr * it; // r30
    class ObjectDir * dir; // r31

    // References
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class ObjectDir * gDir;
    // -> class FilePath sRoot;
    // -> class FilePath sNull;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805E6D94 -> 0x805E6E38
void ObjectDir::SetPathName(class ObjectDir * const this /* r29 */, const char * path /* r30 */) {
    // References
    // -> const char * gNullStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A54F70
static class Symbol _s; // size: 0x4, address: 0x80A54F78
static class Symbol _s; // size: 0x4, address: 0x80A54F80
// Range: 0x805E6E38 -> 0x805E7128
unsigned char ObjectDir::SyncProperty(class ObjectDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class ObjectDir * gDir;
}

struct {
    // total size: 0xB0
} __vt__9ObjectDir; // size: 0xB0, address: 0x80928E50
// Range: 0x805E7128 -> 0x805E721C
struct Entry * KeylessHash::Find(class KeylessHash * const this /* r28 */, const char * const & key /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class DebugWarner _dw; // size: 0x100, address: 0x809894E8
struct {
    // total size: 0x8
} __RTTI__PP9ObjectDir; // size: 0x8, address: 0x80929108
struct {
    // total size: 0x8
} __RTTI__P21ObjDirPtr<9ObjectDir>; // size: 0x8, address: 0x80929128

