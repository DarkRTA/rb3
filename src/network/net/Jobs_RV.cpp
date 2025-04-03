#include "network/net/Jobs_RV.h"
#include "Protocol/ProtocolCallContext.h"
#include "net/QuazalSession.h"
#include "network/Plugins/StationURL.h"
#include "network/ObjDup/Session.h"
#include "net/Net.h"
#include "net/NetSession.h"
#include "obj/Object.h"

RVJob::RVJob() : mAsync(new Quazal::ProtocolCallContext()) {}

RVJob::~RVJob() { delete mAsync; }

bool RVJob::IsFinished() {
    if (!TheNet.GetServer()->IsConnected())
        return true;
    else {
        return mAsync->GetState() != 1;
    }
}

void RVJob::Cancel(Hmx::Object *o) { RELEASE(mAsync); }

MakeSessionJob::MakeSessionJob(
    Quazal::AnyObjectHolder<Quazal::Gathering, Quazal::String> *gathering,
    RVSessionData *data
)
    : mGathering(gathering), mData(data), mAsync(new Quazal::ProtocolCallContext()),
      mState(0) {}

MakeSessionJob::~MakeSessionJob() { delete mAsync; }

void MakeSessionJob::Start() {
    if (!TheNet.GetServer()->IsConnected() || !*mGathering) {
        mState = 4;
    } else if (!TheNet.GetServer()->GetMatchMakingClient()->RegisterGathering(
                   mAsync, *mGathering
               )) {
        mState = 4;
    }
}

bool MakeSessionJob::IsFinished() {
    if (!TheNet.GetServer()->IsConnected())
        return true;
    else if (mState - 3U <= 1)
        return true;
    else if (!*mGathering)
        return true;
    else if (mAsync->GetState() != 1) {
        if (mAsync->GetState() == 3)
            return true;
        Quazal::MatchMakingClient *client = TheNet.GetServer()->GetMatchMakingClient();
        mAsync->Reset();
        bool i4 = true;
        switch (mState) {
        case 0:
            mData->mGatheringID = (*mGathering)->unk4;
            mState = 1;
            i4 = client->Participate(mAsync, (*mGathering)->unk4, "");
            break;
        case 1:
            mState = 2;
            i4 = client->LaunchSession(mAsync, (*mGathering)->unk4, "");
            break;
        case 2:
            mState = 3;
            break;
        default:
            MILO_FAIL("MakeSessionJob in invalid state");
            break;
        }
        if (!i4) {
            mState = 4;
            return true;
        }
    }
    return false;
}

void MakeSessionJob::Cancel(Hmx::Object *) {
    RELEASE(mAsync);
    TheNetSession->OnRegisterSessionJobComplete(false);
}

void MakeSessionJob::OnCompletion(Hmx::Object *) {
    TheNetSession->OnRegisterSessionJobComplete(mState == 3);
}

JoinSessionJob::JoinSessionJob(RVSessionData *data)
    : mData(data), mAsync(new Quazal::ProtocolCallContext()), mState(0) {}

JoinSessionJob::~JoinSessionJob() { delete mAsync; }

void JoinSessionJob::Start() {
    if (!TheNet.GetServer()->IsConnected()) {
        mState = 4;
    } else {
        Quazal::MatchMakingClient *client = TheNet.GetServer()->GetMatchMakingClient();
        if (client->Participate(mAsync, mData->mGatheringID, "")) {
            return;
        } else
            mState = 4;
    }
}

bool JoinSessionJob::IsFinished() {
    if (!TheNet.GetServer()->IsConnected())
        return true;
    else if (mState - 3U <= 1)
        return true;
    else {
        switch (mAsync->GetState()) {
        case 1:
            break;
        case 3:
            return true;
        default:
            mAsync->Reset();
            bool i2 = true;
            static Quazal::qList<Quazal::StationURL> urls;
            switch (mState) {
            case 0:
                mState = 1;
                Quazal::SecureConnectionClient *client =
                    TheNet.GetServer()->GetSecureConnectionClient();
                urls.clear();
                i2 = client->RequestURLs(mAsync, mData->mHostID, &urls);
                break;
            case 1:
                mState = 2;
                i2 = Quazal::Session::JoinSessionImpl(mAsync, urls);
                break;
            case 2:
                urls.clear();
                mState = 3;
                break;
            default:
                MILO_FAIL("MakeSessionJob in invalid state");
                break;
            }
            if (!i2) {
                mState = 4;
                return true;
            }
            break;
        }
        return false;
    }
}

void JoinSessionJob::Cancel(Hmx::Object *) {
    if (mState == 2) {
        QuazalSession::CancelJoinSession();
    }
    RELEASE(mAsync);
    TheNetSession->OnConnectSessionJobComplete(false);
}

void JoinSessionJob::OnCompletion(Hmx::Object *) {
    TheNetSession->OnConnectSessionJobComplete(mState == 3);
}

UpdateSettingsJob::UpdateSettingsJob(
    Quazal::AnyObjectHolder<Quazal::Gathering, Quazal::String> *gathering
)
    : mGathering(gathering) {}

void UpdateSettingsJob::Start() {
    if (!TheNet.GetServer()->IsConnected() || !*mGathering)
        return;
    else {
        Quazal::MatchMakingClient *client = TheNet.GetServer()->GetMatchMakingClient();
        client->UpdateGathering(mAsync, *mGathering);
    }
}

void UpdateSettingsJob::Cancel(Hmx::Object *o) {
    RELEASE(mAsync);
    static Message msg("update_finished", 0);
    o->Handle(msg, true);
}

void UpdateSettingsJob::OnCompletion(Hmx::Object *o) {
    static Message msg("update_finished", 0);
    msg[0] = mAsync->GetState() == 2;
    o->Handle(msg, true);
}

ChangeSessionStateJob::ChangeSessionStateJob(unsigned int id, unsigned int flags)
    : mSessionID(id), mStateFlags(flags) {}

void ChangeSessionStateJob::Start() {
    if (TheNet.GetServer()->IsConnected()) {
        Quazal::MatchMakingClient *client = TheNet.GetServer()->GetMatchMakingClient();
        client->SetState(mAsync, mSessionID, mStateFlags);
    }
}