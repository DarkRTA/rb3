/*
    Compile unit: C:\rockband2\system\src\os\Memcard_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805BF138 -> 0x805C038C
*/
static struct NANDFileInfo info; // size: 0x8C, address: 0x80986628
// Range: 0x805BF138 -> 0x805BF144
void ContainerId::Set() {}

class MemcardWii TheMC; // size: 0x2C, address: 0x809866C0
// Range: 0x805BF144 -> 0x805BF180
void MemcardWii::Init(class MemcardWii * const this /* r31 */) {}

// Range: 0x805BF180 -> 0x805BF184
void MemcardWii::Terminate() {}

// Range: 0x805BF184 -> 0x805BF18C
enum MCResult MemcardWii::DeleteContainer() {}

// Range: 0x805BF18C -> 0x805BF1F4
class MCContainer * MemcardWii::CreateContainer(const struct ContainerId & cid /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14MCContainerWii;
    // -> struct [anonymous] __vt__11MCContainer;
}

// Range: 0x805BF1F4 -> 0x805BF200
void MemcardWii::SetMtapConfig() {}

// Range: 0x805BF200 -> 0x805BF208
enum MCResult MCContainerWii::Mount() {}

// Range: 0x805BF208 -> 0x805BF210
enum MCResult MCContainerWii::Unmount() {}

// Range: 0x805BF210 -> 0x805BF29C
enum MCResult MCContainerWii::GetFreeSpace(int * pFreeSpace /* r31 */) {
    // Local variables
    unsigned long bytes; // r1+0xC
    unsigned long inodes; // r1+0x8
    long result; // r0
}

// Range: 0x805BF29C -> 0x805BF2FC
int MCContainerWii::GetContainerBlocks() {
    // Local variables
    unsigned long blocks; // r31
    unsigned long bytes; // r1+0xC
    unsigned long inodes; // r1+0x8
    long result; // r0
}

// Range: 0x805BF2FC -> 0x805BF398
enum MCResult MCContainerWii::CheckContainer() {
    // Local variables
    unsigned long answer; // r1+0x8
    long result; // r0
}

// Range: 0x805BF398 -> 0x805BF420
enum MCResult MCContainerWii::CheckContainerSpace(int iNodes /* r30 */) {
    // Local variables
    unsigned long bytes; // r1+0xC
    unsigned long inodes; // r1+0x8
    unsigned long totalSpace; // r31
    long result; // r0
}

// Range: 0x805BF420 -> 0x805BF4AC
enum MCResult MCContainerWii::GetFreeInodes(int * pFreeInodes /* r31 */) {
    // Local variables
    unsigned long bytes; // r1+0xC
    unsigned long inodes; // r1+0x8
    long result; // r0
}

// Range: 0x805BF4AC -> 0x805BF50C
enum MCResult MCContainerWii::Delete() {
    // Local variables
    long result; // r0
}

// Range: 0x805BF50C -> 0x805BF514
enum MCResult MCContainerWii::RemoveDir() {}

// Range: 0x805BF514 -> 0x805BF59C
enum MCResult MCContainerWii::MakeDir() {
    // Local variables
    long result; // r0
}

// Range: 0x805BF59C -> 0x805BF5A4
enum MCResult MCContainerWii::PrintDir() {}

// Range: 0x805BF5A4 -> 0x805BF614
enum MCResult MCContainerWii::MakeFile() {
    // Local variables
    long result; // r0
}

// Range: 0x805BF614 -> 0x805BF718
enum MCResult MCContainerWii::WriteFile(void * buffer /* r29 */, int size /* r30 */) {
    // Local variables
    unsigned long result; // r0
    unsigned long bytesWritten; // r0

    // References
    // -> static struct NANDFileInfo info;
}

// Range: 0x805BF718 -> 0x805BF7F8
enum MCResult MCContainerWii::ValidateFile(int size /* r31 */) {
    // Local variables
    struct NANDFileInfo fileInfo; // r1+0xC
    long result; // r0
    unsigned long length; // r1+0x8
}

// Range: 0x805BF7F8 -> 0x805BF8C4
enum MCResult MCContainerWii::GetSize(int * pFileSize /* r30 */) {
    // Local variables
    struct NANDFileInfo fileInfo; // r1+0xC
    enum MCResult mcresult; // r31
    long result; // r0
    unsigned long length; // r1+0x8
    long res; // r0
}

