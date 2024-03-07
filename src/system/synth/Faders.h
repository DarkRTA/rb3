#ifndef SYNTH_FADERS_H
#define SYNTH_FADERS_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"

class Fader : public Hmx::Object {
public:
    Fader();
    virtual ~Fader();
    OBJ_CLASSNAME(Fader);
    OBJ_SET_TYPE(Fader);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    float mVal;
    class FaderTask* mFaderTask;
    Symbol mLocalName;
    // set mClients
    // Mode mMode
};

// class FaderTask {
// public:
//     Timer mTimer;
//     Interpolator* mInterp;
//     Fader* mFader;
//     bool mDone;
// };

#endif
