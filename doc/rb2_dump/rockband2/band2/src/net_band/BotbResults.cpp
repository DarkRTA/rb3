/*
    Compile unit: C:\rockband2\band2\src\net_band\BotbResults.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80216114 -> 0x80218610
*/
// Range: 0x80216114 -> 0x8021617C
class BinStream & __rs(class BinStream & s /* r30 */, class String & str /* r31 */) {
    // Local variables
    int pSize; // r1+0x8
}

// Range: 0x8021617C -> 0x802161F4
class BinStream & __ls(class BinStream & s /* r29 */, const class String & str /* r30 */) {
    // Local variables
    int pSize; // r31
}

// Range: 0x802161F4 -> 0x80216254
class BinStream & __rs(class BinStream & s /* r30 */, class DateTime & dt /* r31 */) {
    // Local variables
    unsigned long long t; // r1+0x10
}

// Range: 0x80216254 -> 0x802162A0
class BinStream & __ls(class BinStream & s /* r31 */) {
    // Local variables
    unsigned long long t; // r0
}

// Range: 0x802162A0 -> 0x802162E0
void * BotbBattleSongInfo::BotbBattleSongInfo(class BotbBattleSongInfo * const this /* r31 */) {}

class _DDL_RBBotbBattleSongInfo : public RootObject {
    // total size: 0x10
public:
    void * __vptr$; // offset 0x0, size 0x4
    class String mShortName; // offset 0x4, size 0x4
    class String mFullName; // offset 0x8, size 0x4
    class String mArtist; // offset 0xC, size 0x4
};
class RBBotbBattleSongInfo : public _DDL_RBBotbBattleSongInfo {
    // total size: 0x10
};
// Range: 0x802162E0 -> 0x80216338
void * BotbBattleSongInfo::BotbBattleSongInfo(class BotbBattleSongInfo * const this /* r30 */, class RBBotbBattleSongInfo * result /* r31 */) {}

// Range: 0x80216338 -> 0x802163B8
void * BotbBattleSongInfo::~BotbBattleSongInfo(class BotbBattleSongInfo * const this /* r29 */) {}

// Range: 0x802163B8 -> 0x802163C0
char * BotbBattleSongInfo::ShortName() {}

// Range: 0x802163C0 -> 0x802163C8
char * BotbBattleSongInfo::FullName() {}

// Range: 0x802163C8 -> 0x8021641C
unsigned char BotbBattleSongInfo::IsCoverSong(const class BotbBattleSongInfo * const this /* r30 */) {}

// Range: 0x8021641C -> 0x80216470
class BinStream & __ls(class BinStream & s /* r30 */, const class BotbBattleSongInfo & bd /* r31 */) {}

// Range: 0x80216470 -> 0x802164C4
class BinStream & __rs(class BinStream & s /* r30 */, class BotbBattleSongInfo & bd /* r31 */) {}

class RBBotbBattleDetails : public _DDL_RBBotbBattleDetails {
    // total size: 0x58
};
// Range: 0x802164C4 -> 0x802165C4
void * BotbBattleDetails::BotbBattleDetails(class BotbBattleDetails * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__Q26Quazal19RBBotbBattleDetails;
    // -> struct [anonymous] __vt__Q26Quazal24_DDL_RBBotbBattleDetails;
}

