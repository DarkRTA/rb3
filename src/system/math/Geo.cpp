#include "Geo.h"
#include "math/Bsp.h"
#include "math/Rot.h"
#include "obj/DataFunc.h"
#include "decomp.h"

float gBSPPosTol = 0.01f;
float gBSPDirTol = 0.985f;
int gBSPMaxDepth = 20;
int gBSPMaxCandidates = 40;
float gBSPCheckScale = 1.1f;

static DataNode SetBSPParams(DataArray* da) {
    SetBSPParams(da->Float(1), da->Float(2), da->Int(3), da->Int(4), da->Float(5));
    return DataNode();
}

void GeoInit() {
    DataArray* cfg = SystemConfig("math");
    float scale = cfg->FindArray("bsp_check_scale", true)->Float(1);
    int candidates = cfg->FindArray("bsp_max_candidates", true)->Int(1);
    int depth = cfg->FindArray("bsp_max_depth", true)->Int(1);
    float dirtol = cfg->FindArray("bsp_dir_tol", true)->Float(1);
    float postol = cfg->FindArray("bsp_pos_tol", true)->Float(1);
    SetBSPParams(postol, dirtol, depth, candidates, scale);
    DataRegisterFunc("set_bsp_params", SetBSPParams);
}

DECOMP_FORCEACTIVE(Geo, "points:");

TextStream& deadstrippedVec2Read(TextStream& ts, const std::vector<Vector2>& vec){
    return ts << vec;
}

BinStream& operator>>(BinStream& bs, BSPNode*& bsp) {
    bool exists;
    bs >> exists;
    if(exists){
        bsp = new BSPNode();
        bs >> bsp->plane >> bsp->left >> bsp->right;
    }
    else bsp = 0;
    return bs;
}

void Box::GrowToContain(const Vector3& vec, bool b){
    if(b){
        mMin = mMax = vec;
    }
    else for(int i = 0; i < 3; i++){
        if(vec[i] < mMin[i]){
            mMin[i] = vec[i];
        }
        else if(vec[i] > mMax[i]){
            mMax[i] = vec[i];
        }
    }
}

void Intersect(const Hmx::Ray& r1, const Hmx::Ray& r2, Vector2& out) {
      float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float a;
  
  fVar1 = (r1.dir).x;
  fVar2 = (r2.dir).y;
  fVar3 = (r2.dir).x;
  fVar4 = (r1.dir).y;
  fVar5 = (r1.base).x;
  a = fVar3 * fVar4 - fVar1 * fVar2;
  fVar6 = (r2.base).x;
  fVar7 = (r1.base).y;
  fVar8 = (r2.base).y;
  if (0.0f != a) {
    a = (fVar4 * (fVar5 - fVar6) + fVar1 * (fVar8 - fVar7)) / a;
    out.x = a * fVar3 + fVar6;
    out.y = a * fVar2 + fVar8;
    return;
  }
  out.x = fVar5;
  out.y = fVar7;
  return;
}

bool Intersect(const Transform&, const Hmx::Polygon&, const BSPNode*) {

}

void SetBSPParams(float f1, float f2, int r3, int r4, float f3) {
    gBSPPosTol = f1;
    gBSPDirTol = f2;
    gBSPMaxDepth = r3;
    gBSPMaxCandidates = r4;
    gBSPCheckScale = f3;
}

