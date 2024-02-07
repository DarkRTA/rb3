/*
    Compile unit: C:\rockband2\system\src\os\File.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805B058C -> 0x805B220C
*/
class vector : protected _Vector_base {
    // total size: 0xC
};
static class vector gFiles; // size: 0xC, address: 0x80984A9C
static class File * gOpenCaptureFile; // size: 0x4, address: 0x80A549C8
static char gRoot[256]; // size: 0x100, address: 0x80984AA8
static char gExecRoot[256]; // size: 0x100, address: 0x80984BA8
static char gSystemRoot[256]; // size: 0x100, address: 0x80984CA8
static unsigned char gUsingHolmes; // size: 0x1, address: 0x80A549CC
// Range: 0x805B058C -> 0x805B0598
char * FileRoot() {
    // References
    // -> static char gRoot[256];
}

// Range: 0x805B0598 -> 0x805B05A4
char * FileExecRoot() {
    // References
    // -> static char gExecRoot[256];
}

// Range: 0x805B05A4 -> 0x805B05B0
char * FileSystemRoot() {
    // References
    // -> static char gSystemRoot[256];
}

// Range: 0x805B05B0 -> 0x805B05BC
static class DataNode OnFileExecRoot() {
    // References
    // -> static char gExecRoot[256];
}

// Range: 0x805B05BC -> 0x805B05C8
static class DataNode OnFileRoot() {
    // References
    // -> static char gRoot[256];
}

// Range: 0x805B05C8 -> 0x805B0620
static class DataNode OnFileGetDrive(class DataArray * arg /* r31 */) {}

// Range: 0x805B0620 -> 0x805B0678
static class DataNode OnFileGetPath(class DataArray * arg /* r31 */) {}

// Range: 0x805B0678 -> 0x805B06D0
static class DataNode OnFileGetBase(class DataArray * arg /* r31 */) {}

// Range: 0x805B06D0 -> 0x805B0728
static class DataNode OnFileGetExt(class DataArray * arg /* r31 */) {}

// Range: 0x805B0728 -> 0x805B0864
static class DataNode OnWithFilePathRoot(class DataArray * arg /* r29 */) {
    // Local variables
    class FilePathTracker _fptracker; // r1+0x10
    int size; // r30
    int i; // r31

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x805B0864 -> 0x805B08C0
static class DataNode OnSynchProc() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805B08C0 -> 0x805B08D0
static class DataNode OnToggleFakeFileErrors() {}

// Range: 0x805B08D0 -> 0x805B0AC0
void FileInit() {
    // Local variables
    const char * file_order; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class File * gOpenCaptureFile;
    // -> class WiiRnd TheWiiRnd;
    // -> class FilePath sRoot;
    // -> static char gSystemRoot[256];
    // -> static char gExecRoot[256];
    // -> static char gRoot[256];
}

// Range: 0x805B0AC0 -> 0x805B0B24
void FileTerminate() {
    // References
    // -> static char gSystemRoot[256];
    // -> static char gExecRoot[256];
    // -> static char gRoot[256];
    // -> static class File * gOpenCaptureFile;
}

// Range: 0x805B0B24 -> 0x805B0D64
class File * NewFile(const char * iFilename /* r27 */, int iMode /* r28 */) {
    // Local variables
    class String strFile; // r1+0x8
    char buffer[256]; // r1+0x118
    class File * file; // r29
    char buf[256]; // r1+0x18

