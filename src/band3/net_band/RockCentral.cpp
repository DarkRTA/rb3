#include "net_band/RockCentral.h"
#include "ContextWrapper.h"
#include "RBBinaryDataDDL_Wii.h"
#include "RBDataDDL_Wii.h"
#include "RBTestDDL_Wii.h"
#include "RockCentral.h"
#include "Services/ServiceClient.h"
#include "band3/meta_band/PerformanceData.h"
#include "bandobj/PatchDir.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/GameMode.h"
#include "game/GamePanel.h"
#include "meta/ConnectionStatusPanel.h"
#include "meta/Profile.h"
#include "meta/WiiProfileMgr.h"
#include "meta_band/BandProfile.h"
#include "meta_band/Campaign.h"
#include "meta_band/GameplayOptions.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SaveLoadManager.h"
#include "meta_band/SongStatusMgr.h"
#include "meta_band/UIEventMgr.h"
#include "net/Net.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/WiiFriendMgr.h"
#include "net/WiiMessenger.h"
#include "net_band/DataResults.h"
#include "net_band/RockCentralJobs.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/Data.h"
#include "obj/DataFile.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/NetworkSocket.h"
#include "os/OnlineID.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "ui/UIPanel.h"
#include "utl/BinStream.h"
#include "utl/DataPointMgr.h"
#include "utl/Loader.h"
#include "utl/MemStream.h"
#include "utl/Option.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include "utl/TextFileStream.h"
#include <utility>

#define INIT_DATAPOINT(type)                                                             \
    static DataPoint dataPoint;                                                          \
    dataPoint.mNameValPairs.clear();                                                     \
    dataPoint.mType = type;

#define ADD_DATA_PAIR(first, second)                                                     \
    dataPoint.mNameValPairs.insert(std::make_pair(first, second));

#define ADD_BUFFER_PAIR(buffer, second, ...)                                             \
    snprintf(buffer, sizeof(buffer), __VA_ARGS__);                                       \
    ADD_DATA_PAIR(buffer, second)

#define RECORD_DATA_POINT(num, results, obj) RecordDataPoint(dataPoint, num, results, obj)

DECOMP_FORCEACTIVE(RockCentral, __FILE__, "mUpdated")

namespace {
    void RockCentralTerminate() { TheRockCentral.Terminate(); }
}

const char *g_szMachineIdString;
TextFileStream *gDataPointLog;
RockCentral TheRockCentral;
String RockCentral::kServerVer = "3";
ContextWrapperPool *RockCentral::mContextWrapperPool;
Quazal::RBDataClient *RockCentral::mRBData;
const char *g_pStatusStrings[3] = { "Offline", "Channel", "Online" };
const char *g_WiiMessageDelimiter = ":";

RockCentral::RockCentral()
    : mRBTest(0), mState(0), mJobMgr(this), mLoginBlocked(0), unk85(0), unk98(0),
      unk9c(0), unka0(0), unka4(0), unkd8(0), unk110(0), unk111(0), unk112(0) {}

RockCentral::~RockCentral() { delete mContextWrapperPool; }

void RockCentral::Terminate() {
    TheNet.GetServer()->RemoveSink(this);
    ThePlatformMgr.RemoveSink(this);
    TheProfileMgr.RemoveSink(this, ProfileChangedMsg::Type());
    TheWiiFriendMgr.RemoveSink(this, WiiFriendsListChangedMsg::Type());
    ThePlatformMgr.RemoveSink(this, SigninChangedMsg::Type());
    ThePlatformMgr.RemoveSink(this, InviteReceivedMsg::Type());
    TheWiiProfileMgr.RemoveSink(this, DeleteQueueUpdatedMsg::Type());
    if (unk98)
        RELEASE(unk98);
    if (unk9c)
        RELEASE(unk9c);
    if (unkd8)
        RELEASE(unkd8);
}

void RockCentral::Init(bool b1) {
    mContextWrapperPool = new ContextWrapperPool();
    SetName("rock_central", ObjectDir::sMainDir);

    TheNet.GetServer()->AddSink(this);
    ThePlatformMgr.AddSink(this, connection_status_changed);
    ThePlatformMgr.AddSink(this, FriendsListChangedMsg::Type());
    TheProfileMgr.AddSink(this, ProfileChangedMsg::Type());
    TheWiiFriendMgr.AddSink(this, WiiFriendsListChangedMsg::Type());
    ThePlatformMgr.AddSink(this, SigninChangedMsg::Type());
    ThePlatformMgr.AddSink(this, InviteReceivedMsg::Type());
    TheWiiProfileMgr.AddSink(this, DeleteQueueUpdatedMsg::Type());

    unk98 = new WiiFriendList();
    unk9c = new WiiFriendList();
    unkd8 = new WiiMessageList();

    ThePlatformMgr.RegisterEnumerateFriendsCallback(EnumerateFriends);
    ThePlatformMgr.RegisterSendMsgCallback(SendMsg);
    TheDebug.AddExitCallback(RockCentralTerminate);
    TheDataPointMgr.SetDataPointRecorder(RecordDataPointNoRet);
    unk88.Generate();

    mTime.Start();
    mRetryTime = mTime.Ms();
    unk85 = b1;
    const char *optionStr = OptionStr("log_datapoints", nullptr);
    if (optionStr) {
        gDataPointLog = new TextFileStream(optionStr, false);
    }
}

void RockCentral::Poll() {
    static bool skipIt;
    skipIt = !skipIt;
    if (!skipIt) {
        mTime.Split();
#ifdef MILO_DEBUG
        if (mState - 1U > 2)
#endif
            if ((mState == 4 || mState == 0) && ThePlatformMgr.IsConnected()
                && (mTime.Ms() < mRetryTime && !IsLoginMandatory())
                && (!mLoginBlocked
                    && (!TheGamePanel || TheGamePanel->GetState() == UIPanel::kUnloaded)
                )) {
                mState = 1;
                TheNet.GetServer()->Login();
            } else {
                MILO_FAIL("Bad Rock Central state");
            }

        mContextWrapperPool->Poll();
        mJobMgr.Poll();
#ifdef MILO_DEBUG
        if (unk112) {
            for (int i = 0; i < 4; i++) {
                int pid = TheServer->GetPlayerID(i);
                if (pid != 0) {
                    WiiProfile *profile = TheWiiProfileMgr.GetProfileForPad(i);
                    if (profile) {
                        profile->SetId(pid);
                    }
                }
            }
            if (TheSaveLoadMgr)
                TheSaveLoadMgr->AutoSave();
            unk112 = false;
        }
#endif
        if (TheServer->IsConnected() && !ThePlatformMgr.IsOnlineRestricted()
            && TheProfileMgr.GetUsingWiiFriends()) {
            if (!unka8.Running() || unka8.SplitMs() > 60000.0f) {
                unka8.Restart();
                TheWiiFriendMgr.EnumerateFriends(unk9c, nullptr);
            }
            if ((!unke0.Running() || unke0.SplitMs() > 10000.0f) && !unk110) {
                unke0.Restart();
                unk110 = true;
                TheWiiMessenger.EnumerateMessages(unkd8, this);
            }
        }
    }
}

DataNode RockCentral::OnMsg(const RockCentralOpCompleteMsg &msg) {
    if (msg.Success()) {
        String str50;
        String str5c;
        mConfigResultList.Update(nullptr);
        DataResult res = *mConfigResultList.GetDataResult(0);
        DataNode na8;
        res.GetDataResultValue("out_dta", na8);
        str50 = na8.Str();
        res.GetDataResultValue("version", na8);
        str5c = na8.Str();
        if (strcmp(kServerVer.c_str(), str5c.c_str()) != 0) {
            MILO_WARN(
                "Can't log in to Rock Central version %s, we're version %s",
                str5c.c_str(),
                kServerVer
            );
            mLoginBlocked = true;
            ForceLogout();
        } else {
            const char *cc = str50.c_str();
            if (strlen(cc) > 1) {
                ExecuteConfig(cc);
            }
        }
    }
    return 1;
}

DataNode RockCentral::OnMsg(const ConnectionStatusChangedMsg &msg) {
    if (msg->Int(2) != 0 && mState == 4) {
        mState = 0;
        mRetryTime = mTime.Ms();
    }
    return 1;
}

