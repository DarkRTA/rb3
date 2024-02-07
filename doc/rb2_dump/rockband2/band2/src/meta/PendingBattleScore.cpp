/*
    Compile unit: C:\rockband2\band2\src\meta\PendingBattleScore.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8013C710 -> 0x8013CA98
*/
class PendingBattleScore : public Object {
    // total size: 0x4C
    int mBattleID; // offset 0x28, size 0x4
    int mAccumScore; // offset 0x2C, size 0x4
    int mTotalStars; // offset 0x30, size 0x4
    class HxGuid mBandGuid; // offset 0x34, size 0x10
    class BotbRecordBattleResponse * mResponse; // offset 0x44, size 0x4
    unsigned char mDirty; // offset 0x48, size 0x1
};
// Range: 0x8013C710 -> 0x8013C760
void * PendingBattleScore::PendingBattleScore(class PendingBattleScore * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__18PendingBattleScore;
}

// Range: 0x8013C760 -> 0x8013C7F8
void * PendingBattleScore::~PendingBattleScore(class PendingBattleScore * const this /* r30 */) {
    // References
    // -> class RockCentralGateway RockCentral;
    // -> struct [anonymous] __vt__18PendingBattleScore;
}

// Range: 0x8013C7F8 -> 0x8013C8A0
void PendingBattleScore::SetNewPendingBattleScore(class PendingBattleScore * const this /* r27 */, int battleID /* r28 */, int accumScore /* r29 */, int totalStars /* r30 */, class HxGuid & bandGuid /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x8013C8A0 -> 0x8013C93C
void PendingBattleScore::SubmitScoreIfDirty(class PendingBattleScore * const this /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x8013C93C -> 0x8013C9F4
class BinStream & __ls(class BinStream & dest /* r30 */, const class PendingBattleScore & pbs /* r31 */) {}

// Range: 0x8013C9F4 -> 0x8013CA98
class BinStream & __rs(class BinStream & src /* r30 */, class PendingBattleScore & pbs /* r31 */) {
    // Local variables
    int version; // r1+0xC
}

struct {
    // total size: 0x54
} __vt__18PendingBattleScore; // size: 0x54, address: 0x808927BC
struct {
    // total size: 0x8
} __RTTI__18PendingBattleScore; // size: 0x8, address: 0x80892838

