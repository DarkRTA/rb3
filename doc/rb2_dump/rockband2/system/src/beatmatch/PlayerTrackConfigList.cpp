/*
    Compile unit: C:\rockband2\system\src\beatmatch\PlayerTrackConfigList.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802F7B48 -> 0x802F811C
*/
// Range: 0x802F7B48 -> 0x802F7BC8
void * PlayerTrackConfigList::PlayerTrackConfigList(class PlayerTrackConfigList * const this /* r31 */) {}

// Range: 0x802F7BC8 -> 0x802F7D34
void PlayerTrackConfigList::Reset(class PlayerTrackConfigList * const this /* r31 */) {}

// Range: 0x802F7D34 -> 0x802F7DFC
void PlayerTrackConfigList::AddConfig() {}

// Range: 0x802F7DFC -> 0x802F7EA4
void PlayerTrackConfigList::AddNullConfig() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x802F7EA4 -> 0x802F7F8C
int PlayerTrackConfigList::TrackPlayer(const class PlayerTrackConfigList * const this /* r28 */, int t /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802F7F8C -> 0x802F7FC0
unsigned char PlayerTrackConfigList::TrackUsed() {}

// Range: 0x802F7FC0 -> 0x802F80C0
int PlayerTrackConfigList::InstrumentPlayer(const class PlayerTrackConfigList * const this /* r28 */, class Symbol & inst /* r29 */, int inst_num /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802F80C0 -> 0x802F811C
int PlayerTrackConfigList::NumActivePlayers() {
    // Local variables
    int num; // r6
    int i; // r7
}

struct {
    // total size: 0x8
} __RTTI__P17PlayerTrackConfig; // size: 0x8, address: 0x808CD448

