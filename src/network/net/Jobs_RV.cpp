#include "network/net/Jobs_RV.h"
#include "Jobs_RV.h"
#include "Protocol/ProtocolCallContext.h"
#include "net/Net.h"
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