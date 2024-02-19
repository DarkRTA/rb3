#include "math/Color.h"
#include "utl/TextStream.h"

Hmx::Color Hmx::Color::kWhite(1.0f, 1.0f, 1.0f, 1.0f);
Hmx::Color Hmx::Color::kTransparent(0.0f, 0.0f, 0.0f, 0.0f);
Hmx::Color Hmx::Color::kBlack(0.0f, 0.0f, 0.0f, 1.0f);

void MakeHSL(const Hmx::Color& color, float& f1, float& f2, float& f3){
    float theGreen = color.green;
    float theBlue = color.blue;
    float theRed = color.red;
    float tmpidk = theBlue;
    if(theBlue < theGreen){
        tmpidk = theGreen;
    }
    float tmp2idk = theRed;
    if(theRed < tmpidk){
        tmp2idk = tmpidk;
    }
    if(theGreen < theBlue){
        theBlue = theGreen;
    }
    if(theBlue < theRed){
        theRed = theBlue;
    }
    

}

// void MakeHSL(Color *param_1,float *param_2,float *param_3,float *param_4)

// {
//   float fVar1;
//   float fVar2;
//   float fVar3;
//   float fVar4;
//   float fVar5;
  
//   fVar1 = *(float *)(param_1 + 8);
//   fVar2 = *(float *)(param_1 + 4);
//   fVar3 = *(float *)param_1;
//   fVar5 = fVar2;
//   if (fVar2 < fVar1) {
//     fVar5 = fVar1;
//   }
//   fVar4 = fVar3;
//   if (fVar3 < fVar5) {
//     fVar4 = fVar5;
//   }
//   if (fVar1 < fVar2) {
//     fVar2 = fVar1;
//   }
//   if (fVar2 < fVar3) {
//     fVar3 = fVar2;
//   }
//   fVar1 = (fVar4 + fVar3) * 0.5;
//   *param_4 = fVar1;
//   if (fVar4 != fVar3) {
//     fVar2 = fVar4 - fVar3;
//     if (0.5 <= fVar1) {
//       *param_3 = fVar2 / ((2.0 - fVar4) - fVar3);
//     }
//     else {
//       *param_3 = fVar2 / (fVar4 + fVar3);
//     }
//     fVar1 = *(float *)param_1;
//     if (fVar1 == fVar4) {
//       *param_2 = (*(float *)(param_1 + 4) - *(float *)(param_1 + 8)) / fVar2;
//     }
//     else if (*(float *)(param_1 + 4) == fVar4) {
//       *param_2 = (*(float *)(param_1 + 8) - fVar1) / fVar2 + 2.0;
//     }
//     else {
//       *param_2 = (fVar1 - *(float *)(param_1 + 4)) / fVar2 + 4.0;
//     }
//     fVar1 = *param_2 / 6.0;
//     *param_2 = fVar1;
//     if (fVar1 < 0.0) {
//       *param_2 = fVar1 + 1.0;
//       return;
//     }
//     return;
//   }
//   *param_2 = 0.0;
//   *param_3 = 0.0;
//   return;
// }

TextStream& operator<<(TextStream& ts, const Hmx::Color& color){
    ts << "(r:" << color.red << " g:" << color.green << " b:" << color.blue << " a:" << color.alpha << ")";
    return ts;
}
