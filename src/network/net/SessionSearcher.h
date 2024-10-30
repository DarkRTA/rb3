#pragma once
#include "MatchmakingSettings.h"
#include "game/GameMessages.h"
#include "net/NetSearchResult.h"
#include "obj/MsgSource.h"
#include "os/User.h"

class SessionSearcher : public MsgSource {
public:
    SessionSearcher();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~SessionSearcher();
    virtual void Poll();
    virtual void StartSearching(User*, const SearchSettings&);
    virtual void StopSearching();
    virtual void ClearSearchResults();
    virtual int OnMsg(const InviteAcceptedMsg&);

    void AllocateNetSearchResults();
    void GetSearchResults(std::vector<NetSearchResult*>&);
    NetSearchResult* GetNextResult();
    void UpdateSearchList(NetSearchResult*);

    NetSearchResult* mLastInviteResult; // 0x1c
    bool mSearching; // 0x20
    std::vector<NetSearchResult*> mSearchList; // 0x24
    int mNextResult; // 0x2c
};