#include "ui/UIListState.h"
#include "ui/UIListProvider.h"
#include "math/MathFuncs.h"

UIListState::UIListState(UIListProvider* provider, UIListStateCallback* callback) : mCircular(0), mNumDisplay(5), mGridSpan(1), mSpeed(0.25f), 
    mMinDisplay(0), mScrollPastMinDisplay(0), mMaxDisplay(-1), mScrollPastMaxDisplay(1), mProvider(provider), mHiddenData(), 
    mFirstShowing(0), mTargetShowing(0), mSelectedDisplay(0), mStepPercent(0.0f), mStepTime(-1.0f), mCallback(callback) {

}

int UIListState::SelectedDisplay() const {
    if(mCircular) return mMinDisplay;
    else return mSelectedDisplay;
}

bool UIListState::IsScrolling() const {
    return mFirstShowing != mTargetShowing;
}

int UIListState::MinDisplay() const { return mMinDisplay; }
int UIListState::MaxDisplay() const { return mMaxDisplay; }
float UIListState::Speed() const { return mSpeed; }
bool UIListState::ScrollPastMinDisplay() const { return mScrollPastMinDisplay; }
bool UIListState::ScrollPastMaxDisplay() const { return mScrollPastMaxDisplay; }

bool UIListState::CanScrollBack(bool b) const {
    if(mCircular) return true;
    int count = b ? Display2Data(mSelectedDisplay) : Showing2Data(mFirstShowing);
    for(count = count - 1; count >= 0; count--){
        if(mProvider->IsActive(count)) return true;
    }
    return false;
}

float UIListState::StepPercent() const { return mStepPercent; }
UIListProvider* UIListState::Provider(){ return mProvider; }
UIListProvider* UIListState::Provider() const { return mProvider; }

int UIListState::WrapShowing(int i) const {
    if(NumShowing() == 0) return 0;
    else return Mod(i, NumShowing());
}

int UIListState::Display2Data(int i) const {
    int disp = Display2Showing(i);
    if(disp == -1) return -1;
    else return Showing2Data(disp);
}

int UIListState::Display2Showing(int i) const {
    int offset = mFirstShowing + i;
    if(mScrollPastMinDisplay && !mCircular){
        int newoffset = offset - mMinDisplay;
        if(newoffset < 0 || newoffset >= NumShowing())
        return -1;
    }
    return WrapShowing(offset);
}

int UIListState::Showing2Data(int i) const {
    int count = WrapShowing(i);
    for(std::vector<int>::const_iterator it = mHiddenData.begin(); it != mHiddenData.end(); it++){
        if(*it <= count) count++;
    }
    return count;
}

int UIListState::NumDisplayWithData() const {
    int ret = mNumDisplay;
    if(!mCircular){
        int num = mProvider->NumData();
        if(mScrollPastMinDisplay) num += mMinDisplay;
        if(num < ret) ret = num;
    }
    return ret;
}