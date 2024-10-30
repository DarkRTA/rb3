#include "net/SessionSearcher.h"
#include "game/GameMessages.h"
#include "net/NetSearchResult.h"
#include "obj/Dir.h"
#include "obj/MsgSource.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "utl/Messages.h"
#include "utl/STLHelpers.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include <algorithm>

namespace {
    bool NumPlayersGreaterThan(const NetSearchResult* n1, const NetSearchResult* n2){
        return n1->mNumOpenSlots > n2->mNumOpenSlots;
    }
}

SessionSearcher::SessionSearcher() : mLastInviteResult(0), mSearching(0), mNextResult(0) {
    SetName("session_searcher", ObjectDir::Main());
    ThePlatformMgr.AddSink(this, invite_accepted);
}

void SessionSearcher::AllocateNetSearchResults(){
    mLastInviteResult = NetSearchResult::New();
}

SessionSearcher::~SessionSearcher(){
    ThePlatformMgr.RemoveSink(this);
    delete mLastInviteResult;
    DeleteAll(mSearchList);
}

void SessionSearcher::Poll(){}

void SessionSearcher::StartSearching(User*, const SearchSettings&){
    MILO_ASSERT(!mSearching, 0x3D);
    DeleteAll(mSearchList);
    mSearching = true;
}

void SessionSearcher::StopSearching(){
    mSearching = false;
    mNextResult = 0;
    std::sort(mSearchList.begin(), mSearchList.end(), NumPlayersGreaterThan);
    Handle(search_finished_msg, false);
}

void SessionSearcher::GetSearchResults(std::vector<NetSearchResult*>& results){
    for(std::vector<NetSearchResult*>::iterator it = mSearchList.begin(); it != mSearchList.end(); ++it){
        results.push_back(*it);
    }
}

NetSearchResult* SessionSearcher::GetNextResult(){
    MILO_ASSERT(!mSearching, 0x5D);
    if(mNextResult >= mSearchList.size()) return nullptr;
    else return mSearchList[mNextResult++];
}

void SessionSearcher::ClearSearchResults(){
    MILO_ASSERT(!mSearching, 0x65);
    DeleteAll(mSearchList);
}

void SessionSearcher::UpdateSearchList(NetSearchResult* res){
    mSearchList.push_back(res);
}

int SessionSearcher::OnMsg(const InviteAcceptedMsg&){ return 1; }

BEGIN_HANDLERS(SessionSearcher)
    HANDLE_ACTION(stop_searching, StopSearching())
    HANDLE_EXPR(get_next_result, GetNextResult())
    HANDLE_EXPR(get_last_invite_result, mLastInviteResult)
    HANDLE_MESSAGE(InviteAcceptedMsg)
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0x7F)
END_HANDLERS