// Range: 0x805BF8C4 -> 0x805BF8CC
enum MCResult MCContainerWii::Format() {}

// Range: 0x805BF8CC -> 0x805BF8D4
enum MCResult MCContainerWii::Unformat() {}

// Range: 0x805BF8D4 -> 0x805BF914
class MCFile * MCContainerWii::CreateMCFile(class MCContainerWii * const this /* r31 */) {}

// Range: 0x805BF914 -> 0x805BF99C
class String MCContainerWii::BuildPath(class String * str /* r29 */) {
    // Local variables
    int i; // r30
}

struct NANDBanner {
    // total size: 0xF0A0
    unsigned long signature; // offset 0x0, size 0x4
    unsigned long flag; // offset 0x4, size 0x4
    unsigned short iconSpeed; // offset 0x8, size 0x2
    unsigned char reserved[22]; // offset 0xA, size 0x16
    unsigned short comment[2][32]; // offset 0x20, size 0x80
    unsigned char bannerTexture[24576]; // offset 0xA0, size 0x6000
    unsigned char iconTexture[8][4608]; // offset 0x60A0, size 0x9000
};
// Range: 0x805BF99C -> 0x805BFE74
enum MCResult MCContainerWii::CreateBanner(const char * path /* r27 */, int icons /* r29 */) {
    // Local variables
    struct NANDFileInfo bannerFileInfo; // r31+0x50
    int i; // r27
    struct NANDBanner s_bnr; // r31+0xFFFF0F80
    long result; // r0
    struct TPLPalette * tplIcons; // r30
    struct TPLDescriptor * tdpIcons; // r0
    unsigned short saveFileName[13]; // r31+0x34
    unsigned short saveFileComment[10]; // r31+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class MCFileWii : public MCFile {
    // total size: 0x98
    int mFileID; // offset 0x8, size 0x4
    struct NANDFileInfo info; // offset 0xC, size 0x8C
};
// Range: 0x805BFE74 -> 0x805BFE90
void * MCFileWii::MCFileWii() {
    // References
    // -> struct [anonymous] __vt__9MCFileWii;
}

// Range: 0x805BFE90 -> 0x805BFED0
void * MCFileWii::~MCFileWii(class MCFileWii * const this /* r31 */) {}

// Range: 0x805BFED0 -> 0x805BFF78
enum MCResult MCFileWii::Open(class MCFileWii * const this /* r30 */, const char * file /* r31 */) {
    // Local variables
    long result; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805BFF78 -> 0x805C00A0
enum MCResult MCFileWii::Read(class MCFileWii * const this /* r29 */, void * data /* r30 */, int size /* r31 */) {
    // Local variables
    long bytesRead; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805C00A0 -> 0x805C0194
enum MCResult MCFileWii::Write(class MCFileWii * const this /* r28 */, void * data /* r29 */, int size /* r30 */) {
    // Local variables
    enum MCResult mcResult; // r31
    long bytesWritten; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805C0194 -> 0x805C026C
enum MCResult MCFileWii::Seek(class MCFileWii * const this /* r29 */, int offset /* r30 */, enum SeekType seek /* r31 */) {
    // Local variables
    long seekTarget; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805C026C -> 0x805C0310
enum MCResult MCFileWii::Close(class MCFileWii * const this /* r31 */) {
    // Local variables
    long result; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805C0310 -> 0x805C032C
unsigned char MCFileWii::IsOpen() {}

struct {
    // total size: 0x24
} __vt__9MCFileWii; // size: 0x24, address: 0x80924898
struct {
    // total size: 0x8
} __RTTI__9MCFileWii; // size: 0x8, address: 0x809248D8
struct {
    // total size: 0x60
} __vt__14MCContainerWii; // size: 0x60, address: 0x809248E0
struct {
    // total size: 0x84
} __vt__10MemcardWii; // size: 0x84, address: 0x80924940
struct {
    // total size: 0x8
} __RTTI__10MemcardWii; // size: 0x8, address: 0x809249F0
struct {
    // total size: 0x8
} __RTTI__6MCFile; // size: 0x8, address: 0x80924A00
// Range: 0x805C032C -> 0x805C038C
static void __sinit_\Memcard_Wii_cpp() {
    // References
    // -> struct [anonymous] __vt__10MemcardWii;
    // -> class MemcardWii TheMC;
}


