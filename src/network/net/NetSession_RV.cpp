#include "network/net/NetSession_RV.h"
#include "HarmonixGatheringDDL_Wii.h"
#include "Plugins/Buffer.h"
#include "Protocol/ProtocolCallContext.h"
#include "Services/MatchMakingClient.h"
#include "decomp.h"
#include "meta/Profile.h"
#include "meta_band/BandNetGameData.h"
#include "net/Jobs_RV.h"
#include "net/Net.h"
#include "net/NetSearchResult.h"
#include "net/NetSession.h"
#include "net/SessionMessages.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "os/PlatformMgr.h"
#include "utl/MemStream.h"
#include "utl/Symbols.h"

namespace {
    void SerializeNetSearchResult(Quazal::Buffer &buffer, NetSearchResult *res) {
        buffer.Clear();
        MemStream ms(true);
        res->Save(ms);
        buffer.AppendData(ms.Buffer(), ms.BufferSize(), -1);
    }
}

NetSession *NetSession::New() { return new RVSession(); }

RVSession::RVSession() : mJoined(0), mUpdateSettingsID(-1) {
    ThePlatformMgr.AddSink(this, signin_changed);
}

RVSession::~RVSession() {
    DeleteSession();
    ThePlatformMgr.RemoveSink(this, signin_changed);
}

void RVSession::LeaveSession(RVSessionData *data) {
    if (TheNet.GetServer()->IsConnected()) {
        Quazal::MatchMakingClient *client = TheNet.GetServer()->GetMatchMakingClient();
        Quazal::ProtocolCallContext *ctx = new Quazal::ProtocolCallContext();
        ctx->SetFlag(2);
        client->CancelParticipation(ctx, data->mGatheringID, "");
    }
}

void RVSession::DeleteSession() {
    if (mGathering) {
        unsigned int u4 = mGathering->unk4;
        if (mUpdateSettingsID != -1) {
            mJobMgr.CancelJob(mUpdateSettingsID);
            mUpdateSettingsID = -1;
        }
        mGathering = nullptr;
        if (TheNet.GetServer()->IsConnected()) {
            Quazal::MatchMakingClient *client =
                TheNet.GetServer()->GetMatchMakingClient();
            Quazal::ProtocolCallContext *ctx = new Quazal::ProtocolCallContext();
            ctx->SetFlag(2);
            client->UnregisterGathering(ctx, u4);
        }
    } else if (mJoined) {
        RVSessionData *sData = dynamic_cast<RVSessionData *>(mData);
        LeaveSession(sData);
        mJoined = false;
    }
}

Job *RVSession::PrepareRegisterHostSessionJob() {
    RVSessionData *data = dynamic_cast<RVSessionData *>(mData);
    Quazal::HarmonixGathering *gathering = new Quazal::HarmonixGathering();
    mGathering = gathering;
    int padnum = mLocalHost->GetPadNum();
    data->mHostID = TheNet.GetServer()->GetPlayerID(padnum);
    gathering->unk10 = 0;
    gathering->unk12 = TheNet.GetGameData()->GetNumPlayersAllowed();
    gathering->unk28 = mSettings->mPublic;
    for (int i = 0; i < mSettings->NumCustomSettings(); i++) {
        switch (i) {
        case 0:
            gathering->unk2c = mSettings->GetCustomValue(i);
            break;
        case 1:
            gathering->unk30 = mSettings->GetCustomValue(i);
            break;
        case 2:
            gathering->unk34 = mSettings->GetCustomValue(i);
            break;
        case 3:
            gathering->unk38 = mSettings->GetCustomValue(i);
            break;
        case 4:
            gathering->unk3c = mSettings->GetCustomValue(i);
            break;
        case 5:
            gathering->unk40 = mSettings->GetCustomValue(i);
            break;
        case 6:
            gathering->unk44 = mSettings->GetCustomValue(i);
            break;
        case 7:
            gathering->unk48 = mSettings->GetCustomValue(i);
            break;
        case 8:
            gathering->unk4c = mSettings->GetCustomValue(i);
            break;
        case 9:
            gathering->unk50 = mSettings->GetCustomValue(i);
            break;
        case 10:
            gathering->unk54 = mSettings->GetCustomValue(i);
            break;
        default:
            MILO_FAIL("Session has too many custom parameters");
            break;
        }
    }
    NetSearchResult *res = NetSearchResult::New();
    mData->CopyInto(res->mSessionData);
    SerializeNetSearchResult(gathering->unk58, res);
    delete res;
    return new MakeSessionJob(&mGathering, data);
}