DataNode RockCentral::OnMsg(const ServerStatusChangedMsg &msg) {
    if (msg.Success() && !mRBData) {
        mState = 2;
        TheNet.GetServer()->GetCompetitionClient();
        Quazal::ServiceClient *client = TheNet.GetServer()->GetPersistentStoreClient();
        mRBTest = new Quazal::RBTestClient();
        if (!client->RegisterExtraProtocol(mRBTest, 't')) {
            MILO_WARN("Couldn't register RB test protocol\n");
        }
        mRBData = new Quazal::RBDataClient();
        if (!client->RegisterExtraProtocol(mRBBinaryData, 'u')) {
            MILO_WARN("Couldn't register RB data protocol\n");
        }
        mRBBinaryData = new Quazal::RBBinaryDataClient();
        if (!client->RegisterExtraProtocol(mRBBinaryData, 'v')) {
            MILO_WARN("Couldn't register RB binary data protocol\n");
        }
        MILO_WARN("%llu"); // something with NWC24GetMyUserId happens here
        INIT_DATAPOINT("config/get");
        ADD_DATA_PAIR(locale, SystemLanguage());
        RecordDataPoint(dataPoint, 0, mConfigResultList, this);
        DeleteNextUser();
    } else if (!msg.Success()) {
        if (mState == 3) {
            mState = 0;
            mRetryTime = mTime.Ms() + 8000.0f;
        } else {
            mState = 4;
            mRetryTime = mTime.Ms() + 40000.0f;
            if (IsLoginMandatory()) {
                static Message init("init", 1);
                TheUIEventMgr->TriggerEvent(lost_connection, init);
            }
        }
        RELEASE(mRBTest);
        RELEASE(mRBBinaryData);
        RELEASE(mRBData);
    }
    MsgSource::Handle(msg, false);
    return 1;
}

DataNode RockCentral::OnMsg(const UserLoginMsg &msg) {
    int padnum = msg.GetPadNum();
    int pid = TheServer->GetPlayerID(padnum);
    WiiProfile *profile = TheWiiProfileMgr.GetProfileForPad(padnum);
    if (profile && pid != profile->mId) {
        MILO_WARN(
            "Save Data PID for %s (%d) does not match Rock Central PID (%d) - you'd better have changed sandboxes recently!\n",
            profile->GetName(),
            profile->mId,
            pid
        );
        unk112 = true;
    }
    UpdateOnlineStatus();
    mJobMgr.QueueJob(new UpdateFriendsListJob(msg.GetPadNum()));
    return 1;
}

DECOMP_FORCEACTIVE(RockCentral, "")

DataNode RockCentral::OnMsg(const FriendsListChangedMsg &msg) {
    mJobMgr.QueueJob(new UpdateFriendsListJob(msg.GetPadNum()));
    mJobMgr.QueueJob(new UpdateMasterProfileFriendsListJob());
    return 1;
}

DataNode RockCentral::OnMsg(const ProfileChangedMsg &msg) {
    BandProfile *p = msg.GetProfile();
    int padnum = p->GetPadNum();
    if (p->HasValidSaveData() && TheNet.GetServer()->GetPlayerID(padnum)) {
        mJobMgr.QueueJob(new UpdateFriendsListJob(padnum));
    }
    return 1;
}

DataNode RockCentral::OnMsg(const DeleteQueueUpdatedMsg &) {
    DeleteNextUser();
    return 1;
}

DataNode RockCentral::OnMsg(const DeleteUserCompleteMsg &msg) {
    if (msg.IsComplete()) {
        TheWiiProfileMgr.RemoveIdFromDeleteQueue(msg.GetUserID());
        TheSaveLoadMgr->AutoSaveNow();
    }
    DeleteNextUser();
    return 1;
}

DataNode RockCentral::OnMsg(const EnumerateMessagesCompleteMsg &) {
    unk110 = false;
    return 1;
}

DataNode RockCentral::OnMsg(const SigninChangedMsg &) {
    UpdateOnlineStatus();
    return 1;
}

DataNode RockCentral::OnMsg(const InviteReceivedMsg &) {
    unk111 = true;
    return 1;
}

void RockCentral::UpdateOnlineStatus() {
    if (TheProfileMgr.GetUsingWiiFriends()) {
        for (int i = 0; i < 4; i++) {
            TheWiiFriendMgr.SetProfileStatus(i, FriendStatusToString(kOffline));
        }
        for (int i = 0; i < 4; i++) {
            int idx = TheWiiProfileMgr.GetIndexForPad(i);
            if (idx >= 0) {
                TheWiiFriendMgr.SetProfileStatus(idx, FriendStatusToString(kOnline));
            }
        }
        TheWiiFriendMgr.SetMasterProfileStatus(FriendStatusToString(kOnline));
    }
}

bool RockCentral::EnumerateFriends(
    int i1, std::vector<Friend *> &friends, Hmx::Object *obj
) {
    if (TheRockCentral.unka0 != 0)
        return false;
    else if (!TheProfileMgr.GetUsingWiiFriends()) {
        if (obj) {
            PlatformMgrOpCompleteMsg msg(1);
            obj->Handle(msg, true);
        }
        return true;
    } else {
        TheRockCentral.unka0 = &friends;
        TheRockCentral.unka4 = obj;
        TheWiiFriendMgr.EnumerateFriends(TheRockCentral.unk98, &TheRockCentral);
        return true;
    }
}

bool RockCentral::SendMsg(
    Friend *friendObj, const char *c1, const char *c2, MemStream &ms
) {
    String str;
    str = EncodeMessage((_WiiMessageType)1, (int)ms.Buffer()[0], c2);
    TheWiiMessenger.SendMessage(friendObj->mFriendKey, c1, str.c_str(), nullptr, 600);
    return true;
}

_WiiFriendStatus RockCentral::StringToFriendStatus(const char *str) {
    if (str) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(str, g_pStatusStrings[i]) == 0)
                return (_WiiFriendStatus)i;
        }
    }
    return (_WiiFriendStatus)-1;
}

const char *RockCentral::FriendStatusToString(_WiiFriendStatus status) {
    if (status <= 2U)
        return g_pStatusStrings[status];
    else
        return "Unknown";
}

void RockCentral::ForceLogout() {
    if (mState == 1 || mState == 2) {
        mState = 3;
        TheNet.GetServer()->Logout();
    }
}

void RockCentral::CancelOutstandingCalls(Hmx::Object *o) {
    mContextWrapperPool->CancelOutstandingContexts(o);
}

void RockCentral::FailAllOutstandingCalls() { mContextWrapperPool->FailAllContexts(); }

Server *RockCentral::IsConnected(Hmx::Object *o, int i, bool b) {
    Server *server = TheNet.GetServer();
    if ((server && !server->IsConnected()) || b) {
        if (i != -1) {
            SendFailure(o, 0, 0);
        } else
            SendFailure(o, 1, i);
        return nullptr;
    }
    return server;
}

