#include "network/net/Jobs_RV.h"
#include "Jobs_RV.h"
#include "Protocol/ProtocolCallContext.h"
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
    if (!TheNet.GetServer()->IsConnected() || !mGathering->mPtr) {
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
    else if (!mGathering->mPtr)
        return true;
    else if (mAsync->GetState() != 1) {
        if (mAsync->GetState() == 3)
            return true;
        Quazal::MatchMakingClient *client = TheNet.GetServer()->GetMatchMakingClient();
        bool i4 = true;
        switch (mState) {
        case 0:
            mState = 1;
            i4 = client->Participate(mAsync, 0, "");
            break;
        case 1:
            mState = 2;
            i4 = client->LaunchSession(mAsync, 0, "");
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