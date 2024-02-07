/*
    Compile unit: C:\rockband2\system\src\net\HarmonixGatheringDDL.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80521F40 -> 0x805223C4
*/
class _DDL_HarmonixGathering : public Gathering {
    // total size: 0x68
public:
    int mGameMode; // offset 0x28, size 0x4
    unsigned char mRanked; // offset 0x2C, size 0x1
    unsigned char mPublic; // offset 0x2D, size 0x1
    int mProp0; // offset 0x30, size 0x4
    int mProp1; // offset 0x34, size 0x4
    int mProp2; // offset 0x38, size 0x4
    int mProp3; // offset 0x3C, size 0x4
    int mProp4; // offset 0x40, size 0x4
    int mProp5; // offset 0x44, size 0x4
    int mProp6; // offset 0x48, size 0x4
    int mProp7; // offset 0x4C, size 0x4
    int mProp8; // offset 0x50, size 0x4
    class Buffer mBuffer; // offset 0x54, size 0x14
};
// Range: 0x80521F40 -> 0x805220A8
void _DDL_HarmonixGathering::Add(class Message * pMessageToSend /* r29 */, const class _DDL_HarmonixGathering & oValue /* r30 */) {}

// Range: 0x805220A8 -> 0x80522238
void _DDL_HarmonixGathering::Extract(class Message * pReceivedMessage /* r29 */, class _DDL_HarmonixGathering * pValue /* r30 */) {}

// Range: 0x80522238 -> 0x80522294
unsigned char _DDL_HarmonixGathering::IsA(const class String & strClass /* r31 */) {}

// Range: 0x80522294 -> 0x80522330
unsigned char _DDL_HarmonixGathering::IsAKindOf(const class _DDL_HarmonixGathering * const this /* r28 */, const class String & strClass /* r29 */) {}

// Range: 0x80522330 -> 0x80522340
void _DDL_HarmonixGathering::StreamIn(const class _DDL_HarmonixGathering * const this /* r0 */) {}

// Range: 0x80522340 -> 0x80522350
void _DDL_HarmonixGathering::StreamOut(class _DDL_HarmonixGathering * const this /* r0 */) {}

struct {
    // total size: 0x28
} __vt__Q26Quazal17HarmonixGathering; // size: 0x28, address: 0x80904BC0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal17HarmonixGathering; // size: 0x8, address: 0x80904C28
struct {
    // total size: 0x28
} __vt__Q26Quazal22_DDL_HarmonixGathering; // size: 0x28, address: 0x80904C30
struct {
    // total size: 0x8
} __RTTI__Q26Quazal22_DDL_HarmonixGathering; // size: 0x8, address: 0x80904C98
struct {
    // total size: 0x8
} __RTTI__Q26Quazal9Gathering; // size: 0x8, address: 0x80904CC8
struct {
    // total size: 0x8
} __RTTI__Q26Quazal14_DDL_Gathering; // size: 0x8, address: 0x80904CF8

