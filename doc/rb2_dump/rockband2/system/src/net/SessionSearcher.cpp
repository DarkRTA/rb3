/*
    Compile unit: C:\rockband2\system\src\net\SessionSearcher.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80536DB8 -> 0x80537C14
*/
// Range: 0x80536DB8 -> 0x80536DD8
static unsigned char NumPlayersGreaterThan() {}

static class Symbol invite_accepted; // size: 0x4, address: 0x80A53DE4
// Range: 0x80536DD8 -> 0x80536F44
void * SessionSearcher::SessionSearcher(class SessionSearcher * const this /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
    // -> static class Symbol invite_accepted;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__15SessionSearcher;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x80536F44 -> 0x80536F74
void SessionSearcher::AllocateNetSearchResults(class SessionSearcher * const this /* r31 */) {}

// Range: 0x80536F74 -> 0x80537124
void * SessionSearcher::~SessionSearcher(class SessionSearcher * const this /* r30 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__15SessionSearcher;
}

// Range: 0x80537124 -> 0x80537168
void SessionSearcher::Poll() {
    // References
    // -> class Net TheNet;
}

// Range: 0x80537168 -> 0x80537260
void SessionSearcher::StartSearching(class SessionSearcher * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message finished; // size: 0x8, address: 0x80982170
// Range: 0x80537260 -> 0x805373D4
void SessionSearcher::StopSearching(class SessionSearcher * const this /* r31 */) {
    // References
    // -> static class Message finished;
    // -> struct [anonymous] __vt__7Message;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x805373D4 -> 0x80537470
class NetSearchResult * SessionSearcher::GetNextResult(class SessionSearcher * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80537470 -> 0x805374E0
void SessionSearcher::UpdateSearchList(class NetSearchResult * result /* r1+0x8 */) {}

// Range: 0x805374E0 -> 0x805374E8
unsigned char SessionSearcher::OnMsg() {}

static class Symbol _s; // size: 0x4, address: 0x80A53DEC
static class Symbol _s; // size: 0x4, address: 0x80A53DF4
static class Symbol _s; // size: 0x4, address: 0x80A53DFC
// Range: 0x805374E8 -> 0x80537C14
class DataNode SessionSearcher::Handle(class SessionSearcher * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__17InviteAcceptedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x7C
} __vt__15SessionSearcher; // size: 0x7C, address: 0x80907688
struct {
    // total size: 0x8
} __RTTI__15SessionSearcher; // size: 0x8, address: 0x80907738
struct {
    // total size: 0x8
} __RTTI__PP15NetSearchResult; // size: 0x8, address: 0x80907808

