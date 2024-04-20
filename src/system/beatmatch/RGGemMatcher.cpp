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