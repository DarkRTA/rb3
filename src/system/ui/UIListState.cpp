#include "ui/UIListState.h"
#include "ui/UIListProvider.h"
#include "math/Utl.h"

UIListState::UIListState(UIListProvider* provider, UIListStateCallback* callback) : mCircular(0), mNumDisplay(5), mGridSpan(1), mSpeed(0.25f), 
    mMinDisplay(0), mScrollPastMinDisplay(0), mMaxDisplay(-1), mScrollPastMaxDisplay(1), mProvider(provider), mHiddenData(), 
    mFirstShowing(0), mTargetShowing(0), mSelectedDisplay(0), mStepPercent(0.0f), mStepTime(-1.0f), mCallback(callback) {

}

int UIListState::Selected() const {
    return Display2Showing(SelectedDisplay());
}

int UIListState::SelectedNoWrap() const {
    int i1 = mFirstShowing + SelectedDisplay();
    if(mScrollPastMinDisplay && !mCircular){
        i1 -= mMinDisplay;
        if(i1 < 0 || i1 >= NumShowing()) return -1;
    }
    return i1;
}

int UIListState::SelectedData() const {
    return Display2Data(SelectedDisplay());
}

int UIListState::SelectedDisplay() const {
    if(mCircular) return mMinDisplay;
    else return mSelectedDisplay;
}

#pragma push
#pragma force_active on
inline bool UIListState::IsScrolling() const {
    return mFirstShowing != mTargetShowing;
}
inline int UIListState::MinDisplay() const { return mMinDisplay; }
#pragma pop

int UIListState::MaxDisplay() const { return mMaxDisplay; }
float UIListState::Speed() const { return mSpeed; }

#pragma push
#pragma force_active on
inline bool UIListState::ScrollPastMinDisplay() const { return mScrollPastMinDisplay; }
#pragma pop

bool UIListState::ScrollPastMaxDisplay() const { return mScrollPastMaxDisplay; }

bool UIListState::CanScrollBack(bool b) const {
    if(mCircular) return true;
    int count = b ? Display2Data(mSelectedDisplay) : Showing2Data(mFirstShowing);
    for(count = count - 1; count >= 0; count--){
        if(mProvider->IsActive(count)) return true;
    }
    return false;
}

bool UIListState::CanScrollNext(bool b) const {
    if(mCircular) return true;
    else if(b){
        for(int data = Display2Data(mSelectedDisplay) + 1; data < mProvider->NumData(); data++){
            if(mProvider->IsActive(data)) return true;
        }
    }
    else {
        return MaxFirstShowing() > mFirstShowing;
    }
    return false;
}

float UIListState::StepPercent() const { return mStepPercent; }

DECOMP_FORCEFUNC(UIListState, UIListState, Provider())

#pragma push
#pragma force_active on
inline UIListProvider* UIListState::Provider(){ return mProvider; }
inline UIListProvider* UIListState::Provider() const { return mProvider; }
#pragma pop

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
        offset = offset - mMinDisplay;
        if(offset < 0 || offset >= NumShowing()) return -1;
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
    int ret = NumDisplay();
    if(!mCircular){
        int num = Provider()->NumData();
        if(ScrollPastMinDisplay()) num += MinDisplay();
        ret = Min(ret, num);
    }
    return ret;
}

int UIListState::MaxFirstShowing() const {
    MILO_ASSERT(!mCircular, 0xE8);
    int curshowing = NumShowing();
    int maxshowing = Max(0, curshowing - mNumDisplay);
    if(mMaxDisplay != -1 && mScrollPastMaxDisplay){
        maxshowing += (Min(curshowing, mNumDisplay) - Clamp(0, mNumDisplay, mMaxDisplay)) - 1;
    }
    if(mScrollPastMinDisplay){
        maxshowing += mMinDisplay;
    }
    return Max(0, maxshowing);
}

int UIListState::ScrollMaxDisplay() const {
    MILO_ASSERT(!mCircular, 0xF7);
    int max = Max(0, Min(NumShowing() - 1, mNumDisplay - 1));
    if(mMaxDisplay != -1){
        max = Clamp(0, max, mMaxDisplay);
    }
    return max;
}

int UIListState::CurrentScroll() const {
    return ScrollToTarget(mTargetShowing);
}

bool UIListState::ShouldHoldDisplayInPlace(int i2) const {
    bool b2 = true;
    bool b1 = false;
    if(mTargetShowing > mFirstShowing && i2 == 0) b1 = true;
    if(!b1){
        b1 = false;
        if(mTargetShowing < mFirstShowing && i2 == -1) b1 = true;
        if(!b1) b2 = false;
    }
    if(b2){
        bool ret = false;
        if(SnappedDataForDisplay(i2) >= 0){
            int numdisp = NumDisplay();
            if(i2 + 1 != numdisp && Display2Data(numdisp) != -1){
                if(!Provider()->IsSnappableAtData(Display2Data(i2 + 1))){
                    ret = true;
                }
            }
        }
        return ret;
    }
    else return false;
}

int UIListState::SnappedDataForDisplay(int i2) const {
    bool b1 = false;
    if(
        (!IsScrolling() && i2 == 0) || 
        (mTargetShowing > mFirstShowing && i2 == 0) ||
        (mTargetShowing < mFirstShowing && i2 == -1)
    ) b1 = true;
    if(b1){
        return Provider()->SnappableAtOrBeforeData(Display2Data(i2));
    }
    else return -1;
}

void UIListState::SetProvider(UIListProvider* provider, RndDir* rdir){
    MILO_ASSERT(provider, 0x126);
    provider->InitData(rdir);
    mProvider = provider;
    mHiddenData.clear();
    for(int i = 0; i < mProvider->NumData(); i++){
        if(mProvider->IsHidden(i)){
            mHiddenData.push_back(i);
        }
    }
    SetSelected(0, -1, true);
}

void UIListState::SetNumDisplay(int num, bool b){
    MILO_ASSERT(num > 0, 0x139);
    mNumDisplay = num;
    if(b){
        SetSelected(0, -1, true);
    }
}

void UIListState::SetGridSpan(int span, bool b){
    MILO_ASSERT(span > 0, 0x141);
    mGridSpan = span;
    if(b){
        SetSelected(0, -1, true);
    }
}

void UIListState::SetMinDisplay(int min){
    MILO_ASSERT(min >= 0, 0x149);
    mMinDisplay = min;
    mSelectedDisplay = Max(min, mSelectedDisplay);
}

void UIListState::SetMaxDisplay(int max){
    MILO_ASSERT(max >= -1, 0x150);
    if(LOADMGR_EDITMODE){
        if(-1 <= max){
            max = Min(mNumDisplay - 1, max);
        }
    }
    mMaxDisplay = max;
}

void UIListState::SetCircular(bool c, bool b){
    mCircular = c;
    if(b){
        SetSelected(0, -1, true);
    }
}

void UIListState::SetSpeed(float speed){
    MILO_ASSERT(speed >= 0, 0x15F);
    mSpeed = speed;
}

void UIListState::SetScrollPastMinDisplay(bool scroll){
    mScrollPastMinDisplay = scroll;
    if(mScrollPastMinDisplay){
        mSelectedDisplay = Max(mSelectedDisplay, mMinDisplay);
    }
}

void UIListState::SetScrollPastMaxDisplay(bool scroll){
    mScrollPastMaxDisplay = scroll;
}

void UIListState::SetSelected(int, int, bool){
    
}