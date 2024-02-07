/*
    Compile unit: C:\rockband2\band2\src\meta\ProfileMgr.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8014C9BC -> 0x8014D1BC
*/
// Range: 0x8014C9BC -> 0x8014CBB4
void * ProfileMgr::ProfileMgr(class ProfileMgr * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10ProfileMgr;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x8014CBB4 -> 0x8014D0DC
void ProfileMgr::Init(class ProfileMgr * const this /* r27 */) {
    // Local variables
    class DataArray * data; // r23
    int count; // r23
    class Profile * it; // r24

    // References
    // -> class RockCentralGateway RockCentral;
    // -> class NetSession * TheNetSession;
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x8014D0DC -> 0x8014D164
class Profile * ProfileMgr::GetProfileFromPad(class ProfileMgr * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8014D164 -> 0x8014D16C
unsigned char ProfileMgr::GetAllUnlocked() {}

// Range: 0x8014D16C -> 0x8014D174
unsigned char ProfileMgr::GetBassBoost() {}

// Range: 0x8014D174 -> 0x8014D17C
int ProfileMgr::GetBackgroundVolume() {}

// Range: 0x8014D17C -> 0x8014D184
int ProfileMgr::GetForegroundVolume() {}

// Range: 0x8014D184 -> 0x8014D18C
int ProfileMgr::GetVocalCueVolume() {}

// Range: 0x8014D18C -> 0x8014D194
int ProfileMgr::GetCrowdVolume() {}

// Range: 0x8014D194 -> 0x8014D19C
unsigned char ProfileMgr::GetDolby() {}

// Range: 0x8014D19C -> 0x8014D1A4
unsigned char ProfileMgr::GetOverscan() {}

// Range: 0x8014D1A4 -> 0x8014D1AC
unsigned char ProfileMgr::GetMono() {}

// Range: 0x8014D1AC -> 0x8014D1B4
int ProfileMgr::GetSyncPresetIx() {}

// Range: 0x8014D1B4 -> 0x8014D1BC
class String ProfileMgr::GetUsername() {}


