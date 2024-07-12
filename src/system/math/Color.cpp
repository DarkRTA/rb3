#include "math/Color.h"
#include "math/MathFuncs.h"
#include "utl/TextStream.h"

Hmx::Color Hmx::Color::kWhite(1.0f, 1.0f, 1.0f, 1.0f);
Hmx::Color Hmx::Color::kTransparent(0.0f, 0.0f, 0.0f, 0.0f);
Hmx::Color Hmx::Color::kBlack(0.0f, 0.0f, 0.0f, 1.0f);

DECOMP_FORCEACTIVE(Color, __FILE__, 
    "( 0.f) <= (hue) && (hue) <= ( 360.f)",
    "( 0.f) <= (sat) && (sat) <= ( 1.f)",
    "( 0.f) <= (val) && (val) <= ( 1.f)");

void MakeHSL(const Hmx::Color& color, float& f1, float& f2, float& f3){
    float b = color.blue;
    float g = color.green;
    float r = color.red;
    float maxCol = Max(r, g, b);
    float minCol = Minimum(r, g, b);
    f3 = (minCol + maxCol) / 2.0f;
    if(minCol == maxCol){
        f1 = 0; f2 = 0;
    }
    else {
        float deltaCol = maxCol - minCol;
        if(f3 < 0.5f) f2 = deltaCol / (minCol + maxCol);
        else f2 = deltaCol / ((2.0f - maxCol) - minCol);
        if(color.red == maxCol){
            f1 = (color.green - color.blue) / deltaCol;
        }
        else if(color.green == maxCol){
            f1 = (color.blue - color.red) / deltaCol + 2.0f;
        }
        else {
            f1 = (color.red - color.green) / deltaCol + 4.0f;
        }
        f1 /= 6.0f;
        if(f1 < 0.0f) f1 += 1.0f;
    }
}

// void MakeHSL(Color *param_1,float *param_2,float *param_3,float *param_4)

// {
//   float fVar1;
//   float fVar2;
//   float fVar3;
//   float fVar4;
  
//   fVar3 = Maximum(param_1->r,param_1->g,param_1->b);
//   fVar4 = Minimum(param_1->r,param_1->g,param_1->b);
//   fVar1 = (fVar3 + fVar4) * 0.5;
//   *param_4 = fVar1;
//   if (fVar3 == fVar4) {
//     *param_2 = 0.0;
//     *param_3 = 0.0;
//   }

//   else {
//     fVar2 = fVar3 - fVar4;
//     if (fVar1 >= 0.5) {
//       *param_3 = fVar2 / ((2.0 - fVar3) - fVar4);
//     }
//     else {
//       *param_3 = fVar2 / (fVar3 + fVar4);
//     }

//     fVar1 = param_1->r;
//     if (fVar1 == fVar3) {
//       *param_2 = (param_1->g - param_1->b) / fVar2;
//     }
//     else if (param_1->g == fVar3) {
//       *param_2 = (param_1->b - fVar1) / fVar2 + 2.0;
//     }
//     else {
//       *param_2 = (fVar1 - param_1->g) / fVar2 + 4.0;
//     }

//     fVar1 = *param_2 / 6.0;
//     *param_2 = fVar1;
//     if (fVar1 < 0.0) {
//       *param_2 = fVar1 + 1.0;
//     }

//   }
//   return;
// }

TextStream& operator<<(TextStream& ts, const Hmx::Color& color){
    ts << "(r:" << color.red << " g:" << color.green << " b:" << color.blue << " a:" << color.alpha << ")";
    return ts;
}
