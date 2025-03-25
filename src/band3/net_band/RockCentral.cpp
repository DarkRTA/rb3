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
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "stl/_pair.h"
#include "ui/UIPanel.h"
#include "utl/DataPointMgr.h"
#include "utl/Option.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/TextFileStream.h"

DECOMP_FORCEACTIVE(RockCentral, __FILE__, "mUpdated")

namespace {
    void RockCentralTerminate() { TheRockCentral.Terminate(); }
}

ContextWrapperPool *RockCentral::mContextWrapperPool;
TextFileStream *gDataPointLog;
RockCentral TheRockCentral;
String RockCentral::kServerVer = "3";

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

        static DataPoint dataPoint;
        dataPoint.mNameValPairs.clear();
        dataPoint.mType = "config/get";
        dataPoint.mNameValPairs.insert(std::make_pair(locale, SystemLanguage()));
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

Symbol PerformanceData::GetMode() const { return mMode; }

int PerformanceData::GetSongID() const { return mSongId; }

bool PerformanceData::IsPlaytest() const { return mIsPlaytest; }

bool PerformanceData::IsOnline() const { return mIsOnline; }

bool PerformanceData::IsCheating() const { return mIsCheating; }

ScoreType PerformanceData::GetScoreType() const { return mScoreType; }

Difficulty PerformanceData::GetDifficulty() const { return mDifficulty; }

int PerformanceData::GetTimeStamp() const { return mTimestamp; }

// Stats& PerformanceData::GetStats() const {
//     return mStats;
// }

int PerformanceData::GetStars() const { return mStars; }

int PerformanceData::GetBattleID() const { return mBattleId; }
