#ifndef CHAR_CHARBONESSAMPLES_H
#define CHAR_CHARBONESSAMPLES_H
#include "char/CharBones.h"

class CharBonesSamples : public CharBones {
public:
    CharBonesSamples();
    virtual ~CharBonesSamples();
    virtual void Print();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);

    short mNumSamples;
    short mPreviewSample;
    char* mRawData;
    std::vector<int> mFrames;
};

#endif