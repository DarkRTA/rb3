#pragma once
#include "obj/MsgSource.h"
#include "obj/Object.h"

class RockCentral : public MsgSource {
public:
    RockCentral();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~RockCentral();

    void CancelOutstandingCalls(Hmx::Object*);
};

extern RockCentral TheRockCentral;