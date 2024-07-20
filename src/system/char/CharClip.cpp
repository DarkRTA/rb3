#include "char/CharClip.h"
#include "char/CharBoneDir.h"
#include "char/CharBonesMeshes.h"
#include "char/CharClipGroup.h"
#include "obj/DataUtl.h"
#include "utl/Symbols.h"

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

CharBoneDir* CharClip::GetResource() const {
    CharBoneDir* dir = 0;
    const DataArray* tdef = TypeDef();
    if(tdef){
        DataArray* found = tdef->FindArray("resource", false);
        if(found) dir = CharBoneDir::FindResource(found->Str(1));
    }
    if(!dir){
        MILO_WARN("%s has no resource", PathName(this));
    }
    return dir;
}

int CharClip::GetContext() const {
    const DataArray* tdef = TypeDef();
    if(tdef){
        DataArray* found = tdef->FindArray("resource", false);
        if(found){
            return DataGetMacro(found->Str(2))->Int(0);
        }
    }
    return 0;
}

void CharClip::StuffBones(CharBones& bones){
    std::list<CharBones::Bone> blist;
    ListBones(blist);
    bones.AddBones(blist);
}

void CharClip::PoseMeshes(ObjectDir* dir, float f){
    CharBonesMeshes meshes;
    meshes.SetName("tmp_viseme_bones", dir);
    StuffBones(meshes);
    ScaleDown(meshes, 0.0f);
    ScaleAdd(meshes, 1.0f, f, 0.0f);
    meshes.PoseMeshes();
}

void CharClip::SetPlayFlags(int i){
    if(i != mPlayFlags){
        mPlayFlags = i;
        mDirty = true;
    }
}

void CharClip::SetFlags(int i){
    if(i != mFlags){
        mFlags = i;
        mDirty = true;
    }
}

bool CharClip::SharesGroups(CharClip* clip){
    std::vector<ObjRef*>::const_reverse_iterator it = Refs().rbegin();
    std::vector<ObjRef*>::const_reverse_iterator itEnd = Refs().rend();
    for(; it != itEnd; it++){
        CharClipGroup* grp = dynamic_cast<CharClipGroup*>((*it)->RefOwner());
        if(grp && grp->HasClip(clip)) return true;
    }
    return false;
}

BEGIN_CUSTOM_PROPSYNC(CharGraphNode)
    SYNC_PROP(cur_beat, o.curBeat)
    SYNC_PROP(next_beat, o.nextBeat)
END_CUSTOM_PROPSYNC

bool PropSyncArray(CharClip::NodeVector&, DataNode&, DataArray*, int, PropOp);
bool PropSync(CharClip::NodeVector&, DataNode&, DataArray*, int, PropOp);

bool PropSyncArray(CharClip::NodeVector& o, DataNode& val, DataArray* prop, int i, PropOp op){
    if(i == prop->Size()){
        MILO_ASSERT(op == kPropSize, 0x6FE);
        val = DataNode(o.size);
        return true;
    }
    else {
        int idx = prop->Int(i++);
        if(i < prop->Size() || op & kPropGet){
            return PropSync(o.nodes[idx], val, prop, i, op);
        }
        else return false;
    }
}

BEGIN_CUSTOM_PROPSYNC(CharClip::NodeVector)
    SYNC_PROP_SET(clip, o.clip, )
    {
        static Symbol _s("nodes");
        // if(sym == symbol) return PropSync(member, _val, _prop, _i + 1, _op);
        if(sym == _s){
            PropSyncArray(o, _val, _prop, _i + 1, _op);
            return true;
        }
    }
END_CUSTOM_PROPSYNC

bool PropSync(CharClip::Transitions& o, DataNode& val, DataArray* prop, int i, PropOp op){
    if(i == prop->Size()){
        MILO_ASSERT(op == kPropSize, 0x719);
        val = DataNode(o.Size());
        return true;
    }
    else {
        int idx = prop->Int(i++);
        if(i < prop->Size() || op & kPropSize|kPropGet){
            
        }
        else return false;
    }
}

BEGIN_CUSTOM_PROPSYNC(CharClip::BeatEvent)
    SYNC_PROP_SET(beat, o.beat, o.beat = _val.Float(0))
    SYNC_PROP_SET(event, o.event, o.event = _val.Sym(0))
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(CharClip)
    SYNC_PROP_SET(start_beat, StartBeat(), )
    SYNC_PROP_SET(end_beat, EndBeat(), )
    SYNC_PROP_SET(length_beats, LengthBeats(), )
    SYNC_PROP_SET(frames_per_sec, mFramesPerSec, )
    SYNC_PROP_SET(length_seconds, LengthSeconds(), )
    SYNC_PROP_SET(average_beats_per_sec, AverageBeatsPerSecond(), )
    SYNC_PROP_SET(flags, mFlags, SetFlags(_val.Int(0)))
    SYNC_PROP_SET(default_blend, mPlayFlags & 0xF, SetDefaultBlend(_val.Int(0)))
    SYNC_PROP_SET(default_loop, mPlayFlags & 0xF0, SetDefaultLoop(_val.Int(0)))
    SYNC_PROP_SET(beat_align, mPlayFlags & 0xF600, SetBeatAlignMode(_val.Int(0)))
    SYNC_PROP(range, mRange)
    SYNC_PROP_SET(relative, mRelative, SetRelative(_val.Obj<CharClip>(0)))
    SYNC_PROP(events, mBeatEvents)
    SYNC_PROP_SET(dirty, mDirty, )
    SYNC_PROP_SET(size, AllocSize(), )
    SYNC_PROP(do_not_compress, mDoNotCompress)
    SYNC_PROP(transitions, mTransitions)
    {
        static Symbol _s("full");
        if(sym == _s) return mFull.SyncProperty(_val, _prop, _i + 1, _op);
    }
    {
        static Symbol _s("one");
        if(sym == _s) return mOne.SyncProperty(_val, _prop, _i + 1, _op);
    }
    SYNC_PROP_SET(compression, mFull.mCompression, )
    SYNC_PROP_SET(num_frames, NumFrames(), )
    SYNC_PROP(sync_anim, mSyncAnim)
END_PROPSYNCS