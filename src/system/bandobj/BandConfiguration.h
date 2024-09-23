#pragma once
#include "obj/Object.h"
#include "math/Mtx.h"
#include "char/Waypoint.h"

class BandConfiguration : public Hmx::Object {
public:
    // size 0x34
    class TargTransform {
    public:
        Symbol targName; // 0x0
        Transform xfm; // 0x4
    };

    // size 0xa0
    class TargTransforms {
    public:
        TargTransform xfms[3];
        Waypoint* mWay;
    };

    BandConfiguration();
    virtual ~BandConfiguration();
    OBJ_CLASSNAME(BandConfiguration);
    OBJ_SET_TYPE(BandConfiguration);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    void SyncPlayMode();

    DataNode OnStoreConfiguration(DataArray*);
    DataNode OnReleaseConfiguration(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    TargTransforms mXfms[4]; // 0x1c, 0xbc, 0x15c, 0x1fc
    // 0x29c
};