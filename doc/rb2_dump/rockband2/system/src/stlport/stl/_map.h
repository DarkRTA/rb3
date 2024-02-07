/*
    Compile unit: C:\rockband2\system\src\stlport\stl\_map.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805C7428 -> 0x805C7CF0
*/
// Range: 0x805C7428 -> 0x805C7528
char * PlatformMgr::GetName(int padNum /* r28 */, unsigned char numbered /* r29 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Net TheNet;
}

// Range: 0x805C7528 -> 0x805C7594
char * PlatformMgr::GetNameForLocalLB() {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Net TheNet;
}

// Range: 0x805C7594 -> 0x805C76F0
void PlatformMgr::DeleteMessage(class PlatformMgr * const this /* r29 */, unsigned int messageID /* r30 */) {
    // Local variables
    class qList lstIDs; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

// Range: 0x805C76F0 -> 0x805C79F4
void PlatformMgr::SendMsg(class PlatformMgr * const this /* r27 */, class Friend * dest /* r24 */, class String & subject /* r28 */, class String & body /* r29 */, class MemStream & data /* r23 */) {
    // Local variables
    unsigned int destPID; // r0
    unsigned int * gid; // r23
    class CustomDataHolder holder; // r1+0x10

    // References
    // -> struct [anonymous] __vt__Q26Quazal16MessageRecipient;
    // -> struct [anonymous] __vt__Q26Quazal40CustomDataHolder<Q26Quazal11UserMessage>;
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __vt__Q26Quazal11TextMessage;
    // -> struct [anonymous] __vt__Q26Quazal16_DDL_TextMessage;
    // -> const class DateTime & Never;
    // -> struct [anonymous] __vt__Q26Quazal11UserMessage;
    // -> struct [anonymous] __vt__Q26Quazal16_DDL_UserMessage;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

// Range: 0x805C79F4 -> 0x805C7C74
void PlatformMgr::AcceptInvite(class PlatformMgr * const this /* r31 */, const char * sessionID /* r30 */) {
    // Local variables
    unsigned int gatheringID; // r0
    class InviteAcceptedMsg msg; // r1+0x38

    // References
    // -> struct [anonymous] __vt__17InviteAcceptedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Debug TheDebug;
}

// Range: 0x805C7C74 -> 0x805C7CF0
unsigned char PlatformMgr::IsUserAGuest(const class PlatformMgr * const this /* r30 */) {
    // Local variables
    int padNum; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}


