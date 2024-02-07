/*
    Compile unit: C:\rockband2\system\src\os\User.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CB1EC -> 0x805CBD14
*/
// Range: 0x805CB1EC -> 0x805CB1F0
static void Ignore() {}

void (* sUserReadyCallbackFunction)(int); // size: 0x4, address: 0x80A478C8
// Range: 0x805CB1F0 -> 0x805CB1F8
void SetUserReadyCallbackFunction() {
    // References
    // -> void (* sUserReadyCallbackFunction)(int);
}

// Range: 0x805CB1F8 -> 0x805CB27C
void * User::User(class User * const this /* r30 */, int userNum /* r31 */) {
    // References
    // -> struct [anonymous] __vt__4User;
}

// Range: 0x805CB27C -> 0x805CB290
void User::Reset() {}

// Range: 0x805CB290 -> 0x805CB310
void User::UpdateOnlineID(class User * const this /* r29 */) {
    // Local variables
    int padNum; // r30

    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x805CB310 -> 0x805CB318
int User::GetPadNum() {}

// Range: 0x805CB318 -> 0x805CB32C
void User::SetReady() {
    // References
    // -> void (* sUserReadyCallbackFunction)(int);
}

// Range: 0x805CB32C -> 0x805CB3A8
void User::SyncSave(const class User * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x805CB3A8 -> 0x805CB428
void User::SyncLoad(class User * const this /* r30 */, class BinStream & src /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A54D9C
static class Symbol _s; // size: 0x4, address: 0x80A54DA4
static class Symbol _s; // size: 0x4, address: 0x80A54DAC
static class Symbol _s; // size: 0x4, address: 0x80A54DB4
static class Symbol _s; // size: 0x4, address: 0x80A54DBC
// Range: 0x805CB428 -> 0x805CBB48
class DataNode User::Handle(class User * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A54DC4
static class Symbol _s; // size: 0x4, address: 0x80A54DCC
// Range: 0x805CBB48 -> 0x805CBD14
unsigned char User::SyncProperty(class User * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x60
} __vt__4User; // size: 0x60, address: 0x80926748

