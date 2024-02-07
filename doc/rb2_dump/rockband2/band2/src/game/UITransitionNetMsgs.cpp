/*
    Compile unit: C:\rockband2\band2\src\game\UITransitionNetMsgs.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80098BB4 -> 0x8009926C
*/
class NetTransitionMsg : public NetMessage {
    // total size: 0x4
};
// Range: 0x80098BB4 -> 0x80098BC0
void NetTransitionMsg::Dispatch() {
    // References
    // -> class NetSync * TheNetSync;
}

class LocalTransitionCompleteMsg : public NetTransitionMsg {
    // total size: 0x10
    class vector mLocalPlayers; // offset 0x4, size 0xC
};
// Range: 0x80098BC0 -> 0x80098C98
void * LocalTransitionCompleteMsg::LocalTransitionCompleteMsg(class LocalTransitionCompleteMsg * const this /* r29 */, class vector & locals /* r30 */) {
    // Local variables
    int n; // r31

    // References
    // -> struct [anonymous] __vt__26LocalTransitionCompleteMsg;
}

// Range: 0x80098C98 -> 0x80098D50
void LocalTransitionCompleteMsg::GetPlayers(const class LocalTransitionCompleteMsg * const this /* r29 */, class vector & players /* r30 */) {
    // Local variables
    int n; // r31
}

// Range: 0x80098D50 -> 0x80098DF8
void LocalTransitionCompleteMsg::Save(const class LocalTransitionCompleteMsg * const this /* r28 */, class BinStream & dest /* r29 */) {
    // Local variables
    unsigned char numPlayers; // r31
    int n; // r30
}

// Range: 0x80098DF8 -> 0x80098EBC
void LocalTransitionCompleteMsg::Load(class LocalTransitionCompleteMsg * const this /* r29 */, class BinStream & src /* r30 */) {
    // Local variables
    unsigned char numPlayers; // r1+0xC
    int n; // r31
    int playerNum; // r1+0x10
}

class StartTransitionMsg : public NetTransitionMsg {
    // total size: 0x10
    class String mScreenName; // offset 0x4, size 0xC
};
// Range: 0x80098EBC -> 0x80098F1C
void * StartTransitionMsg::StartTransitionMsg(class StartTransitionMsg * const this /* r30 */, class UIScreen * screen /* r31 */) {
    // References
    // -> struct [anonymous] __vt__18StartTransitionMsg;
}

// Range: 0x80098F1C -> 0x80099004
class UIScreen * StartTransitionMsg::GetScreen() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x80099004 -> 0x80099014
void StartTransitionMsg::Save(const class StartTransitionMsg * const this /* r5 */) {}

// Range: 0x80099014 -> 0x80099024
void StartTransitionMsg::Load(class StartTransitionMsg * const this /* r5 */) {}

class NetGotoScreenMsg : public StartTransitionMsg {
    // total size: 0x14
    unsigned char mForce; // offset 0x10, size 0x1
    unsigned char mBack; // offset 0x11, size 0x1
};
// Range: 0x80099024 -> 0x80099080
void * NetGotoScreenMsg::NetGotoScreenMsg(class NetGotoScreenMsg * const this /* r29 */, unsigned char force /* r30 */, unsigned char back /* r31 */) {
    // References
    // -> struct [anonymous] __vt__16NetGotoScreenMsg;
}

// Range: 0x80099080 -> 0x800990E8
void NetGotoScreenMsg::Save(const class NetGotoScreenMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x800990E8 -> 0x80099168
void NetGotoScreenMsg::Load(class NetGotoScreenMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

class NetSyncScreenMsg : public StartTransitionMsg {
    // total size: 0x14
    unsigned char mDepth; // offset 0x10, size 0x1
};
// Range: 0x80099168 -> 0x800991C0
void * NetSyncScreenMsg::NetSyncScreenMsg(class NetSyncScreenMsg * const this /* r30 */, int depth /* r31 */) {
    // References
    // -> struct [anonymous] __vt__16NetSyncScreenMsg;
}

// Range: 0x800991C0 -> 0x80099210
void NetSyncScreenMsg::Save(const class NetSyncScreenMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x80099210 -> 0x8009926C
void NetSyncScreenMsg::Load(class NetSyncScreenMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

struct {
    // total size: 0x28
} __vt__16NetSyncScreenMsg; // size: 0x28, address: 0x8087A818
struct {
    // total size: 0x8
} __RTTI__16NetSyncScreenMsg; // size: 0x8, address: 0x8087A870
struct {
    // total size: 0x28
} __vt__16NetGotoScreenMsg; // size: 0x28, address: 0x8087A878
struct {
    // total size: 0x8
} __RTTI__16NetGotoScreenMsg; // size: 0x8, address: 0x8087A8D0
struct {
    // total size: 0x28
} __vt__18StartTransitionMsg; // size: 0x28, address: 0x8087A8D8
struct {
    // total size: 0x8
} __RTTI__18StartTransitionMsg; // size: 0x8, address: 0x8087A928
struct {
    // total size: 0x28
} __vt__26LocalTransitionCompleteMsg; // size: 0x28, address: 0x8087A930
struct {
    // total size: 0x8
} __RTTI__26LocalTransitionCompleteMsg; // size: 0x8, address: 0x8087A988
struct {
    // total size: 0x8
} __RTTI__16NetTransitionMsg; // size: 0x8, address: 0x8087A9B0
class AllTransitionCompleteMsg : public NetTransitionMsg {
    // total size: 0x4
};