void RockCentral::GetLinkingCode(int i1, DataResultList &results, Hmx::Object *o) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        INIT_DATAPOINT("entities/linkcode/get");
        ADD_DATA_PAIR(pid, server->GetPlayerID(i1));
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::GetTickerInfo(
    const Profile *profile, ScoreType s, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        MILO_ASSERT(profile, 0x43C);
        INIT_DATAPOINT("ticker/info/get");
        ADD_DATA_PAIR(pid, server->GetPlayerID(profile->GetPadNum()));
        ADD_DATA_PAIR(role_id, (char)s);
        ADD_DATA_PAIR(locale, SystemLanguage());
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::GetSongFullOffer(int i1, DataResultList &results, Hmx::Object *o) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        INIT_DATAPOINT("entities/song_offer/get");
        ADD_DATA_PAIR(song_id, i1);
        ADD_DATA_PAIR(locale, SystemLanguage());
        PlatformRegion regionEnum = ThePlatformMgr.GetRegion();
        if (regionEnum - 1 <= 1U) {
            ADD_DATA_PAIR(region, PlatformRegionToSymbol(regionEnum));
        } else {
            ADD_DATA_PAIR(region, PlatformRegionToSymbol(kRegionNA));
        }
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::GetMaxRank(
    std::vector<int> &vec,
    int i1,
    ScoreType s,
    LeaderboardType l,
    DataResultList &results,
    Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        INIT_DATAPOINT("leaderboards/maxrank/get");
        ADD_DATA_PAIR(role_id, (char)s);
        ADD_DATA_PAIR(song_id, i1);
        ADD_DATA_PAIR(lb_type, l);
        for (int i = 0; i < vec.size(); i++) {
            char buf[12];
            ADD_BUFFER_PAIR(buf, vec[i], "pid%03d", i);
        }
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::GetAccMaxRank(
    std::vector<int> &vec, Symbol &sym, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        INIT_DATAPOINT("leaderboards/acc_maxrank/get");
        ADD_DATA_PAIR(acc_id, sym.Str());
        for (int i = 0; i < vec.size(); i++) {
            char buf[12];
            ADD_BUFFER_PAIR(buf, vec[i], "pid%03d", i);
        }
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::GetBattleMaxRank(
    std::vector<int> &vec, int i1, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        INIT_DATAPOINT("leaderboards/battle_maxrank/get");
        ADD_DATA_PAIR(battle_id, i1);
        for (int i = 0; i < vec.size(); i++) {
            char buf[12];
            ADD_BUFFER_PAIR(buf, vec[i], "pid%03d", i);
        }
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::GetLeaderboardByPlayer(
    std::vector<int> &vec,
    int i2,
    ScoreType s,
    LeaderboardType lt,
    LeaderboardMode lm,
    int i6,
    DataResultList &results,
    Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        if (!vec.empty()) {
            INIT_DATAPOINT("leaderboards/player/get");
            ADD_DATA_PAIR(role_id, (char)s);
            ADD_DATA_PAIR(song_id, i2);
            ADD_DATA_PAIR(lb_type, lt);
            ADD_DATA_PAIR(lb_mode, lm);
            ADD_DATA_PAIR(num_rows, i6);
            for (int i = 0; i < vec.size(); i++) {
                char buf[12];
                ADD_BUFFER_PAIR(buf, vec[i], "pid%03d", i);
            }
            RECORD_DATA_POINT(0, results, o);
        } else {
            RockCentralOpCompleteMsg msg(false, 0, 0);
            o->Handle(msg, true);
        }
    }
}

void RockCentral::GetAccLeaderboardByPlayer(
    std::vector<int> &vec,
    Symbol &s,
    LeaderboardMode lm,
    int i4,
    DataResultList &results,
    Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        if (vec.empty()) {
            RockCentralOpCompleteMsg msg(false, 0, 0);
            o->Handle(msg, true);
        } else {
            INIT_DATAPOINT("leaderboards/acc_player/get");
            ADD_DATA_PAIR(acc_id, s.Str());
            ADD_DATA_PAIR(lb_mode, lm);
            ADD_DATA_PAIR(num_rows, i4);
            for (int i = 0; i < vec.size(); i++) {
                char buf[12];
                ADD_BUFFER_PAIR(buf, vec[i], "pid%03d", i);
            }
            RECORD_DATA_POINT(0, results, o);
        }
    }
}

void RockCentral::GetBattleLeaderboardByPlayer(
    std::vector<int> &vec,
    int i2,
    LeaderboardMode lm,
    int i4,
    DataResultList &results,
    Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        if (vec.empty()) {
            RockCentralOpCompleteMsg msg(false, 0, 0);
            o->Handle(msg, true);
        } else {
            INIT_DATAPOINT("leaderboards/battle_player/get");
            ADD_DATA_PAIR(battle_id, i2);
            ADD_DATA_PAIR(lb_mode, lm);
            ADD_DATA_PAIR(num_rows, i4);
            for (int i = 0; i < vec.size(); i++) {
                char buf[12];
                ADD_BUFFER_PAIR(buf, vec[i], "pid%03d", i);
            }
            RECORD_DATA_POINT(0, results, o);
        }
    }
}

void RockCentral::GetLeaderboardByRankRange(
    std::vector<int> &vec,
    int i2,
    ScoreType s,
    int i4,
    int i5,
    LeaderboardType lt,
    DataResultList &results,
    Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        if (vec.empty()) {
            RockCentralOpCompleteMsg msg(false, 0, 0);
            o->Handle(msg, true);
        } else {
            INIT_DATAPOINT("leaderboards/rankrange/get");
            ADD_DATA_PAIR(role_id, (char)s)
            ADD_DATA_PAIR(song_id, i2)
            ADD_DATA_PAIR(start_rank, i4)
            ADD_DATA_PAIR(end_rank, i5)
            ADD_DATA_PAIR(lb_type, lt)
            for (int i = 0; i < vec.size(); i++) {
                char buf[12];
                ADD_BUFFER_PAIR(buf, vec[i], "pid%03d", i);
            }
            RECORD_DATA_POINT(0, results, o);
        }
    }
}

void RockCentral::GetAccLeaderboardByRankRange(
    std::vector<int> &vec,
    Symbol &s,
    int i3,
    int i4,
    DataResultList &results,
    Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        INIT_DATAPOINT("leaderboards/acc_rankrange/get");
        ADD_DATA_PAIR(acc_id, s.Str())
        ADD_DATA_PAIR(start_rank, i3)
        ADD_DATA_PAIR(end_rank, i4)
        if (vec.empty()) {
            RockCentralOpCompleteMsg msg(false, 0, 0);
            o->Handle(msg, true);
        } else {
            for (int i = 0; i < vec.size(); i++) {
                char buf[12];
                ADD_BUFFER_PAIR(buf, vec[i], "pid%03d", i);
            }
            RECORD_DATA_POINT(0, results, o);
        }
    }
}

void RockCentral::GetBattleLeaderboardByRankRange(
    std::vector<int> &vec, int i2, int i3, int i4, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        if (vec.empty()) {
            RockCentralOpCompleteMsg msg(false, 0, 0);
            o->Handle(msg, true);
        } else {
            INIT_DATAPOINT("leaderboards/battle_rankrange/get");
            ADD_DATA_PAIR(battle_id, i2)
            ADD_DATA_PAIR(start_rank, i3)
            ADD_DATA_PAIR(end_rank, i4)
            for (int i = 0; i < vec.size(); i++) {
                char buf[12];
                ADD_BUFFER_PAIR(buf, vec[i], "pid%03d", i);
            }
            RECORD_DATA_POINT(0, results, o);
        }
    }
}

