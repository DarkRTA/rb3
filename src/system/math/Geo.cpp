#include "Geo.h"
#include "math/Bsp.h"
#include "obj/DataFunc.h"


static DataNode SetBSPParams(DataArray* da) {

}

void GeoInit() {
    DataRegisterFunc("set_bsp_params", SetBSPParams);
}

BinStream& operator>>(BinStream&, BSPNode*&) {

}

void SetBSPParams(float f1, float f2, int r3, int r4, float f3) {
    gBSPPosTol = f1;
    gBSPDirTol = f2;
    gBSPMaxDepth = r3;
    gBSPMaxCandidates = r4;
    gBSPCheckScale = f3;
}
