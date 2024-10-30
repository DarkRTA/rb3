#pragma once
#include "NetSession.h"

class RVSessionData : public SessionData {
public:
    RVSessionData();
    virtual ~RVSessionData(){}
    virtual void CopyInto(const SessionData*);
    virtual void Save(BinStream&) const;
    virtual void Load(BinStream&);
    virtual bool Equals(const SessionData*) const;

};