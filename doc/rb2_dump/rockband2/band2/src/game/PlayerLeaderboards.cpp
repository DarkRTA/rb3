/*
    Compile unit: C:\rockband2\band2\src\game\PlayerLeaderboards.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800ACA60 -> 0x800ACE2C
*/
class SoloScoreLeaderboard : public PlayerLeaderboardData {
    // total size: 0x64
    class PlayerResultList mResultList; // offset 0x40, size 0x1C
    enum TrackType mTrackType; // offset 0x5C, size 0x4
    class Symbol mSong; // offset 0x60, size 0x4
};
// Range: 0x800ACA60 -> 0x800ACB00
void * SoloScoreLeaderboard::SoloScoreLeaderboard(class SoloScoreLeaderboard * const this /* r29 */, enum TrackType t /* r30 */, class Symbol & song /* r31 */) {
    // References
    // -> struct [anonymous] __vt__20SoloScoreLeaderboard;
    // -> class Symbol points;
    // -> struct [anonymous] __vt__21PlayerLeaderboardData;
}

// Range: 0x800ACB00 -> 0x800ACB78
void * SoloScoreLeaderboard::~SoloScoreLeaderboard(class SoloScoreLeaderboard * const this /* r30 */) {}

// Range: 0x800ACB78 -> 0x800ACB80
class LeaderboardResultList * SoloScoreLeaderboard::GetResultList() {}

// Range: 0x800ACB80 -> 0x800ACC40
void SoloScoreLeaderboard::EnumerateFromID(class SoloScoreLeaderboard * const this /* r28 */, class EntityID & id /* r29 */, int pageSize /* r30 */) {
    // References
    // -> class RockCentralGateway RockCentral;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800ACC40 -> 0x800ACCD0
void SoloScoreLeaderboard::EnumerateFromRank(class SoloScoreLeaderboard * const this /* r28 */, int rank /* r29 */, int pageSize /* r30 */) {
    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x800ACCD0 -> 0x800ACE2C
void SoloScoreLeaderboard::EnumerateFriendStats(class SoloScoreLeaderboard * const this /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP6Friend;
    // -> unsigned char gStlAllocNameLookup;
    // -> class LeaderboardsMgr * TheLeaderboards;
}

struct _OKToMemCpy {
    // total size: 0x1
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class PlayerResultRow : public LeaderboardResultRow {
    // total size: 0x40
    class String mPlayerName; // offset 0x1C, size 0xC
    int mRanking; // offset 0x28, size 0x4
    int mScore; // offset 0x2C, size 0x4
    class String mCharName; // offset 0x30, size 0xC
    unsigned int mDifficultyID; // offset 0x3C, size 0x4
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class PlayerResultRow * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class PlayerResultRow * * _M_start; // offset 0x0, size 0x4
    class PlayerResultRow * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__PP15PlayerResultRow; // size: 0x8, address: 0x8087D290
struct {
    // total size: 0x7C
} __vt__20SoloScoreLeaderboard; // size: 0x7C, address: 0x8087D298
struct {
    // total size: 0x8
} __RTTI__20SoloScoreLeaderboard; // size: 0x8, address: 0x8087D350
struct {
    // total size: 0x1C
} __vt__15PlayerResultRow; // size: 0x1C, address: 0x8087D358
struct {
    // total size: 0x8
} __RTTI__15PlayerResultRow; // size: 0x8, address: 0x8087D398
struct {
    // total size: 0x1C
} __vt__20LeaderboardResultRow; // size: 0x1C, address: 0x8087D3A0
struct {
    // total size: 0x8
} __RTTI__20LeaderboardResultRow; // size: 0x8, address: 0x8087D3D8
class UserLoginMsg : public Message {
    // total size: 0x8
};

