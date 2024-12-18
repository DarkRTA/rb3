#pragma once
#include "ui/UIListProvider.h"
#include "types.h"
#include <vector>

class UIListStateCallback;

class UIListState { // 0x48
public:
    UIListState(class UIListProvider*, UIListStateCallback*);

    int Display2Showing(int) const;
    int Display2Data(int) const;
    int Showing2Data(int) const;
    int SelectedDisplay() const;
    bool IsScrolling() const;
    int MinDisplay() const;
    int MaxDisplay() const;
    float Speed() const;
    bool ScrollPastMinDisplay() const;
    bool ScrollPastMaxDisplay() const;
    bool CanScrollBack(bool) const;
    bool CanScrollNext(bool) const;
    float StepPercent() const;
    UIListProvider* Provider();
    UIListProvider* Provider() const;
    int WrapShowing(int) const;
    int NumDisplayWithData() const;
    void SetScrollPastMinDisplay(bool);
    void SetScrollPastMaxDisplay(bool);
    void SetMinDisplay(int);
    void SetMaxDisplay(int);
    int Selected() const;
    int SelectedData() const;
    void SetNumDisplay(int, bool);
    void SetGridSpan(int, bool);
    void SetSelected(int, int, bool);
    void SetCircular(bool, bool);
    void SetSpeed(float);
    void SetSelectedSimulateScroll(int);
    void SetProvider(UIListProvider*, RndDir*);
    void Scroll(int, bool);
    int SnappedDataForDisplay(int) const;
    void Poll(float);
    int SelectedNoWrap() const;
    int MaxFirstShowing() const;
    int CurrentScroll() const;
    void PageScroll(int);
    int ScrollToTarget(int) const;
    int ScrollMaxDisplay() const;
    bool ShouldHoldDisplayInPlace(int) const;

    int NumShowing() const {
    #ifdef MILO_DEBUG
        return mProvider->NumData() - mHiddenData.size();
    #else
        int hiddenCnt = mHiddenData.size();
        return mProvider->NumData() - hiddenCnt;
    #endif
    }
    int NumDisplay() const { return mNumDisplay; }
    int FirstShowing() const { return mFirstShowing; }
    int GridSpan() const { return mGridSpan; }

    /** "Does the list scrolling wrap?" */
    bool mCircular; // 0x0
    int mNumDisplay; // 0x4
    int mGridSpan; // 0x8
    float mSpeed; // 0xc
    /** "How far from top of list to start scrolling". Range from 0 to 50 */
    int mMinDisplay; // 0x10
    bool mScrollPastMinDisplay; // 0x14
    /** "How far down can the highlight travel before scoll? Use -1 for no limit". Range from -1 to 50 */
    int mMaxDisplay; // 0x18
    /** "Allow selected data to move beyond max highlight?" */
    bool mScrollPastMaxDisplay; // 0x1c
    UIListProvider* mProvider; // 0x20
    std::vector<int> mHiddenData; // 0x24
    int mFirstShowing; // 0x2c
    int mTargetShowing; // 0x30
    int mSelectedDisplay; // 0x34
    float mStepPercent; // 0x38
    float mStepTime; // 0x3c
    UIListStateCallback* mCallback; // 0x40
};

class UIListStateCallback {
public:
    UIListStateCallback() {}
    virtual ~UIListStateCallback() {}
    virtual void StartScroll(const UIListState&, int, bool) = 0;
    virtual void CompleteScroll(const UIListState&) = 0;
};
