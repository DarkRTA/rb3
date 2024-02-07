/*
    Compile unit: C:\rockband2\system\src\utl\Loader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8060DFE0 -> 0x8060EFD4
*/
class LoadMgr TheLoadMgr; // size: 0x60, address: 0x80989ED8
// Range: 0x8060DFE0 -> 0x8060E080
void * LoadMgr::LoadMgr(class LoadMgr * const this /* r31 */) {}

struct pair {
    // total size: 0x10
    class String first; // offset 0x0, size 0xC
    class Loader * (* second)(class FilePath &, enum LoaderPos); // offset 0xC, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0x18
public:
    struct pair _M_data; // offset 0x8, size 0x10
};
static class DataNode & edit_mode; // size: 0x4, address: 0x80A55444
// Range: 0x8060E080 -> 0x8060E124
void LoadMgr::SetEditMode(class LoadMgr * const this /* r31 */) {
    // References
    // -> static class DataNode & edit_mode;
}

static class DataNode & cache_mode; // size: 0x4, address: 0x80A5544C
// Range: 0x8060E124 -> 0x8060E1C8
void LoadMgr::SetCacheMode(class LoadMgr * const this /* r31 */) {
    // References
    // -> static class DataNode & cache_mode;
}

// Range: 0x8060E1C8 -> 0x8060E238
static class DataNode OnSetCacheMode(class DataArray * a /* r31 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8060E238 -> 0x8060E2A8
static class DataNode OnSetEditMode(class DataArray * a /* r31 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8060E2A8 -> 0x8060E30C
static class DataNode OnSetLoaderPeriod(class DataArray * a /* r31 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8060E30C -> 0x8060E3C8
void LoadMgr::Init(class LoadMgr * const this /* r30 */) {
    // References
    // -> class Archive * TheArchive;
}

// Range: 0x8060E3C8 -> 0x8060E508
class Loader * LoadMgr::GetLoader(class LoadMgr * const this /* r27 */, const class FilePath & file /* r28 */, unsigned char force /* r29 */) {
    // Local variables
    class Loader * l; // r30
    struct _List_iterator i; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class LoadMgr TheLoadMgr;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8060E508 -> 0x8060E68C
class Loader * LoadMgr::AddLoader(class LoadMgr * const this /* r29 */, const class FilePath & file /* r30 */, enum LoaderPos pos /* r31 */) {
    // Local variables
    const char * ext; // r27
    struct _List_iterator i; // r1+0x10

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8060E68C -> 0x8060E774
void LoadMgr::PollUntilLoaded(class LoadMgr * const this /* r31 */, class Loader * l /* r1+0x8 */) {
    // Local variables
    float period; // f31
}

// Range: 0x8060E774 -> 0x8060E7DC
char * LoadMgr::CachedPath(const char * file /* r30 */) {}

static char * names[3]; // size: 0xC, address: 0x8092CC00
static char * abbrevs[4]; // size: 0x10, address: 0x8092CC10
// Range: 0x8060E7DC -> 0x8060E950
void LoadMgr::Poll(class LoadMgr * const this /* r31 */) {
    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x8060E950 -> 0x8060EA1C
void LoadMgr::RegisterFactory(class LoadMgr * const this /* r31 */, class Loader * (* fact)(class FilePath &, enum LoaderPos) /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std75_List_node<Q211stlpmtx_std46pair<6String,PFRC8FilePath9LoaderPos_P6Loader>>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std75_List_node<Q211stlpmtx_std46pair<6String,PFRC8FilePath9LoaderPos_P6Loader>>; // size: 0x8, address: 0x8092CCB0
// Range: 0x8060EA1C -> 0x8060EC44
void * Loader::Loader(class Loader * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x20

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6Loader>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__6Loader;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std20_List_node<P6Loader>; // size: 0x8, address: 0x8092CCE0
// Range: 0x8060EC44 -> 0x8060ED98
void * Loader::~Loader(class Loader * const this /* r30 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__6Loader;
}

// Range: 0x8060ED98 -> 0x8060EE3C
void * FileLoader::~FileLoader(class FileLoader * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__10FileLoader;
}

// Range: 0x8060EE3C -> 0x8060EE44
int FileLoader::GetSize() {}

// Range: 0x8060EE44 -> 0x8060EE54
unsigned char FileLoader::IsLoaded() {}

// Range: 0x8060EE54 -> 0x8060EF08
void FileLoader::PollLoading(class FileLoader * const this /* r30 */) {
    // Local variables
    int bytes; // r1+0x8
}

struct {
    // total size: 0x14
} __vt__10FileLoader; // size: 0x14, address: 0x8092CDEC
struct {
    // total size: 0x14
} __vt__6Loader; // size: 0x14, address: 0x8092CE20
// Range: 0x8060EF08 -> 0x8060EF50
static void __sinit_\Loader_cpp() {
    // References
    // -> class LoadMgr TheLoadMgr;
}


