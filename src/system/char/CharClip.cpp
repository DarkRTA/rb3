#include "char/CharClip.h"

const char* CharClip::BeatAlignString(int mask){
    switch(mask & 0xF600){
        case 0x200: return "RealTime";
        case 0x400: return "UserTime";
        case 0x1000: return "BeatAlign1";
        case 0x2000: return "BeatAlign2";
        case 0x4000: return "BeatAlign4";
        case 0x8000: return "BeatAlign8";
        default: return "NoAlign";
    }
}

CharClip::BeatEvent::BeatEvent() : beat(0) {

}

CharClip::BeatEvent::BeatEvent(const BeatEvent& ev) : event(ev.event), beat(ev.beat) {

}

CharClip::BeatEvent& CharClip::BeatEvent::operator=(const BeatEvent& ev){
    event = ev.event;
    beat = ev.beat;
}

void CharClip::BeatEvent::Load(BinStream& bs){
    bs >> event;
    bs >> beat;
}

CharClip::Transitions::Transitions(Hmx::Object* o) : mNodeStart(0), mNodeEnd(0), mOwner(o) {

}

CharClip::Transitions::~Transitions(){ Clear(); }

void CharClip::Transitions::Clear(){
    for(NodeVector* it = mNodeStart; it < mNodeEnd; it = &it[it->size]){
        it->clip->Release(mOwner);
    }
    Resize(0, 0);
}

int CharClip::Transitions::Size() const {
    int size = 0;
    for(NodeVector* it = mNodeStart; it < mNodeEnd; it = &it[it->size]){
        size++;
    }
    return size;
}

void CharClip::Init(){
    FacingSet::Init();
    REGISTER_OBJ_FACTORY(CharClip);
}

CharClip::CharClip() : mTransitions(this), mFramesPerSec(30.0f), mBeatTrack(), mFlags(0), mPlayFlags(0), mRange(0.0f), 
    mDirty(1), mDoNotCompress(0), unk42(-1), mRelative(this, 0), mBeatEvents(), mSyncAnim(this, 0), mFull(), mOne(), mFacing() {
    mBeatTrack.resize(1, Key<float>(0,0));
    mBeatTrack.front().frame = 0.0f;
    mBeatTrack.front().value = 0.0f;
}

CharClip::~CharClip(){
    
}