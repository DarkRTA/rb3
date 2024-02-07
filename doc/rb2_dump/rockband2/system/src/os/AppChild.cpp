/*
    Compile unit: C:\rockband2\system\src\os\AppChild.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CD77C -> 0x805CDBE0
*/
class AppChild * TheAppChild; // size: 0x4, address: 0x80A54E08
// Range: 0x805CD77C -> 0x805CD7A0
static class DataNode EnableAppChild() {
    // References
    // -> class AppChild * TheAppChild;
}

// Range: 0x805CD7A0 -> 0x805CD7C4
static class DataNode DisableAppChild() {
    // References
    // -> class AppChild * TheAppChild;
}

// Range: 0x805CD7C4 -> 0x805CD808
static class DataNode SyncAppChild() {
    // References
    // -> class AppChild * TheAppChild;
}

// Range: 0x805CD808 -> 0x805CD95C
void AppChild::Init() {
    // Local variables
    unsigned char app_child; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class AppChild * TheAppChild;
}

// Range: 0x805CD95C -> 0x805CD990
void AppChild::Terminate() {
    // References
    // -> class AppChild * TheAppChild;
}

// Range: 0x805CD990 -> 0x805CDA30
void * AppChild::AppChild(class AppChild * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805CDA30 -> 0x805CDAA4
void * AppChild::~AppChild(class AppChild * const this /* r30 */) {}

// Range: 0x805CDAA4 -> 0x805CDAB0
void AppChild::Sync() {}

// Range: 0x805CDAB0 -> 0x805CDABC
void AppChild::Sync() {}

static class Symbol tool_sync_cam; // size: 0x4, address: 0x80A54E10
// Range: 0x805CDABC -> 0x805CDBE0
void AppChild::Poll(class AppChild * const this /* r31 */) {
    // Local variables
    class DataArrayPtr cmd; // r1+0x10

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol tool_sync_cam;
}


