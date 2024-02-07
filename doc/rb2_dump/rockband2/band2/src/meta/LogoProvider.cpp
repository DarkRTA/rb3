/*
    Compile unit: C:\rockband2\band2\src\meta\LogoProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800FE324 -> 0x800FECE4
*/
class LogoProvider * sLogoProvider; // size: 0x4, address: 0x80A4B2B8
class LogoProvider : public ListProvider, public Object {
    // total size: 0x38
    class DataArray * mLogoList; // offset 0x2C, size 0x4
    class RndMat * mMat; // offset 0x30, size 0x4
    class RndTex * mTex; // offset 0x34, size 0x4
};
// Range: 0x800FE324 -> 0x800FE540
void * LogoProvider::LogoProvider(class LogoProvider * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Symbol name;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__12LogoProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x800FE540 -> 0x800FE574
void LogoProvider::Init() {
    // References
    // -> class LogoProvider * sLogoProvider;
}

// Range: 0x800FE574 -> 0x800FE610
class Symbol LogoProvider::DataSymbol(const class LogoProvider * const this /* r31 */, int data /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800FE610 -> 0x800FE664
int LogoProvider::NumData() {}

// Range: 0x800FE664 -> 0x800FE6D0
char * LogoProvider::Text(int data /* r30 */) {}

// Range: 0x800FE6D0 -> 0x800FE870
class RndMat * LogoProvider::Mat(const class LogoProvider * const this /* r27 */, int data /* r28 */) {
    // Local variables
    class String logo; // r1+0x2C
    class FilePath bandlogo_path; // r1+0x20

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800FE870 -> 0x800FE924
char * LogoProvider::GetLogoName(class LogoProvider * const this /* r29 */, int index /* r30 */) {
    // References
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A4B2C0
// Range: 0x800FE924 -> 0x800FECE4
class DataNode LogoProvider::Handle(class LogoProvider * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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
    // total size: 0x9C
} __vt__12LogoProvider; // size: 0x9C, address: 0x808897E8
struct {
    // total size: 0x8
} __RTTI__12LogoProvider; // size: 0x8, address: 0x808898B0

