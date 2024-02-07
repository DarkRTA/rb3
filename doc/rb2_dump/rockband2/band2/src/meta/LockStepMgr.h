/*
    Compile unit: C:\rockband2\band2\src\meta\LockStepMgr.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800FE02C -> 0x800FE29C
*/
// Range: 0x800FE02C -> 0x800FE064
class NetMessage * StartLockMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__12StartLockMsg;
}

// Range: 0x800FE064 -> 0x800FE0AC
class NetMessage * LockResponseMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__15LockResponseMsg;
}

// Range: 0x800FE0AC -> 0x800FE0E4
class NetMessage * EndLockMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__10EndLockMsg;
}

// Range: 0x800FE0E4 -> 0x800FE0E8
void EndLockMsg::Load() {}

// Range: 0x800FE0E8 -> 0x800FE0EC
void EndLockMsg::Save() {}

// Range: 0x800FE0EC -> 0x800FE120
char * EndLockMsg::Name() {}

// Range: 0x800FE120 -> 0x800FE17C
unsigned char EndLockMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x800FE17C -> 0x800FE1B0
char * LockResponseMsg::Name() {}

// Range: 0x800FE1B0 -> 0x800FE20C
unsigned char LockResponseMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x800FE20C -> 0x800FE240
char * StartLockMsg::Name() {}

// Range: 0x800FE240 -> 0x800FE29C
unsigned char StartLockMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}


