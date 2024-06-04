#ifndef SYNTH_EMITTER_H
#define SYNTH_EMITTER_H
#include "rndobj/Trans.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "synth/SfxInst.h"
#include "obj/ObjPtr_p.h"

class Sfx;

class SynthEmitter : public RndTransformable, public RndDrawable, public RndPollable {
public:
    SynthEmitter();
    OBJ_CLASSNAME(SynthEmitter);
    OBJ_SET_TYPE(SynthEmitter);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~SynthEmitter();
    virtual void Highlight(){ RndDrawable::Highlight(); }
    virtual void DrawShowing();
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual void Poll();

    void CheckLoadResources();

    ObjPtr<Sfx, ObjectDir> mSfx; // 0xb8
    ObjPtr<SfxInst, ObjectDir> mInst; // 0xc4
    ObjPtr<RndTransformable, ObjectDir> mListener; // 0xd0
    float mRadInner; // 0xdc
    float mRadOuter; // 0xe0
    float mVolInner; // 0xe4
    float mVolOuter; // 0xe8

    // mEnabled: 0x98 >> 5 & 1
};

#endif