#pragma push
#pragma dont_inline on
bool CheckBSPTree(const BSPNode* node, const Box& box){
    if(!gBSPCheckScale) return true;
    Box box68;
    Multiply(box, gBSPCheckScale, box68);
    Hmx::Polygon polygon70;
    polygon70.mPoints.resize(4);
    Transform tf50;
    polygon70.mPoints[0] = Vector2(box68.mMin.x, box68.mMin.y);
    polygon70.mPoints[1] = Vector2(box68.mMax.x, box68.mMin.y);
    polygon70.mPoints[2] = Vector2(box68.mMax.x, box68.mMax.y);
    polygon70.mPoints[3] = Vector2(box68.mMin.x, box68.mMax.y);
    tf50.m.Identity();
    tf50.v.Set(0,0,box68.mMin.z);
    if(Intersect(tf50, polygon70, node)) return false;
    // first intersect check

    polygon70.mPoints.clear();
    polygon70.mPoints.resize(4);
    polygon70.mPoints[0] = Vector2(box68.mMin.x, -box68.mMax.y);
    polygon70.mPoints[1] = Vector2(box68.mMax.x, -box68.mMax.y);
    polygon70.mPoints[2] = Vector2(box68.mMax.x, -box68.mMin.y);
    polygon70.mPoints[3] = Vector2(box68.mMin.x, -box68.mMin.y);
    float negone = -1.0f;
    tf50.m.Set(1.0f,0.0f,0.0f,0.0f,negone,0.0f,0.0f,0.0f,0.0f);
    tf50.v.Set(0, 0, box68.mMax.z);
    if(Intersect(tf50, polygon70, node)) return false;
    // second intersect check

    polygon70.mPoints.clear();
    polygon70.mPoints.resize(4);
    polygon70.mPoints[0] = Vector2(box68.mMin.y, box68.mMin.z);
    polygon70.mPoints[1] = Vector2(box68.mMax.y, box68.mMin.z);
    polygon70.mPoints[2] = Vector2(box68.mMax.y, box68.mMax.z);
    polygon70.mPoints[3] = Vector2(box68.mMin.y, box68.mMax.z);
    tf50.m.Set(1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f);
    tf50.v.Set(box68.mMin.x, 0, 0);
    if(Intersect(tf50, polygon70, node)) return false;
    // third intersect check

    polygon70.mPoints.clear();
    polygon70.mPoints.resize(4);
    polygon70.mPoints[0] = Vector2(-box68.mMax.y, box68.mMin.z);
    polygon70.mPoints[1] = Vector2(-box68.mMin.y, box68.mMin.z);
    polygon70.mPoints[2] = Vector2(-box68.mMin.y, box68.mMax.z);
    polygon70.mPoints[3] = Vector2(-box68.mMax.y, box68.mMax.z);
    tf50.m.Set(1.0f,0.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,0.0f,0.0f);
    tf50.v.Set(box68.mMax.x, 0, 0);
    if(Intersect(tf50, polygon70, node)) return false;
    // fourth intersect check

    polygon70.mPoints.clear();
    polygon70.mPoints.resize(4);
    polygon70.mPoints[0] = Vector2(box68.mMin.x, box68.mMin.z);
    polygon70.mPoints[1] = Vector2(box68.mMax.x, box68.mMin.z);
    polygon70.mPoints[2] = Vector2(box68.mMax.x, box68.mMax.z);
    polygon70.mPoints[3] = Vector2(box68.mMin.x, box68.mMax.z);
    tf50.m.Set(1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f);
    tf50.v.Set(0, box68.mMax.y, 0);
    if(Intersect(tf50, polygon70, node)) return false;
    // fifth intersect check

    polygon70.mPoints.clear();
    polygon70.mPoints.resize(4);
    polygon70.mPoints[0] = Vector2(-box68.mMax.x, box68.mMin.z);
    polygon70.mPoints[1] = Vector2(-box68.mMin.x, box68.mMin.z);
    polygon70.mPoints[2] = Vector2(-box68.mMin.x, box68.mMax.z);
    polygon70.mPoints[3] = Vector2(-box68.mMax.x, box68.mMax.z);
    tf50.m.Set(-1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f);
    tf50.v.Set(0, box68.mMin.y, 0);
    if(Intersect(tf50, polygon70, node)) return false;
    return true;
    // sixth and final intersect check
}
#pragma pop

void NumNodes(const BSPNode* node, int& num, int& maxDepth){
    static int depth = 0;
    if(node){
        depth++;
        if(depth == 1){
            num = 0;
            maxDepth = 1;
        }
        else if(depth > maxDepth){
            maxDepth = depth;
        }
        NumNodes(node->left, num, maxDepth);
        NumNodes(node->right, num, maxDepth);
        num++;
        depth--;
    }
}

void Clip(const Hmx::Polygon&, const Hmx::Ray&, Hmx::Polygon&) {}