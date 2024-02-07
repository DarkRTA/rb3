/*
    Compile unit: C:\rockband2\system\src\net\Synchronize.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8053BD24 -> 0x8053C06C
*/
// Range: 0x8053BD24 -> 0x8053BDE0
void * Synchronizable::~Synchronizable(class Synchronizable * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__14Synchronizable;
}

// Range: 0x8053BDE0 -> 0x8053BE5C
void Synchronizable::Unpublish(class Synchronizable * const this /* r31 */) {
    // References
    // -> class SyncStore * TheSyncStore;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class SyncObjMsg : public NetMessage {
    // total size: 0x34
    class String mObjTag; // offset 0x4, size 0xC
    unsigned int mDirtyMask; // offset 0x10, size 0x4
    class MemStream mObjData; // offset 0x14, size 0x20
};
// Range: 0x8053BE5C -> 0x8053BFF4
void Synchronizable::SynchronizeIfDirty(class Synchronizable * const this /* r31 */) {
    // Local variables
    int playerNum; // r30
    class SyncObjMsg msg; // r1+0x48
    class SyncObjMsg msg; // r1+0x14

    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x8053BFF4 -> 0x8053BFFC
char * Synchronizable::GetUniqueTag() {}

// Range: 0x8053BFFC -> 0x8053C06C
void Synchronizable::AddDirtyPlayer(int playerNum /* r1+0x8 */) {}

struct {
    // total size: 0x20
} __vt__14Synchronizable; // size: 0x20, address: 0x809081E0

