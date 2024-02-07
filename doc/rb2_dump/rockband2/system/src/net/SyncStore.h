/*
    Compile unit: C:\rockband2\system\src\net\SyncStore.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8053CD38 -> 0x8053CFBC
*/
// Range: 0x8053CD38 -> 0x8053CD94
class NetMessage * SyncObjMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__10SyncObjMsg;
}

// Range: 0x8053CD94 -> 0x8053CDCC
class NetMessage * SyncPlayerMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__13SyncPlayerMsg;
}

// Range: 0x8053CDCC -> 0x8053CE04
class NetMessage * SyncAllMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__10SyncAllMsg;
}

// Range: 0x8053CE04 -> 0x8053CE08
void SyncAllMsg::Load() {}

// Range: 0x8053CE08 -> 0x8053CE0C
void SyncAllMsg::Save() {}

// Range: 0x8053CE0C -> 0x8053CE40
char * SyncAllMsg::Name() {}

// Range: 0x8053CE40 -> 0x8053CE9C
unsigned char SyncAllMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x8053CE9C -> 0x8053CED0
char * SyncPlayerMsg::Name() {}

// Range: 0x8053CED0 -> 0x8053CF2C
unsigned char SyncPlayerMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x8053CF2C -> 0x8053CF60
char * SyncObjMsg::Name() {}

// Range: 0x8053CF60 -> 0x8053CFBC
unsigned char SyncObjMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}


