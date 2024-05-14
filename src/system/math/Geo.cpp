#include "Geo.h"
#include "math/Bsp.h"
#include "obj/DataFunc.h"

float gBSPPosTol = 0.01;
float gBSPDirTol = 0.985;
int gBSPMaxDepth = 20;
int gBSPMaxCandidates = 40;
float gBSPCheckScale = 1.1;

static DataNode SetBSPParams(DataArray* da) {
    SetBSPParams(da->Float(1), da->Float(2), da->Int(3), da->Int(4), da->Float(5));
    return DataNode();
}

void GeoInit() {
    DataRegisterFunc("set_bsp_params", SetBSPParams);
}

BinStream& operator>>(BinStream& bs, BSPNode*& bsp) {

    return bs;
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


void Clip(const Hmx::Polygon&, const Hmx::Ray&, Hmx::Polygon&) {}