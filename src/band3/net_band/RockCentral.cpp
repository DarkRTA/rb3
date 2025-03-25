#include "net_band/RockCentral.h"
#include "ContextWrapper.h"
#include "band3/meta_band/PerformanceData.h"
#include "decomp.h"
#include "game/GamePanel.h"
#include "meta/ConnectionStatusPanel.h"
#include "meta/Profile.h"
#include "meta/WiiProfileMgr.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SaveLoadManager.h"
#include "net/Net.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/WiiFriendMgr.h"
#include "net/WiiMessenger.h"
#include "net_band/DataResults.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "ui/UIPanel.h"
#include "utl/DataPointMgr.h"
#include "utl/Option.h"
#include "utl/Symbols2.h"
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

DataNode RockCentral::OnMsg(const ServerStatusChangedMsg &) {
    // clang-format off
    // iVar1 = fn_800BED14(msg);
    // if ((iVar1 == 0) || (DAT_809009c4 != 0x0)) {
    //   iVar1 = fn_800BED14(msg);
    //   if (iVar1 == 0) {
    //     if (*(this + 0x3c) == 3) {
    //       *(this + 0x3c) = 0;
    //       dVar6 = Timer::Ms(this + 0x40);
    //       *(this + 0x70) = dVar6 + 8000.0;
    //     }
    //     else {
    //       *(this + 0x3c) = 4;
    //       dVar6 = Timer::Ms(this + 0x40);
    //       *(this + 0x70) = dVar6 + 40000.0;
    //       iVar1 = IsLoginMandatory(this);
    //       if (iVar1 != 0) {
    //         if (lbl_808E4379 == '\0') {
    //           DataNode::DataNode(auStack_48,1);
    //           uVar2 = Symbol::Symbol(auStack_64,&DAT_8084ff54);
    //           Message::Message(&DAT_80900a00,uVar2,auStack_48);
    //           DataNode::~DataNode(auStack_48,0xffffffff);
    //           __register_global_object(&DAT_80900a00,Message::~Message,&DAT_809009f0);
    //           lbl_808E4379 = '\x01';
    //         }
    //         local_68 = SymLostConnection;
    //         uVar2 = MergedGet0x4(&DAT_80900a00);
    //         UIEventMgr::TriggerEvent(TheUIEventMgr,&local_68,uVar2);
    //       }
    //     }
    //     piVar4 = *(this + 0x38);
    //     if (piVar4 != 0x0) {
    //       (**(*piVar4 + 8))(piVar4,1);
    //     }
    //     piVar4 = *(this + 0x34);
    //     *(this + 0x38) = 0;
    //     if (piVar4 != 0x0) {
    //       (**(*piVar4 + 8))(piVar4,1);
    //     }
    //     *(this + 0x34) = 0;
    //     if (DAT_809009c4 != 0x0) {
    //       (**(*DAT_809009c4 + 8))(DAT_809009c4,1);
    //     }
    //     DAT_809009c4 = 0x0;
    //   }
    // }
    // else {
    //   *(this + 0x3c) = 2;
    //   iVar1 = MergedGet0x28(TheNet);
    //   (**(*(iVar1 + 4) + 0x58))();
    //   iVar1 = MergedGet0x28(TheNet);
    //   uVar2 = (**(*(iVar1 + 4) + 0x54))();
    //   pvVar3 = Quazal::RootObject::operator_new(0x80900838);
    //   if (pvVar3 != 0x0) {
    //     pvVar3 = fn_802C4788();
    //   }
    //   *(this + 0x38) = pvVar3;
    //   fn_80092F8C(uVar2,pvVar3,0x74);
    //   piVar4 = Quazal::RootObject::operator_new(0x80900838);
    //   if (piVar4 != 0x0) {
    //     piVar4 = fn_802C4748();
    //   }
    //   DAT_809009c4 = piVar4;
    //   fn_80092F8C(uVar2,piVar4,0x75);
    //   pvVar3 = Quazal::RootObject::operator_new(0x80900838);
    //   if (pvVar3 != 0x0) {
    //     pvVar3 = fn_802C4708();
    //   }
    //   *(this + 0x34) = pvVar3;
    //   fn_80092F8C(uVar2,pvVar3,0x76);
    //   local_2c = 0xffffffff;
    //   local_30 = 0xffffffff;
    //   iVar1 = fn_807BDBA0(&local_30);
    //   if (iVar1 == 0) {
    //     snprintf(lbl_80900838 + 0x10,0x18,&DAT_8084ff44);
    //   }
    //   if (lbl_808E4378 == '\0') {
    //     DataPoint::DataPoint(&DAT_809009d4);
    //     __register_global_object(&DAT_809009d4,fn_8012BE94,&DAT_809009c8);
    //     lbl_808E4378 = '\x01';
    //   }
    //   fn_802C4704(&DAT_809009d8);
    //   uVar2 = Symbol::Symbol(auStack_58,s_config/get_8084ff49);
    //   Symbol::Symbol(&DAT_809009d4,uVar2);
    //   local_60 = SystemLanguage();
    //   local_5c = SymLocale;
    //   fn_802C4700(auStack_40,&local_5c,&local_60);
    //   fn_802C46B0(auStack_28,auStack_40);
    //   fn_802C46AC(auStack_38,&DAT_809009d8,auStack_28);
    //   VarStack::~VarStack(auStack_28,0xffffffff);
    //   pRVar5 = this;
    //   if (this != 0x0) {
    //     pRVar5 = *this;
    //   }
    //   fn_802CF1CC(&DAT_809009d4,0,this + 0x1c,pRVar5);
    //   fn_802CD8D4(this);
    // }
    // uVar2 = MergedGet0x4(msg);
    // MsgSource::Handle(auStack_50,this,uVar2,0);
    // DataNode::~DataNode(auStack_50,0xffffffff);
    // DataNode::DataNode(out,1);
    // return;
    // clang-format on
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
