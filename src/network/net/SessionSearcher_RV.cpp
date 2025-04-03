#include "network/net/SessionSearcher_RV.h"
#include "HarmonixGatheringDDL_Wii.h"
#include "MatchmakingSettings.h"
#include "NetSession_RV.h"
#include "Protocol/ProtocolCallContext.h"
#include "SessionSearcher.h"
#include "ddl/ResultRange.h"
#include "decomp.h"
#include "net/Net.h"
#include "net/NetSearchResult.h"
#include "net/NetSession.h"
#include "obj/Msg.h"
#include "os/Debug.h"
#include "utl/BinStream.h"
#include "utl/MemStream.h"

SessionSearcher *SessionSearcher::New() { return new RVSessionSearcher(); }

RVSessionSearcher::RVSessionSearcher() : mSearchCallback(0), mInviteCallback(0) {}

RVSessionSearcher::~RVSessionSearcher() { delete mSearchCallback; }

UNPOOL_DATA
void RVSessionSearcher::Poll() {
    SessionSearcher::Poll();
    if (mSearchCallback) {
        switch (mSearchCallback->GetState()) {
        case 1:
            break;
        case 2:
            FOREACH (it, mResultsList) {
                Quazal::HarmonixGathering *gathering =
                    dynamic_cast<Quazal::HarmonixGathering *>(it->Ptr());
                int bufferSize = gathering->unk58.GetContentSize();
                MemStream ms(true);
                ms.Resize(bufferSize);
                gathering->unk58.CopyContent((void *)ms.Buffer(), bufferSize, 0);
                ms.Seek(0, BinStream::kSeekBegin);
                NetSearchResult *res = NetSearchResult::New();
                res->Load(ms);
                RVSessionData *rvData = dynamic_cast<RVSessionData *>(res->mSessionData);
                rvData->mGatheringID = gathering->unk4;
                rvData->mHostID = gathering->unkc;
                UpdateSearchList(res);
            }
        default:
            RELEASE(mSearchCallback);
            StopSearching();
            break;
        }
    }
    if (mInviteCallback) {
        switch (mInviteCallback->GetState()) {
        case 1:
            break;
        case 2: {
            Quazal::HarmonixGathering *gathering =
                dynamic_cast<Quazal::HarmonixGathering *>(mInviteResult.Ptr());
            int bufferSize = gathering->unk58.GetContentSize();
            MemStream ms(true);
            ms.Resize(bufferSize);
            gathering->unk58.CopyContent((void *)ms.Buffer(), bufferSize, 0);
            ms.Seek(0, BinStream::kSeekBegin);
            mLastInviteResult->Load(ms);
            RVSessionData *rvData =
                dynamic_cast<RVSessionData *>(mLastInviteResult->mSessionData);
            rvData->mGatheringID = gathering->unk4;
            rvData->mHostID = gathering->unkc;
            static InviteAcceptedMsg inviteMsg(unk48, 0, 0);
            MsgSource::Handle(inviteMsg, false);
            goto ending;
            break;
        }
        default:
            static InviteAcceptedMsg inviteMsg(unk48, 0, 1);
            MsgSource::Handle(inviteMsg, false);
        ending:
            RELEASE(mInviteCallback);
            break;
        }
    }
}
END_UNPOOL_DATA

UNPOOL_DATA
void RVSessionSearcher::StartSearching(User *user, const SearchSettings &settings) {
    SessionSearcher::StartSearching(user, settings);
    mResultsList.clear();
    static Quazal::ResultRange range(0, 20);
    mSearchCallback = new Quazal::ProtocolCallContext();
    static Quazal::qList<int> props;
    static int queryID = settings.mQueryID;
    props.clear();
    for (int i = 0; i < settings.NumCustomSettings(); i++) {
    }
    if (TheNet.GetServer()->IsConnected()) {
        TheNet.GetServer()->GetCustomMatchMakingClient()->CallCustomFind(
            mSearchCallback, queryID, props, range, &mResultsList
        );
    }
}
END_UNPOOL_DATA

void RVSessionSearcher::StopSearching() {
    SessionSearcher::StopSearching();
    RELEASE(mSearchCallback);
}

void RVSessionSearcher::ClearSearchResults() {
    SessionSearcher::ClearSearchResults();
    mResultsList.clear();
}

int RVSessionSearcher::OnMsg(const InviteAcceptedMsg &msg) {
    if (!TheNet.GetServer()->IsConnected()) {
        MILO_WARN("Invite Lost Due to Disconnected state");
        return 0;
    } else {
        int i6 = msg->Int(3);
        RELEASE(mInviteCallback);
        mInviteCallback = new Quazal::ProtocolCallContext();
        mInviteResult = nullptr;
        unk48 = msg->Int(2);
        bool success = TheNet.GetServer()->GetMatchMakingClient()->FindByID(
            mInviteCallback, i6, &mInviteResult
        );
        MILO_ASSERT(success, 0xCF);
        return 1;
    }
}