#include "char/CharClip.h"
#include "char/CharBoneDir.h"
#include "char/CharBonesMeshes.h"
#include "char/CharClipGroup.h"
#include "obj/Data.h"
#include "obj/DataUtl.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "utl/MemMgr.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/TextStream.h"
#include <vector>

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
    return *this;
}

void CharClip::BeatEvent::Load(BinStream& bs){
    bs >> event;
    bs >> beat;
}

CharClip::Transitions::Transitions(Hmx::Object* o) : mNodeStart(0), mNodeEnd(0), mOwner(o) {

}

CharClip::Transitions::~Transitions(){ Clear(); }

void CharClip::Transitions::Clear(){
    for(NodeVector* it = mNodeStart; it < mNodeEnd; it = it->Next()){
        it->clip->Release(mOwner);
    }
    Resize(0, 0);
}

int CharClip::Transitions::Size() const {
    int size = 0;
    for(NodeVector* it = mNodeStart; it < mNodeEnd; it = it->Next()){
        size++;
    }
    return size;
}

CharClip::NodeVector* CharClip::Transitions::GetNodes(int idx) const {
    NodeVector* ret = mNodeStart;
    for(; idx > 0; idx--) ret = ret->Next();
    return ret;
}

CharClip::NodeVector* CharClip::Transitions::Resize(int i, const CharClip::NodeVector* vec){
    static int _x = MemFindHeap("char");
    MemTempHeap temp(_x);
    NodeVector* old = mNodeStart;
    if(i != BytesInMemory()){
        if(i == 0){
            _MemFree(mNodeStart);
            mNodeStart = 0;
        }
        else {
            if(i < BytesInMemory()){
                mNodeStart = (NodeVector*)MemTruncate(mNodeStart, i);
            }
            else {
                mNodeStart = (NodeVector*)_MemRealloc(mNodeStart, i, 0);
            }
        }
    }
    NodeVector* v = mNodeStart;
    mNodeEnd = v + i;
    return v + (vec - old);
}

void CharClip::Transitions::RemoveNodes(CharClip* clip){
    NodeVector* found = FindNodes(clip);
    if(found){
        clip->Release(mOwner);
        NodeVector* next = found->Next();
        memmove(found, next, mNodeEnd - next);
        Resize(BytesInMemory() - (next - found), nullptr);
    }
}

void CharClip::Transitions::Replace(Hmx::Object* from, Hmx::Object* to){
    for(NodeVector* it = mNodeStart; it < mNodeEnd; it = it->Next()){
        if(it->clip == from){
            CharClip* toClip = dynamic_cast<CharClip*>(to);
            if(!toClip) RemoveNodes(it->clip);
            else {
                it->clip->Release(mOwner);
                it->clip = toClip;
                it->clip->AddRef(mOwner);
            }
            return;
        }
    }
}

CharClip::NodeVector* CharClip::Transitions::FindNodes(CharClip* clip) const {
    for(NodeVector* it = mNodeStart; it < mNodeEnd; it = it->Next()){
        if(it->clip == clip) return it;
    }
    return nullptr;
}

void CharClip::Init(){
    FacingSet::Init();
    CharClip::Register();
}

CharClip::CharClip() : mTransitions(this), mFramesPerSec(30.0f), mBeatTrack(), mFlags(0), mPlayFlags(0), mRange(0.0f),
    mDirty(1), mDoNotCompress(0), unk42(-1), mRelative(this, 0), mBeatEvents(), mSyncAnim(this, 0), mFull(), mOne(), mFacing() {
    mBeatTrack.resize(1);
    mBeatTrack[0].frame = 0.0f;
    mBeatTrack[0].value = 0.0f;
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
    for(; it != itEnd; ++it){
        CharClipGroup* grp = dynamic_cast<CharClipGroup*>((*it)->RefOwner());
        if(grp && grp->HasClip(clip)) return true;
    }
    return false;
}

void CharClip::ListBones(std::list<CharBones::Bone>& bones){
    mFull.ListBones(bones);
    mOne.ListBones(bones);
    mFacing.ListBones(bones);
    for(int i = 0; i < mZeros.size(); i++){
        bones.push_back(mZeros[i]);
    }
}

int CharClip::AllocSize(){
    int size = mTransitions.BytesInMemory();
    size += mFull.AllocateSize() + mOne.AllocateSize();
    size += 0x138;
    return size;
}

CharClip::FacingSet::FacingBones::FacingBones(){}

void CharClip::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    mTransitions.Replace(from, to);
}

struct SortByFrame {
    bool operator()(const CharClip::BeatEvent& e1, const CharClip::BeatEvent& e2) const {
        return e1.beat < e2.beat ? true : false;
    }
};

