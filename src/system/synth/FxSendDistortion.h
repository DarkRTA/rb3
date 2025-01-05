#pragma once
#include "synth/FxSend.h"

/** "distortion effect" */
class FxSendDistortion : public FxSend {
public:
    FxSendDistortion();
    virtual ~FxSendDistortion();
    OBJ_CLASSNAME(FxSendDistortion);
    OBJ_SET_TYPE(FxSendDistortion);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;

    /** "amount of drive". Ranges from 0 to 100. */
    float mDrive; // 0x48
};
