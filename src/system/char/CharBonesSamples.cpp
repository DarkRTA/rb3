#include "char/CharBonesSamples.h"
#include "utl/Symbols.h"

int gVer;

DECOMP_FORCEACTIVE(CharBonesSamples, __FILE__, "set.mNumSamples == mNumSamples",
    "CharBonesSamples are already compressed.", "CharBonesSamples are already compressed, can't remove bones.")

CharBonesSamples::CharBonesSamples() : mNumSamples(0), mPreviewSample(0), mRawData(0) {

}

CharBonesSamples::~CharBonesSamples(){
    _MemFree(mRawData);
}

void CharBonesSamples::Set(const std::vector<CharBones::Bone>& bones, int i, CharBones::CompressionType ty){
    ClearBones();
    SetCompression(ty);
    mNumSamples = i;
    AddBones(bones);
    _MemFree(mRawData);
    mRawData = (char*)_MemAlloc(AllocateSize(), 0);
    mFrames.clear();
}

void CharBonesSamples::Clone(const CharBonesSamples& samp){
    Set(samp.mBones, samp.mNumSamples, samp.mCompression);
    memcpy(mRawData, samp.mRawData, AllocateSize());
    mFrames = samp.mFrames;
}

void CharBonesSamples::RotateBy(CharBones& bones, int i){
    mStart = &mRawData[mTotalSize * i];
    CharBones::RotateBy(bones);
}

void CharBonesSamples::RotateTo(CharBones& bones, float f1, int i, float f2){
    mStart = &mRawData[mTotalSize * i];
    CharBones::RotateTo(bones, (1.0f - f2) * f1);
    if(f2 > 0.0f){
        mStart = &mRawData[mTotalSize * (i + 1)];
        CharBones::RotateTo(bones, f2 * f1);
    }
}

void CharBonesSamples::ScaleAddSample(CharBones& bones, float f1, int i, float f2){
    mStart = &mRawData[mTotalSize * i];
    CharBones::ScaleAdd(bones, (1.0f - f2) * f1);
    if(f2 > 0.0f){
        mStart = &mRawData[mTotalSize * (i + 1)];
        CharBones::ScaleAdd(bones, f2 * f1);
    }
}

void CharBonesSamples::Print(){
    MILO_LOG("samples: %d size: %d address: %x compression %d\n", mNumSamples, AllocateSize(), (int)mRawData, mCompression);
    if(mNumSamples == 0){
        TheDebug << "Bones:\n";
        for(int i = 0; i < mBones.size(); i++){
            TheDebug << "   " << mBones[i].name << "\n";
        }
    }
    for(int i = 0; i < mNumSamples; i++){
        TheDebug << i << ")\n";
        mStart = &mRawData[mTotalSize * i];
        CharBones::Print();
    }
}

DECOMP_FORCEACTIVE(CharBonesSamples, "numSamples > 0", "firstSample >= 0 && firstSample < mNumSamples",
    "(firstSample + numSamples) >= 0 && (firstSample + numSamples) < mNumSamples", "mNumSamples >= 0")

void CharBonesSamples::SetVer(int ver){
    MILO_ASSERT(ver < 13, 0x22B);
    gVer = ver;
}

DECOMP_FORCEACTIVE(CharBonesSamples, "0")

#define VER 16

void CharBonesSamples::Load(BinStream& bs){
    bs >> gVer;
    MILO_ASSERT(gVer > 12 && gVer <= VER, 0x2A0);
    LoadHeader(bs);
    LoadData(bs);
}

void CharBonesSamples::SetPreview(int i){
    int tmp = Clamp(0, mNumSamples - 1, i);
    MILO_ASSERT(mPreviewSample < 32767, 0x38B);
    mPreviewSample = tmp;
    mStart = &mRawData[mTotalSize * tmp];
}

BEGIN_PROPSYNCS(CharBonesSamples)
    SYNC_PROP(num_samples, mNumSamples)
    SYNC_PROP_SET(preview_sample, mPreviewSample, SetPreview(_val.Int()))
    SYNC_PROP(frames, mFrames)
    SYNC_PROP_SET(compression, mCompression, )
    else {
        gPropBones = this;
        if(sym == bones) return PropSync(mBones, _val, _prop, _i + 1, _op);
    }
END_PROPSYNCS