void RockCentral::UpdateFriendList(
    int i1, std::vector<Friend *> friends, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        INIT_DATAPOINT("leaderboards/friends/update");
        ADD_DATA_PAIR(pid, i1);
        for (int i = 0; i < friends.size(); i++) {
            String str;
            str = friends[i]->mName.c_str();
            unsigned long long key = friends[i]->mFriendKey;
            char buf[8];
            char buf2[0x18];
            ADD_BUFFER_PAIR(buf, str, "name%03d", i);
            snprintf(buf, 8, "guid%03d", i);
            snprintf(buf2, 0x18, "%lld", key);
            ADD_DATA_PAIR(buf2, buf);
        }
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::RecordBattleScore(
    int i1,
    int i2,
    std::vector<BandProfile *> &profiles,
    int i4,
    DataResultList &results,
    Hmx::Object *o
) {
    Server *server = IsConnected(o, i2, profiles.empty());
    if (server) {
        std::vector<int> playerIds;
        std::vector<int> vec8a0;
        FOREACH (it, profiles) {
            BandProfile *cur = *it;
            playerIds.push_back(server->GetPlayerID(cur->GetPadNum()));
            vec8a0.push_back(cur->GetPadNum());
        }
        MILO_ASSERT(!playerIds.empty(), 0x62D);
        INIT_DATAPOINT("battles/record");
        ADD_DATA_PAIR(battle_id, i1);
        ADD_DATA_PAIR(score, i4);
        for (int i = 0; i < playerIds.size(); i++) {
            char buf[0x14];
            ADD_BUFFER_PAIR(buf, playerIds[i], "pid%03d", i);
            ADD_BUFFER_PAIR(buf, vec8a0[i], "slot%03d", i);
            if (playerIds[i] == 0) {
                MILO_WARN("RecordBattleScore() - PID == 0!");
            }
        }
        RECORD_DATA_POINT(i2, results, o);
    }
}

void RockCentral::RecordScore(
    int i1,
    int i2,
    std::vector<PlayerScore> &scores,
    int i4,
    int i5,
    bool b6,
    Hmx::Object *o,
    DataResultList &results
) {
    Server *server = IsConnected(o, i2, false);
    if (server) {
        if (!scores.empty()) {
            INIT_DATAPOINT("scores/record");
            ADD_DATA_PAIR(song_id, i1);
            ADD_DATA_PAIR(boi_id, i4);
            ADD_DATA_PAIR(band_mask, i5);
            ADD_DATA_PAIR(provide_insta_rank, (int)b6);
            for (int i = 0; i < scores.size(); i++) {
                char buf[0x14];
                ADD_BUFFER_PAIR(buf, scores[i].mScoreType, "role_id%03d", i);
                ADD_BUFFER_PAIR(buf, scores[i].mScore, "score%03d", i);
                ADD_BUFFER_PAIR(buf, scores[i].mStars, "stars%03d", i);
                ADD_BUFFER_PAIR(buf, scores[i].mPlayerID, "pid%03d", i);
                ADD_BUFFER_PAIR(buf, scores[i].unk18, "slot%03d", i);
                if (scores[i].mPlayerID == 0) {
                    MILO_WARN("RecordScore() - PID == 0!");
                }
                ADD_BUFFER_PAIR(buf, GetDifficultyID(scores[i].mDiff), "diff_id%03d", i);
                ADD_BUFFER_PAIR(buf, scores[i].mTotalScore, "c_score%03d", i);
                ADD_BUFFER_PAIR(buf, scores[i].mTotalDiscScore, "cc_score%03d", i);
                ADD_BUFFER_PAIR(buf, scores[i].mAccuracy, "percent%03d", i);
            }
            ADD_DATA_PAIR(locale, SystemLanguage());
            PlatformRegion regionEnum = ThePlatformMgr.GetRegion();
            if (regionEnum - 1 <= 1U) {
                ADD_DATA_PAIR(region, PlatformRegionToSymbol(regionEnum));
            } else {
                ADD_DATA_PAIR(region, PlatformRegionToSymbol(kRegionNA));
            }
            RECORD_DATA_POINT(i2, results, o);
        } else
            MILO_WARN("RecordScore() - no players!");
    }
}

#pragma push
#pragma dont_inline on
void RockCentral::RecordPerformance(
    const Profile *profile,
    const PerformanceData *data,
    int i3,
    Hmx::Object *o,
    DataResultList &results
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        MILO_ASSERT(profile, 0x69B);
        INIT_DATAPOINT("performance/record");
        ADD_DATA_PAIR(pid, server->GetPlayerID(profile->GetPadNum()));
        ADD_DATA_PAIR(mode, data->GetMode());
        ADD_DATA_PAIR(song_id, data->GetSongID());
        ADD_DATA_PAIR(is_playtest, data->IsPlaytest());
        ADD_DATA_PAIR(is_online, data->IsOnline());
        ADD_DATA_PAIR(is_cheating, data->IsCheating());
        ADD_DATA_PAIR(score_type, data->GetScoreType());
        ADD_DATA_PAIR(difficulty, data->GetDifficulty());
        ADD_DATA_PAIR(time_stamp, data->GetTimeStamp());
        const Stats &stats = data->GetStats();
        ADD_DATA_PAIR(end_game_score, stats.GetEndGameScore());
        ADD_DATA_PAIR(stars, data->GetStars());
        int battleID = data->GetBattleID();
        if (battleID > 0) {
            ADD_DATA_PAIR(battle_id, battleID);
        }
        ADD_DATA_PAIR(notes_hit_fraction, stats.GetNotesHitFraction());
        ADD_DATA_PAIR(hit_count, stats.GetHitCount());
        ADD_DATA_PAIR(miss_count, stats.GetMissCount());
        ADD_DATA_PAIR(times_saved, stats.GetTimesSaved());
        ADD_DATA_PAIR(players_saved, stats.GetPlayersSaved());
        ADD_DATA_PAIR(hit_streak_start, stats.GetCurrentStreakInfo().mStart);
        ADD_DATA_PAIR(hit_streak_duration, stats.GetCurrentStreakInfo().mDuration);
        ADD_DATA_PAIR(end_game_overdrive, stats.GetEndGameOverdrive());
        ADD_DATA_PAIR(end_game_crowdlevel, stats.GetEndGameCrowdLevel());
        ADD_DATA_PAIR(coda_points, stats.GetCodaPoints());
        ADD_DATA_PAIR(od_phrases_completed, stats.GetOverdrivePhrasesCompleted());
        ADD_DATA_PAIR(od_phrase_count, stats.GetOverdrivePhraseCount());
        ADD_DATA_PAIR(unison_phrases_completed, stats.GetUnisonPhrasesCompleted());
        ADD_DATA_PAIR(unison_phrase_count, stats.GetUnisonPhraseCount());
        ADD_DATA_PAIR(average_ms_error, stats.GetAverageMsError());

        char buf[64];
        const std::vector<Symbol> &awards = stats.GetPerformanceAwards();
        int numAwards = awards.size();
        for (int i = 0; i < numAwards; i++) {
            ADD_BUFFER_PAIR(buf, awards[i], "award%03d", i);
        }
        int numFailurePts = stats.GetFailurePoints().size();
        for (int i = 0; i < numFailurePts; i++) {
            ADD_BUFFER_PAIR(buf, stats.GetFailurePoints()[i], "failure_point%03d", i);
        }
        int numSavedPts = stats.GetSavedPoints().size();
        for (int i = 0; i < numSavedPts; i++) {
            ADD_BUFFER_PAIR(buf, stats.GetSavedPoints()[i], "save_point%03d", i);
        }
        int numClosestTimesSaved = stats.GetClosestTimesSaved().size();
        for (int i = 0; i < numClosestTimesSaved; i++) {
            ADD_BUFFER_PAIR(buf, stats.GetClosestTimesSaved()[i], "times_saved%03d", i);
        }
        int numClosestPlayersSaved = stats.GetClosestPlayersSaved().size();
        for (int i = 0; i < numClosestPlayersSaved; i++) {
            ADD_BUFFER_PAIR(
                buf, stats.GetClosestPlayersSaved()[i], "players_saved%03d", i
            );
        }
        int numBestSolos = stats.GetBestSolos().size();
        for (int i = 0; i < numBestSolos; i++) {
            ADD_BUFFER_PAIR(buf, stats.GetBestSolos()[i], "best_solo%03d", i);
        }
        int numHitStreaks = stats.GetHitStreakCount();
        ADD_DATA_PAIR(hit_streak_count, numHitStreaks);
        for (int i = 0; i < numHitStreaks; i++) {
            const Stats::StreakInfo &curStreak = stats.GetHitStreak(i);
            ADD_BUFFER_PAIR(buf, curStreak.mStart, "hit_streak_start%03d", i);
            ADD_BUFFER_PAIR(buf, curStreak.mDuration, "hit_streak_duration%03d", i);
        }
        int numMissStreaks = stats.GetMissStreakCount();
        ADD_DATA_PAIR(miss_streak_count, numMissStreaks);
        for (int i = 0; i < numMissStreaks; i++) {
            const Stats::StreakInfo &curStreak = stats.GetMissStreak(i);
            ADD_BUFFER_PAIR(buf, curStreak.mStart, "miss_streak_start%03d", i);
            ADD_BUFFER_PAIR(buf, curStreak.mDuration, "miss_streak_duration%03d", i);
        }
        int numBestODs = stats.GetBestOverdriveDeploymentsCount();
        ADD_DATA_PAIR(best_od_deployment_count, numBestODs);
        for (int i = 0; i < numBestODs; i++) {
            const Stats::MultiplierInfo &curInfo = stats.GetBestOverdriveDeployment(i);
            ADD_BUFFER_PAIR(buf, curInfo.mStartMs, "best_od_deployment_start%03d", i);
            ADD_BUFFER_PAIR(
                buf, curInfo.mDurationMs, "best_od_deployment_duration%03d", i
            );
            ADD_BUFFER_PAIR(
                buf,
                curInfo.mStartingMultiplier,
                "best_od_deployment_starting_multiplier%03d",
                i
            );
            ADD_BUFFER_PAIR(
                buf,
                curInfo.mEndingMultiplier,
                "best_od_deployment_ending_multiplier%03d",
                i
            );
            ADD_BUFFER_PAIR(buf, curInfo.mPoints, "best_od_deployment_points%03d", i);
        }
        int numBestStreakMults = stats.GetBestStreakMultipliersCount();
        ADD_DATA_PAIR(best_streak_multipliers_count, numBestStreakMults);
        for (int i = 0; i < numBestStreakMults; i++) {
            const Stats::MultiplierInfo &curInfo = stats.GetBestStreakMultiplier(i);
            ADD_BUFFER_PAIR(buf, curInfo.mStartMs, "best_streak_multiplier_start%03d", i);
            ADD_BUFFER_PAIR(
                buf, curInfo.mDurationMs, "best_streak_multiplier_duration%03d", i
            );
            ADD_BUFFER_PAIR(
                buf,
                curInfo.mStartingMultiplier,
                "best_streak_multiplier_starting_multiplier%03d",
                i
            );
            ADD_BUFFER_PAIR(
                buf,
                curInfo.mEndingMultiplier,
                "best_streak_multiplier_ending_multiplier%03d",
                i
            );
            ADD_BUFFER_PAIR(buf, curInfo.mPoints, "best_streak_multiplier_points%03d", i);
        }
        ADD_DATA_PAIR(total_od_duration, stats.GetTotalOverdriveDuration());
        ADD_DATA_PAIR(total_multiplier_duration, stats.GetTotalMultiplierDuration());
        ADD_DATA_PAIR(rolls_hit_completely, stats.GetRollsHitCompletely());
        ADD_DATA_PAIR(roll_count, stats.GetRollCount());
        ADD_DATA_PAIR(hopo_gems_hopoed, stats.GetHopoGemsHopoed());
        ADD_DATA_PAIR(hopo_gem_count, stats.GetHopoGemCount());
        ADD_DATA_PAIR(high_gems_hit_high, stats.GetHighGemsHitHigh());
        ADD_DATA_PAIR(high_gems_hit_low, stats.GetHighGemsHitLow());
        ADD_DATA_PAIR(high_fret_gem_count, stats.GetHighFretGemCount());
        ADD_DATA_PAIR(sustain_gems_hit_completely, stats.GetSustainGemsHitCompletely());
        ADD_DATA_PAIR(sustain_gems_hit_partially, stats.GetSustainGemsHitPartially());
        ADD_DATA_PAIR(sustain_gems_count, stats.GetSustainGemCount());
        ADD_DATA_PAIR(trills_hit_completely, stats.GetTrillsHitCompletely());
        ADD_DATA_PAIR(trills_hit_partially, stats.GetTrillsHitPartially());
        ADD_DATA_PAIR(trill_count, stats.GetTrillCount());
        ADD_DATA_PAIR(cymbal_gems_hit_on_cymbals, stats.GetCymbalGemsHitOnCymbals());
        ADD_DATA_PAIR(cymbal_gems_hit_on_pads, stats.GetCymbalGemsHitOnPads());
        ADD_DATA_PAIR(cymbal_gem_count, stats.GetCymbalGemCount());
        ADD_DATA_PAIR(double_harmony_hit, stats.GetDoubleHarmonyHit())
        ADD_DATA_PAIR(double_harmony_phrase_count, stats.GetDoubleHarmonyPhraseCount());
        ADD_DATA_PAIR(triple_harmony_hit, stats.GetTripleHarmonyHit());
        ADD_DATA_PAIR(triple_harmony_phrase_count, stats.GetTripleHarmonyPhraseCount());

        int numSingers = stats.GetNumberOfSingers();
        ADD_DATA_PAIR(num_singers, numSingers);
        int numVocalParts = stats.GetNumberOfVocalParts();
        ADD_DATA_PAIR(num_vocal_parts, numVocalParts);
        for (int i = 0; i < numSingers; i++) {
            const SingerStats &curStats = stats.GetSingerStats(i);
            for (int j = 0; j < numVocalParts; j++) {
                const std::pair<int, float> &curRankData = curStats.GetRankData(j);
                ADD_BUFFER_PAIR(buf, curRankData.first, "singer%03d_part%03d_part", i, j);
                ADD_BUFFER_PAIR(buf, curRankData.second, "singer%03d_part%03d_pct", i, j);
            }
            float f920, f924;
            curStats.GetPitchDeviationInfo(f920, f924);
            ADD_BUFFER_PAIR(buf, f920, "singer%03d_pitch_deviation", i);
            ADD_BUFFER_PAIR(buf, f924, "singer%03d_pitch_deviation_of_deviation", i);
        }
        RECORD_DATA_POINT(i3, results, o);
    }
}

