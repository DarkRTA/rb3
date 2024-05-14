#include "char/CharBonesSamples.h"

CharBonesSamples::CharBonesSamples() : mNumSamples(0), mPreviewSample(0), mRawData(0) {

}

CharBonesSamples::~CharBonesSamples(){
    _MemFree(mRawData);
}