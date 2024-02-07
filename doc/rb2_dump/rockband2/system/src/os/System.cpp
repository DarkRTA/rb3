/*
    Compile unit: C:\rockband2\system\src\os\System.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805C89CC -> 0x805C9A8C
*/
static class Symbol gSystemLanguage; // size: 0x4, address: 0x80A54D28
static class DataArray * gSystemConfig; // size: 0x4, address: 0x80A54D2C
static class DataArray * gSystemTitles; // size: 0x4, address: 0x80A54D30
static int gUsingCD; // size: 0x4, address: 0x80A54D34
enum GfxMode {
    kOldGfx = 0,
    kNewGfx = 1,
};
static enum GfxMode gGfxMode; // size: 0x4, address: 0x80A54D38
static int gSystemMs; // size: 0x4, address: 0x80A54D3C
static float gSystemFrac; // size: 0x4, address: 0x80A54D40
static class Timer gSystemTimer; // size: 0x38, address: 0x80988B40
class vector TheSystemArgs; // size: 0xC, address: 0x80988B84
const char * gNullStr; // size: 0x4, address: 0x80A4788C
unsigned char gHostConfig; // size: 0x1, address: 0x80A54D44
unsigned char gHostLogging; // size: 0x1, address: 0x80A54D45
// Range: 0x805C89CC -> 0x805C8A44
void SetGfxMode() {
    // References
    // -> static enum GfxMode gGfxMode;
}

// Range: 0x805C8A44 -> 0x805C8A4C
enum GfxMode GetGfxMode() {
    // References
    // -> static enum GfxMode gGfxMode;
}

// Range: 0x805C8A4C -> 0x805C8A6C
static class DataNode OnSystemLanguage() {
    // References
    // -> static class Symbol gSystemLanguage;
}

// Range: 0x805C8A6C -> 0x805C8AC4
static class DataNode OnSystemExec(class DataArray * a /* r31 */) {}

// Range: 0x805C8AC4 -> 0x805C8AFC
static class DataNode OnUsingCD() {}

// Range: 0x805C8AFC -> 0x805C8C30
static void LanguageInit() {
    // Local variables
    class DataArray * array; // r31
    class Symbol lang; // r1+0x2C
    class DataArray * remap; // r0
    class Symbol force; // r1+0x28

    // References
    // -> const char * gNullStr;
}

static class Symbol sym[6]; // size: 0x18, address: 0x80988B90
// Range: 0x805C8C30 -> 0x805C8CD8
class Symbol PlatformSymbol(enum Platform plat /* r30 */) {
    // References
    // -> static class Symbol sym[6];
}

// Range: 0x805C8CD8 -> 0x805C8F94
static void InitSystem(const char * config /* r28 */) {
    // Local variables
    unsigned char usingCD; // r30
    class Archive * ark; // r29
    class DataArrayPtr one; // r1+0x40
    const char * define; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class DataArray * gSystemConfig;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> unsigned char gHostConfig;
    // -> class Archive * TheArchive;
}

// Range: 0x805C8F94 -> 0x805C90D0
void SystemTerminate() {
    // References
    // -> class vector TheSystemArgs;
    // -> class ContentMgr & TheContentMgr;
    // -> class TaskMgr TheTaskMgr;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class MemcardWii TheMC;
    // -> class Locale TheLocale;
    // -> class VirtualKeyboard TheVirtualKeyboard;
    // -> class Debug TheDebug;
}

// Range: 0x805C90D0 -> 0x805C9300
void SystemInit(const char * config /* r31 */) {
    // Local variables
    struct DateTime d; // r1+0x14

    // References
    // -> unsigned char gSystemInitialized;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<PFv_v>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class VirtualKeyboard TheVirtualKeyboard;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class MemcardWii TheMC;
    // -> class TaskMgr TheTaskMgr;
    // -> class LoadMgr TheLoadMgr;
    // -> static class DataArray * gSystemTitles;
    // -> class Debug TheDebug;
    // -> class ContentMgr & TheContentMgr;
    // -> unsigned char gHostLogging;
    // -> unsigned char gHostConfig;
    // -> static class Timer gSystemTimer;
}

