/*
    Compile unit: C:\rockband2\band2\src\net_band\RockCentral.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80224214 -> 0x8022BDA4
*/
class Symbol t; // size: 0x4, address: 0x80A4EA74
class BandProfileCache {
    // total size: 0x40
    unsigned char mNextProfile; // offset 0x0, size 0x1
    unsigned char mUsed[3]; // offset 0x1, size 0x3
    class HxGuid mGuids[3]; // offset 0x4, size 0x30
    class RemoteBandData * mProfiles[3]; // offset 0x34, size 0xC
};
// Range: 0x80224214 -> 0x8022428C
void * BandProfileCache::BandProfileCache(class BandProfileCache * const this /* r30 */) {
    // Local variables
    int n; // r4
}

// Range: 0x8022428C -> 0x802242F8
void BandProfileCache::Init(class BandProfileCache * const this /* r30 */) {
    // Local variables
    int n; // r31
}

// Range: 0x802242F8 -> 0x8022436C
void BandProfileCache::Terminate(class BandProfileCache * const this /* r30 */) {
    // Local variables
    int n; // r31
}

// Range: 0x8022436C -> 0x80224404
class RemoteBandData * BandProfileCache::FindBandProfile(class BandProfileCache * const this /* r29 */, const class HxGuid & guid /* r30 */) {
    // Local variables
    int n; // r31
}

// Range: 0x80224404 -> 0x80224494
void BandProfileCache::InvalidateBandProfile(class BandProfileCache * const this /* r28 */, const class HxGuid & bandGuid /* r29 */) {
    // Local variables
    int n; // r30
}

// Range: 0x80224494 -> 0x80224528
void BandProfileCache::InvalidateBandProfileByMember(class BandProfileCache * const this /* r28 */, const class HxGuid & charGuid /* r29 */) {
    // Local variables
    int n; // r30
}

// Range: 0x80224528 -> 0x8022458C
class RemoteBandData * BandProfileCache::GetNewProfile() {
    // Local variables
    int nextProfile; // r7
}

class RBBotbClient : public ClientProtocol {
    // total size: 0x38
};
class RockCentralGateway RockCentral; // size: 0xC8, address: 0x8097CA50
// Range: 0x8022458C -> 0x80224598
static void RockCentralTerminate() {
    // References
    // -> class RockCentralGateway RockCentral;
}

