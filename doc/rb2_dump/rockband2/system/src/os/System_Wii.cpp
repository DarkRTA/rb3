/*
    Compile unit: C:\rockband2\system\src\os\System_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805C9A8C -> 0x805CA130
*/
enum quitType gPowerCallback; // size: 0x4, address: 0x80A54D58
unsigned char gSystemLocked; // size: 0x1, address: 0x80A54D5C
unsigned char gSystemInitialized; // size: 0x1, address: 0x80A54D5D
// Range: 0x805C9A8C -> 0x805C9D14
void AppendStackTrace(char * msg /* r30 */) {
    // Local variables
    unsigned int results[50]; // r1+0x130
    unsigned long i; // r29
    unsigned long * p; // r3
    class String elfName; // r1+0x20
    class Elf * elf; // r29
    unsigned int * r; // r28
    char buffer[256]; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> class vector TheSystemArgs;
}

// Range: 0x805C9D14 -> 0x805C9DBC
void CheckForArchive() {
    // Local variables
    class File * f; // r0
}

// Range: 0x805C9DBC -> 0x805C9EBC
void SystemInit(int argc /* r28 */, char * * argv /* r29 */, const char * config /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class vector TheSystemArgs;
}

// Range: 0x805C9EBC -> 0x805C9EF0
int SystemExec() {}

static class Symbol eng; // size: 0x4, address: 0x80A54D60
static class Symbol deu; // size: 0x4, address: 0x80A54D68
static class Symbol ita; // size: 0x4, address: 0x80A54D70
static class Symbol fre; // size: 0x4, address: 0x80A54D78
static class Symbol esl; // size: 0x4, address: 0x80A54D80
// Range: 0x805C9EF0 -> 0x805CA00C
class Symbol TrySetLanguage() {
    // Local variables
    unsigned char langType; // r0

    // References
    // -> static class Symbol esl;
    // -> static class Symbol fre;
    // -> static class Symbol ita;
    // -> static class Symbol deu;
    // -> static class Symbol eng;
}

// Range: 0x805CA00C -> 0x805CA02C
void WiiPoll() {
    // References
    // -> unsigned char gSystemLocked;
    // -> enum quitType gPowerCallback;
}

// Range: 0x805CA02C -> 0x805CA0DC
void WiiShutdown(enum quitType type /* r31 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x805CA0DC -> 0x805CA0EC
void CaptureStackTrace() {}

// Range: 0x805CA0EC -> 0x805CA104
unsigned char PlatformDebugBreak() {}

// Range: 0x805CA104 -> 0x805CA130
void _Vector_base::_M_throw_length_error() {}

struct _OKToMemCpy {
    // total size: 0x1
};

