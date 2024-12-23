#include "beatmatch/RGGemMatcher.h"
#include "beatmatch/RGState.h"
#include "beatmatch/Output.h"

// fn_80475750
RGGemMatcher::RGGemMatcher(){
    Reset();
}

// starts at 0x48, continues until 0x108
// float/int pair, size 0x8
// loop takes up 0xC0
// so array of 24 float/int pairs

void RGGemMatcher::Reset(){
    mState = RGState();
    ClearStringSwings();
    ClearNonStrums();
}

void RGGemMatcher::Swing(int iii, float f){
    for(int i = 0; i < 6; i++){
        if(iii & 1 << i){
            mStringSwings[i] = f;
        }
    }
}

void RGGemMatcher::FretDown(int iii, float f){
    int x, y;
    UnpackRGData(iii, x, y);
    mState.FretDown(x, y);
    mStringNonStrum[x] = f;
    AddFretHistory(x, y, f);
}

void RGGemMatcher::FretUp(int iii, float f){
    int x, y;
    UnpackRGData(iii, x, y);
    mState.FretUp(x, y);
    mStringNonStrum[x] = f;
}

bool RGGemMatcher::FretMatch(const GameGem& gem, float f1, float f2, float f3, float f4, bool b1, bool b2, RGMatchType ty) const {
    bool matchimpl = FretMatchImpl(gem, f1, f2, f3, f4, b1, b2, ty);
    if(TheBeatMatchOutput.IsActive()){
        const char* str;
        if(matchimpl) str = MakeString("(%2d%10.1f MATCH_SUCCESS)\n", 0, f4 + f3);
        else str = MakeString("(%2d%10.1f MATCH_FAIL)\n", 0, f4 + f3);
        TheBeatMatchOutput.Print(str);
    }
    return matchimpl;
}

RGState* RGGemMatcher::GetState(){ return &mState; }
const RGState* RGGemMatcher::GetState() const { return &mState; }

void RGGemMatcher::ClearStringSwings(){
    for(int i = 0; i < 6; i++){
        mStringSwings[i] = 0.0f;
    }
}

void RGGemMatcher::ClearNonStrums(){
    for(int i = 0; i < 6; i++){
        mStringNonStrum[i] = 0.0f;
    }
}

bool RGGemMatcher::FretHistoryMatch(int i1, int i2, float f3, float f4, RGMatchType ty) const {
    
}

void RGGemMatcher::AddFretHistory(int i1, int i2, float f3){
    for(int i = 3; i > 0; i--){

    }
}

// void __thiscall
// RGGemMatcher::AddFretHistory(double param_1,RGGemMatcher *this,int param_3,undefined4 param_4)

// {
//   int iVar1;
//   RGGemMatcher *pRVar2;
//   int iVar3;
  
//   iVar1 = 3;
//   pRVar2 = this + param_3 * 0x20 + 0x48;
//   iVar3 = 0x18;
//   do {
//     fn_8016E284(pRVar2 + iVar3,pRVar2 + (iVar1 + -1) * 8);
//     iVar1 = iVar1 + -1;
//     iVar3 = iVar3 + -8;
//   } while (iVar1 > 0);
//   *(undefined4 *)(this + param_3 * 0x20 + 0x4c) = param_4;
//   *(float *)pRVar2 = (float)param_1;
//   return;
// }