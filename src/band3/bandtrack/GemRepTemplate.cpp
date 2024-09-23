#include "GemRepTemplate.h"
#include "bandtrack/GraphicsUtl.h"
#include "bandtrack/TrackConfig.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Mat.h"
#include <algorithm>

#define kNumGemSlotMats 1

GemRepTemplate::GemRepTemplate(const TrackConfig& tc) : mConfig(SystemConfig("track_graphics", "gem")), 
    kTailPulseRate(mConfig->FindArray("tail_pulse_rate", true)->Float(1)), 
    kTailPulseSmoothing(mConfig->FindArray("tail_pulse_smoothing", true)->Float(1)),
    kTailOffsetX(mConfig->FindArray("tail_offset_x", true)->Float(1)),
    kTailMinAlpha(mConfig->FindArray("tail_min_alpha", true)->Float(1)),
    kTailMaxAlpha(mConfig->FindArray("tail_max_alpha", true)->Float(1)),
    kTailAlphaSmoothing(mConfig->FindArray("tail_alpha_smoothing", true)->Float(1)),
    kTailFadeDistance(mConfig->FindArray("tail_fade_distance", true)->Float(1)),
    kTailMaxLength(mConfig->FindArray("tail_max_length", true)->Float(1)),
    kTailFrequencyRange(mConfig->FindArray("tail_min_freq", true)->Float(1), mConfig->FindArray("tail_max_freq", true)->Float(1)),
    kTailAmplitudeRange(mConfig->FindArray("tail_min_amp", true)->Float(1), mConfig->FindArray("tail_max_amp", true)->Float(1)),
    mTrackCfg(tc), unk_0x3C(0), unk_0x40(1.0f), objectDir(NULL) {
    mSlots = (RndMat**)new void*[tc.GetMaxSlots()]; // it doesn't call the ctors, so i have to do This to just alloc
}

GemRepTemplate::~GemRepTemplate() {
    RndMesh* end = *mTails.end();
    for (RndMesh* it = *mTails.begin(); it != end; it++) delete it; // i hate how well this matches
    mTails.clear();
    delete[] mSlots;
}

void GemRepTemplate::Init(ObjectDir*) {

}

RndMesh* GemRepTemplate::GetTail() {
    RndMesh* m;
    if (mTails.size() == 0) m = CreateTail();
    else {
        m = mTails.back();
        mTails.pop_back();
    }
    return m;
}

void GemRepTemplate::ReturnTail(RndMesh* m) {
    if (m != NULL) {
        UnhookAllParents(m);
        mTails.push_back(m);
    }
}

RndMesh* GemRepTemplate::CreateTail() {
    RndMesh* m = Hmx::Object::New<RndMesh>();
    m->SetMutable(0x3F);
    m->Verts().reserve(mTailVerts.size() * (1 + mNumTailSections), true);
    m->Faces().reserve((mTailVerts.size() - 1) * mNumTailSections * 2);
    return m;
}

int GemRepTemplate::GetRequiredVertCount(int i) const {
    return mTailVerts.size() * (i + 1);
}

int GemRepTemplate::GetRequiredFaceCount(int i) const {
    return (mTailVerts.size() - 1) * i * 2;
}

RndMat* GemRepTemplate::GetMatByTag(const char* c, int slot) {
    const char* s = mConfig->FindArray("mat_formats", true)->FindArray(c, true)->Str(1);
    return objectDir->Find<RndMat>(MakeString("%s.mat", MakeString(s, slot < mTrackCfg.GetMaxSlots() ? mTrackCfg.GetSlotColor(slot) : "star")), true);
}

bool VertLess(const RndMesh::Vert& v1, const RndMesh::Vert& v2) {
    if ((float)__fabs(v1.pos.y - v2.pos.y) < 0.1f) { // nonsense regswap
        return v1.pos.x < v2.pos.x;
    }
    return v1.pos.y < v2.pos.y;
}

void GemRepTemplate::SetupTailVerts() {
    objectDir->Find<RndMesh>("tail02.mesh", false)->Verts() = mTailVerts; // where assert
    MILO_ASSERT(!(mTailVerts.size()%2), 212);
    std::sort(mTailVerts.begin(), mTailVerts.end(), VertLess);
    unk_0x64 = mTailVerts;
    int i = 420;
    mTailVerts.resize(i, true);
    unk_0x64.resize(i, true);
}

int GemRepTemplate::GetNumTailSections(GemRepTemplate::TailType type) const {
    MILO_ASSERT(type < kNumTailTypes, 232);
    return this[type * 4].mNumTailSections; // ????
}

float GemRepTemplate::GetTailSectionLength(GemRepTemplate::TailType type) const {
    MILO_ASSERT(type < kNumTailTypes, 238);
    return this[type * 4].mTailSectionLen; // ????
}

RndMat* GemRepTemplate::GetSlotMat(int matIndex, int slotIndex) const {
    MILO_ASSERT(( 0) <= (matIndex) && (matIndex) < ( kNumGemSlotMats), 244);
    MILO_ASSERT(( 0) <= (slotIndex) && (slotIndex) < ( mTrackCfg.GetMaxSlots()), 245);
    return mSlots[matIndex + slotIndex];
}

void GemRepTemplate::SetSlotMat(int matIndex, int slotIndex, RndMat* mat) {
    MILO_ASSERT(( 0) <= (matIndex) && (matIndex) < ( kNumGemSlotMats), 251);
    MILO_ASSERT(( 0) <= (slotIndex) && (slotIndex) < ( mTrackCfg.GetMaxSlots()), 252);
    mSlots[matIndex + slotIndex] = mat;
}
