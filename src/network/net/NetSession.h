#pragma once
#include "obj/MsgSource.h"

class NetSession : public MsgSource {
public:
    NetSession();
    // virtual methods here

    bool IsLocal() const;
};

extern NetSession* TheNetSession;