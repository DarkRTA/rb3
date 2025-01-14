#include "char/CharClip.h"
#include "char/CharBoneDir.h"
#include "char/CharBones.h"
#include "char/CharBonesMeshes.h"
#include "char/CharClipGroup.h"
#include "decomp.h"
#include "math/Rot.h"
#include "obj/Data.h"
#include "obj/DataUtl.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "utl/MemMgr.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/TextStream.h"
#include <vector>

int gOldRev;
CharClip::FacingSet::FacingBones CharClip::FacingSet::sFacingPos;
CharClip::FacingSet::FacingBones CharClip::FacingSet::sFacingRotAndPos;

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

DECOMP_FORCEACTIVE(CharClip, __FILE__, "0")

CharClip::NodeVector* CharClip::Transitions::Resize(int i, const CharClip::NodeVector* old){
    static int _x = MemFindHeap("char");
    MemTempHeap temp(_x);
    int n = (int)old - (int)mNodeStart;
    MILO_ASSERT((old == NULL) || (n >= 0), 0x91);
    if(i != BytesInMemory()){
        if(i == 0){
            _MemFree(mNodeStart);
            mNodeStart = 0;
            MILO_ASSERT(old == NULL, 0x9E);
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
    return v + n;
}

void CharClip::Transitions::AddNode(CharClip* clip, const CharGraphNode& node){
    NodeVector* nodes = FindNodes(clip);
    NodeVector* resized;
    if(nodes){
        int bytes = BytesInMemory();
        NodeVector* next = nodes->Next();
        NodeVector* end = mNodeEnd;
        resized = Resize(bytes + 8, nodes);
        
        memmove(resized->Next() + 8, resized->Next(), (int)end - (int)next);
    }
    else {
        clip->AddRef(mOwner);
        resized = Resize(BytesInMemory() + 0x10, mNodeEnd);
        resized->clip = clip;
        resized->size = 0;
    }
    int size = resized->size;
    int i = 0;
    if(size > 0){
        for(; i < size; i++){
            if(node.curBeat < resized->nodes[i].curBeat) break;
        }
    }
    for(; i < size; i++){
        resized->nodes[i] = resized->nodes[i - 1];
    }
    resized->nodes[i] = node;
    resized->size++;
}

DECOMP_FORCEACTIVE(CharClip, "%s nodes start %x\n", "\n", "   %s: ", "(%g,%g) ")

void CharClip::Transitions::RemoveNodes(CharClip* clip){
    NodeVector* found = FindNodes(clip);
    if(found){
        clip->Release(mOwner);
        NodeVector* next = found->Next();
        memmove(found, next, (int)mNodeEnd - (int)next);
        Resize(BytesInMemory() - ((int)next - (int)found), nullptr);
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

DECOMP_FORCEACTIVE(CharClip, "beatTrack.size() >= 2")

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

CharGraphNode* CharClip::FindFirstNode(CharClip* clip, float beat) const {
    NodeVector* nodes = mTransitions.FindNodes(clip);
    if(nodes){
        for(int i = 0; i < nodes->size; i++){
            if(nodes->nodes[i].curBeat >= beat) return &nodes->nodes[i];
        }
    }
    return nullptr;
}

CharGraphNode* CharClip::FindLastNode(CharClip* clip, float beat) const {
    NodeVector* nodes = mTransitions.FindNodes(clip);
    if(nodes){
        for(int i = nodes->size - 1; i >= 0; i--){
            if(nodes->nodes[i].curBeat >= beat) return &nodes->nodes[i];
        }
    }
    return nullptr;
}

CharGraphNode* CharClip::FindNode(CharClip* clip, float f1, int iii, float f2) const {
    CharGraphNode* n = nullptr;
    int blendMode = iii & 0xF;
    switch(blendMode){
        case kPlayNoDefault: break;
        case kPlayNow: break;
        case kPlayDirty: break;
        case kPlayNoBlend:
            n = nullptr;
            break;
        case kPlayFirst:
            n = FindFirstNode(clip, f1);
            break;
        case kPlayLast:
            n = FindLastNode(clip, f1);
            break;
        default:
            MILO_WARN("Unknown mode flags %x, default to kPlayNow", iii);
            break;
    }
    if(!n){
        static CharGraphNode node;
        node.curBeat = f1;
        if(blendMode == 4){
            MaxEq(node.curBeat, EndBeat() - f2 * 0.5f);
        }
        n = &node;
        node.nextBeat = StartBeat();
    }
    return n;
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

void CharClip::FacingSet::FacingBones::Set(bool b){
    ClearBones();
    std::list<CharBones::Bone> bones;
    bones.push_back(CharBones::Bone(Symbol("bone_facing_delta.pos"), 1));
    if(b){
        bones.push_back(CharBones::Bone(Symbol("bone_facing_delta.rotz"), 1));
    }
    AddBones(bones);
}

void CharClip::FacingSet::FacingBones::ReallocateInternal(){
    mStart = (char*)&mDeltaPos;
}

void CharClip::FacingSet::Init(){
    sFacingPos.Set(false);
    sFacingRotAndPos.Set(true);
}

CharClip::FacingSet::FacingSet() : mFullRot(-1), mFullPos(-1), mFacingBones(0), mWeight(1) {
    
}

#define MAX_SHORT 0x7FFF

void CharClip::FacingSet::Set(CharBonesSamples& samples){
    mFacingBones = nullptr;
    mFullRot = -1;
    int off = samples.FindOffset("bone_facing.pos");
    MILO_ASSERT(off < MAX_SHORT, 0x280);
    mFullPos = off;
    if(mFullPos != -1){
        int offset = samples.FindOffset("bone_facing.rotz");
        MILO_ASSERT(offset < MAX_SHORT, 0x287);
        mFullRot = offset;
        mFacingBones = mFullRot == -1 ? &sFacingPos : &sFacingRotAndPos;
    }
}

void CharClip::FacingSet::ListBones(std::list<CharBones::Bone>& bones){
    if(mFacingBones){
        mFacingBones->SetWeights(mWeight);
        mFacingBones->ListBones(bones);
    }
}

void CharClip::FacingSet::ScaleDown(CharBones& bones, float f){
    if(mFacingBones) mFacingBones->ScaleDown(bones, f);
}

void CharClip::FacingSet::ScaleAddSample(CharBonesSamples& samples, CharBones& bones, float f1, int i1, float f2, int i2, float f3){
    if(mFacingBones){
        Vector3 v;
        samples.EvaluateChannel(&v, mFullPos, i1, f2);
        samples.EvaluateChannel(&mFacingBones->mDeltaPos, mFullPos, i2, f3);
        Subtract(v, mFacingBones->mDeltaPos, mFacingBones->mDeltaPos);
        if(mFullRot != -1){
            float f64, f68;
            samples.EvaluateChannel(&f64, mFullRot, i1, f2);
            samples.EvaluateChannel(&f68, mFullRot, i2, f3);
            mFacingBones->mDeltaAng = LimitAng(f64 - f68);
            RotateAboutZ(mFacingBones->mDeltaPos, -f68, mFacingBones->mDeltaPos);
        }
        mFacingBones->SetWeights(f1);
        mFacingBones->ScaleAdd(bones, f1);
    }
}

float CharClip::LengthSeconds() const {
    if(NumFrames() < 2) return 0;
    else return (NumFrames() - 1) / mFramesPerSec;
}

float CharClip::FrameToBeat(float frame) const {
    float ret = 0;
    mBeatTrack.Linear(frame, ret);
    return ret;
}

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

bool CharClip::InGroup(Hmx::Object* o){
    std::vector<ObjRef*>::const_reverse_iterator it = Refs().rbegin();
    std::vector<ObjRef*>::const_reverse_iterator itEnd = Refs().rend();
    for(; it != itEnd; ++it){
        if(o == (*it)->RefOwner()) return true;
    }
    return false;
}

void CharClip::MakeMRU(){
    CharClipGroup* groups[128];
    static int sMaxGroups = 0;
    static Symbol s("CharClipGroup");
    std::vector<ObjRef*>::const_reverse_iterator it = Refs().rbegin();
    std::vector<ObjRef*>::const_reverse_iterator itEnd = Refs().rend();
    int groupIdx = 0;
    for(; it != itEnd; ++it){
        ObjRef* cur = *it;
        Hmx::Object* owner = cur->RefOwner();
        if(owner && owner->ClassName() == s){
            CharClipGroup* g = dynamic_cast<CharClipGroup*>(owner);
            MILO_ASSERT(g, 0x424);
            MILO_ASSERT_FMT(groupIdx < 128, "%s has more than 127 groups reffing it", Name());
            groups[groupIdx++] = g;
            if(groupIdx == 128) break;
        }
    }
    if(MaxEq(sMaxGroups, groupIdx)){
        MILO_WARN("%s refs %d groups", PathName(this), sMaxGroups);
    }
    while(groupIdx > 0){
        groups[groupIdx--]->MakeMRU(this);
    }
}

void CharClip::LockAndDelete(CharClip**, int remaining, int){
    MILO_ASSERT(remaining >= 0, 0x43A);
}

void CharClip::PreSave(BinStream&){
    MILO_WARN("You can only save a CharClip from PC");
}

void CharClip::PostSave(BinStream&){}

void CharClip::Transitions::Load(BinStream& bs){
    Clear();
    static ObjectDir* sdir;
    if(gOldRev < 8){
        int num; bs >> num;
        if(num > 0){
            ObjectDir* myDir = mOwner->Dir();
            if(myDir != sdir){
                MILO_LOG("NOTIFY: %s has old clip format, should resave\n", PathName(myDir));
                sdir = mOwner->Dir();
            }
        }
        for(int i = 0; i < num; i++){
            char buf[0x100];
            bs.ReadString(buf, 0x100);
            CharClip* clip = mOwner->Dir()->Find<CharClip>(buf, false);
            int numNodes; bs >> numNodes;
            for(int j = 0; j < numNodes; j++){
                CharGraphNode gNode;
                bs >> gNode.curBeat;
                bs >> gNode.nextBeat;
                if(clip) AddNode(clip, gNode);
            }
        }
    }
    else {
        int temp, numNodes;
        bs >> temp;
        bs >> numNodes;
        NodeVector* start = (NodeVector*)_MemAllocTemp(temp, 0);
        NodeVector* it = start;
        for(int i = 0; i < numNodes; i++){
            char buf[0x100];
            bs.ReadString(buf, 0x100);
            CharClip* clip = mOwner->Dir()->Find<CharClip>(buf, false);
            if(clip){
                clip->AddRef(mOwner);
                it->clip = clip;
                bs >> it->size;
                for(int j = 0; j < it->size; j++){
                    bs >> it->nodes[j].curBeat;
                    bs >> it->nodes[j].nextBeat;
                }
                it = it->Next();
            }
            else {
                int count; bs >> count;
                for(int j = 0; j < count; j++){
                    int x, y;
                    bs >> x; bs >> y;
                }
            }
        }
        Resize((int)it - (int)start, nullptr);
        memcpy(mNodeStart, start, BytesInMemory());
        _MemFree(start);
    }
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