class String kServerVer; // size: 0xC, address: 0x8097CB24
// Range: 0x80224598 -> 0x802246D4
void * RockCentralGateway::RockCentralGateway(class RockCentralGateway * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__18RockCentralGateway;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x802246D4 -> 0x80224810
void * RockCentralGateway::~RockCentralGateway(class RockCentralGateway * const this /* r28 */) {
    // References
    // -> struct [anonymous] __vt__18RockCentralGateway;
}

// Range: 0x80224810 -> 0x802248F0
void RockCentralGateway::Terminate(class RockCentralGateway * const this /* r31 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class Symbol t;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Net TheNet;
    // -> const char * gNullStr;
}

static class Symbol connection_status_changed; // size: 0x4, address: 0x80A4EA7C
// Range: 0x802248F0 -> 0x80224B5C
void RockCentralGateway::Init(class RockCentralGateway * const this /* r31 */) {
    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<PFv_v>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Symbol t;
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class Symbol connection_status_changed;
    // -> class Net TheNet;
    // -> const char * gNullStr;
    // -> unsigned int s_uiDefaultStringEncoding;
    // -> class ObjectDir * sMainDir;
}

static class Symbol modifier_online_feature; // size: 0x4, address: 0x80A4EA84
// Range: 0x80224B5C -> 0x80224E58
void RockCentralGateway::Poll(class RockCentralGateway * const this /* r30 */) {
    // References
    // -> class String kServerVer;
    // -> class Debug TheDebug;
    // -> class Net TheNet;
    // -> class GamePanel * TheGamePanel;
    // -> class ModifierMgr * TheModifierMgr;
    // -> static class Symbol modifier_online_feature;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x80224E58 -> 0x80224F34
class DataNode RockCentralGateway::OnMsg(class RockCentralGateway * const this /* r30 */) {
    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

static class Symbol lost_connection; // size: 0x4, address: 0x80A4EA8C
static class Message init; // size: 0x8, address: 0x8097CB40
// Range: 0x80224F34 -> 0x802256B4
class DataNode RockCentralGateway::OnMsg(class RockCentralGateway * const this /* r29 */, const class ServerStatusChangedMsg & msg /* r30 */) {
    // Local variables
    class String inDTA; // r1+0x14

    // References
    // -> class BandUI * TheBandUI;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol lost_connection;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__Q26Quazal12RBBotbClient;
    // -> struct [anonymous] __vt__Q26Quazal14RBConfigClient;
    // -> struct [anonymous] __vt__Q26Quazal16RBEntitiesClient;
    // -> struct [anonymous] __vt__Q26Quazal20RBLeaderboardsClient;
    // -> struct [anonymous] __vt__Q26Quazal14RBScoresClient;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

// Range: 0x802256B4 -> 0x80225754
class DataNode RockCentralGateway::OnMsg(class RockCentralGateway * const this /* r29 */, const class UserLoginMsg & msg /* r31 */) {}

// Range: 0x80225754 -> 0x8022584C
class DataNode RockCentralGateway::OnMsg(class RockCentralGateway * const this /* r29 */) {
    // Local variables
    int padNum; // r30

    // References
    // -> class Net TheNet;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7Profile;
}

// Range: 0x8022584C -> 0x8022587C
void RockCentralGateway::ForceLogout() {
    // References
    // -> class Net TheNet;
}

// Range: 0x8022587C -> 0x80225884
void RockCentralGateway::CancelOutstandingCalls() {}

// Range: 0x80225884 -> 0x8022588C
void RockCentralGateway::FailAllOutstandingCalls() {}

// Range: 0x8022588C -> 0x802259E0
void RockCentralGateway::SubmitPlayerScore(class RockCentralGateway * const this /* r23 */, class Symbol & song /* r24 */, int trackType /* r25 */, int difficulty /* r26 */, int score /* r27 */, int careerScore /* r28 */, int playerNum /* r29 */, class Object * callback /* r31 */) {
    // Local variables
    signed char role; // r1+0x9
    signed char diffID; // r1+0x8
    int padNum; // r29
    class ContextWrapper * wrapper; // r0

    // References
    // -> class Net TheNet;
}

static class Symbol career; // size: 0x4, address: 0x80A4EA94
// Range: 0x802259E0 -> 0x80225B38
void RockCentralGateway::GetPlayerStatsByID(class RockCentralGateway * const this /* r25 */, int playerID /* r26 */, class Symbol & song /* r27 */, int trackType /* r28 */, int pivotRange /* r29 */, class PlayerResultList & results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    signed char role; // r1+0x8
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class Symbol career;
    // -> class Net TheNet;
}

static class Symbol career; // size: 0x4, address: 0x80A4EA9C
// Range: 0x80225B38 -> 0x80225C90
void RockCentralGateway::GetPlayerStatsByRanking(class RockCentralGateway * const this /* r25 */, int topRank /* r26 */, class Symbol & song /* r27 */, int trackType /* r28 */, int numResults /* r30 */, class PlayerResultList & results /* r29 */, class Object * callback /* r31 */) {
    // Local variables
    signed char role; // r1+0x8
    int bottomRank; // r30
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class Symbol career;
    // -> class Net TheNet;
}

static class qList friendsGuids; // size: 0x8, address: 0x8097CB58
static class Symbol career; // size: 0x4, address: 0x80A4EAA4
// Range: 0x80225C90 -> 0x80226014
void RockCentralGateway::GetPlayerStatsByFriends(class RockCentralGateway * const this /* r26 */, class Symbol & song /* r27 */, int trackType /* r22 */, class vector & friends /* r28 */, class PlayerResultList & results /* r29 */, class Object * callback /* r30 */) {
    // Local variables
    signed char role; // r1+0x8
    int n; // r31
    class RBPlatformGuid guid; // r1+0x40
    class RBPlatformGuid guidself; // r1+0x30
    class String guidstring; // r1+0x1C
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class Symbol career;
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __vt__Q26Quazal14RBPlatformGuid;
    // -> struct [anonymous] __vt__Q26Quazal19_DDL_RBPlatformGuid;
    // -> static class qList friendsGuids;
    // -> class Net TheNet;
}

// Range: 0x80226014 -> 0x80226110
void RockCentralGateway::SubmitBandScore(class RockCentralGateway * const this /* r25 */, class Symbol & song /* r26 */, int score /* r27 */, int careerScore /* r28 */, int fans /* r29 */, class HxGuid & bandID /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0x18
    class ContextWrapper * wrapper; // r0

    // References
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Net TheNet;
}

// Range: 0x80226110 -> 0x802261BC
void RockCentralGateway::SubmitBandFans(class RockCentralGateway * const this /* r29 */, int fans /* r30 */, class HxGuid & bandID /* r31 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0xC
    class ContextWrapper * wrapper; // r0

    // References
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Net TheNet;
}

static class Symbol career; // size: 0x4, address: 0x80A4EAAC
// Range: 0x802261BC -> 0x80226308
void RockCentralGateway::GetBandStatsByID(class RockCentralGateway * const this /* r26 */, class HxGuid & bandID /* r27 */, class Symbol & song /* r28 */, int pivotRange /* r29 */, class BandResultList & results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0x10
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class Symbol career;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Net TheNet;
}

static class Symbol career; // size: 0x4, address: 0x80A4EAB4
// Range: 0x80226308 -> 0x8022646C
void RockCentralGateway::GetBandStatsByRanking(class RockCentralGateway * const this /* r26 */, int topRank /* r27 */, class Symbol & song /* r28 */, int numResults /* r30 */, class BandResultList & results /* r29 */, class Object * callback /* r31 */) {
    // Local variables
    int bottomRank; // r30
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class Symbol career;
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

static class qList friendsGuids; // size: 0x8, address: 0x8097CB70
static class Symbol career; // size: 0x4, address: 0x80A4EABC
// Range: 0x8022646C -> 0x802267E0
void RockCentralGateway::GetBandStatsByFriends(class RockCentralGateway * const this /* r26 */, class Symbol & song /* r27 */, class vector & friends /* r28 */, class BandResultList & results /* r29 */, class Object * callback /* r30 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0x50
    int n; // r31
    class RBPlatformGuid guid; // r1+0x40
    class RBPlatformGuid guidself; // r1+0x30
    class String guidstring; // r1+0x18
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class Symbol career;
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __vt__Q26Quazal14RBPlatformGuid;
    // -> struct [anonymous] __vt__Q26Quazal19_DDL_RBPlatformGuid;
    // -> static class qList friendsGuids;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Net TheNet;
}

// Range: 0x802267E0 -> 0x802268B4
void RockCentralGateway::GetBandFansByID(class RockCentralGateway * const this /* r27 */, class HxGuid & bandID /* r28 */, int pivotRange /* r29 */, class BandResultList & results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0xC
    class ContextWrapper * wrapper; // r0

    // References
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Net TheNet;
}

// Range: 0x802268B4 -> 0x802269A0
void RockCentralGateway::GetBandFansByRanking(class RockCentralGateway * const this /* r27 */, int topRank /* r28 */, int numResults /* r31 */, class BandResultList & results /* r29 */, class Object * callback /* r30 */) {
    // Local variables
    int bottomRank; // r31
    class ContextWrapper * wrapper; // r0

    // References
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

static class qList friendsGuids; // size: 0x8, address: 0x8097CB88
// Range: 0x802269A0 -> 0x80226C98
void RockCentralGateway::GetBandFansByFriends(class RockCentralGateway * const this /* r27 */, class vector & friends /* r28 */, class BandResultList & results /* r29 */, class Object * callback /* r30 */) {
    // Local variables
    int n; // r31
    class RBPlatformGuid guid; // r1+0x38
    class RBPlatformGuid guidself; // r1+0x28
    class String guidstring; // r1+0x14
    class ContextWrapper * wrapper; // r0

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __vt__Q26Quazal14RBPlatformGuid;
    // -> struct [anonymous] __vt__Q26Quazal19_DDL_RBPlatformGuid;
    // -> static class qList friendsGuids;
    // -> class Net TheNet;
}

// Range: 0x80226C98 -> 0x80226FBC
void RockCentralGateway::UpdateChar(class RockCentralGateway * const this /* r25 */, class TourCharLocal * tourChar /* r26 */, class Object * pObjCallback /* r27 */, int id /* r28 */, int flags /* r29 */) {
    // Local variables
    int playerNum; // r0
    int padNum; // r30
    class RBGuid guid; // r1+0x38
    class RBCharacter latestChar; // r1+0x50
    class MemStream s; // r1+0x18
    class ContextWrapper * wrapper; // r30

    // References
    // -> struct [anonymous] __vt__9IdUpdater;
    // -> struct [anonymous] __vt__Q26Quazal11RBCharacter;
    // -> struct [anonymous] __vt__Q26Quazal16_DDL_RBCharacter;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Net TheNet;
}

class IdUpdater : public Updatable {
    // total size: 0x10
public:
    signed char mRetCode; // offset 0x8, size 0x1
    unsigned int mID; // offset 0xC, size 0x4
};
// Range: 0x80226FBC -> 0x80226FFC
void * IdUpdater::~IdUpdater(class IdUpdater * const this /* r31 */) {}

// Range: 0x80226FFC -> 0x8022718C
void RockCentralGateway::UpdateCharSecData(class RockCentralGateway * const this /* r27 */, class TourCharLocal * tourChar /* r28 */, class Object * pObjCallback /* r29 */, int id /* r30 */) {
    // Local variables
    int playerNum; // r0
    int padNum; // r0
    class RBGuid guid; // r1+0xC
    class ContextWrapper * wrapper; // r30

    // References
    // -> struct [anonymous] __vt__9IdUpdater;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Net TheNet;
}

// Range: 0x8022718C -> 0x802272C8
void RockCentralGateway::VerifyCharName(class RockCentralGateway * const this /* r26 */, const char * charName /* r27 */, class Object * pObjCallback /* r28 */, int id /* r30 */, int flags /* r29 */) {
    // Local variables
    class ContextWrapper * wrapper; // r30

    // References
    // -> struct [anonymous] __vt__9IdUpdater;
    // -> class Net TheNet;
}

static class qList memberGuids; // size: 0x8, address: 0x8097CBA0
class RBBandTopScoreQList {
    // total size: 0x8
public:
    class qList mData; // offset 0x0, size 0x8
};
static class RBBandTopScoreQList topScores; // size: 0x8, address: 0x8097CBB8
// Range: 0x802272C8 -> 0x80227A48
void RockCentralGateway::UpdateBand(class RockCentralGateway * const this /* r25 */, class TourBand * b /* r26 */, class Object * callback /* r28 */, int id /* r24 */, int flags /* r27 */) {
    // Local variables
    int playerNum; // r0
    int padNum; // r22
    class RBGuid guid; // r1+0xBC
    class RBBand latestBand; // r1+0xD0
    class String bandLogoString; // r1+0x48
    class ContextWrapper * wrapper; // r29
    class vector membership; // r1+0x88
    int i; // r28
    class RBGuid r; // r1+0xA8
    class vector bandTopScores; // r1+0x7C
    int i; // r28
    class RBBandTopScore t; // r1+0x94

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__Q26Quazal14RBBandTopScore;
    // -> struct [anonymous] __vt__Q26Quazal19_DDL_RBBandTopScore;
    // -> static class RBBandTopScoreQList topScores;
    // -> struct [anonymous] __vt__Q26Quazal11_DDL_RBGuid;
    // -> static class qList memberGuids;
    // -> struct [anonymous] __vt__9IdUpdater;
    // -> struct [anonymous] __vt__Q26Quazal6RBBand;
    // -> struct [anonymous] __vt__Q26Quazal11_DDL_RBBand;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Net TheNet;
}

// Range: 0x80227A48 -> 0x80227B84
void RockCentralGateway::VerifyBandName(class RockCentralGateway * const this /* r26 */, const char * bandName /* r27 */, class Object * pObjCallback /* r28 */, int id /* r30 */, int flags /* r29 */) {
    // Local variables
    class ContextWrapper * wrapper; // r30

    // References
    // -> struct [anonymous] __vt__9IdUpdater;
    // -> class Net TheNet;
}

// Range: 0x80227B84 -> 0x80227CC0
void RockCentralGateway::VerifyBandMotto(class RockCentralGateway * const this /* r26 */, const char * bandMotto /* r27 */, class Object * pObjCallback /* r28 */, int id /* r30 */, int flags /* r29 */) {
    // Local variables
    class ContextWrapper * wrapper; // r30

    // References
    // -> struct [anonymous] __vt__9IdUpdater;
    // -> class Net TheNet;
}

class RBBandMemberQList {
    // total size: 0x8
public:
    class qList mData; // offset 0x0, size 0x8
};
class BandRowConverter : public Updatable {
    // total size: 0x2C
public:
    class RBBand * mQBandData; // offset 0x8, size 0x4
    class DateTime * mQCreateDate; // offset 0xC, size 0x4
    class RBBandMemberQList * mQMemberList; // offset 0x10, size 0x4
    class RBBandTopScoreQList * mQTopScoreList; // offset 0x14, size 0x4
    class RBPlatformGuid * mQPlatformGuid; // offset 0x18, size 0x4
    unsigned int mFans; // offset 0x1C, size 0x4
    unsigned int mCareerHighScore; // offset 0x20, size 0x4
private:
    class RemoteBandData * mBandData; // offset 0x24, size 0x4
    unsigned char mUpdated; // offset 0x28, size 0x1
};
// Range: 0x80227CC0 -> 0x80227E54
void * BandRowConverter::BandRowConverter(class BandRowConverter * const this /* r30 */, class RemoteBandData * pBand /* r31 */, const class HxGuid & guid /* r28 */) {
    // References
    // -> struct [anonymous] __vt__Q26Quazal14RBPlatformGuid;
    // -> struct [anonymous] __vt__Q26Quazal19_DDL_RBPlatformGuid;
    // -> struct [anonymous] __vt__Q26Quazal6RBBand;
    // -> struct [anonymous] __vt__Q26Quazal11_DDL_RBBand;
    // -> struct [anonymous] __vt__16BandRowConverter;
}

// Range: 0x80227E54 -> 0x80227F60
void * BandRowConverter::~BandRowConverter(class BandRowConverter * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__16BandRowConverter;
}

// Range: 0x80227F60 -> 0x80228488
void BandRowConverter::Update(class BandRowConverter * const this /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x54
    struct BandMember bm; // r1+0x78
    struct _List_iterator it; // r1+0x50
    struct SongStatus ss; // r1+0x60
    struct DateTime createDate; // r1+0x58

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80228488 -> 0x80228490
void RockCentralGateway::InvalidateBandProfile() {}

static class RockCentralOpCompleteMsg msg; // size: 0x8, address: 0x8097CBD0
static class RockCentralOpCompleteMsg msg; // size: 0x8, address: 0x8097CBE8
static class RockCentralOpCompleteMsg msg; // size: 0x8, address: 0x8097CC00
// Range: 0x80228490 -> 0x80228880
void RockCentralGateway::GetBandProfile(class RockCentralGateway * const this /* r26 */, const class HxGuid & guid /* r27 */, class RemoteBandData * * pProfile /* r28 */, class Object * pObjCallback /* r30 */, int id /* r29 */) {
    // Local variables
    class RemoteBandData * profile; // r0
    class ContextWrapper * wrapper; // r30
    class RBGuid bandGuid; // r1+0x40

    // References
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> static class RockCentralOpCompleteMsg msg;
    // -> class Debug TheDebug;
    // -> static class RockCentralOpCompleteMsg msg;
    // -> class Net TheNet;
    // -> static class RockCentralOpCompleteMsg msg;
}

static class RockCentralOpCompleteMsg msg; // size: 0x8, address: 0x8097CC18
static class qList guidList; // size: 0x8, address: 0x8097CC30
// Range: 0x80228880 -> 0x80228A74
void RockCentralGateway::GetPresenceInfo(class RockCentralGateway * const this /* r27 */, class vector & idList /* r28 */, class PresenceResultList & resultList /* r29 */, class Object * callback /* r30 */) {
    // Local variables
    int n; // r31
    class RBPlatformGuid guid; // r1+0x20
    class ContextWrapper * wrapper; // r0

    // References
    // -> struct [anonymous] __vt__Q26Quazal14RBPlatformGuid;
    // -> struct [anonymous] __vt__Q26Quazal19_DDL_RBPlatformGuid;
    // -> static class qList guidList;
    // -> class Net TheNet;
}

// Range: 0x80228A74 -> 0x80228B74
void RockCentralGateway::GetBattleById(class RockCentralGateway * const this /* r28 */, unsigned int battleID /* r1+0x8 */, const char * localeName /* r29 */, class BotbBattleDetails * results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class ContextWrapper * wrapper; // r0

    // References
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

// Range: 0x80228B74 -> 0x80228CA4
void RockCentralGateway::GetOpenBattles(class RockCentralGateway * const this /* r26 */, class HxGuid & bandID /* r27 */, const char * showIn /* r28 */, const char * localeName /* r29 */, class BotbOpenBattlesList & results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0x10
    class ContextWrapper * wrapper; // r0

    // References
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

static class qList idsDst; // size: 0x8, address: 0x8097CC48
// Range: 0x80228CA4 -> 0x80228EEC
void RockCentralGateway::GetOpenBattleResultsByBand(class RockCentralGateway * const this /* r29 */, unsigned int battleID /* r1+0x8 */, class HxGuid & bandID /* r26 */, class BotbBattleResultsByBandInfo * results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0x34
    class vector idsSrc; // r1+0x28
    int n; // r26
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class qList idsDst;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

// Range: 0x80228EEC -> 0x80228F48
void RockCentralGateway::GetBattlesByBandByQuantity(const char * localeName /* r11 */, class BotbBattlesParticipatedInList & results /* r10 */) {}

static class qList idsDst; // size: 0x8, address: 0x8097CC60
// Range: 0x80228F48 -> 0x802291C4
void RockCentralGateway::GetBattlesByBandInternal(class RockCentralGateway * const this /* r28 */, class HxGuid & bandID /* r25 */, unsigned int howFarBack /* r1+0x8 */, unsigned char byQuantity /* r1+0xC */, const char * localeName /* r29 */, class BotbBattlesParticipatedInList & results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0x3C
    class vector idsSrc; // r1+0x30
    int n; // r25
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class qList idsDst;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

static class qList idsDst; // size: 0x8, address: 0x8097CC78
// Range: 0x802291C4 -> 0x8022940C
void RockCentralGateway::PlayBattle(class RockCentralGateway * const this /* r29 */, unsigned int battleID /* r1+0x8 */, class HxGuid & bandID /* r26 */, class BotbPlayBattleResponse * results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0x34
    class vector idsSrc; // r1+0x28
    int n; // r26
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class qList idsDst;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

// Range: 0x8022940C -> 0x80229520
void RockCentralGateway::GetBattleResultsByBand(class RockCentralGateway * const this /* r28 */, unsigned int battleID /* r1+0x8 */, class HxGuid & bandID /* r29 */, unsigned int bandsAround /* r1+0xC */, unsigned int offset /* r1+0x10 */, class BotbBattleResultsList & results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0x14
    class ContextWrapper * wrapper; // r0

    // References
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

// Range: 0x80229520 -> 0x8022960C
void RockCentralGateway::GetBattleResultsByRankRange(class RockCentralGateway * const this /* r29 */, unsigned int battleID /* r1+0x8 */, unsigned int topRank /* r1+0xC */, unsigned int bottomRank /* r1+0x10 */, class BotbBattleResultsList & results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class ContextWrapper * wrapper; // r0

    // References
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

static class qList idsDst; // size: 0x8, address: 0x8097CC90
// Range: 0x8022960C -> 0x8022985C
void RockCentralGateway::GetBattleResultsByFriends(class RockCentralGateway * const this /* r29 */, unsigned int battleID /* r1+0x8 */, class HxGuid & bandID /* r26 */, class BotbBattleResultsList & results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0x34
    class vector idsSrc; // r1+0x28
    int n; // r26
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class qList idsDst;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

static class qList idsDst; // size: 0x8, address: 0x8097CCA8
// Range: 0x8022985C -> 0x80229AB4
void RockCentralGateway::RecordBattleScore(class RockCentralGateway * const this /* r29 */, unsigned int battleID /* r1+0x8 */, class HxGuid & bandID /* r26 */, unsigned int score /* r1+0xC */, unsigned int stars /* r1+0x10 */, class BotbRecordBattleResponse * results /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0x3C
    class vector idsSrc; // r1+0x30
    int n; // r26
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class qList idsDst;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

static class DateTime qLastTime; // size: 0x8, address: 0x8097CCC0
static class qList idsDst; // size: 0x8, address: 0x8097CCD8
static class String cookies; // size: 0x4, address: 0x80A4EAD0
// Range: 0x80229AB4 -> 0x80229DF8
void RockCentralGateway::GetDailyNews(class RockCentralGateway * const this /* r24 */, class HxGuid & bandID /* r23 */, const char * localeName /* r25 */, struct DateTime & lastTime /* r26 */, class String & lastCookies /* r27 */, class BotbNewsList & results /* r28 */, class Object * callback /* r29 */) {
    // Local variables
    class RBGuid bandGuid; // r1+0x44
    class vector idsSrc; // r1+0x38
    int n; // r30
    class ContextWrapper * wrapper; // r0

    // References
    // -> static class String cookies;
    // -> static class qList idsDst;
    // -> static class DateTime qLastTime;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

// Range: 0x80229DF8 -> 0x80229EAC
class DataNode RockCentralGateway::OnUpdateChar(class RockCentralGateway * const this /* r29 */, class DataArray * data /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
}

// Range: 0x80229EAC -> 0x80229F5C
class DataNode RockCentralGateway::OnUpdateCharSecData(class RockCentralGateway * const this /* r29 */, class DataArray * data /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
}

// Range: 0x80229F5C -> 0x80229FF4
class DataNode RockCentralGateway::OnVerifyCharName(class RockCentralGateway * const this /* r29 */, class DataArray * data /* r30 */) {}

// Range: 0x80229FF4 -> 0x8022A0A8
class DataNode RockCentralGateway::OnUpdateBand(class RockCentralGateway * const this /* r29 */, class DataArray * data /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8TourBand;
}

// Range: 0x8022A0A8 -> 0x8022A140
class DataNode RockCentralGateway::OnVerifyBandName(class RockCentralGateway * const this /* r29 */, class DataArray * data /* r30 */) {}

// Range: 0x8022A140 -> 0x8022A1D8
class DataNode RockCentralGateway::OnVerifyBandMotto(class RockCentralGateway * const this /* r29 */, class DataArray * data /* r30 */) {}

// Range: 0x8022A1D8 -> 0x8022A228
unsigned char RockCentralGateway::IsLoginMandatory() {
    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x8022A228 -> 0x8022A2B8
signed char RockCentralGateway::GetRoleID() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8022A2B8 -> 0x8022A348
signed char RockCentralGateway::GetDifficultyID() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8022A348 -> 0x8022A3B8
void RockCentralGateway::HxToRBGuid(const class HxGuid & in /* r30 */, class RBGuid & out /* r31 */) {}

// Range: 0x8022A3B8 -> 0x8022A42C
void RockCentralGateway::RBToHxGuid(const class RBGuid & in /* r30 */, class HxGuid & out /* r31 */) {}

// Range: 0x8022A42C -> 0x8022A648
char * RockCentralGateway::PrepareConfig() {
    // Local variables
    class String s; // r1+0x28
}

// Range: 0x8022A648 -> 0x8022A814
void RockCentralGateway::ExecuteConfig() {
    // Local variables
    class DataNode cmd; // r1+0x20
}

static class Symbol _s; // size: 0x4, address: 0x80A4EAD8
static class Symbol _s; // size: 0x4, address: 0x80A4EAE0
static class Symbol _s; // size: 0x4, address: 0x80A4EAE8
static class Symbol _s; // size: 0x4, address: 0x80A4EAF0
static class Symbol _s; // size: 0x4, address: 0x80A4EAF8
static class Symbol _s; // size: 0x4, address: 0x80A4EB00
static class Symbol _s; // size: 0x4, address: 0x80A4EB08
static class Symbol _s; // size: 0x4, address: 0x80A4EB10
static class Symbol _s; // size: 0x4, address: 0x80A4EB18
// Range: 0x8022A814 -> 0x8022BC30
class DataNode RockCentralGateway::Handle(class RockCentralGateway * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x64
    class MessageTimer _mt; // r1+0xE0
    class DataNode r; // r1+0xD8
    class DataNode r; // r1+0xD0
    class DataNode r; // r1+0xC8
    class DataNode r; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode _n; // r1+0x88

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __vt__17ProfileChangedMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__26ConnectionStatusChangedMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__12UserLoginMsg;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__22ServerStatusChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

// Range: 0x8022BC30 -> 0x8022BC38
class ContextWrapper * RockCentralGateway::NewContextWrapper() {}

// Range: 0x8022BC38 -> 0x8022BD30
void RockCentralGateway::SendFailure(class Object * object /* r31 */) {
    // Local variables
    class RockCentralOpCompleteMsg msg; // r1+0x18

    // References
    // -> struct [anonymous] __vt__7Message;
}

struct {
    // total size: 0x14
} __vt__16BandRowConverter; // size: 0x14, address: 0x808AEFAC
struct {
    // total size: 0x8
} __RTTI__16BandRowConverter; // size: 0x8, address: 0x808AEFE0
// Range: 0x8022BD30 -> 0x8022BDA4
void IdUpdater::Update() {}

struct {
    // total size: 0x14
} __vt__9IdUpdater; // size: 0x14, address: 0x808AEFE8
struct {
    // total size: 0x8
} __RTTI__9IdUpdater; // size: 0x8, address: 0x808AF018
struct {
    // total size: 0xC
} __vt__12UserLoginMsg; // size: 0xC, address: 0x808AF468
struct {
    // total size: 0x8
} __RTTI__12UserLoginMsg; // size: 0x8, address: 0x808AF490
struct {
    // total size: 0x6C
} __vt__18RockCentralGateway; // size: 0x6C, address: 0x808AF4D0
struct {
    // total size: 0x8
} __RTTI__18RockCentralGateway; // size: 0x8, address: 0x808AF570
struct {
    // total size: 0x64
} __vt__Q26Quazal14ClientProtocol; // size: 0x64, address: 0x808AF620
unsigned int s_uiDefaultStringEncoding; // size: 0x4, address: 0x80A48650
class PersistentStoreProtocolClient : public ClientProtocol {
    // total size: 0x38
};
class PersistentStoreClient : public ServiceClient {
    // total size: 0x54
    class PersistentStoreProtocolClient m_oProtocol; // offset 0x1C, size 0x38
};
class CompetitionProtocolClient : public ClientProtocol {
    // total size: 0x38
};
class CompetitionClient : public ServiceClient {
    // total size: 0x54
    class CompetitionProtocolClient m_oProtocol; // offset 0x1C, size 0x38
};