// Range: 0x805C9300 -> 0x805C938C
int SystemMs() {
    // Local variables
    int ms; // r4

    // References
    // -> static int gSystemMs;
    // -> static float gSystemFrac;
    // -> static class Timer gSystemTimer;
}

static class Timer * _t; // size: 0x4, address: 0x80A54D48
// Range: 0x805C938C -> 0x805C9520
void SystemPoll(unsigned char pollTasks /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> class ContentMgr & TheContentMgr;
    // -> class VirtualKeyboard TheVirtualKeyboard;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class TaskMgr TheTaskMgr;
    // -> class AppChild * TheAppChild;
    // -> class NetCacheMgr * TheNetCacheMgr;
    // -> class CacheMgr * TheCacheMgr;
    // -> class LoadMgr TheLoadMgr;
    // -> class MemcardWii TheMC;
    // -> class Debug TheDebug;
    // -> static class Timer * _t;
}

// Range: 0x805C9520 -> 0x805C9534
unsigned char UsingCD() {
    // References
    // -> static int gUsingCD;
}

// Range: 0x805C9534 -> 0x805C953C
void SetUsingCD() {
    // References
    // -> static int gUsingCD;
}

// Range: 0x805C953C -> 0x805C9544
class DataArray * SystemConfig() {
    // References
    // -> static class DataArray * gSystemConfig;
}

// Range: 0x805C9544 -> 0x805C9578
class DataArray * SystemConfig() {
    // References
    // -> static class DataArray * gSystemConfig;
}

// Range: 0x805C9578 -> 0x805C95C0
class DataArray * SystemConfig() {
    // References
    // -> static class DataArray * gSystemConfig;
}

// Range: 0x805C95C0 -> 0x805C961C
class DataArray * SystemConfig() {
    // References
    // -> static class DataArray * gSystemConfig;
}

// Range: 0x805C961C -> 0x805C968C
class DataArray * SystemConfig() {
    // References
    // -> static class DataArray * gSystemConfig;
}

// Range: 0x805C968C -> 0x805C9710
class DataArray * SystemConfig() {
    // References
    // -> static class DataArray * gSystemConfig;
}

// Range: 0x805C9710 -> 0x805C9718
class Symbol SystemLanguage() {
    // References
    // -> static class Symbol gSystemLanguage;
}

// Range: 0x805C9718 -> 0x805C9720
class DataArray * SystemTitles() {
    // References
    // -> static class DataArray * gSystemTitles;
}

static class DataArray * langs; // size: 0x4, address: 0x80A54D50
// Range: 0x805C9720 -> 0x805C97EC
unsigned char IsSupportedLanguage(class Symbol & lang /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> static class DataArray * langs;
}

// Range: 0x805C97EC -> 0x805C9958
void SetSystemLanguage(class Symbol & lang /* r29 */) {
    // Local variables
    class DataArray * pdaLanguage; // r31
    class DataArray * pdaDefault; // r31
    class Symbol langDefault; // r1+0x30

    // References
    // -> class Locale TheLocale;
    // -> static class Symbol gSystemLanguage;
    // -> class Debug TheDebug;
}

// Range: 0x805C9958 -> 0x805C9A2C
void AppendThreadStackTrace(char * msg /* r28 */, unsigned int * stack /* r29 */) {
    // Local variables
    int stack_size; // r30
}

// Range: 0x805C9A2C -> 0x805C9A8C
static void __sinit_\System_cpp() {
    // References
    // -> class vector TheSystemArgs;
    // -> static class Timer gSystemTimer;
    // -> static class Symbol gSystemLanguage;
    // -> const char * gNullStr;
}

class VirtualKeyboard : public Object {
    // total size: 0x3C
    class Object * mPobjKeyboardCallback; // offset 0x28, size 0x4
    unsigned char mCallbackReady; // offset 0x2C, size 0x1
    unsigned char mMsgOk; // offset 0x2D, size 0x1
    class String mCallbackMsg; // offset 0x30, size 0xC
};

