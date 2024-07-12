#ifndef RNDOBJ_UTL_H
#define RNDOBJ_UTL_H
#include "rndobj/Anim.h"
#include "rndobj/Group.h"
#include "rndobj/Mesh.h"
#include "rndobj/Poll.h"
#include "utl/Cache.h"

RndGroup* GroupOwner(Hmx::Object*);
bool GroupedUnder(RndGroup*, Hmx::Object*);
RndAnimatable* AnimController(Hmx::Object*);
RndMat* GetMat(RndDrawable*);
float ConvertFov(float a, float b);
void SetLocalScale(RndTransformable*, const Vector3&);
void AttachMesh(RndMesh*, RndMesh*);
void UtilDrawSphere(const Vector3&, float, const Hmx::Color&);
void UtilDrawString(const char*, const Vector3&, const Hmx::Color&);
void UtilDrawAxes(const Transform&, float, const Hmx::Color&);
void TransformKeys(class RndTransAnim*, const Transform&);
MatShaderOptions GetDefaultMatShaderOpts(const Hmx::Object*, RndMat*);
void TestTextureSize(ObjectDir*, int, int, int, int, int);
void TestTexturePaths(ObjectDir*);
void TestMaterialTextures(ObjectDir*);
void RndScaleObject(Hmx::Object*, float, float);
bool AnimContains(const RndAnimatable*, const RndAnimatable*);
void ResetColors(std::vector<Hmx::Color>&, int);
void CalcBox(RndMesh* m, Box& b);
void MoveXfms(RndMultiMesh*, const Vector3&);
void DistributeXfms(RndMultiMesh*, int, float);
void RndScaleObject(Hmx::Object*, float, float);
void SpliceKeys(RndTransAnim*, RndTransAnim*, float, float);
void LinearizeKeys(RndTransAnim*, float, float, float, float, float);
const char* CacheResource(const char*, Hmx::Object*);
const char* CacheResource(const char*, CacheResourceResult&);
bool SortDraws(RndDrawable*, RndDrawable*);
bool SortPolls(const RndPollable*, const RndPollable*);

void RndUtlPreInit();
void RndUtlInit();
void RndUtlTerminate();

DataNode GetNormalMapTextures(ObjectDir*);
DataNode GetRenderTextures(ObjectDir*);
DataNode GetRenderTexturesNoZ(ObjectDir*);

// idk where else to put this
template <class T1, class T2, class T3>
void VectorRemove(std::vector<T1,T2>& vec, const T3& obj){
    for(std::vector<T1,T2>::iterator it = vec.begin(); it != vec.end(); ++it){
        if(*it == obj){
            vec.erase(it);
            return;
        }
    }
}

#endif // RNDOBJ_UTL_H
