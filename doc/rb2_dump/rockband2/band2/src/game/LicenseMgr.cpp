/*
    Compile unit: C:\rockband2\band2\src\game\LicenseMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800AC430 -> 0x800ACA04
*/
static const char * const kRB1ExportLicenseContents; // size: 0x4, address: 0x80A56438
class LicenseMgr : public Object, public Callback {
    // total size: 0x30
    unsigned char mRB1ExportLicenseValid; // offset 0x2C, size 0x1
};
static class LicenseMgr gLicenseMgr; // size: 0x30, address: 0x80977B78
class LicenseMgr & TheLicenseMgr; // size: 0x4, address: 0x80A4A488
// Range: 0x800AC430 -> 0x800AC494
void LicenseMgr::Init(class LicenseMgr * const this /* r31 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x800AC494 -> 0x800AC4AC
void LicenseMgr::Terminate() {
    // References
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x800AC4AC -> 0x800AC4B4
unsigned char LicenseMgr::IsRB1ExportLicenseValid() {}

// Range: 0x800AC4B4 -> 0x800AC4C0
void LicenseMgr::ContentStarted() {}

// Range: 0x800AC4C0 -> 0x800AC590
void LicenseMgr::ContentLoaded(class LicenseMgr * const this /* r29 */) {
    // Local variables
    class FileLoader * f; // r31
    char * buf; // r30

    // References
    // -> static const char * const kRB1ExportLicenseContents;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__10FileLoader;
}

// Range: 0x800AC590 -> 0x800AC594
void LicenseMgr::ContentDone() {}

// Range: 0x800AC594 -> 0x800AC598
void LicenseMgr::ContentMounted() {}

// Range: 0x800AC598 -> 0x800AC59C
void LicenseMgr::ContentUnmounted() {}

// Range: 0x800AC59C -> 0x800AC5A8
char * LicenseMgr::ContentPattern() {}

// Range: 0x800AC5A8 -> 0x800AC5B4
char * LicenseMgr::ContentDir() {}

// Range: 0x800AC5B4 -> 0x800AC5BC
char * LicenseMgr::ContentDirAlt() {}

static class Symbol _s; // size: 0x4, address: 0x80A4A490
// Range: 0x800AC5BC -> 0x800AC944
class DataNode LicenseMgr::Handle(class LicenseMgr * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xBC
} __vt__10LicenseMgr; // size: 0xBC, address: 0x8087D148
struct {
    // total size: 0x8
} __RTTI__10LicenseMgr; // size: 0x8, address: 0x8087D230
struct {
    // total size: 0x8
} __RTTI__10FileLoader; // size: 0x8, address: 0x8087D250
// Range: 0x800AC944 -> 0x800AC9BC
static void __sinit_\LicenseMgr_cpp() {
    // References
    // -> class LicenseMgr & TheLicenseMgr;
    // -> struct [anonymous] __vt__10LicenseMgr;
    // -> struct [anonymous] __vt__Q210ContentMgr8Callback;
    // -> static class LicenseMgr gLicenseMgr;
}