void RockCentral::RecordAccomplishmentData(
    const Profile *profile,
    AccomplishmentProgress *prog,
    int i3,
    Hmx::Object *o,
    DataResultList &results
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        MILO_ASSERT(profile, 0x79E);
        INIT_DATAPOINT("accomplishment/record");
        if (server->GetPlayerID(profile->GetPadNum()) == 0) {
            MILO_WARN("RecordAccomplishmentData() - PID == 0!");
        }
        ADD_DATA_PAIR(pid, server->GetPlayerID(profile->GetPadNum()));
        ADD_DATA_PAIR(num_completed, prog->GetNumCompleted());
        ADD_DATA_PAIR(meta_score, prog->GetMetaScore());
        ADD_DATA_PAIR(
            campaign_level,
            TheCampaign->GetCampaignLevelForMetaScore(prog->GetMetaScore())
        );
        ADD_DATA_PAIR(tot_gems_smashed, prog->GetTotalGemsSmashed());
        ADD_DATA_PAIR(tot_guitar_hopos, prog->GetTotalGuitarHopos());
        ADD_DATA_PAIR(tot_bass_hopos, prog->GetTotalBassHopos());
        ADD_DATA_PAIR(tot_upstrums, prog->GetTotalUpstrums());
        ADD_DATA_PAIR(tot_times_revived, prog->GetTotalTimesRevived());
        ADD_DATA_PAIR(tot_saves, prog->GetTotalSaves());
        ADD_DATA_PAIR(tot_awesomes, prog->GetTotalAwesomes());
        ADD_DATA_PAIR(tot_double_awesomes, prog->GetTotalDoubleAwesomes());
        ADD_DATA_PAIR(tot_triple_awesomes, prog->GetTotalTripleAwesomes());
        char buf[64];
        for (int i = 0; i < kNumScoreTypes; i++) {
            ADD_BUFFER_PAIR(buf, prog->GetBestStreak((ScoreType)i), "best_streak%03d", i);
            ADD_BUFFER_PAIR(
                buf, prog->GetTotalOverdriveDeploys((ScoreType)i), "tot_od_deploys%03d", i
            );
            ADD_BUFFER_PAIR(
                buf, prog->GetTotalOverdriveTime((ScoreType)i), "tot_od_time%03d", i
            );
            ADD_BUFFER_PAIR(
                buf, prog->GetTotalOverdrivePhrases((ScoreType)i), "tot_od_phrases%03d", i
            );
            ADD_BUFFER_PAIR(
                buf, prog->GetTotalUnisonPhrases((ScoreType)i), "tot_unison_phrases%03d", i
            );
            ADD_BUFFER_PAIR(
                buf, prog->GetMostOverdriveDeploys((ScoreType)i), "most_od_deploys%03d", i
            );
            ADD_BUFFER_PAIR(
                buf, prog->GetMostOverdriveTime((ScoreType)i), "most_od_time%03d", i
            );
            ADD_BUFFER_PAIR(
                buf, prog->GetMostUnisonPhrases((ScoreType)i), "most_unison_phrases%03d", i
            );
            ADD_BUFFER_PAIR(
                buf, prog->GetTotalBREsHit((ScoreType)i), "tot_bres_hit%03d", i
            );
            for (int j = 0; j < kNumDifficulties; j++) {
                ADD_BUFFER_PAIR(
                    buf,
                    prog->GetBestStars((ScoreType)i, (Difficulty)j),
                    "best_stars%03d_%03d",
                    i,
                    j
                );
                ADD_BUFFER_PAIR(
                    buf,
                    prog->GetBestSolo((ScoreType)i, (Difficulty)j),
                    "best_solo%03d_%03d",
                    i,
                    j
                );
                ADD_BUFFER_PAIR(
                    buf,
                    prog->GetBestAccuracy((ScoreType)i, (Difficulty)j),
                    "best_accuracy%03d_%03d",
                    i,
                    j
                );
                ADD_BUFFER_PAIR(
                    buf,
                    prog->GetBestHoposPercent((ScoreType)i, (Difficulty)j),
                    "best_hopos_percent%03d_%03d",
                    i,
                    j
                );
            }
        }

        for (int i = 0; i < kNumDifficulties; i++) {
            ADD_BUFFER_PAIR(
                buf,
                prog->GetBestPercussionPercent((Difficulty)i),
                "best_perc_percent%03d",
                i
            );
            ADD_BUFFER_PAIR(
                buf,
                prog->GetTotalDrumRollCount((Difficulty)i),
                "total_drumroll_count%03d",
                i
            );
            ADD_BUFFER_PAIR(
                buf,
                prog->GetTotalProDrumRollCount((Difficulty)i),
                "total_pro_drumroll_count%03d",
                i
            );
            ADD_BUFFER_PAIR(
                buf, prog->GetBestKickPercent((Difficulty)i), "best_kick_percent%03d", i
            );
            ADD_BUFFER_PAIR(
                buf,
                prog->GetBestProKickPercent((Difficulty)i),
                "best_pro_kick_percent%03d",
                i
            );
            ADD_BUFFER_PAIR(
                buf,
                prog->GetBestDrumRollPercent((Difficulty)i),
                "best_drumroll_percent%03d",
                i
            );
            ADD_BUFFER_PAIR(
                buf,
                prog->GetBestSoloButtonPercent((Difficulty)i),
                "best_solo_but_percent%03d",
                i
            );
        }

        ADD_DATA_PAIR(tot_songs_played, prog->GetTotalSongsPlayed());
        ADD_DATA_PAIR(tour_tot_songs_played, prog->GetTourTotalSongsPlayed());
        std::map<Symbol, int>::const_iterator it;
        for (it = prog->GetToursPlayedMap().begin();
             it != prog->GetToursPlayedMap().end();
             it++) {
            ADD_BUFFER_PAIR(buf, it->second, "tour_%s_played", it->first.Str());
        }
        for (it = prog->GetToursMostStarsMap().begin();
             it != prog->GetToursMostStarsMap().end();
             it++) {
            ADD_BUFFER_PAIR(buf, it->second, "tour_%s_most_stars", it->first.Str());
        }
        for (it = prog->GetToursGotAllStarsMap().begin();
             it != prog->GetToursGotAllStarsMap().end();
             it++) {
            ADD_BUFFER_PAIR(buf, it->second, "tour_%s_got_all_stars", it->first.Str());
        }
        std::map<int, int>::const_iterator git;
        for (git = prog->GetGigTypeCompletedMap().begin();
             git != prog->GetGigTypeCompletedMap().end();
             git++) {
            ADD_BUFFER_PAIR(buf, git->second, "gig_%03d_completed", git->first);
        }

        std::map<Symbol, int> goalLBData;
        prog->InqGoalLeaderboardData(goalLBData);
        for (it = goalLBData.begin(); it != goalLBData.end(); it++) {
            ADD_BUFFER_PAIR(buf, it->second, "lb_goal_value_%s", it->first.Str());
        }
        const std::set<Symbol> &goals = prog->GetNewGoalsSet();
        FOREACH_POST (it, goals) {
            Symbol cur = *it;
            ADD_BUFFER_PAIR(buf, 0, "earned_accomplishment_%s", cur.Str());
        }
        RECORD_DATA_POINT(i3, results, o);
    }
}
#pragma pop

