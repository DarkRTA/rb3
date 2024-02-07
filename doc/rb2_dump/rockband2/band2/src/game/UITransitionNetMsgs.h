/*
    Compile unit: C:\rockband2\band2\src\game\UITransitionNetMsgs.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8012AD44 -> 0x8012B2B8
*/
// Range: 0x8012AD44 -> 0x8012AD8C
class NetMessage * LocalTransitionCompleteMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__26LocalTransitionCompleteMsg;
}

// Range: 0x8012AD8C -> 0x8012ADC4
class NetMessage * AllTransitionCompleteMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__24AllTransitionCompleteMsg;
}

// Range: 0x8012ADC4 -> 0x8012AE20
class NetMessage * NetGotoScreenMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__16NetGotoScreenMsg;
    // -> struct [anonymous] __vt__18StartTransitionMsg;
}

// Range: 0x8012AE20 -> 0x8012AE7C
class NetMessage * NetPushScreenMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__16NetPushScreenMsg;
    // -> struct [anonymous] __vt__18StartTransitionMsg;
}

// Range: 0x8012AE7C -> 0x8012AECC
class NetMessage * NetPopScreenMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__15NetPopScreenMsg;
}

// Range: 0x8012AECC -> 0x8012AF28
class NetMessage * NetResetScreenMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__17NetResetScreenMsg;
    // -> struct [anonymous] __vt__18StartTransitionMsg;
}

// Range: 0x8012AF28 -> 0x8012AF84
class NetMessage * NetForceResetScreenMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__22NetForceResetScreenMsg;
    // -> struct [anonymous] __vt__18StartTransitionMsg;
}

// Range: 0x8012AF84 -> 0x8012AFE0
class NetMessage * NetSyncScreenMsg::NewNetMessage() {
    // References
    // -> struct [anonymous] __vt__16NetSyncScreenMsg;
    // -> struct [anonymous] __vt__18StartTransitionMsg;
}

// Range: 0x8012AFE0 -> 0x8012B014
char * NetForceResetScreenMsg::Name() {}

// Range: 0x8012B014 -> 0x8012B070
unsigned char NetForceResetScreenMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x8012B070 -> 0x8012B0A4
char * NetResetScreenMsg::Name() {}

// Range: 0x8012B0A4 -> 0x8012B100
unsigned char NetResetScreenMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x8012B100 -> 0x8012B134
char * NetPopScreenMsg::Name() {}

// Range: 0x8012B134 -> 0x8012B190
unsigned char NetPopScreenMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x8012B190 -> 0x8012B1C4
char * NetPushScreenMsg::Name() {}

// Range: 0x8012B1C4 -> 0x8012B220
unsigned char NetPushScreenMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x8012B220 -> 0x8012B224
void AllTransitionCompleteMsg::Load() {}

// Range: 0x8012B224 -> 0x8012B228
void AllTransitionCompleteMsg::Save() {}

// Range: 0x8012B228 -> 0x8012B25C
char * AllTransitionCompleteMsg::Name() {}

// Range: 0x8012B25C -> 0x8012B2B8
unsigned char AllTransitionCompleteMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}


