#include "net_band/RockCentral.h"
#include "ContextWrapper.h"
#include "RBBinaryDataDDL_Wii.h"
#include "RBDataDDL_Wii.h"
#include "RBTestDDL_Wii.h"
#include "Services/ServiceClient.h"
#include "band3/meta_band/PerformanceData.h"
#include "decomp.h"
#include "game/GamePanel.h"
#include "meta/ConnectionStatusPanel.h"
#include "meta/Profile.h"
#include "meta/WiiProfileMgr.h"
#include "meta_band/BandProfile.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SaveLoadManager.h"
#include "meta_band/UIEventMgr.h"
#include "net/Net.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/WiiFriendMgr.h"
#include "net/WiiMessenger.h"
#include "net_band/DataResults.h"
#include "net_band/RockCentralJobs.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "ui/UIPanel.h"
#include "utl/DataPointMgr.h"
#include "utl/Option.h"
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

ContextWrapperPool *RockCentral::mContextWrapperPool;
TextFileStream *gDataPointLog;
RockCentral TheRockCentral;
String RockCentral::kServerVer = "3";
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
        mRBTest = new Quazal::RBTestClient(1);
        if (!client->RegisterExtraProtocol(mRBTest, 't')) {
            MILO_WARN("Couldn't register RB test protocol\n");
        }
        mRBData = new Quazal::RBDataClient(1);
        if (!client->RegisterExtraProtocol(mRBBinaryData, 'u')) {
            MILO_WARN("Couldn't register RB data protocol\n");
        }
        mRBBinaryData = new Quazal::RBBinaryDataClient(1);
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
#pragma pop