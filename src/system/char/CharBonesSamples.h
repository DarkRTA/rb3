#ifndef CHAR_CHARBONESSAMPLES_H
#define CHAR_CHARBONESSAMPLES_H
#include "char/CharBones.h"

class CharBonesSamples : public CharBones {
public:
    CharBonesSamples();
    virtual ~CharBonesSamples();
    virtual void Print();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);

    void Set(const std::vector<CharBones::Bone>&, int, CharBones::CompressionType);
    void Clone(const CharBonesSamples&);
    int AllocateSize();
    void RotateBy(CharBones&, int);
    void RotateTo(CharBones&, float, int, float);
    void ScaleAddSample(CharBones&, float, int, float);
    void Load(BinStream&);
    void LoadHeader(BinStream&);
    void LoadData(BinStream&);
    void SetPreview(int);
    void ReadCounts(BinStream&, int);
    void Relativize(CharClip*);
    void EvaluateChannel(void*, int, int, float);
    int FracToSample(float*) const;

    static void SetVer(int);

    short mNumSamples; // 0x50
    short mPreviewSample; // 0x52
    char* mRawData; // 0x54
    std::vector<float> mFrames; // 0x58
};

#endif