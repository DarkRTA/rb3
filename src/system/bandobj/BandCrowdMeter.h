#pragma once
#include "rndobj/Dir.h"
#include "bandobj/CrowdMeterIcon.h"

class BandCrowdMeter : public RndDir {
public:
    BandCrowdMeter();
    OBJ_CLASSNAME(BandCrowdMeterDir);
    OBJ_SET_TYPE(BandCrowdMeterDir);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~BandCrowdMeter();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void Poll();

    bool Disabled() const;
    CrowdMeterIcon* PlayerIcon(int);
};