#pragma once
#include "rndobj/Trans.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "synth/SfxInst.h"
#include "obj/ObjPtr_p.h"

class Sfx;

/** "A 3D positional emitter.  The volume and surround-panning of
 *  a sfx are controlled by its position relative to a listener (usually the
 *  camera)." */
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

    /** "sfx this emitter should play" */
    ObjPtr<Sfx> mSfx; // 0xb8
    ObjPtr<SfxInst> mInst; // 0xc4
    /** "object representing the listener's position" */
    ObjPtr<RndTransformable> mListener; // 0xd0
    /** "volume and pan are fixed inside this radius." */
    float mRadInner; // 0xdc
    /** "the sound starts playing when you cross inside this radius." */
    float mRadOuter; // 0xe0
    /** "volume at inner radius (and inside)" */
    float mVolInner; // 0xe4
    /** "volume at outer radius, in dB" */
    float mVolOuter; // 0xe8

    // mEnabled: 0x98 >> 5 & 1
};
