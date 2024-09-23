#include "bandobj/BandList.h"
#include "ui/UIListDir.h"
#include "utl/Symbols.h"

HighlightObject::HighlightObject(Hmx::Object* o) : mTargetObj(o, 0), mXOffset(0), mYOffset(0), mZOffset(0) {

}

BandList::BandList() : mFocusAnim(this, 0), mPulseAnim(this, 0), mRevealAnim(this, 0), mConcealAnim(this, 0), mRevealSound(this, 0), mConcealSound(this, 0),
    mRevealSoundDelay(0), mConcealSoundDelay(0), mRevealStartDelay(0), mRevealEntryDelay(0), mRevealScale(1.0f), mConcealStartDelay(0), mConcealEntryDelay(0),
    mConcealScale(1.0f), mAutoReveal(0), unk2e8(1), unk2ec(0), mHighlightObjects(this) {

}

BandList::~BandList(){

}

BEGIN_HANDLERS(BandList)
    HANDLE_ACTION(reveal, Reveal())
    HANDLE_ACTION(conceal, Conceal())
    HANDLE_ACTION(conceal_now, ConcealNow())
    HANDLE_ACTION(is_animating, IsAnimating())
    HANDLE_EXPR(is_revealed, !unk2e8 && !IsAnimating())
    HANDLE_ACTION(restart_highlight_matanim, mListDir->ListEntered())
    HANDLE_SUPERCLASS(UIList)
    HANDLE_CHECK(0x468)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(HighlightObject)
    SYNC_PROP(target_object, o.mTargetObj)
    SYNC_PROP(x_offset, o.mXOffset)
    SYNC_PROP(y_offset, o.mYOffset)
    SYNC_PROP(z_offset, o.mZOffset)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(BandList)
    SYNC_PROP(focus_anim, mFocusAnim)
    SYNC_PROP(pulse_anim, mPulseAnim)
    SYNC_PROP(reveal_anim, mRevealAnim)
    SYNC_PROP(reveal_start_delay, mRevealStartDelay)
    SYNC_PROP(reveal_entry_delay, mRevealEntryDelay)
    SYNC_PROP(reveal_scale, mRevealScale)
    SYNC_PROP(reveal_sound, mRevealSound)
    SYNC_PROP(reveal_sound_delay, mRevealSoundDelay)
    SYNC_PROP(conceal_anim, mConcealAnim)
    SYNC_PROP(conceal_start_delay, mConcealStartDelay)
    SYNC_PROP(conceal_entry_delay, mConcealEntryDelay)
    SYNC_PROP(conceal_scale, mConcealScale)
    SYNC_PROP(conceal_sound, mConcealSound)
    SYNC_PROP(conceal_sound_delay, mConcealSoundDelay)
    SYNC_PROP(auto_reveal, mAutoReveal)
    SYNC_PROP(highlight_objects, mHighlightObjects)
    SYNC_SUPERCLASS(UIList)
END_PROPSYNCS