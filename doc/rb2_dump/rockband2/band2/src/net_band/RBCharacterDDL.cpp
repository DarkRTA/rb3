/*
    Compile unit: C:\rockband2\band2\src\net_band\RBCharacterDDL.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8021A2E8 -> 0x8021A490
*/
class _DDL_RBCharacter : public RootObject {
    // total size: 0x28
public:
    void * __vptr$; // offset 0x0, size 0x4
    unsigned int mPrincipalID; // offset 0x4, size 0x4
    class String mName; // offset 0x8, size 0x4
    class String mHometown; // offset 0xC, size 0x4
    class Buffer mOutfit; // offset 0x10, size 0x14
    unsigned int mCash; // offset 0x24, size 0x4
};
// Range: 0x8021A2E8 -> 0x8021A3A8
void _DDL_RBCharacter::Add(class Message * pMessageToSend /* r29 */, const class _DDL_RBCharacter & oValue /* r30 */) {}

// Range: 0x8021A3A8 -> 0x8021A490
void _DDL_RBCharacter::Extract(class Message * pReceivedMessage /* r29 */, class _DDL_RBCharacter * pValue /* r30 */) {}


