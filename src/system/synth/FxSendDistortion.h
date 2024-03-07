#ifndef SYNTH_FXSENDDISTORTION_H
#define SYNTH_FXSENDDISTORTION_H
#include "synth/FxSend.h"

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

    static unsigned short gRev;
    static unsigned short gAltRev;

    float mDrive;
};

#endif
