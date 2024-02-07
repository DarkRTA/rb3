/*
    Compile unit: C:\rockband2\system\src\os\UserMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CBD14 -> 0x805CC24C
*/
class UserMgr * TheUserMgr; // size: 0x4, address: 0x80A54DD0
// Range: 0x805CBD14 -> 0x805CBD70
void * UserMgr::UserMgr(class UserMgr * const this /* r31 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__7UserMgr;
}

// Range: 0x805CBD70 -> 0x805CBDB8
class User * UserMgr::GetUserFromPadNum(const class UserMgr * const this /* r31 */) {
    // Local variables
    int userID; // r0
}

// Range: 0x805CBDB8 -> 0x805CBDC0
void SetTheUserMgr() {
    // References
    // -> class UserMgr * TheUserMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A54DD8
static class Symbol _s; // size: 0x4, address: 0x80A54DE0
// Range: 0x805CBDC0 -> 0x805CC24C
class DataNode UserMgr::Handle(class UserMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x60
} __vt__7UserMgr; // size: 0x60, address: 0x809268C0

