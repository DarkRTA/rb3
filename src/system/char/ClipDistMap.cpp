#include "char/ClipDistMap.h"
#include "char/CharBoneDir.h"
#include "char/CharBonesMeshes.h"
#include "char/CharUtl.h"
#include "decomp.h"
#include "math/Utl.h"
#include "math/Vec.h"
#include "obj/Data.h"
#include "rndobj/Trans.h"

void FindWeights(std::vector<RndTransformable*>& transes, std::vector<float>& floats, const DataArray* arr){
    floats.resize(transes.size());
    float f1 = 0;
    for(int i = 0; i < transes.size(); i++){
        float len = Length(transes[i]->mLocalXfm.v);
        if(arr){
            float f84 = 1;
            arr->FindData(transes[i]->Name(), f84, false);
            len *= f84;
        }
        floats[i] = len;
        f1 += floats[i];
    }
    for(int i = 0; i < floats.size(); i++){
        floats[i] *= floats.size() / f1;
    }
}

ClipDistMap::ClipDistMap(CharClip* clip1, CharClip* clip2, float f1, float f2, int i, const DataArray* a) : mClipA(clip1), mClipB(clip2), mWeightData(a),
    mSamplesPerBeat(0), mLastMinErr(kHugeFloat), mBeatAlign(f1), mBeatAlignOffset(0), mBlendWidth(f2), mNumSamples(i) {

}

DECOMP_FORCEACTIVE(ClipDistMap, "bone_facing.rotz")

#pragma push
#pragma dont_inline on
void ClipDistMap::FindDists(float f1, DataArray* arr){
    CharBoneDir* rsrcA = mClipA->GetResource();
    CharUtlBoneSaver saver(rsrcA);
    CharBonesMeshes meshes;
    meshes.SetName("tmp_bones", rsrcA);
    rsrcA->StuffBones(meshes, mClipA->GetContext());
    std::vector<RndTransformable*> transes;
    for(ObjDirItr<RndTransformable> it(rsrcA, true); it != nullptr; ++it){
        if(strnicmp(it->Name(), "bone_", 4) == 0){
            transes.push_back(&*it);
        }
    }
    mClipA->GetChannel("bone_facing.rotz");

    DataNode& dataVarABeat = DataVariable("a_beat");
    float varABeat = dataVarABeat.Float();
    DataNode& dataVarBBeat = DataVariable("b_beat");
    float varBBeat = dataVarBBeat.Float();
    DataNode& dataVarAStart = DataVariable("a_start");
    float varAStart = dataVarAStart.Float();
    DataNode& dataVarAEnd = DataVariable("a_end");
    float varAEnd = dataVarAEnd.Float();
    DataNode& dataVarBStart = DataVariable("b_start");
    float varBStart = dataVarBStart.Float();
    DataNode& dataVarBEnd = DataVariable("b_end");
    float varBEnd = dataVarBEnd.Float();
    DataNode& dataVarAMiddle = DataVariable("a_middle");
    float varAMiddle = dataVarAMiddle.Float();
    DataNode& dataVarBMiddle = DataVariable("b_middle");
    float varBMiddle = dataVarBMiddle.Float();
    DataNode& dataVarDelta = DataVariable("delta");
    float varDelta = dataVarDelta.Float();

    std::vector<DistEntry> distEntries;
    distEntries.resize(mDists.Height());
    std::vector<float> floatVec;
    float interpA = Interp(mClipA->StartBeat(), mClipA->EndBeat(), 0.5f);
    float interpB = Interp(mClipB->StartBeat(), mClipB->EndBeat(), 0.5f);
    mWorstErr = 0;

    for(int i = 0; i < mDists.Width(); i++){
        float beatA = BeatA(i);
        DistEntry newDistEntry;
        for(int j = 0; j < mDists.Height(); j++){
            mDists(i, j) = kHugeFloat;
            float beatB = BeatB(j);
            if(mBeatAlign == 0 || BeatAligned(i, j)){
                if(arr){
                    dataVarABeat = beatA;
                    dataVarBBeat = beatB;
                    dataVarAStart = beatA - mClipA->StartBeat();
                    dataVarAEnd = mClipA->EndBeat() - beatA;
                    dataVarBStart = beatB - mClipB->StartBeat();
                    dataVarBEnd = mClipB->EndBeat() - beatB;
                    dataVarAMiddle = beatA - interpA;
                    dataVarBMiddle = beatB - interpB;
                    dataVarDelta = beatA - beatB;
                    if(arr->Evaluate(1).Int() == 0) continue;
                }
                
//     DistEntry::DistEntry(aDStack_240);
//         pDVar11 = stlpmtx_std::vector<><>::operator_[](distEntries,uVar9);
//         if (param_1 > 0.0) {
//           pvVar17 = avStack_23c; the vector in the distentry
//           fVar1 = 0.3333333;
//           iVar15 = 1;
//           fVar2 = local_234[0]; start of facing in distentry
//           pDVar3 = pDVar11;
//           do {
//             dVar28 = fVar1;
//             dVar26 = LimitAng(*(pvVar17 + 0xc) - *(pvVar17 + 8));
//             dVar27 = LimitAng(*(pDVar3 + 0x10) - *(pDVar3 + 0xc));
//             iVar15 = iVar15 + 1;
//             fVar1 = dVar28 + 0.3333333432674408;
//             pvVar17 = pvVar17 + 4;
//             fVar2 = fVar2 + (1.0 - dVar28) * dVar26 + dVar28 * dVar27;
//             pDVar3 = pDVar3 + 4;
//           } while (iVar15 < 4);
//           this_11 = LimitAng(fVar2 - *(pDVar11 + 0x18));
//           dVar26 = std::fabs(this_11);
//           if (param_1 < dVar26) {
//             pfVar10 = Array2d::operator_()(this + 0x38,iVar4,uVar9);
//             *pfVar10 = 1e+30;
//             goto LAB_8072e548;
//           }
//         }
                DistEntry& curDistEntry = distEntries[j];
                GenerateDistEntry(meshes, curDistEntry, BeatB(j), mClipB, transes);
                GenerateDistEntry(meshes, newDistEntry, BeatA(i), mClipA, transes);
                if(f1 > 0){
                    float fvar1 = 0.33333334f;
                    float fvar2 = newDistEntry.facing[0];
                    // some more stuff happens here
                }
                if(floatVec.empty()){
                    FindWeights(transes, floatVec, mWeightData);
                }
                float f314 = 0;
                for(int k = 0; k < newDistEntry.bones.size(); k++){
                    float curFloat = floatVec[k % floatVec.size()];
                    f314 += DistanceSquared(newDistEntry.bones[k], curDistEntry.bones[k]) * curFloat;
                }
                f314 = std::sqrt(f314 / (float)newDistEntry.bones.size());
                MaxEq(mWorstErr, f314);
                mDists(i, j) = f314;
            }
        }
    }
    dataVarABeat = varABeat;
    dataVarBBeat = varBBeat;
    dataVarAStart = varAStart;
    dataVarAEnd = varAEnd;
    dataVarBStart = varBStart;
    dataVarBEnd = varBEnd;
    dataVarAMiddle = varAMiddle;
    dataVarBMiddle = varBMiddle;
    dataVarDelta = varDelta;
}
#pragma pop

void ClipDistMap::FindNodes(float, float, float){
    std::sort(mNodes.begin(), mNodes.end(), DistMapNodeSort());
}

float ClipDistMap::BeatA(int i){
    return (float)(mAStart + i) / (float)mSamplesPerBeat;
}