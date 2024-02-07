/*
    Compile unit: C:\rockband2\system\src\net\MatchmakingSettings.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805247C4 -> 0x80524FB4
*/
class Symbol t; // size: 0x4, address: 0x80A53C7C
// Range: 0x805247C4 -> 0x805247D4
void MatchmakingSettings::SetMode() {}

// Range: 0x805247D4 -> 0x805248A4
void MatchmakingSettings::AddCustomSetting(class MatchmakingSettings * const this /* r31 */, int settingID /* r1+0x8 */, int settingValue /* r1+0xC */) {}

// Range: 0x805248A4 -> 0x8052494C
void MatchmakingSettings::ClearCustomSettings(class MatchmakingSettings * const this /* r30 */) {}

// Range: 0x8052494C -> 0x80524964
int MatchmakingSettings::NumCustomSettings() {}

// Range: 0x80524964 -> 0x80524B40
void MatchmakingSettings::Load(class MatchmakingSettings * const this /* r30 */, class BinStream & src /* r31 */) {
    // Local variables
    unsigned char numCustom; // r1+0x29
    int n; // r29
    int id; // r1+0x30
    int value; // r1+0x2C
}

// Range: 0x80524B40 -> 0x80524B7C
void SessionSettings::Clear(class SessionSettings * const this /* r31 */) {}

// Range: 0x80524B7C -> 0x80524BE4
void SessionSettings::SetPublic(unsigned char isPublic /* r31 */) {
    // Local variables
    unsigned char dirty; // r0

    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x80524BE4 -> 0x80524C54
void SessionSettings::SetMode(class SessionSettings * const this /* r30 */) {}

// Range: 0x80524C54 -> 0x80524C80
void SessionSettings::SetRanked() {
    // Local variables
    unsigned char dirty; // r0
}

// Range: 0x80524C80 -> 0x80524CB8
void SessionSettings::AddCustomSetting(class SessionSettings * const this /* r31 */) {}

// Range: 0x80524CB8 -> 0x80524D08
void SessionSettings::SyncSave(const class SessionSettings * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x80524D08 -> 0x80524D64
void SessionSettings::SyncLoad(class SessionSettings * const this /* r30 */, class BinStream & src /* r31 */) {}

// Range: 0x80524D64 -> 0x80524DB4
unsigned char SessionSettings::HasSyncPermission() {
    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x80524DB4 -> 0x80524DF4
void SessionSettings::OnSynchronizing() {
    // References
    // -> class NetSession * TheNetSession;
}

class SettingsChangedMsg : public Message {
    // total size: 0x8
};
static class SettingsChangedMsg msg; // size: 0x8, address: 0x80981BB0
// Range: 0x80524DF4 -> 0x80524F68
void SessionSettings::OnSynchronized() {
    // References
    // -> class NetSession * TheNetSession;
    // -> struct [anonymous] __vt__18SettingsChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class SettingsChangedMsg msg;
}

// Range: 0x80524F68 -> 0x80524FB4
void * SearchSettings::SearchSettings() {
    // References
    // -> struct [anonymous] __vt__14SearchSettings;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__19MatchmakingSettings;
}

struct {
    // total size: 0xC
} __vt__18SettingsChangedMsg; // size: 0xC, address: 0x80905038
struct {
    // total size: 0x8
} __RTTI__18SettingsChangedMsg; // size: 0x8, address: 0x80905068
struct {
    // total size: 0x18
} __vt__14SearchSettings; // size: 0x18, address: 0x80905070
struct {
    // total size: 0x8
} __RTTI__14SearchSettings; // size: 0x8, address: 0x809050A8
struct {
    // total size: 0x4C
} __vt__15SessionSettings; // size: 0x4C, address: 0x809050B0
struct {
    // total size: 0x8
} __RTTI__15SessionSettings; // size: 0x8, address: 0x80905128
struct {
    // total size: 0x18
} __vt__19MatchmakingSettings; // size: 0x18, address: 0x80905130
struct {
    // total size: 0x8
} __RTTI__19MatchmakingSettings; // size: 0x8, address: 0x80905160