    // References
    // -> static class File * gOpenCaptureFile;
    // -> class Archive * TheArchive;
    // -> class Debug TheDebug;
}

// Range: 0x805B0D64 -> 0x805B0DB0
void FileQualifiedFilename(class String & oNewName /* r31 */, const char * iOldName /* r0 */) {
    // Local variables
    char tmp[256]; // r1+0x8
}

// Range: 0x805B0DB0 -> 0x805B0DB8
void SetFileUsingHolmes() {
    // References
    // -> static unsigned char gUsingHolmes;
}

// Range: 0x805B0DB8 -> 0x805B0DC0
unsigned char FileUsingHolmes() {
    // References
    // -> static unsigned char gUsingHolmes;
}

// Range: 0x805B0DC0 -> 0x805B0E2C
void FileNormalizePath() {
    // References
    // -> struct __locale _current_locale;
}

static char buffer[256]; // size: 0x100, address: 0x80984DA8
// Range: 0x805B0E2C -> 0x805B11F4
char * FileMakePath(const char * root /* r30 */, const char * file /* r27 */) {
    // Local variables
    char * start; // r30
    char temp[256]; // r1+0x88
    const char * drive; // r29
    char * dirs[32]; // r1+0x8
    const char * * endDir; // r29
    char * c; // r28
    unsigned char leadingSlash; // r27
    const char * * dir; // r4
    const char * cd; // r5

    // References
    // -> static char buffer[256];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static char relative[256]; // size: 0x100, address: 0x80984EA8
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x805B11F4 -> 0x805B171C
char * FileRelativePath(const char * root /* r29 */, const char * filepath /* r30 */) {
    // Local variables
    char path[256]; // r1+0x1D8
    char file[256]; // r1+0xD8
    class list pathDirs; // r1+0xD0
    class list fileDirs; // r1+0xC8
    char * c; // r29
    char * p; // r30
    char * f; // r4

    // References
    // -> static char relative[256];
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std14_List_node<Pc>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    char * _M_data; // offset 0x8, size 0x4
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
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std14_List_node<Pc>; // size: 0x8, address: 0x80923720
static char path[256]; // size: 0x100, address: 0x80984FA8
// Range: 0x805B171C -> 0x805B17F4
char * FileGetPath() {
    // Local variables
    char * c; // r4

    // References
    // -> static char path[256];
}

// Range: 0x805B17F4 -> 0x805B1864
char * FileGetExt(const char * file /* r31 */) {
    // Local variables
    int len; // r0
    const char * c; // r4
}

static char drive[256]; // size: 0x100, address: 0x809850A8
// Range: 0x805B1864 -> 0x805B18E8
char * FileGetDrive(const char * file /* r29 */) {
    // Local variables
    const char * c; // r0

    // References
    // -> static char drive[256];
}

static char path[256]; // size: 0x100, address: 0x809851A8
// Range: 0x805B18E8 -> 0x805B1988
char * FileGetBase(const char * file /* r31 */) {
    // Local variables
    const char * c; // r4

    // References
    // -> static char path[256];
}

static char path[256]; // size: 0x100, address: 0x809852A8
// Range: 0x805B1988 -> 0x805B1A08
char * FileGetName(const char * file /* r31 */) {
    // Local variables
    const char * c; // r4

    // References
    // -> static char path[256];
}

// Range: 0x805B1A08 -> 0x805B1A94
static int GetUnusedFile() {
    // Local variables
    int i; // r3

    // References
    // -> class Debug TheDebug;
    // -> static class vector gFiles;
}

// Range: 0x805B1A94 -> 0x805B1B10
int FileOpen(const char * iFilename /* r26 */, int iMode /* r27 */) {
    // Local variables
    int index; // r28

    // References
    // -> static class vector gFiles;
}

// Range: 0x805B1B10 -> 0x805B1C24
int FileClose(int iFd /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class vector gFiles;
}

// Range: 0x805B1C24 -> 0x805B1D34
int FileWrite(int iFd /* r30 */, void * iBuff /* r28 */, unsigned int iLen /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class vector gFiles;
}

static char mybuffer[256]; // size: 0x100, address: 0x809853A8
// Range: 0x805B1D34 -> 0x805B1FE0
char * FileLocalize(const char * iFilename /* r28 */, char * buffer /* r29 */) {
    // Local variables
    unsigned char nextGen; // r31
    enum Platform platform; // r30
    const char * c; // r27
    const char * c; // r27
    const char * c; // r30

    // References
    // -> static char mybuffer[256];
    // -> const char * gNullStr;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x805B1FE0 -> 0x805B208C
static unsigned char FileMatchInternal(const char * path /* r29 */, const char * pattern /* r30 */, unsigned char all /* r31 */) {}

// Range: 0x805B208C -> 0x805B2154
unsigned char FileMatch() {}

struct {
    // total size: 0x8
} __RTTI__PP4File; // size: 0x8, address: 0x80923820
// Range: 0x805B2154 -> 0x805B220C
static void __sinit_\File_cpp() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP4File;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class vector gFiles;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class File * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class File * * _M_start; // offset 0x0, size 0x4
    class File * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};

