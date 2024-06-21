#include "rndobj/PartLauncher.h"
#include "utl/Symbols.h"

INIT_REVS(RndPartLauncher)

RndPartLauncher::RndPartLauncher() : mPart(this, 0), mTrans(this, 0), mMeshEmitter(this, 0), mNumParts(0), mEmitRate(0.0f, 0.0f), mEmitCount(0.0f), mPartOverride(&gNoPartOverride) {

}

SAVE_OBJ(RndPartLauncher, 0x91)

BEGIN_HANDLERS(RndPartLauncher)
    HANDLE_ACTION(launch_particles, LaunchParticles())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x104)
END_HANDLERS

BEGIN_PROPSYNCS(RndPartLauncher)
    SYNC_PROP_MODIFY_ALT(part, mPart, CopyPropsFromPart())
    SYNC_PROP(trans, mTrans)
    SYNC_PROP(num_parts, mNumParts)
    SYNC_PROP(emit_rate, mEmitRate)
    SYNC_PROP_SET(override_life, int(mPartOverride->mask & 1), SetBit(1, _val.Int(0)))
    SYNC_PROP(life, mPartOverride->life)
    SYNC_PROP_SET(override_speed, int(mPartOverride->mask >> 1 & 1), SetBit(2, _val.Int(0)))
    SYNC_PROP(speed, mPartOverride->speed)
    SYNC_PROP_SET(override_size, int(mPartOverride->mask >> 2 & 1), SetBit(4, _val.Int(0)))
    SYNC_PROP(size, mPartOverride->size)
    SYNC_PROP_SET(override_delta_size, int(mPartOverride->mask >> 3 & 1), SetBit(8, _val.Int(0)))
    SYNC_PROP(delta_size, mPartOverride->deltaSize)
    SYNC_PROP_SET(override_start_color, int(mPartOverride->mask >> 4 & 1), SetBit(0x10, _val.Int(0)))
    SYNC_PROP(start_color, mPartOverride->startColor)
    SYNC_PROP(start_alpha, mPartOverride->startColor.alpha)
    SYNC_PROP_SET(override_mid_color, int(mPartOverride->mask >> 5 & 1), SetBit(0x20, _val.Int(0)))
    SYNC_PROP(mid_color, mPartOverride->midColor)
    SYNC_PROP(mid_alpha, mPartOverride->midColor.alpha)
    SYNC_PROP_SET(override_end_color, int(mPartOverride->mask >> 6 & 1), SetBit(0x40, _val.Int(0)))
    SYNC_PROP(end_color, mPartOverride->endColor)
    SYNC_PROP(end_alpha, mPartOverride->endColor.alpha)
    SYNC_PROP_SET(override_emit_direction, int(mPartOverride->mask >> 7 & 1), SetBit(0x80, _val.Int(0)))
    SYNC_PROP(pitch_low, mPartOverride->pitch.x)
    SYNC_PROP(pitch_high, mPartOverride->pitch.y)
    SYNC_PROP(yaw_low, mPartOverride->yaw.x)
    SYNC_PROP(yaw_high, mPartOverride->yaw.y)
    SYNC_PROP_SET(override_box_emitter, int(mPartOverride->mask >> 9 & 1), SetBit(0x200, _val.Int(0)))
    SYNC_PROP(box_extent_1, mPartOverride->box.mMin)
    SYNC_PROP(box_extent_2, mPartOverride->box.mMax)
    SYNC_PROP_SET(override_mesh_emitter, int(mPartOverride->mask >> 8 & 1), SetBit(0x100, _val.Int(0)))
    SYNC_PROP(mesh, mMeshEmitter)
END_PROPSYNCS