void RockCentral::RecordOptionData() {
    Server *server = IsConnected(nullptr, -1, false);
    if (server) {
        INIT_DATAPOINT("misc/option_data");
        ADD_DATA_PAIR("cymbal_config", (int)TheProfileMgr.GetCymbalConfiguration());
        ADD_DATA_PAIR("overscan", (int)TheProfileMgr.GetOverscan());
        ADD_DATA_PAIR("secondpedal_hihat", (int)TheProfileMgr.GetSecondPedalHiHat());
        ADD_DATA_PAIR("izotope", (int)TheProfileMgr.GetSynapseEnabled());
        ADD_DATA_PAIR("bg_vol", (int)TheProfileMgr.GetBackgroundVolume());
        ADD_DATA_PAIR("fg_vol", (int)TheProfileMgr.GetForegroundVolume());
        ADD_DATA_PAIR("fx_vol", (int)TheProfileMgr.GetFxVolume());
        ADD_DATA_PAIR("crowd_vol", (int)TheProfileMgr.GetCrowdVolume());
        ADD_DATA_PAIR("vocalcue_vol", (int)TheProfileMgr.GetVocalCueVolume());
        ADD_DATA_PAIR("voicechat_vol", (int)TheProfileMgr.GetVoiceChatVolume());
        ADD_DATA_PAIR("bass_boost", (int)TheProfileMgr.GetBassBoost());
        ADD_DATA_PAIR("dolby", (int)TheProfileMgr.GetDolby());
        //
        ADD_DATA_PAIR("video_cal", TheProfileMgr.GetSyncOffsetRaw());
        ADD_DATA_PAIR("audio_cal", TheProfileMgr.GetSongToTaskMgrMsRaw());
        //
        ADD_DATA_PAIR(
            "pro_guitar_connected", (int)TheProfileMgr.GetHasConnectedProGuitar()
        );
        ADD_DATA_PAIR(
            mod_auto_vocals, (int)TheModifierMgr->IsModifierActive(mod_auto_vocals)
        );
        ADD_DATA_PAIR(
            mod_no_fail_band, (int)TheModifierMgr->IsModifierActive(mod_no_fail_band)
        );
        ADD_DATA_PAIR(
            mod_drum_surface_navigation,
            (int)TheModifierMgr->IsModifierActive(mod_drum_surface_navigation)
        );
        ADD_DATA_PAIR(
            mod_miss_sounds, (int)TheModifierMgr->IsModifierActive(mod_miss_sounds)
        );
        ADD_DATA_PAIR(
            mod_drum_fills, (int)TheModifierMgr->IsModifierActive(mod_drum_fills)
        );
        std::vector<LocalBandUser *> users;
        TheBandUserMgr->GetLocalBandUsersInSession(users);
        int idx = 0;
        FOREACH (it, users) {
            LocalBandUser *pUser = *it;
            MILO_ASSERT(pUser, 0x866);
            BandProfile *profile = TheProfileMgr.GetProfileForUser(pUser);
            if (profile && profile->HasValidSaveData()) {
                char buf[12];
                ADD_BUFFER_PAIR(
                    buf, server->GetPlayerID(pUser->GetPadNum()), "pid_%i", idx
                );
                ADD_BUFFER_PAIR(buf, pUser->GetSlot(), "slot_%i", idx);
                GameplayOptions *pOptions = profile->GetGameplayOptions();
                MILO_ASSERT(pOptions, 0x874);
                ADD_BUFFER_PAIR(buf, (int)pOptions->GetLefty(), "leftyflip_%i", idx);
                ADD_BUFFER_PAIR(buf, (int)pOptions->GetVocalStyle(), "vocalmode_%i", idx);
            }
            idx++;
        }
        RecordDataPointNoRet(dataPoint, 0);
    }
}

DECOMP_FORCEACTIVE(
    RockCentral, "reviews/song/review", "reviews/song/get", "reviews/song/get_by_player"
)

