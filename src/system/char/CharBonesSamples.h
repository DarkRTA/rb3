#pragma once
#include "char/CharBones.h"

class CharBonesSamples : public CharBones {
public:
    CharBonesSamples();
    virtual ~CharBonesSamples();
    virtual void Print();
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);

    void Set(const std::vector<CharBones::Bone> &, int, CharBones::CompressionType);
    void Clone(const CharBonesSamples &);
    int AllocateSize();
    void RotateBy(CharBones &, int);
    void RotateTo(CharBones &, float, int, float);
    void ScaleAddSample(CharBones &, float, int, float);
    void Load(BinStream &);
    void LoadHeader(BinStream &);
    void LoadData(BinStream &);
    void SetPreview(int);
    void ReadCounts(BinStream &, int);
    void Relativize(CharClip *);
    void EvaluateChannel(void *, int, int, float);
    int FracToSample(float *) const;

    static void SetVer(int);
    int NumSamples() const { return mNumSamples; }

    void SetStartFromRawData(int idx){
        SetStart(&mRawData[mTotalSize * idx]);
    }
    // set mStart to mRawData[mTotalSize * 2];

//     void fn_804B1CE8(int param_1,int param_2)

// {
//   fn_8034D25C(param_1,*(param_1 + 0x54) + *(param_1 + 0x4c) * param_2);
//   return;
// }

    short mNumSamples; // 0x50
    short mPreviewSample; // 0x52
    char *mRawData; // 0x54
    std::vector<float> mFrames; // 0x58
};
