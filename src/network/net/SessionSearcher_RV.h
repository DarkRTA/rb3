#pragma once
#include "Platform/Holder.h"
#include "Platform/String.h"
#include "Protocol/ProtocolCallContext.h"
#include "Services/Gathering.h"
#include "net/SessionSearcher.h"

class RVSessionSearcher : public SessionSearcher {
public:
    RVSessionSearcher();
    virtual ~RVSessionSearcher();
    virtual void Poll();
    virtual void StartSearching(User *, const SearchSettings &);
    virtual void StopSearching();
    virtual void ClearSearchResults();
    virtual int OnMsg(const InviteAcceptedMsg &);

    Quazal::ProtocolCallContext *mSearchCallback; // 0x30
    Quazal::qList<Quazal::AnyObjectHolder<Quazal::Gathering, Quazal::String> >
        mResultsList; // 0x34
    Quazal::ProtocolCallContext *mInviteCallback; // 0x3c
    Quazal::AnyObjectHolder<Quazal::Gathering, Quazal::String> mInviteResult; // 0x40
    int unk48; // 0x48
};