void RockCentral::GetMultipleRankingsForPlayer(
    Profile *profile,
    ScoreType s,
    std::vector<int> &vec,
    DataResultList &results,
    Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        MILO_ASSERT(profile, 0x8B7);
        INIT_DATAPOINT("leaderboards/playerranks/get");
        ADD_DATA_PAIR(pid, server->GetPlayerID(profile->GetPadNum()));
        ADD_DATA_PAIR(role_id, (char)s);
        for (int i = 0; i < vec.size(); i++) {
            char buf[12];
            ADD_BUFFER_PAIR(buf, vec[i], "song_id%03d", i);
        }
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::GetAllSonglists(
    std::vector<BandProfile *> &profiles, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, profiles.empty());
    if (server) {
        std::vector<int> playerIds;
        FOREACH (it, profiles) {
            playerIds.push_back(server->GetPlayerID((*it)->GetPadNum()));
        }
        MILO_ASSERT(!playerIds.empty(), 0x8D6);
        INIT_DATAPOINT("songlists/get");
        for (int i = 0; i < playerIds.size(); i++) {
            char buf[12];
            ADD_BUFFER_PAIR(buf, playerIds[i], "pid%03d", i);
        }
        ADD_DATA_PAIR(locale, SystemLanguage());
        PlatformRegion regionEnum = ThePlatformMgr.GetRegion();
        if (regionEnum - 1 <= 1U) {
            ADD_DATA_PAIR(region, PlatformRegionToSymbol(regionEnum));
        } else {
            ADD_DATA_PAIR(region, PlatformRegionToSymbol(kRegionNA));
        }
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::GetClosedBattles(
    std::vector<BandProfile *> &profiles, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, profiles.empty());
    if (server) {
        std::vector<int> playerIds;
        FOREACH (it, profiles) {
            playerIds.push_back(server->GetPlayerID((*it)->GetPadNum()));
        }
        MILO_ASSERT(!playerIds.empty(), 0x8FF);
        INIT_DATAPOINT("battles/closed/get");
        for (int i = 0; i < playerIds.size(); i++) {
            char buf[12];
            ADD_BUFFER_PAIR(buf, playerIds[i], "pid%03d", i);
        }
        ADD_DATA_PAIR(locale, SystemLanguage());
        PlatformRegion regionEnum = ThePlatformMgr.GetRegion();
        if (regionEnum - 1 <= 1U) {
            ADD_DATA_PAIR(region, PlatformRegionToSymbol(regionEnum));
        } else {
            ADD_DATA_PAIR(region, PlatformRegionToSymbol(kRegionNA));
        }
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::SyncSetlists(
    std::vector<BandProfile *> &profiles, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, profiles.empty());
    if (server) {
        std::vector<int> playerIds;
        std::vector<std::pair<int, const char *> > pairs;
        FOREACH (it, profiles) {
            BandProfile *cur = *it;
            int pid = server->GetPlayerID(cur->GetPadNum());
            playerIds.push_back(pid);
            std::vector<LocalSavedSetlist *> setlists = cur->GetSavedSetlists();
            FOREACH (sit, setlists) {
                pairs.push_back(std::make_pair(pid, (*sit)->mGuid.ToString()));
            }
        }
        MILO_ASSERT(!playerIds.empty(), 0x938);
        INIT_DATAPOINT("setlists/sync");
        for (int i = 0; i < playerIds.size(); i++) {
            char buf[15];
            ADD_BUFFER_PAIR(buf, playerIds[i], "pid%03d", i);
            for (int j = 0; j < pairs.size(); j++) {
                MILO_WARN("pid%03d_guid%03d");
            }
        }
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::ConvertToStr(PatchDir *dir, String &str) {
    MemStream ms;
    dir->Save(ms);
    ConvertToStr(ms, str);
}

void RockCentral::ConvertToStr(MemStream &ms, String &str) {
    str.reserve(ms.BufferSize() * 2 + 1);
    ms.Seek(0, BinStream::kSeekBegin);
    while (!ms.Eof()) {
        char uc;
        ms >> uc;
        short us = uc >> 4;
        if (us > 9) {
            str = str + (us + 0x37);
        } else {
            str = str + (us + 0x30);
        }
        us = uc & 0xF;
        if (us > 9) {
            str = str + (us + 0x37);
        } else {
            str = str + (us + 0x30);
        }
    }
}

void RockCentral::UpdateSetlist(
    LocalSavedSetlist *setlist, DataResultList &results, Hmx::Object *o, int i4, int i5
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        BandProfile *profile = setlist->GetOwnerProfile();
        MILO_ASSERT(profile, 0x979);
        PatchDir *p6 = nullptr;
        if (setlist->mArt.patchType == 1) {
            p6 = profile->mPatches[setlist->mArt.patchIndex];
        }
        INIT_DATAPOINT("setlists/update");
        ADD_DATA_PAIR(pid, server->GetPlayerID(profile->GetPadNum()));
        ADD_DATA_PAIR(name, setlist->GetTitle());
        ADD_DATA_PAIR(description, setlist->GetDescription());
        ADD_DATA_PAIR(type, SavedSetlist::kSetlistLocal);
        ADD_DATA_PAIR(shared, setlist->GetShared() ? "t" : "f")
        ADD_DATA_PAIR(list_guid, setlist->mGuid.ToString())
        ADD_DATA_PAIR(flags, i5)
        if (p6) {
            String str;
            ConvertToStr(p6, str);
            ADD_DATA_PAIR(art, str.c_str())
        }
        std::vector<int> &songs = setlist->mSongs;
        for (int i = 0; i < songs.size(); i++) {
            char buf[12];
            ADD_BUFFER_PAIR(buf, songs[i], "song_id%03d", i);
        }
        RECORD_DATA_POINT(i4, results, o);
    }
}

void RockCentral::UpdateBand(
    TourBand *band, DataResultList &results, Hmx::Object *o, int i4, int i5
) {
    Server *server = IsConnected(o, i4, false);
    if (server) {
        PatchDir *dir = nullptr;
        BandProfile *profile = band->unk1c;
        if (band->mBandLogo->patchType == 1) {
            dir = profile->mPatches[band->mBandLogo->patchIndex];
        }
        INIT_DATAPOINT("entities/band/update");
        ADD_DATA_PAIR(pid, server->GetPlayerID(profile->GetPadNum()));
        ADD_DATA_PAIR(name, band->GetName());
        ADD_DATA_PAIR(flags, i5);
        if (dir) {
            String str;
            ConvertToStr(dir, str);
            ADD_DATA_PAIR(art, str.c_str())
        }
        RECORD_DATA_POINT(i4, results, o);
    }
}

void RockCentral::CheckBattleLimits(
    BandProfile *profile, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        INIT_DATAPOINT("battles/limit/check");
        ADD_DATA_PAIR(pid, server->GetPlayerID(profile->GetPadNum()));
        RECORD_DATA_POINT(0, results, o);
    }
}

void RockCentral::CreateBattle(
    BandProfile *profile,
    const char *nameStr,
    const char *descStr,
    const std::vector<int> &vec,
    PatchDescriptor &desc,
    int i6,
    ScoreType s,
    int timeEnd,
    BattleTimeUnits units,
    DataResultList &results,
    Hmx::Object *o,
    int i12,
    int i13
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        MILO_ASSERT(profile, 0x9E7);
        const char *battleStr = GetBattleEndTimeStr(units);
        PatchDir *pDir = nullptr;
        if (desc.patchType == 1) {
            pDir = profile->mPatches[desc.patchIndex];
        }
        INIT_DATAPOINT("battles/create");
        ADD_DATA_PAIR(pid, server->GetPlayerID(profile->GetPadNum()));
        ADD_DATA_PAIR(name, nameStr);
        ADD_DATA_PAIR(description, descStr);
        ADD_DATA_PAIR(type, 1000);
        ADD_DATA_PAIR(instrument, (char)s);
        ADD_DATA_PAIR(time_end_val, timeEnd);
        ADD_DATA_PAIR(time_end_units, battleStr);
        ADD_DATA_PAIR(flags, i13);
        if (i6 > 0) {
            ADD_DATA_PAIR(art_id, i6);
        }
        if (pDir) {
            String str;
            ConvertToStr(pDir, str);
            ADD_DATA_PAIR(art, str.c_str())
        }
        for (int i = 0; i < vec.size(); i++) {
            char buf[12];
            ADD_BUFFER_PAIR(buf, vec[i], "song_id%03d", i);
        }
        RECORD_DATA_POINT(i12, results, o);
    }
}

void RockCentral::DeleteNextUser() {
    int id = TheWiiProfileMgr.GetNextDeleteQueueId();
    if (id != 0) {
        OnlineID oid;
        oid.SetPrincipalID(id);
        TheNet.GetServer()->DeleteProfile(oid);
    }
}

void RockCentral::UpdateSetlistArt(
    LocalSavedSetlist *setlist, int i2, Hmx::Object *o, int i4
) {
    HxGuid guid = setlist->mGuid;
    String str(MakeString(
        "{\"type\": \"setlist_art\", \"setlist_guid\": \"%s\", \"revision\": %d}",
        guid.ToString(),
        i2
    ));
    SaveBinaryData(setlist->GetArtTex(), str, o, i4);
}

void RockCentral::UpdateBattleArt(RndTex *tex, Hmx::Object *o, int i) {
    String str(MakeString("{\"type\": \"battle_art\", \"revision\": 1 }"));
    SaveBinaryData(tex, str, o, i);
}

void RockCentral::UpdateBandLogo(int i1, RndTex *tex, int i3, Hmx::Object *o, int i5) {
    String str(MakeString(
        "{\"type\": \"band_logo\", \"band_id\": %d, \"revision\": %d }", i1, i3
    ));
    SaveBinaryData(tex, str, o, i5);
}

void RockCentral::GetSetlistArt(const char *cc, RndTex *tex, Hmx::Object *o, int i) {
    String str(MakeString(
        "{\"type\": \"setlist_art\", \"setlist_guid\": \"%s\", \"revision\": -1}", cc
    ));
    GetArtFile(str, tex, nullptr, o, i);
}

void RockCentral::GetBattleArt(int i1, RndTex *tex, Hmx::Object *o, int i4) {
    String str(
        MakeString("{\"type\": \"battle_art\", \"battle_id\": %d, \"revision\": -1}", i1)
    );
    GetArtFile(str, tex, nullptr, o, i4);
}

DECOMP_FORCEACTIVE(RockCentral, "band")

void RockCentral::RedeemToken(
    int i1, String str, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        INIT_DATAPOINT("trs/redeem_token");
        ADD_DATA_PAIR(tr_pid, i1);
        ADD_DATA_PAIR(token, str);
        RECORD_DATA_POINT(0, results, o);
    }
}

DECOMP_FORCEACTIVE(RockCentral, "trs/complete_purchase")

void RockCentral::GetRedeemedTokensByPlayer(
    int i1, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        INIT_DATAPOINT("trs/redeemed_tokens");
        ADD_DATA_PAIR(tr_pid, i1);
        RECORD_DATA_POINT(0, results, o);
    }
}

DECOMP_FORCEACTIVE(RockCentral, "entities/online_friends/get")

void RockCentral::UpdateChar(
    TourCharLocal *tcl, DataResultList &results, Hmx::Object *o, int i4, int i5
) {
    Server *server = IsConnected(o, i4, false);
    if (server) {
        BandProfile *profile = TheProfileMgr.FindCharOwnerFromGuid(tcl->GetGuid());
        if (profile) {
            MILO_ASSERT(profile, 0xB35);
            MemStream ms;
            tcl->SaveDb(ms);
            INIT_DATAPOINT("entities/character/update");
            ADD_DATA_PAIR(guid, tcl->GetGuid().ToString());
            ADD_DATA_PAIR(pid, server->GetPlayerID(profile->GetPadNum()));
            ADD_DATA_PAIR(name, tcl->GetCharacterName());
            ADD_DATA_PAIR(flags, i5);
            String str;
            ConvertToStr(ms, str);
            ADD_DATA_PAIR(char_data, str);
            RECORD_DATA_POINT(i4, results, o);
        }
    }
}

void RockCentral::VerifyCharName(
    const char *cc, DataResultList &results, Hmx::Object *o, int i4, int i5
) {
    Server *server = IsConnected(o, i4, false);
    if (server) {
        INIT_DATAPOINT("entities/character/name/check");
        ADD_DATA_PAIR(name, cc);
        ADD_DATA_PAIR(flags, i5);
        RECORD_DATA_POINT(i4, results, o);
    }
}

void RockCentral::VerifyBandName(
    const char *cc, DataResultList &results, Hmx::Object *o, int i4, int i5
) {
    Server *server = IsConnected(o, i4, false);
    if (server) {
        INIT_DATAPOINT("entities/band/name/check");
        ADD_DATA_PAIR(name, cc);
        ADD_DATA_PAIR(flags, i5);
        RECORD_DATA_POINT(i4, results, o);
    }
}

DECOMP_FORCEACTIVE(RockCentral, "store/get_index_page")

void RockCentral::GetWebLinkStatus(
    const Profile *profile, int i2, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, i2, false);
    if (server) {
        MILO_ASSERT(profile, 0xB97);
        INIT_DATAPOINT("misc/get_accounts_web_linked_status");
        ADD_DATA_PAIR(pid, server->GetPlayerID(profile->GetPadNum()));
        RECORD_DATA_POINT(i2, results, o);
    }
}

void RockCentral::GetSetlistCreationStatus(
    const Profile *profile, int i2, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, i2, false);
    if (server) {
        MILO_ASSERT(profile, 0xBA9);
        INIT_DATAPOINT("misc/get_accounts_setlist_creation_status");
        ADD_DATA_PAIR(pid, server->GetPlayerID(profile->GetPadNum()));
        RECORD_DATA_POINT(i2, results, o);
    }
}