void CharClip::SortEvents(){
    std::sort(mBeatEvents.begin(), mBeatEvents.end(), SortByFrame());
}

int CharClip::TransitionVersion(){
    int version = -1;
    if(!Type().Null()){
        DataNode* prop = Property("transition_version", false);
        if(prop) version = prop->Int();
    }
    return version;
}

void CharClip::SetDefaultBlend(int blend){
    int flags = mPlayFlags;
    SetDefaultBlendFlag(flags, blend);
    SetPlayFlags(flags);

}

void CharClip::SetDefaultLoop(int loop){
    int flags = mPlayFlags;
    SetDefaultLoopFlag(flags, loop);
    SetPlayFlags(flags);
}

void CharClip::SetBeatAlignMode(int align){
    int flags = mPlayFlags;
    SetDefaultBeatAlignModeFlag(flags, align);
    SetPlayFlags(flags);
}

int CharClip::InGroups(){
    int num = 0;
    std::vector<ObjRef*>::const_reverse_iterator it = Refs().rbegin();
    std::vector<ObjRef*>::const_reverse_iterator itEnd = Refs().rend();
    for(; it != itEnd; ++it){
        if(dynamic_cast<CharClipGroup*>((*it)->RefOwner())) num++;
    }
    return num;
}

SAVE_OBJ(CharClip, 0x4F6)

void CharClip::SetTypeDef(DataArray* arr){
    if(TypeDef() != arr){
        Hmx::Object::SetTypeDef(arr);
        mDirty = true;
    }
}

BEGIN_COPYS(CharClip)
    static int _x = MemFindHeap("char");
    MemTempHeap temp(_x);
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharClip)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mFramesPerSec)
        COPY_MEMBER(mBeatTrack)
        if(ty != kCopyFromMax){
            COPY_MEMBER(mFlags)
            COPY_MEMBER(mPlayFlags)
            COPY_MEMBER(mRange)
            COPY_MEMBER(mRelative)
            mBeatEvents.resize(c->mBeatEvents.size());
            for(int i = 0; i < mBeatEvents.size(); i++){
                mBeatEvents[i] = c->mBeatEvents[i];
            }
            COPY_MEMBER(mDoNotCompress)
            COPY_MEMBER(mSyncAnim)
        }
        mFull.Clone(c->mFull);
        mOne.Clone(c->mOne);
        COPY_MEMBER(mZeros)
        mFacing.Set(mFull);
        mDirty = true;
    END_COPYING_MEMBERS
END_COPYS

void CharClip::Print(){
    TextStream& ts = TheDebug;
    ts << "CharClip: " << Name() << "\n";
    ts << MakeString("total allocation size %d\n", AllocSize());
    ts << "Full:\n";
    mFull.Print();
    ts << "One:\n";
    mOne.Print();
}

BEGIN_HANDLERS(CharClip)
    HANDLE_EXPR(in_groups, InGroups())
    HANDLE(groups, OnGroups)
    HANDLE_EXPR(shares_groups, SharesGroups(_msg->Obj<CharClip>(2)))
    HANDLE(has_group, OnHasGroup)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x651)
END_HANDLERS

DataNode CharClip::OnGroups(DataArray* arr){

}

DataNode CharClip::OnHasGroup(DataArray* arr){

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
    SYNC_PROP_SET(beat, o.beat, o.beat = _val.Float())
    SYNC_PROP_SET(event, o.event, o.event = _val.Sym())
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(CharClip)
    SYNC_PROP_SET(start_beat, StartBeat(), )
    SYNC_PROP_SET(end_beat, EndBeat(), )
    SYNC_PROP_SET(length_beats, LengthBeats(), )
    SYNC_PROP_SET(frames_per_sec, mFramesPerSec, )
    SYNC_PROP_SET(length_seconds, LengthSeconds(), )
    SYNC_PROP_SET(average_beats_per_sec, AverageBeatsPerSecond(), )
    SYNC_PROP_SET(flags, mFlags, SetFlags(_val.Int()))
    SYNC_PROP_SET(default_blend, mPlayFlags & 0xF, SetDefaultBlend(_val.Int()))
    SYNC_PROP_SET(default_loop, mPlayFlags & 0xF0, SetDefaultLoop(_val.Int()))
    SYNC_PROP_SET(beat_align, mPlayFlags & 0xF600, SetBeatAlignMode(_val.Int()))
    SYNC_PROP(range, mRange)
    SYNC_PROP_SET(relative, mRelative, SetRelative(_val.Obj<CharClip>()))
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