Job *RVSession::PrepareConnectSessionJob() {
    RVSessionData *data = dynamic_cast<RVSessionData *>(mJoinData);
    return new JoinSessionJob(data);
}

void RVSession::FinishJoin(const JoinResponseMsg &msg) {
    if (IsOnlineEnabled()) {
        if (msg.Joined()) {
            DeleteSession();
            mJoined = true;
        } else {
            RVSessionData *data = dynamic_cast<RVSessionData *>(mJoinData);
            LeaveSession(data);
        }
    }
}

void RVSession::UpdateSettings() {
    if (IsHost() && mGathering) {
        Quazal::HarmonixGathering *gathering =
            dynamic_cast<Quazal::HarmonixGathering *>(mGathering.mPtr);
        NetSearchResult *res = NetSearchResult::New();
        mData->CopyInto(res->mSessionData);
        SerializeNetSearchResult(gathering->unk58, res);
        delete res;
        for (int i = 0; i < mSettings->NumCustomSettings(); i++) {
            switch (i) {
            case 0:
                gathering->unk2c = mSettings->GetCustomValue(i);
                break;
            case 1:
                gathering->unk30 = mSettings->GetCustomValue(i);
                break;
            case 2:
                gathering->unk34 = mSettings->GetCustomValue(i);
                break;
            case 3:
                gathering->unk38 = mSettings->GetCustomValue(i);
                break;
            case 4:
                gathering->unk3c = mSettings->GetCustomValue(i);
                break;
            case 5:
                gathering->unk40 = mSettings->GetCustomValue(i);
                break;
            case 6:
                gathering->unk44 = mSettings->GetCustomValue(i);
                break;
            case 7:
                gathering->unk48 = mSettings->GetCustomValue(i);
                break;
            case 8:
                gathering->unk4c = mSettings->GetCustomValue(i);
                break;
            case 9:
                gathering->unk50 = mSettings->GetCustomValue(i);
                break;
            case 10:
                gathering->unk54 = mSettings->GetCustomValue(i);
                break;
            default:
                MILO_FAIL("Session has too many custom parameters");
                break;
            }
        }
        gathering->unk28 = mSettings->mPublic;
        if (TheNet.GetServer()->IsConnected()) {
            UpdateSettingsJob *job = new UpdateSettingsJob(&mGathering);
            mUpdateSettingsID = job->ID();
            mJobMgr.QueueJob(job);
        }
    }
}

DataNode RVSession::OnUpdateFinished(DataArray *) {
    mUpdateSettingsID = -1;
    return 1;
}

void RVSession::StartSession() {
    if (mGathering && IsHost()) {
        ChangeSessionStateJob *job = new ChangeSessionStateJob(mGathering->unk4, 2);
        mJobMgr.QueueJob(job);
    }
}

void RVSession::EndSession(bool) {
    if (mGathering && IsHost()) {
        ChangeSessionStateJob *job = new ChangeSessionStateJob(mGathering->unk4, 6);
        mJobMgr.QueueJob(job);
    }
}

bool RVSession::OnMsg(const SigninChangedMsg &msg) {
    MsgSource::Handle(msg, false);
    return true;
}

void RVSession::InviteFriend(Friend *fr, const char *c1, const char *c2) {
    RVSessionData *data = dynamic_cast<RVSessionData *>(mData);
    int i4 = data->mGatheringID;
    MemStream ms;
    ms << i4;
    ThePlatformMgr.SendMsg(fr, c1, c2, ms);
}

Job *RVSession::PrepareRegisterArbitrationJob() {
    MILO_FAIL("Ranked modes not supported");
    return nullptr;
}

BEGIN_HANDLERS(RVSession)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE(update_finished, OnUpdateFinished)
    HANDLE_SUPERCLASS(NetSession)
    HANDLE_CHECK(0x133)
END_HANDLERS

SessionData *SessionData::New() { return new RVSessionData(); }

RVSessionData::RVSessionData() : mGatheringID(0), mHostID(0) {}

void RVSessionData::CopyInto(SessionData *data) {
    RVSessionData *rvData = dynamic_cast<RVSessionData *>(data);
    rvData->mGatheringID = mGatheringID;
    rvData->mHostID = mHostID;
}

void RVSessionData::Save(BinStream &bs) const {
    bs << mGatheringID;
    bs << mHostID;
}

void RVSessionData::Load(BinStream &bs) {
    bs >> mGatheringID;
    bs >> mHostID;
}

bool RVSessionData::Equals(const SessionData *data) const {
    const RVSessionData *rvData = dynamic_cast<const RVSessionData *>(data);
    return mHostID == rvData->mHostID && mGatheringID == rvData->mGatheringID;
}