bool RockCentral::GetIsDiskSong(int songID) {
    bool ret = false;
    if (songID - 0x3e9U > 0x69)
        return ret;
    static const int sSongIds[] = {
        0x3e9, 0x3eb, 0x3ec, 0x3f0, 0x3f1, 0x3f3, 0x3f4, 0x3f5, 0x3f6, 0x3f7, 0x3f8,
        0x3fa, 0x3fd, 0x400, 0x401, 0x404, 0x405, 0x406, 0x407, 0x408, 0x409, 0x40a,
        0x40b, 0x40c, 0x40d, 0x40e, 0x413, 0x414, 0x415, 0x416, 0x417, 0x418, 0x419,
        0x41a, 0x41c, 0x41d, 0x41e, 0x41f, 0x420, 0x421, 0x422, 0x424, 0x425, 0x427,
        0x428, 0x42a, 0x42b, 0x42d, 0x42e, 0x42f, 0x430, 0x431, 0x432, 0x433, 0x434,
        0x435, 0x436, 0x437, 0x438, 0x439, 0x43a, 0x43b, 0x43c, 0x43d, 0x43e, 0x43f,
        0x440, 0x441, 0x442, 0x443, 0x444, 0x445, 0x446, 0x447, 0x449, 0x44a, 0x44c,
        0x44d, 0x44e, 0x44f, 0x450, 0x451, 0x452
    };
    for (int i = 0; i < 83; i++) {
        if (songID == sSongIds[i]) {
            ret = true;
            break;
        } else if (sSongIds[i] > songID)
            break;
    }
    return ret;
}

void RockCentral::SyncAvailableSongs(
    const std::vector<BandProfile *> &profiles,
    const std::vector<int> &ivec1,
    const std::vector<int> &ivec2,
    Hmx::Object *o
) {
    Server *server = IsConnected(o, -1, false);
    if (server) {
        INIT_DATAPOINT("misc/sync_available_songs");
        for (int i = 0; i < profiles.size(); i++) {
            char buf[8];
            ADD_BUFFER_PAIR(
                buf, server->GetPlayerID(profiles[i]->GetPadNum()), "pid%03d", i
            );
        }
        String str;
        char strBuf[0x18];
        FOREACH (it, ivec1) {
            int cur = *it;
            if (!GetIsDiskSong(cur)) {
                if (str.length() != 0) {
                    str += ",";
                }
                snprintf(strBuf, 0x18, "%d", cur);
                str += strBuf;
            }
        }
        ADD_DATA_PAIR(sids, str);

        String ustr;
        FOREACH (it, ivec2) {
            int cur = *it;
            if (!GetIsDiskSong(cur)) {
                if (ustr.length() != 0) {
                    ustr += ",";
                }
                snprintf(strBuf, 0x18, "%d", cur);
                ustr += strBuf;
            }
        }
        ADD_DATA_PAIR(usids, ustr);
        RecordDataPointNoRet(dataPoint, 0);
    }
}

void RockCentral::DataPointToQString(const DataPoint &, Quazal::String &) {
    MILO_WARN("RockCentral::DataPointToQString - Unsupported type %d!");
}

void RockCentral::AddBuildInfoToDP(DataPoint &dataPoint) {
    String str14;
    str14 = "n/a";
    ADD_DATA_PAIR(h_sdkVer, str14);
    ADD_DATA_PAIR(h_drs, "r");

    String str20 = SystemConfig()->File();
    ADD_DATA_PAIR(h_cfgName, str20);

    String str2c;
    SystemConfig()->FindData("version", str2c, false);
    ADD_DATA_PAIR(h_buildVersion, str2c);
    ADD_DATA_PAIR(h_host, NetworkSocket::GetHostName());
    ADD_DATA_PAIR(h_plat, PlatformSymbol(TheLoadMgr.GetPlatform()));
    ADD_DATA_PAIR(h_lang, SystemLanguage());
    ADD_DATA_PAIR(h_cd, (int)UsingCD());
}

void RockCentral::RecordDataPoint(
    DataPoint &dataPoint, int i2, DataResultList &results, Hmx::Object *o
) {
    Server *server = IsConnected(o, i2, false);
    if (server) {
        MILO_ASSERT(!dataPoint.mType.Null(), 0xC9F);
        if (dataPoint.mType.Null())
            SendFailure(o, 0, i2);
        else {
            results.Clear();
            DataArray *cfg = SystemConfig("data_point_mgr", "filters");
            if (cfg) {
                int numCfg = cfg->Size();
                for (int i = 1; i < numCfg; i++) {
                    if (dataPoint.mType == cfg->Sym(i)) {
                        SendFailure(o, 0, i2);
                        return;
                    }
                }
            }
            IdUpdater *u = new IdUpdater(i2);
            ContextWrapper *wrapper =
                mContextWrapperPool->NewContextWrapper(o, u, true, i2);
            if (!wrapper) {
                delete u;
            } else {
                u->SetWrapper(wrapper);
                AddBuildInfoToDP(dataPoint);
                ADD_DATA_PAIR(machine_id, g_szMachineIdString);
                ADD_DATA_PAIR(system_ms, SystemMs());
                ADD_DATA_PAIR(region, PlatformRegionToSymbol(ThePlatformMgr.GetRegion()));
                ADD_DATA_PAIR(session_guid, TheRockCentral.unk88.ToString());
                static Quazal::String qString;
                qString = "";
                DataPointToQString(dataPoint, qString);
                if (gDataPointLog) {
                    *gDataPointLog << qString.m_szContent << "\n";
                    gDataPointLog->mFile.Flush();
                }
                if (mRBData) {
                    if (o) {
                        mRBData->CallDataPoint(
                            wrapper->mContext, qString, results.mQDataResultString
                        );
                    } else {
                        mRBData->CallDataPointNoRet(wrapper->mContext, qString);
                    }
                }
            }
        }
    }
}

DECOMP_FORCEACTIVE(RockCentral, "QUAZAL CALL FAILED", "NOT LOGGED IN")

void RockCentral::RecordDataPointNoRet(DataPoint &dp, int i2) {
    DataResultList list;
    RecordDataPoint(dp, i2, list, nullptr);
}

bool RockCentral::IsLoginMandatory() {
    if (TheGameMode) {
        if (TheGameMode->Property("online_play_required")->Int()) {
            return true;
        }
    }
    return false;
}

const char *RockCentral::GetBattleEndTimeStr(BattleTimeUnits units) {
    switch (units) {
    case kBattleTimeSeconds:
        return "seconds";
    case kBattleTimeMinutes:
        return "minutes";
    case kBattleTimeHours:
        return "hours";
    case kBattleTimeDays:
        return "days";
    case kBattleTimeWeeks:
        return "weeks";
    default:
        MILO_FAIL("Bad time unit in GetBattleEndTimeStr");
        return nullptr;
    }
}

char RockCentral::GetDifficultyID(int x) {
    switch (x) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    default:
        MILO_WARN("Bad difficulty state in Rock Central call: %i", x);
        return 1;
    }
}

DECOMP_FORCEACTIVE(RockCentral, "Bad difficulty state in Rock Central call")

int RockCentral::GetActiveContextHighWatermark() {
    if (mContextWrapperPool)
        return mContextWrapperPool->unk8ca0;
    else
        return 0;
}

void RockCentral::ExecuteConfig(const char *cc) {
    DataArray *cfg = SystemConfig("objects");
    if (!*cc || unk85)
        return;
    DataNode n18(0);
    n18 = DataNode(DataReadString(cc), kDataArray);
    n18.Array()->Release();
    if (n18.Array()->Type(0) == kDataCommand && n18.Array()->Size() == 1) {
        n18.Array()->Command(0)->Execute();
    } else {
        n18.Array()->Execute();
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(RockCentral)
    HANDLE_MESSAGE(ServerStatusChangedMsg)
    HANDLE_MESSAGE(UserLoginMsg)
    HANDLE_MESSAGE(FriendsListChangedMsg)
    HANDLE_MESSAGE(ConnectionStatusChangedMsg)
    HANDLE_MESSAGE(ProfileChangedMsg)
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_MESSAGE(DeleteQueueUpdatedMsg)
    HANDLE_MESSAGE(DeleteUserCompleteMsg)
    HANDLE_MESSAGE(WiiFriendMgrOpCompleteMsg)
    HANDLE_MESSAGE(WiiFriendsListChangedMsg)
    HANDLE_MESSAGE(EnumerateMessagesCompleteMsg)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_MESSAGE(InviteReceivedMsg)
    HANDLE_ACTION(clear_pending_invitations, ClearPendingInvitations())
    HANDLE_EXPR(state, mState)
    HANDLE_ACTION(force_logout, ForceLogout())
    HANDLE_EXPR(is_online, IsOnline())
    HANDLE_EXPR(toggle_block_login, BlockLoginToggle())
    HANDLE_ACTION(block_login, BlockLogin(_msg->Int(2)))
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0xD98)
END_HANDLERS
#pragma pop

void RockCentral::SendFailure(Hmx::Object *o, int i2, int i3) {
    if (o) {
        RockCentralOpCompleteMsg msg(false, i2, i3);
        o->Handle(msg, true);
    }
}