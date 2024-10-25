#pragma once
#include "obj/Object.h"
#include "utl/Str.h"
#include <set>

class BandMachine : public Hmx::Object {
public:
    BandMachine();
    virtual ~BandMachine(){}
    virtual DataNode Handle(DataArray*, bool);
    virtual bool IsLocal() const = 0;
    virtual String GetPrimaryBandName(){ return unk60; }

    void Reset();

    int unk1c;
    int unk20;
    std::set<int> unk24;
    std::set<int> unk3c;
    String unk54;
    String unk60;
    String unk6c;
    int unk78;
};