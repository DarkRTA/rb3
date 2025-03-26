#pragma once
#include "ContextWrapper.h"
#include "RBBinaryDataDDL_Wii.h"
#include "RBDataDDL_Wii.h"
#include "RBTestDDL_Wii.h"
#include "game/Defines.h"
#include "meta/ConnectionStatusPanel.h"
#include "meta/Profile.h"
#include "meta/WiiProfileMgr.h"
#include "meta_band/BandProfile.h"
#include "meta_band/Leaderboard.h"
#include "meta_band/ProfileMessages.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/WiiFriendMgr.h"
#include "net/WiiMessenger.h"
#include "net_band/DataResults.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "os/Friend.h"
#include "os/PlatformMgr.h"
#include "utl/DataPointMgr.h"
#include "utl/HxGuid.h"
#include "utl/JobMgr.h"
#include "utl/MemStream.h"

class PerformanceData;
class PlayerScore;
class AccomplishmentProgress;

class RockCentral : public MsgSource {
public:
    RockCentral();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~RockCentral();

    void ForceLogout();
    void FailAllOutstandingCalls();
    void CancelOutstandingCalls(Hmx::Object *);
    void
    GetLeaderboardByPlayer(std::vector<int> &, int, ScoreType, LeaderboardType, LeaderboardMode, int, DataResultList &, Hmx::Object *);
    void
    GetLeaderboardByRankRange(std::vector<int> &, int, ScoreType, int, int, LeaderboardType, DataResultList &, Hmx::Object *);
    void
    GetMaxRank(std::vector<int> &, int, ScoreType, LeaderboardType, DataResultList &, Hmx::Object *);
    void
    GetBattleLeaderboardByPlayer(std::vector<int> &, int, LeaderboardMode, int, DataResultList &, Hmx::Object *);
    void
    GetBattleLeaderboardByRankRange(std::vector<int> &, int, int, int, DataResultList &, Hmx::Object *);
    void GetBattleMaxRank(std::vector<int> &, int, DataResultList &, Hmx::Object *);
    void
    GetAccLeaderboardByPlayer(std::vector<int> &, Symbol &, LeaderboardMode, int, DataResultList &, Hmx::Object *);
    void
    GetAccLeaderboardByRankRange(std::vector<int> &, Symbol &, int, int, DataResultList &, Hmx::Object *);
    void GetAccMaxRank(std::vector<int> &, Symbol &, DataResultList &, Hmx::Object *);
    void
    RecordPerformance(const Profile *, const PerformanceData *, int, Hmx::Object *, DataResultList &);
    void
    RecordAccomplishmentData(const Profile *, AccomplishmentProgress *, int, Hmx::Object *, DataResultList &);
    void UpdateBandLogo(int, RndTex *, int, Hmx::Object *, int);
    void GetWebLinkStatus(const Profile *, int, DataResultList &, Hmx::Object *);
    void GetSetlistCreationStatus(const Profile *, int, DataResultList &, Hmx::Object *);
    void
    SyncAvailableSongs(const std::vector<BandProfile *> &, const std::vector<int> &, const std::vector<int> &, Hmx::Object *);
    void GetTickerInfo(const Profile *, ScoreType, DataResultList &, Hmx::Object *);

    void Init(bool);
    void Poll();
    void SyncSetlists(std::vector<BandProfile *> &, DataResultList &, Hmx::Object *);
    void GetAllSonglists(std::vector<BandProfile *> &, DataResultList &, Hmx::Object *);
    void
    RecordScore(int, int, std::vector<PlayerScore> &, int, int, bool, Hmx::Object *, DataResultList &);
    void RecordOptionData();
    int GetActiveContextHighWatermark();
    void
    RecordBattleScore(int, int, std::vector<BandProfile *> &, int, DataResultList &, Hmx::Object *);
    void GetLinkingCode(int, DataResultList &, Hmx::Object *);
    void UpdateOnlineStatus();
    void RedeemToken(int, String, DataResultList &, Hmx::Object *);
    void GetRedeemedTokensByPlayer(int, DataResultList &, Hmx::Object *);
    void GetSongFullOffer(int, DataResultList &, Hmx::Object *);
    void Terminate();
    void ExecuteConfig(const char *);
    bool IsLoginMandatory();
    void DeleteNextUser();
    void UpdateFriendList(int, std::vector<Friend *>, DataResultList &, Hmx::Object *);
    void
    UpdateFriendList(Profile *, std::vector<Friend *>, DataResultList &, Hmx::Object *);
    char GetDifficultyID(int);
    void
    GetMultipleRankingsForPlayer(Profile *, ScoreType, std::vector<int> &, DataResultList &, Hmx::Object *);
    void GetClosedBattles(std::vector<BandProfile *> &, DataResultList &, Hmx::Object *);

    bool IsOnline() { return mState == 2; }

    static String kServerVer;
    static ContextWrapperPool *mContextWrapperPool;
    static Quazal::RBDataClient *mRBData;
    static bool EnumerateFriends(int, std::vector<Friend *> &, Hmx::Object *);
    static bool SendMsg(Friend *, const char *, const char *, MemStream &);
    static void RecordDataPointNoRet(DataPoint &, int);
    static String EncodeMessage(_WiiMessageType, unsigned int, const char *);
    static _WiiFriendStatus StringToFriendStatus(const char *);
    static const char *FriendStatusToString(_WiiFriendStatus);
    static Server *IsConnected(Hmx::Object *, int, bool);
    static void SendFailure(Hmx::Object *, int, int);
    static void RecordDataPoint(DataPoint &, int, DataResultList &, Hmx::Object *);

    DataNode OnMsg(const RockCentralOpCompleteMsg &);
    DataNode OnMsg(const ConnectionStatusChangedMsg &);
    DataNode OnMsg(const ServerStatusChangedMsg &);
    DataNode OnMsg(const UserLoginMsg &);
    DataNode OnMsg(const FriendsListChangedMsg &);
    DataNode OnMsg(const ProfileChangedMsg &);
    DataNode OnMsg(const DeleteQueueUpdatedMsg &);
    DataNode OnMsg(const DeleteUserCompleteMsg &);
    DataNode OnMsg(const WiiFriendMgrOpCompleteMsg &);
    DataNode OnMsg(const WiiFriendsListChangedMsg &);
    DataNode OnMsg(const EnumerateMessagesCompleteMsg &);
    DataNode OnMsg(const SigninChangedMsg &);
    DataNode OnMsg(const InviteReceivedMsg &);

    DataResultList mConfigResultList; // 0x1c
    Quazal::RBBinaryDataClient *mRBBinaryData; // 0x34
    Quazal::RBTestClient *mRBTest; // 0x38
    int mState; // 0x3c - anon enum State
    Timer mTime; // 0x40
    float mRetryTime; // 0x70
    JobMgr mJobMgr; // 0x74
    bool mLoginBlocked; // 0x84
    bool unk85;
    HxGuid unk88;
    WiiFriendList *unk98; // 0x98
    WiiFriendList *unk9c; // 0x9c
    std::vector<Friend *> *unka0;
    Hmx::Object *unka4;
    Timer unka8;
    WiiMessageList *unkd8; // 0xd8
    Timer unke0;
    bool unk110;
    bool unk111;
    bool unk112;
};

extern RockCentral TheRockCentral;