class _List_node : public _List_node_base {
    // total size: 0x18
public:
    class RBBotbBattleSongInfo _M_data; // offset 0x8, size 0x10
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class _DDL_RBBotbBattleDetails : public RootObject {
    // total size: 0x58
public:
    void * __vptr$; // offset 0x0, size 0x4
    unsigned int mBattleID; // offset 0x4, size 0x4
    class String mShortName; // offset 0x8, size 0x4
    class String mTitle; // offset 0xC, size 0x4
    class String mDescription; // offset 0x10, size 0x4
    class String mArtFilename; // offset 0x14, size 0x4
    class String mVenueName; // offset 0x18, size 0x4
    unsigned int mDifficulty; // offset 0x1C, size 0x4
    class String mShowIn; // offset 0x20, size 0x4
    class DateTime mStartTime; // offset 0x28, size 0x8
    class DateTime mEndTime; // offset 0x30, size 0x8
    unsigned int mTimeLeftInSeconds; // offset 0x38, size 0x4
    class String mWinMetric; // offset 0x3C, size 0x4
    class String mEntryConditions; // offset 0x40, size 0x4
    class String mPerformanceModifiers; // offset 0x44, size 0x4
    class qList mSetList; // offset 0x48, size 0x8
    unsigned int mPrize; // offset 0x50, size 0x4
    int mSecondsUntilStart; // offset 0x54, size 0x4
};
// Range: 0x802165C4 -> 0x80216648
void * BotbBattleDetails::~BotbBattleDetails(class BotbBattleDetails * const this /* r30 */) {}

// Range: 0x80216728 -> 0x80216764
void BotbBattleDetails::Clear(class BotbBattleDetails * const this /* r31 */) {}

// Range: 0x80216764 -> 0x80216770
char * BotbBattleDetails::Title() {}

// Range: 0x80216770 -> 0x8021677C
char * BotbBattleDetails::Description() {}

// Range: 0x8021677C -> 0x80216788
char * BotbBattleDetails::ArtFilename() {}

// Range: 0x80216788 -> 0x80216794
int BotbBattleDetails::TimeLeftInSeconds() {}

// Range: 0x80216794 -> 0x802167A0
char * BotbBattleDetails::EntryConditions() {}

// Range: 0x802167A0 -> 0x802167AC
char * BotbBattleDetails::PerformanceModifiers() {}

struct iterator {
    // total size: 0x1
};
class reverse_iterator : public iterator {
    // total size: 0x4
protected:
    struct _List_iterator current; // offset 0x0, size 0x4
};
// Range: 0x802167AC -> 0x80216948
void BotbBattleDetails::CacheSetList(const class BotbBattleDetails * const this /* r30 */) {
    // Local variables
    class list & setList; // r31
    class reverse_iterator it; // r1+0x48

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std32_List_node<18BotbBattleSongInfo>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80216948 -> 0x80216978
class list & BotbBattleDetails::SetList(const class BotbBattleDetails * const this /* r31 */) {}

// Range: 0x80216978 -> 0x80216984
int BotbBattleDetails::SecondsUntilStart() {}

// Range: 0x80216984 -> 0x80216B08
class BinStream & __ls(class BinStream & s /* r30 */, const class BotbBattleDetails & bd /* r31 */) {}

// Range: 0x80216B08 -> 0x80216C68
class BinStream & __rs(class BinStream & s /* r30 */, class BotbBattleDetails & bd /* r31 */) {}

class RBBotbBattleResultsByBandInfo : public _DDL_RBBotbBattleResultsByBandInfo {
    // total size: 0x10
};
// Range: 0x80216C68 -> 0x80216CD4
void * BotbBattleResultsByBandInfo::BotbBattleResultsByBandInfo(class BotbBattleResultsByBandInfo * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__Q26Quazal29RBBotbBattleResultsByBandInfo;
    // -> struct [anonymous] __vt__Q26Quazal34_DDL_RBBotbBattleResultsByBandInfo;
}

class _DDL_RBBotbBattleResultsByBandInfo : public RootObject {
    // total size: 0x10
public:
    void * __vptr$; // offset 0x0, size 0x4
    class String mCarrotInfo; // offset 0x4, size 0x4
    unsigned int mOverallRank; // offset 0x8, size 0x4
    unsigned int mTotalRanked; // offset 0xC, size 0x4
};
// Range: 0x80216CD4 -> 0x80216D48
void * BotbBattleResultsByBandInfo::~BotbBattleResultsByBandInfo(class BotbBattleResultsByBandInfo * const this /* r30 */) {}

// Range: 0x80216DAC -> 0x80216DB8
char * BotbBattleResultsByBandInfo::CarrotInfo() {}

// Range: 0x80216DB8 -> 0x80216DC4
int BotbBattleResultsByBandInfo::OverallRank() {}

// Range: 0x80216DC4 -> 0x80216DD0
int BotbBattleResultsByBandInfo::TotalRanked() {}

// Range: 0x80216DD0 -> 0x80216E4C
class BinStream & __ls(class BinStream & s /* r30 */, const class BotbBattleResultsByBandInfo & brbi /* r31 */) {}

// Range: 0x80216E4C -> 0x80216EB8
class BinStream & __rs(class BinStream & s /* r30 */, class BotbBattleResultsByBandInfo & brbi /* r31 */) {}

class RBBotbPlayBattleResponse : public _DDL_RBBotbPlayBattleResponse {
    // total size: 0x30
};
// Range: 0x80216EB8 -> 0x80216F54
void * BotbPlayBattleResponse::BotbPlayBattleResponse(class BotbPlayBattleResponse * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__Q26Quazal24RBBotbPlayBattleResponse;
    // -> struct [anonymous] __vt__Q26Quazal14RBPlatformGuid;
    // -> struct [anonymous] __vt__Q26Quazal19_DDL_RBPlatformGuid;
    // -> struct [anonymous] __vt__Q26Quazal29_DDL_RBBotbPlayBattleResponse;
}

class _DDL_RBBotbPlayBattleResponse : public RootObject {
    // total size: 0x30
public:
    void * __vptr$; // offset 0x0, size 0x4
    unsigned char mCanPlay; // offset 0x4, size 0x1
    class String mRivalBandName; // offset 0x8, size 0x4
    unsigned int mRivalBandScore; // offset 0xC, size 0x4
    unsigned int mRivalBandStars; // offset 0x10, size 0x4
    class RBPlatformGuid mRivalBandLeader; // offset 0x18, size 0x10
    class String mLogoName; // offset 0x28, size 0x4
};
// Range: 0x80216F54 -> 0x80216FDC
void * BotbPlayBattleResponse::~BotbPlayBattleResponse(class BotbPlayBattleResponse * const this /* r30 */) {}

// Range: 0x80217070 -> 0x802170B8
void BotbPlayBattleResponse::Clear(class BotbPlayBattleResponse * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x802170B8 -> 0x802170C4
unsigned char BotbPlayBattleResponse::CanPlay() {}

// Range: 0x802170C4 -> 0x802170D0
char * BotbPlayBattleResponse::RivalBandName() {}

// Range: 0x802170D0 -> 0x802170DC
int BotbPlayBattleResponse::RivalBandScore() {}

// Range: 0x802170DC -> 0x802170E8
int BotbPlayBattleResponse::RivalBandStars() {}

// Range: 0x802170E8 -> 0x802170F4
char * BotbPlayBattleResponse::RivalBandLogoName() {}

// Range: 0x802170F4 -> 0x802171D0
class BinStream & __ls(class BinStream & s /* r30 */, const class BotbPlayBattleResponse & pbr /* r31 */) {}

// Range: 0x802171D0 -> 0x802172A0
class BinStream & __rs(class BinStream & s /* r29 */, class BotbPlayBattleResponse & pbr /* r30 */) {}

class RBBotbRecordBattleResponse : public _DDL_RBBotbRecordBattleResponse {
    // total size: 0x18
};
// Range: 0x802172A0 -> 0x80217324
void * BotbRecordBattleResponse::BotbRecordBattleResponse(class BotbRecordBattleResponse * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__Q26Quazal26RBBotbRecordBattleResponse;
    // -> struct [anonymous] __vt__Q26Quazal31_DDL_RBBotbRecordBattleResponse;
}

class _DDL_RBBotbRecordBattleResponse : public RootObject {
    // total size: 0x18
public:
    void * __vptr$; // offset 0x0, size 0x4
    class String mPerformanceInfo; // offset 0x4, size 0x4
    unsigned int mApproxOverallRank; // offset 0x8, size 0x4
    class String mCarrotInfo; // offset 0xC, size 0x4
    class String mLogoName; // offset 0x10, size 0x4
    class String mNewsCookies; // offset 0x14, size 0x4
};
// Range: 0x80217324 -> 0x80217398
void * BotbRecordBattleResponse::~BotbRecordBattleResponse(class BotbRecordBattleResponse * const this /* r30 */) {}

// Range: 0x80217428 -> 0x80217434
char * BotbRecordBattleResponse::PerformanceInfo() {}

// Range: 0x80217434 -> 0x80217440
unsigned int BotbRecordBattleResponse::ApproxOverallRank() {}

// Range: 0x80217440 -> 0x8021744C
char * BotbRecordBattleResponse::CarrotInfo() {}

// Range: 0x8021744C -> 0x80217458
char * BotbRecordBattleResponse::GetCookies() {}

class _DDL_RBBotbOpenBattleInfo : public RootObject {
    // total size: 0x20
public:
    void * __vptr$; // offset 0x0, size 0x4
    unsigned int mBattleID; // offset 0x4, size 0x4
    class String mShortName; // offset 0x8, size 0x4
    class String mTitle; // offset 0xC, size 0x4
    unsigned char mAlreadyPlayed; // offset 0x10, size 0x1
    class String mShowIn; // offset 0x14, size 0x4
    class String mVenueName; // offset 0x18, size 0x4
    class String mArtFilename; // offset 0x1C, size 0x4
};
class RBBotbOpenBattleInfo : public _DDL_RBBotbOpenBattleInfo {
    // total size: 0x20
};
// Range: 0x80217458 -> 0x80217504
void * BotbOpenBattleRow::BotbOpenBattleRow(class BotbOpenBattleRow * const this /* r30 */, class RBBotbOpenBattleInfo * result /* r31 */) {}

class qList : public list, public RootObject {
    // total size: 0x8
};
class RBBotbOpenBattlesQList {
    // total size: 0x8
public:
    class qList mData; // offset 0x0, size 0x8
};
// Range: 0x80217504 -> 0x8021759C
void * BotbOpenBattlesList::BotbOpenBattlesList(class BotbOpenBattlesList * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__19BotbOpenBattlesList;
}

class _List_node : public _List_node_base {
    // total size: 0x28
public:
    class RBBotbOpenBattleInfo _M_data; // offset 0x8, size 0x20
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x8021759C -> 0x8021763C
void * BotbOpenBattlesList::~BotbOpenBattlesList(class BotbOpenBattlesList * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__19BotbOpenBattlesList;
}

// Range: 0x8021763C -> 0x8021767C
void BotbOpenBattlesList::Clear(class BotbOpenBattlesList * const this /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8021767C -> 0x80217800
void BotbOpenBattlesList::Update(class BotbOpenBattlesList * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std31_List_node<17BotbOpenBattleRow>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std31_List_node<17BotbOpenBattleRow>; // size: 0x8, address: 0x808ADD90
class _DDL_RBBotbBattleParticipatedIn : public RootObject {
    // total size: 0x1C
public:
    void * __vptr$; // offset 0x0, size 0x4
    unsigned int mBattleID; // offset 0x4, size 0x4
    class String mBattleName; // offset 0x8, size 0x4
    unsigned int mBandRank; // offset 0xC, size 0x4
    unsigned char mBattleOpen; // offset 0x10, size 0x1
    class String mArtFilename; // offset 0x14, size 0x4
    unsigned int mNumPostedScores; // offset 0x18, size 0x4
};
class RBBotbBattleParticipatedIn : public _DDL_RBBotbBattleParticipatedIn {
    // total size: 0x1C
};
// Range: 0x80217800 -> 0x80217880
void * BotbBattlesParticipatedInRow::BotbBattlesParticipatedInRow(class BotbBattlesParticipatedInRow * const this /* r30 */, class RBBotbBattleParticipatedIn * result /* r31 */) {}

class qList : public list, public RootObject {
    // total size: 0x8
};
class RBBotbBattlesParticipatedInQList {
    // total size: 0x8
public:
    class qList mData; // offset 0x0, size 0x8
};
// Range: 0x80217880 -> 0x80217918
void * BotbBattlesParticipatedInList::BotbBattlesParticipatedInList(class BotbBattlesParticipatedInList * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__29BotbBattlesParticipatedInList;
}

class _List_node : public _List_node_base {
    // total size: 0x24
public:
    class RBBotbBattleParticipatedIn _M_data; // offset 0x8, size 0x1C
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x80217918 -> 0x802179B8
void * BotbBattlesParticipatedInList::~BotbBattlesParticipatedInList(class BotbBattlesParticipatedInList * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__29BotbBattlesParticipatedInList;
}

// Range: 0x802179B8 -> 0x802179F8
void BotbBattlesParticipatedInList::Clear(class BotbBattlesParticipatedInList * const this /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x802179F8 -> 0x80217B44
void BotbBattlesParticipatedInList::Update(class BotbBattlesParticipatedInList * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std42_List_node<28BotbBattlesParticipatedInRow>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std42_List_node<28BotbBattlesParticipatedInRow>; // size: 0x8, address: 0x808ADDF0
// Range: 0x80217B44 -> 0x80217BA8
class list * BotbBattlesParticipatedInList::GetRowList(const class BotbBattlesParticipatedInList * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class _DDL_RBBotbCityWithBattle : public RootObject {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
    class String mVenueName; // offset 0x4, size 0x4
};
class RBBotbCityWithBattle : public _DDL_RBBotbCityWithBattle {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    class RBBotbCityWithBattle _M_data; // offset 0x8, size 0x8
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class _DDL_RBBotbBattleRow : public RootObject {
    // total size: 0x2C
public:
    void * __vptr$; // offset 0x0, size 0x4
    class String mName; // offset 0x4, size 0x4
    unsigned int mScore; // offset 0x8, size 0x4
    unsigned int mStars; // offset 0xC, size 0x4
    unsigned int mOverallRank; // offset 0x10, size 0x4
    class RBGuid mBandGuid; // offset 0x14, size 0x14
    class String mLogoName; // offset 0x28, size 0x4
};
class RBBotbBattleRow : public _DDL_RBBotbBattleRow {
    // total size: 0x2C
};
// Range: 0x80217BA8 -> 0x80217C2C
void * BotbBattleResultsRow::BotbBattleResultsRow(class BotbBattleResultsRow * const this /* r30 */, class RBBotbBattleRow * result /* r31 */) {}

// Range: 0x80217C2C -> 0x80217C78
void * BotbBattleResultsRow::BotbBattleResultsRow(class BotbBattleResultsRow * const this /* r31 */) {}

// Range: 0x80217C78 -> 0x80217CEC
void * BotbBattleResultsRow::~BotbBattleResultsRow(class BotbBattleResultsRow * const this /* r29 */) {}

// Range: 0x80217CEC -> 0x80217D88
class BinStream & __ls(class BinStream & s /* r30 */, const class BotbBattleResultsRow & brr /* r31 */) {}

// Range: 0x80217D88 -> 0x80217E0C
class BinStream & __rs(class BinStream & s /* r30 */, class BotbBattleResultsRow & brr /* r31 */) {}

class qList : public list, public RootObject {
    // total size: 0x8
};
class RBBotbBattleResultsQList {
    // total size: 0x8
public:
    class qList mData; // offset 0x0, size 0x8
};
// Range: 0x80217E0C -> 0x80217EA4
void * BotbBattleResultsList::BotbBattleResultsList(class BotbBattleResultsList * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__21BotbBattleResultsList;
}

class _List_node : public _List_node_base {
    // total size: 0x34
public:
    class RBBotbBattleRow _M_data; // offset 0x8, size 0x2C
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x80217EA4 -> 0x80217F44
void * BotbBattleResultsList::~BotbBattleResultsList(class BotbBattleResultsList * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__21BotbBattleResultsList;
}

// Range: 0x80217F44 -> 0x80217F84
void BotbBattleResultsList::Clear(class BotbBattleResultsList * const this /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80217F84 -> 0x802180B8
void BotbBattleResultsList::Update(class BotbBattleResultsList * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std34_List_node<20BotbBattleResultsRow>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std34_List_node<20BotbBattleResultsRow>; // size: 0x8, address: 0x808ADE28
// Range: 0x802180B8 -> 0x8021811C
class list * BotbBattleResultsList::GetRowList(const class BotbBattleResultsList * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8021811C -> 0x80218174
class BinStream & __ls(class BinStream & s /* r30 */, const class BotbBattleResultsList & brl /* r31 */) {}

// Range: 0x80218174 -> 0x802181D8
class BinStream & __rs(class BinStream & s /* r30 */, class BotbBattleResultsList & brl /* r31 */) {}

class _DDL_RBBotbNewsItem : public RootObject {
    // total size: 0xC
public:
    void * __vptr$; // offset 0x0, size 0x4
    class String mNewsItem; // offset 0x4, size 0x4
    class String mArtFilename; // offset 0x8, size 0x4
};
class RBBotbNewsItem : public _DDL_RBBotbNewsItem {
    // total size: 0xC
};
// Range: 0x802181D8 -> 0x80218234
void * BotbNewsRow::BotbNewsRow(class BotbNewsRow * const this /* r30 */, class RBBotbNewsItem * result /* r31 */) {}

class qList : public list, public RootObject {
    // total size: 0x8
};
class RBBotbNewsQList {
    // total size: 0x8
public:
    class qList mData; // offset 0x0, size 0x8
};
// Range: 0x80218234 -> 0x80218314
void * BotbNewsList::BotbNewsList(class BotbNewsList * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__12BotbNewsList;
}

class _List_node : public _List_node_base {
    // total size: 0x14
public:
    class RBBotbNewsItem _M_data; // offset 0x8, size 0xC
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x80218314 -> 0x802183E0
void * BotbNewsList::~BotbNewsList(class BotbNewsList * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__12BotbNewsList;
}

// Range: 0x802183E0 -> 0x80218420
void BotbNewsList::Clear(class BotbNewsList * const this /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80218420 -> 0x802185AC
void BotbNewsList::Update(class BotbNewsList * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std25_List_node<11BotbNewsRow>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std25_List_node<11BotbNewsRow>; // size: 0x8, address: 0x808ADE58
// Range: 0x802185AC -> 0x80218610
class list * BotbNewsList::GetRowList(const class BotbNewsList * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xC
} __vt__Q26Quazal26RBBotbRecordBattleResponse; // size: 0xC, address: 0x808ADE60
struct {
    // total size: 0x8
} __RTTI__Q26Quazal26RBBotbRecordBattleResponse; // size: 0x8, address: 0x808ADEA8
struct {
    // total size: 0xC
} __vt__Q26Quazal31_DDL_RBBotbRecordBattleResponse; // size: 0xC, address: 0x808ADEB0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal31_DDL_RBBotbRecordBattleResponse; // size: 0x8, address: 0x808ADEF8
struct {
    // total size: 0xC
} __vt__Q26Quazal24RBBotbPlayBattleResponse; // size: 0xC, address: 0x808ADF00
struct {
    // total size: 0x8
} __RTTI__Q26Quazal24RBBotbPlayBattleResponse; // size: 0x8, address: 0x808ADF48
struct {
    // total size: 0xC
} __vt__Q26Quazal29_DDL_RBBotbPlayBattleResponse; // size: 0xC, address: 0x808ADF50
struct {
    // total size: 0x8
} __RTTI__Q26Quazal29_DDL_RBBotbPlayBattleResponse; // size: 0x8, address: 0x808ADF90
struct {
    // total size: 0xC
} __vt__Q26Quazal29RBBotbBattleResultsByBandInfo; // size: 0xC, address: 0x808ADF98
struct {
    // total size: 0x8
} __RTTI__Q26Quazal29RBBotbBattleResultsByBandInfo; // size: 0x8, address: 0x808ADFE0
struct {
    // total size: 0xC
} __vt__Q26Quazal34_DDL_RBBotbBattleResultsByBandInfo; // size: 0xC, address: 0x808ADFE8
struct {
    // total size: 0x8
} __RTTI__Q26Quazal34_DDL_RBBotbBattleResultsByBandInfo; // size: 0x8, address: 0x808AE030
struct {
    // total size: 0xC
} __vt__Q26Quazal19RBBotbBattleDetails; // size: 0xC, address: 0x808AE038
struct {
    // total size: 0x8
} __RTTI__Q26Quazal19RBBotbBattleDetails; // size: 0x8, address: 0x808AE078
struct {
    // total size: 0xC
} __vt__Q26Quazal24_DDL_RBBotbBattleDetails; // size: 0xC, address: 0x808AE080
struct {
    // total size: 0x8
} __RTTI__Q26Quazal24_DDL_RBBotbBattleDetails; // size: 0x8, address: 0x808AE0C0
struct {
    // total size: 0xC
} __vt__Q26Quazal14RBPlatformGuid; // size: 0xC, address: 0x808AE0C8
struct {
    // total size: 0x8
} __RTTI__Q26Quazal14RBPlatformGuid; // size: 0x8, address: 0x808AE100
struct {
    // total size: 0xC
} __vt__Q26Quazal19_DDL_RBPlatformGuid; // size: 0xC, address: 0x808AE108
struct {
    // total size: 0x8
} __RTTI__Q26Quazal19_DDL_RBPlatformGuid; // size: 0x8, address: 0x808AE140
struct {
    // total size: 0x8
} __RTTI__Q26Quazal10RootObject; // size: 0x8, address: 0x808AE160
struct {
    // total size: 0x14
} __vt__12BotbNewsList; // size: 0x14, address: 0x808AE168
struct {
    // total size: 0x8
} __RTTI__12BotbNewsList; // size: 0x8, address: 0x808AE198
struct {
    // total size: 0x14
} __vt__21BotbBattleResultsList; // size: 0x14, address: 0x808AE1A0
struct {
    // total size: 0x8
} __RTTI__21BotbBattleResultsList; // size: 0x8, address: 0x808AE1D8
struct {
    // total size: 0x14
} __vt__29BotbBattlesParticipatedInList; // size: 0x14, address: 0x808AE1E0
struct {
    // total size: 0x8
} __RTTI__29BotbBattlesParticipatedInList; // size: 0x8, address: 0x808AE220
struct {
    // total size: 0x14
} __vt__19BotbOpenBattlesList; // size: 0x14, address: 0x808AE228
struct {
    // total size: 0x8
} __RTTI__19BotbOpenBattlesList; // size: 0x8, address: 0x808AE260

