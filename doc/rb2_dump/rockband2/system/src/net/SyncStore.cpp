/*
    Compile unit: C:\rockband2\system\src\net\SyncStore.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8053C2F4 -> 0x8053CD38
*/
class SyncStore * TheSyncStore; // size: 0x4, address: 0x80A53E10
// Range: 0x8053C2F4 -> 0x8053C414
void * SyncStore::SyncStore(class SyncStore * const this /* r29 */) {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SyncStore * TheSyncStore;
}

// Range: 0x8053C414 -> 0x8053C478
void SyncStore::Poll(class SyncStore * const this /* r30 */) {
    // Local variables
    int n; // r31
}

// Range: 0x8053C478 -> 0x8053C58C
void SyncStore::AddSyncObj(class SyncStore * const this /* r29 */, class Synchronizable * s /* r1+0x8 */, class String & tag /* r30 */) {
    // Local variables
    int n; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8053C58C -> 0x8053C67C
void SyncStore::RemoveSyncObj(class SyncStore * const this /* r29 */, class String & tag /* r30 */) {
    // Local variables
    class Synchronizable * * it; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8053C67C -> 0x8053C754
class Synchronizable * SyncStore::GetSyncObj(class SyncStore * const this /* r28 */, class String & tag /* r29 */) {
    // Local variables
    int n; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8053C754 -> 0x8053C7F0
void SyncStore::SyncPlayer(class SyncStore * const this /* r28 */, int playerNum /* r29 */) {
    // Local variables
    int n; // r30
}

// Range: 0x8053C7F0 -> 0x8053C880
void SyncStore::SyncAllPlayers(class SyncStore * const this /* r29 */) {
    // Local variables
    int n; // r30
}

// Range: 0x8053C880 -> 0x8053C914
void * SyncObjMsg::SyncObjMsg(class SyncObjMsg * const this /* r29 */, unsigned int dirtyMask /* r30 */, class Synchronizable * s /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10SyncObjMsg;
}

// Range: 0x8053C914 -> 0x8053C92C
void SyncObjMsg::GetObjData(const class SyncObjMsg * const this /* r5 */) {}

// Range: 0x8053C92C -> 0x8053C9B0
void SyncObjMsg::Save(const class SyncObjMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8053C9B0 -> 0x8053CA8C
void SyncObjMsg::Load(class SyncObjMsg * const this /* r29 */, class BinStream & src /* r30 */) {
    // Local variables
    int numBytes; // r1+0x10
}

// Range: 0x8053CA8C -> 0x8053CBB0
void SyncObjMsg::Dispatch(class SyncObjMsg * const this /* r30 */) {
    // Local variables
    class Synchronizable * obj; // r31
    class MemStream objData; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> class SyncStore * TheSyncStore;
}

// Range: 0x8053CBB0 -> 0x8053CC20
void SyncObjMsg::Print(const class SyncObjMsg * const this /* r30 */, class TextStream & text /* r31 */) {}

// Range: 0x8053CC20 -> 0x8053CCA8
void * SyncPlayerMsg::SyncPlayerMsg(class SyncPlayerMsg * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__13SyncPlayerMsg;
}

// Range: 0x8053CCA8 -> 0x8053CCE0
void SyncPlayerMsg::Save(const class SyncPlayerMsg * const this /* r5 */) {}

// Range: 0x8053CCE0 -> 0x8053CD20
void SyncPlayerMsg::Load(class SyncPlayerMsg * const this /* r31 */) {
    // Local variables
    unsigned char playerNum; // r1+0x8
}

// Range: 0x8053CD20 -> 0x8053CD30
void SyncPlayerMsg::Dispatch(class SyncPlayerMsg * const this /* r4 */) {
    // References
    // -> class SyncStore * TheSyncStore;
}

// Range: 0x8053CD30 -> 0x8053CD38
void SyncAllMsg::Dispatch() {
    // References
    // -> class SyncStore * TheSyncStore;
}

struct {
    // total size: 0x28
} __vt__10SyncAllMsg; // size: 0x28, address: 0x80908348
struct {
    // total size: 0x8
} __RTTI__10SyncAllMsg; // size: 0x8, address: 0x80908388
struct {
    // total size: 0x28
} __vt__13SyncPlayerMsg; // size: 0x28, address: 0x80908390
struct {
    // total size: 0x8
} __RTTI__13SyncPlayerMsg; // size: 0x8, address: 0x809083D8
struct {
    // total size: 0x28
} __vt__10SyncObjMsg; // size: 0x28, address: 0x809083E0
struct {
    // total size: 0x8
} __RTTI__10SyncObjMsg; // size: 0x8, address: 0x80908420
struct {
    // total size: 0x8
} __RTTI__PP14Synchronizable; // size: 0x8, address: 0x80908440

